#include "utils.h"

static bool isCurrentCPULittleEndian();

const bool g_isLittleEndian = isCurrentCPULittleEndian();

// the attribute stuff is to make sure the compiler doesn't optimize this code away.
__attribute__((optimize("O0")))
static bool isCurrentCPULittleEndian()
{
	short int word = 0x0001;
   char *byte = (char *) &word;
   return (byte[0] ? true : false);
}