#include <cstdarg>
#include <ctype.h>
#include <cstdlib>
#include <errno.h>

#include <sys/iosupport.h>

#define MAX_HANDLES 3

static __handle __stdin_handle  = {0, 1, NULL};
static __handle __stdout_handle = {1, 1, NULL};
static __handle __stderr_handle = {2, 1, NULL};

static __handle* handles[MAX_HANDLES] = {
	&__stdin_handle,
	&__stdout_handle,
	&__stderr_handle
};

extern "C"
{
// HACK:
// Unfortunately, libtonc references siscanf, which in turn causes a "lot" of binary bloat from newlibc (in regards to locale support)
// to be pulled in by the linker.
// However, if you look at what it is actually used for (in libtonc's tte_iohook.c), is just to extract 1 or 2 integers from a string
// by specifying a custom -extremely simplified- version, we can avoid pulling in the version from libc (alongside all the symbols IT references)
// Obviously it doesn't support everything it should. Just enough to support libtonc's current iteration.
//
// Anyway, doing this optimizes away a lot of scanf related functions from newlib and locale support among which a 13KB "categories" symbol.
int siscanf(const char *str, const char *format, ...)
{
    bool expectingFormatSpecifier = false;
    va_list args;
    int* resultVal;
    int ret = 0;
    va_start(args, format);

    while(*format != '\0')
    {
        if(*str == '\0')
        {
            //EOF encountered.
            return -1;
        }

        if(expectingFormatSpecifier)
        {
            if(*format == 'd')
            {
                resultVal = va_arg(args, int*);
                (*resultVal) = 0;
                while(isdigit(*str))
                {
                    (*resultVal) *= 10;
                    (*resultVal) += (*str) - '0';
                    ++str;
                }
                // go back to the last character of the int, because we'll forward by one again at the end of the outer loop
                --str;
                ++ret;
            }
            expectingFormatSpecifier = false;
        }
        else if((*format) == '%')
        {
            expectingFormatSpecifier = true;
        }

        ++format;
        ++str;
    }

    va_end(args);
    return ret;
}

// HACK: stub the libsysbase_libsysbase_a-handle_manager.o functions
// this, alongside the -Wl,--wrap linker options ensures that this object file
// and its 4KB IWRAM "handles" buffer is not getting pulled in by the linker.
// We don't need it and we could use the 4KB of extra IWRAM!
__handle *__wrap___get_handle(int fd)
{
	if ( fd < 0 || fd >= MAX_HANDLES ) return NULL;

	return handles[fd];
}

int __wrap__close_r(struct _reent *ptr, int fd)
{
	return 0;
}
}