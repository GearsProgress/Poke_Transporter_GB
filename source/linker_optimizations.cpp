#include <cstdarg>
#include <ctype.h>
#include <cstdlib>
#include <errno.h>

#include <sys/iosupport.h>

// Okay, let's go over the basics of this file for a moment.
// By default, a lot of code is getting pulled in by the linker from static libraries such as newlibc and libtonc.
// The problem is that everytime a single symbol/function is needed from one of the .o files inside one of these static libs,
// the entire .o file is getting pulled in, alongside all of ITS dependencies. This cascades pretty quickly.
// So this pulls in a lot of unnecessary code, but also (global) variables.
// To solve that, we can try to override these functions by defining a custom version of them here.
// But to avoid still pulling in the .o file, we have to define every symbol that could be referenced somehow in either our code or the static libraries themselves.
// Worst case, this means we have to redefine every single function that is defined in that .o file.
// But doing so, means we can modify the code slightly to avoid pulling in a lot of bloat. we don't need.

// HACK: Avoid pulling in a large handles buffer, which we don't need. Only define the minimum.

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

// HACK: The functions below were defined here to avoid pulling in the verdana9 font (4 KB) into the rom, which we're not using.
// The original function in libtonc would use verdana9 as a default if the specified font was NULL.
#include <tonc_tte.h>
#include <tonc_video.h>
#include <tonc_bios.h>
#include <string.h>

//! Initialize text system for 4bpp tiled, column-major surfaces.
/*!	
	\param bgnr		Background number.
	\param bgcnt	Background control flags.
	\param se0		Base offset for screen-entries.
	\param cattrs	Color attributes; one byte per attr.
	\param clrs		ink(/shadow) colors.
	\param font		Font to initialize with.
	\param proc		Glyph renderer
*/
void tte_init_chr4c(int bgnr, u16 bgcnt, u16 se0, u32 cattrs, u32 clrs, 
	const TFont *font, fnDrawg proc)
{
	if(proc==NULL)	proc= chr4c_drawg_default;

	tte_init_base(font, proc, chr4c_erase);

	TTC *tc= tte_get_context();
	TSurface *srf= &tc->dst;

	srf_init(srf, SRF_CHR4C, 
		&tile_mem[BFN_GET(bgcnt, BG_CBB)][se0 & SE_ID_MASK], 
		SCREEN_WIDTH, SCREEN_HEIGHT, 4, pal_bg_mem);
	schr4c_prep_map(srf, se_mem[BFN_GET(bgcnt, BG_SBB)], se0);

	tc->flags0= bgnr;
	tc->ctrl= bgcnt;
	REG_BGCNT[bgnr]= bgcnt;

	// --- Init color attributes ---
	u32 ink, shadow, paper; //spec;
	ink=	 cattrs     & 15;
	shadow=	(cattrs>> 8)& 15;
	paper=	(cattrs>>16)& 15;
	//spec=   (cattrs>>24)&255;

	tc->cattr[TTE_INK]= ink;
	tc->cattr[TTE_SHADOW]= shadow;
	tc->cattr[TTE_PAPER]= paper;
	//tc->cattr[TTE_SPECIAL]= 0;

	srf->palData= pal_bg_bank[se0>>12];
	srf->palData[ink]= clrs&0xFFFF;
	srf->palData[shadow]= clrs>>16;
}

void chr4c_erase(int left, int top, int right, int bottom)
{	
	TTC *tc= tte_get_context();

	//# Check for single sequence
	schr4c_rect(&tc->dst, left, top, right, bottom, tc->cattr[TTE_PAPER]);
}

// HACK: We need to replace the entirety of tte_main.c in libtonc to avoid pulling in sys8font (because it's used as a default in tte_init_base() if the specified font is NULL)
// So here's a modified version of tte_main.c (only tte_init_base() is really changed though):
//////////////////////// tte_main.c ////////////////////////

// --------------------------------------------------------------------
// CONSTANTS
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// GLOBALS
// --------------------------------------------------------------------

TTC	__tte_main_context;
TTC	*gp_tte_context= &__tte_main_context;


// --------------------------------------------------------------------
// INLINES
// --------------------------------------------------------------------

