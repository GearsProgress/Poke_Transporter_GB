#define NANOPRINTF_IMPLEMENTATION 1

#include "libstd_replacements.h"
#include "libraries/nanoprintf/nanoprintf.h"
#include <cstdlib>
#include <stdarg.h>
#include <ctype.h>

// recommended for a 32 bit system to have at least 33 bytes available
// source: https://cplusplus.com/reference/cstdlib/itoa/
// unfortunately itoa is not standardized, so we'll have to make do with snprintf
static char conversion_buffer[33];

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
}

const char* ptgb::to_string(int intVal)
{
    npf_snprintf(conversion_buffer, sizeof(conversion_buffer), "%d", intVal);
    return conversion_buffer;
}

const char* ptgb::to_string(unsigned int wordVal)
{
    npf_snprintf(conversion_buffer, sizeof(conversion_buffer), "%u", wordVal);
    return conversion_buffer;
}

// when compiling with -nostdlib++, we need to provide our own operator new and delete implementations
// Regular operator new
void* operator new(std::size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) {
        // mimic standard behavior: throw std::bad_alloc
        // but we can't use std::bad_alloc without libstdc++
        // so instead we can abort or return nullptr
        // You can also implement a custom exception if needed
        std::abort();
    }
    return ptr;
}

// nothrow version
void* operator new(std::size_t size, const std::nothrow_t&) noexcept {
    return std::malloc(size);
}

// operator delete
void operator delete(void* ptr) noexcept {
    std::free(ptr);
}

// nothrow delete
void operator delete(void* ptr, const std::nothrow_t&) noexcept {
    std::free(ptr);
}

// sized delete (optional, for C++14 and newer)
void operator delete(void* ptr, std::size_t size) noexcept {
    (void)size;
    std::free(ptr);
}