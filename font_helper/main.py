import os 
import math
from PIL import Image
import numpy as np

# THIS PROGRAM ASSUMES THAT THE FIRST TWO COLORS IN THE PALETTE ARE THE BACKGROUND AND CELL BACKGROUND!

dir = os.curdir
BACKGROUND_PAL_INDEX = 0
CELL_PAL_INDEX = 1

class Font:
    def __init__(self, fileName, numColors, numChars, numCharsX, numCharsY, cellWidth, cellHeight):
        self.fileName = fileName
        self.numColors = numColors
        self.numChars = numChars
        self.numCharsX = numCharsX
        self.numCharsY = numCharsY
        self.cellWidth = cellWidth
        self.cellHeight = cellHeight

        self.bpp = int(math.log(numColors, 2)) + 1
        self.numWords = self.numChars * self.cellWidth * self.cellHeight * self.bpp // (8 * 4)
        self.numBytes = self.numWords * 4

        self.charWordTable = [0] * self.numWords
        self.charWidthTable = [0] * self.numBytes


def build_h(myFont):
    with open(dir + "/include/" + myFont.fileName + ".h", 'w') as f:
        f.write(f'''
#ifndef __{myFont.fileName.upper()}__
#define __{myFont.fileName.upper()}__

extern const TFont {myFont.fileName}Font;

#define {myFont.fileName}GlyphsLen {myFont.numBytes}
extern const unsigned int {myFont.fileName}Glyphs[{myFont.numBytes}];

#define {myFont.fileName}WidthsLen {myFont.numChars}
extern const unsigned char {myFont.fileName}Widths[{myFont.numChars}];

#endif
''')
        f.close()

def build_c(myFont):
    with open(dir + "/source/" + myFont.fileName + ".c", 'w') as f:
        f.write(f'''typedef struct TFont
{{
	const void	*data;				//!< Character data.
	const unsigned char	*widths;	//!< Width table for vwf.
	const unsigned char	*heights;	//!< Height table for vhf.
	unsigned short	charOffset;		//!< Character offset.
	unsigned short	charnumChars;		//!< Character numChars.
	unsigned char	charW;			//!< Character width (fwf).
	unsigned char	charH;			//!< Character height.
	unsigned char	cellW;			//!< Glyph cell width.
	unsigned char	cellH;			//!< Glyph cell height.
	unsigned short	cellSize;		//!< Cell-size (bytes).
	unsigned char	bpp;				//!< Font bitdepth;
	unsigned char	extra;			//!< Padding. Free to use.
}} TFont;\n
''')
        
        f.write(f'const unsigned int {myFont.fileName}Glyphs[{myFont.numWords}] __attribute__((aligned(4)))=\n{{\n\t')

        for i in range(myFont.numWords):
            f.write(f'{myFont.charWordTable[i]:#010x},')
            if (i == myFont.numWords - 1):
                f.write("\n};\n\n")
            elif (i % 64 == 63):
                f.write("\n\n\t")
            elif (i % 8 == 7):
                f.write("\n\t")

        f.write(f'const unsigned char {myFont.fileName}Widths[{myFont.numChars}] __attribute__((aligned(4)))=\n{{\n\t')

        for i in range(myFont.numChars):
            f.write(f'{myFont.charWidthTable[i]:#04x}, ')
            if (i == myFont.numChars - 1):
                f.write("\n};\n\n")
            elif (i % 128 == 127):
                f.write("\n\n\t")
            elif (i % 16 == 15):
                f.write("\n\t")

        f.write(f'''const TFont {myFont.fileName}Font= 
{{
	{myFont.fileName}Glyphs, 
    {myFont.fileName}Widths, 
    0, // All heights are the same 
	0, // Character offset, is set to zero
    {myFont.numChars},
	{myFont.cellWidth}, {myFont.cellHeight},
	{myFont.cellWidth}, {myFont.cellHeight}, 
    {myFont.numBytes // myFont.numChars}, 
	{myFont.bpp}, 
    0, // Padding, left blank
}};
                ''')

        f.close()

def generate_tables(myFont):
    img = Image.open(f'{dir}/graphics/{myFont.fileName}.png')
    if (img.mode != "P"):
        print("Error: Image file does not contain a palette")
        exit()
    pixels = img.load()

    bitsPerWord = 32
    pixelsPerTileX = 8
    pixelsPerTileY = 8
    tilesPerCharX = myFont.cellWidth // pixelsPerTileX
    tilesPerCharY = myFont.cellHeight // pixelsPerTileY
    charsPerChartX = myFont.numCharsX
    charsPerChartY = myFont.numCharsY

    globalX = 0
    globalY = 0
    bitTotal = 0

    for charY in range(charsPerChartY):
        for charX in range(charsPerChartX):
            for tileY in range(tilesPerCharY):
                for tileX in range(tilesPerCharX):
                    for pixelY in range(pixelsPerTileY):
                        for pixelX in range(pixelsPerTileX):
                            
                            arrayIndex = bitTotal // bitsPerWord
                            bitIndex = bitTotal % bitsPerWord

                            globalX = pixelX + (tileX * pixelsPerTileX) + (charX * tilesPerCharX * pixelsPerTileX)
                            globalY = pixelY + (tileY * pixelsPerTileY) + (charY * tilesPerCharY * pixelsPerTileY)

                            val = (pixels[globalX, globalY] - 2) & ((1 << myFont.bpp) - 1)
                            myFont.charWordTable[arrayIndex] |= val << bitIndex

                            #print(f'globalX: {globalX}, globalY: {globalY}, arrayIndex:{arrayIndex}, bitIndex:{bitIndex}, val:{val}')
                            bitTotal += myFont.bpp
            
            #print(f'{charX, charY}')

            myFont.charWidthTable[(charY * charsPerChartX) + charX] = (tilesPerCharX * pixelsPerTileX)
            for x in range(tilesPerCharX * pixelsPerTileX):
                globalX = x + (charX * tilesPerCharX * pixelsPerTileX)
                globalY = 0 + (charY * tilesPerCharY * pixelsPerTileY)
                #print(f'x: {globalX}, y: {globalY}')
                if (pixels[globalX, globalY] == BACKGROUND_PAL_INDEX):
                    myFont.charWidthTable[(charY * charsPerChartX) + charX] = x
                    break

# Main:
latin_normal = Font("latin_normal", 1, 256, 16, 16, 16, 16)
generate_tables(latin_normal)
build_h(latin_normal)
build_c(latin_normal)