INLINE char *eatwhite(const char *str)
{
	while(isspace(*str))
		str++;

	return (char*)str;
}

// --------------------------------------------------------------------
// OPERATIONS
// --------------------------------------------------------------------

//! Set the master context pointer.
void tte_set_context(TTC *tc)
{	
	gp_tte_context= tc ? tc : &__tte_main_context;
}


//! Set color attribute of \a type to \a cattr.
void tte_set_color_attr(eint type, u16 cattr)
{
	TTC *tc= tte_get_context();
	tc->cattr[type]= cattr;
}

//! Load important color attribute data.
void tte_set_color_attrs(const u16 cattrs[])
{
	int ii;
	TTC *tc= tte_get_context();

	for(ii=0; ii<4; ii++)
		tc->cattr[ii]= cattrs[ii];
}

//! Set color attribute of \a type to \a cattr.
void tte_set_color(eint type, u16 color)
{
	TTC *tc= tte_get_context();
	
	if(tc->dst.palData != NULL)
		tc->dst.palData[tc->cattr[type]]= color;
	else
		tc->cattr[type]= color;
}

//! Load important color data.
void tte_set_colors(const u16 colors[])
{
	int ii;
	TTC *tc= tte_get_context();

	if(tc->dst.palData != NULL)
		for(ii=0; ii<4; ii++)
			tc->dst.palData[tc->cattr[ii]]= colors[ii];
	else
		for(ii=0; ii<4; ii++)
			tc->cattr[ii]= colors[ii];
}


//! Base initializer of a TTC.
void tte_init_base(const TFont *font, fnDrawg drawProc, fnErase eraseProc)
{
	if(tte_get_context() == NULL)
		tte_set_context(&__tte_main_context);
	
	TTC *tc= tte_get_context();
	memset(tc, 0, sizeof(TTC));
		
	tc->font= (TFont*)font;
	tc->drawgProc= drawProc;
	tc->eraseProc= eraseProc;

	// Default is SBB 0
	const TSurface srf= { (u8*)se_mem, 32*2, 32, 32, 8, SRF_BMP16, 256, pal_bg_mem };
	tc->dst = srf;

	tc->cattr[TTE_INK]    = 0xF1;
	tc->cattr[TTE_SHADOW] = 0xF2;
	tc->cattr[TTE_PAPER]  = 0;
	tc->cattr[TTE_SPECIAL]= 0;
	
	tc->marginRight= SCREEN_WIDTH;
	tc->marginBottom= SCREEN_HEIGHT;	
}


// --------------------------------------------------------------------
// String interpretations
// --------------------------------------------------------------------

//! Retrieve a single multibyte utf8 character.
uint utf8_decode_char(const char *ptr, char **endptr)
{
	uchar *src= (uchar*)ptr;
	uint ch8, ch32;

	// Poor man's try-catch.
	do
	{
		// UTF8 formats:
		// 0aaaaaaa                            ->                   0aaaaaaa
		// 110aaaaa 10bbbbbb                   ->          00000aaa aabbbbbb 
		// 1110aaaa 10bbbbbb 10cccccc          ->          aaaabbbb bbcccccc
		// 11110aaa 10bbbbbb 10cccccc 10dddddd -> 000aaabb bbbbcccc ccdddddd
		// 
		// Any invalid format will be returned as a single byte.

		ch8= *src;
		if(ch8 < 0x80)						// 7b
		{
			ch32= ch8;
		}
		else if(0xC0<=ch8 && ch8<0xE0)		// 11b
		{
			ch32  = (*src++&0x1F)<< 6;	if((*src>>6)!=2)	break;
			ch32 |= (*src++&0x3F)<< 0;
		}
		else if(0xE0<=ch8 && ch8<0xF0)		// 16b
		{
			ch32  = (*src++&0x0F)<<12;	if((*src>>6)!=2)	break;
			ch32 |= (*src++&0x3F)<< 6;	if((*src>>6)!=2)	break;
			ch32 |= (*src++&0x3F)<< 0;
		}
		else if(0xF0<=ch8 && ch8<0xF8)		// 21b
		{
			ch32  = (*src++&0x0F)<<18;	if((*src>>6)!=2)	break;
			ch32 |= (*src++&0x3F)<<12;	if((*src>>6)!=2)	break;
			ch32 |= (*src++&0x3F)<< 6;	if((*src>>6)!=2)	break;
			ch32 |= (*src++&0x3F)<< 0;
		}
		else
			break;

		// Proper UTF8 char: set endptr and return
		if(endptr)
			*endptr= (char*)src;

		return ch32;

	} while(0);


	// Not really UTF: interpret as single byte.
	src= (uchar*)ptr;
	ch32= *src++;
	if(endptr)
		*endptr= (char*)src;

	return ch32;
}

//! Find the string-position after the command.
/*!
	\param str	String to check.
	\return		The string-pointer after the current/next command.
		If there is no command-end, this moves to the end of the 
		string.
*/
char *tte_cmd_skip(const char *str)
{
	int ch;

	while( (ch= *str) != '\0')
	{
		str++;
		if(ch == '}')
			break;
	}

	return (char*)str;
}

//! Move to the next command in a sequence.
/*!
	\return	Position of EOS (\'0'), EOC ('}') or next cmd token (rest)
*/
char *tte_cmd_next(const char *str)
{
	int ch;

	// Find EOC, separator or NULL
	while(1)
	{
		ch= *str;
		if(ch == '\0' || ch == '}')		// EOS/EOC
			return (char*)str;
		else if(ch == ';')				// More commands
			break;

		str++;
	}

	// More commands: try to find next token (or EOS/EOC again)
	while(1)
	{
		ch= *++str;
		if(ch == '\0' || !isspace(ch))
			return (char*)str;
	}
}

//! Erase a porttion of the screen (ignores margins)
void tte_erase_rect(int left, int top, int right, int bottom)
{
	TTC *tc= tte_get_context();

	if(tc->eraseProc)
		tc->eraseProc(left, top, right, bottom);
}

//! Erase the screen (within the margins).
/*!
	\note Ponder: set paper color?
*/
void tte_erase_screen()
{
	TTC *tc= tte_get_context();

	if(tc->eraseProc)
		tc->eraseProc(tc->marginLeft, tc->marginTop, 
			tc->marginRight, tc->marginBottom);
}


//! Erase the whole line (within the margins).
/*!
	\note Ponder: set paper color?
*/
void tte_erase_line()
{
	TTC *tc= tte_get_context();
	int height= tc->font->charH;

	if(tc->eraseProc)
		tc->eraseProc(tc->marginLeft, tc->cursorY, 
			tc->marginRight, tc->cursorY+height);
}


//! Get the size taken up by a string.
/*!
	\param str	String to check.
	\return	width and height, packed into a POINT16.
	\note	This function \e ignores tte commands, so don't use
		on strings that use commands.
*/
POINT16 tte_get_text_size(const char *str)
{
	TTC *tc= tte_get_context();

	int charW, charH= tc->font->charH;

	s16 x=0, width= 12, height= charH;
	int ch;

	while( (ch= *str++) != 0 )
	{
		switch(ch)
		{
		// --- Newline/carriage return ---
		case '\r':
			if(str[0] == '\n')	// deal with CRLF pair
				str++;
			// FALLTHRU
		case '\n':
			height += charH;
			if(x > width)
				width= x;
			x= 0;
			break;			

		// --- Special char ---
		case '\\':
			//# Use cmd-functino
			//# Take care of positioning commands.
			if(str[0] == '{')
				str= tte_cmd_skip(str);
			break;

		// --- Normal char ---
		default:
			charW= tc->font->cellW;
			if(x+charW > tc->marginRight)
			{
				height += charH;		
				if(x>width)
					width= x;
				x=0;			
			}
			else
				x += tte_get_glyph_width(tte_get_glyph_id(ch));	
		}
	}

	// One more to make sure we got it >_<
	if(x>width)
		width= x;

	POINT16 pt= { width, height };
	return pt;
}

void tte_set_margins(int left, int top, int right, int bottom)
{
	TTC *tc= tte_get_context();

	tc->marginLeft  = left;
	tc->marginTop   = top;
	tc->marginRight = right;
	tc->marginBottom= bottom;
}


// EOF
////////////////////// end tte_main.c //////////////////////

}