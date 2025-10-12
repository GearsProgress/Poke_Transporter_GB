#include "Pokemon.h"

Pokemon::Pokemon()
{
    isValid = false;
}

u32 Pokemon::getSpeciesIndexNumber()
{
    return 0;
}

u32 Pokemon::getVar(DataVarInfo dataVar)
{
    return getVar(dataVar, 0);
}

u32 Pokemon::getVar(DataVarInfo dataVar, int extraByteOffset)
{
    u32 out = 0;
    if (dataVar.dataLength < 8)
    { // is less than a byte, do bitwise stuff on a single byte
        // ... but we can't assume that the data is within a single byte (thanks gen 3)
        if (dataVar.dataLength + dataVar.bitOffset > 8)
        {
            int numBytes = (dataVar.dataLength + dataVar.bitOffset) / 8 + 1;
            if (numBytes > 4)
            {
                numBytes = 4; // This avoids importing math for rounding. Silly though.
            }
            int arrayIndex;
            for (int i = 0; i < numBytes; i++)
            {
                arrayIndex = (isBigEndian ? i : numBytes - (i + 1));
                out = (out << 8) | dataArrayPtr[dataVar.byteOffset + extraByteOffset + arrayIndex];
            }
            out = (out >> dataVar.bitOffset) & sizeToMask(dataVar.dataLength);
        }
        else
        {
            out = (dataArrayPtr[dataVar.byteOffset + extraByteOffset] >> dataVar.bitOffset) & sizeToMask(dataVar.dataLength);
        }
    }
    else
    { // is larger than a byte, will have to access multiple parts of the array
        int numBytes = dataVar.dataLength / 8;
        int arrayIndex;
        for (int i = 0; i < numBytes; i++)
        {
            arrayIndex = (isBigEndian ? i : numBytes - (i + 1));
            out = (out << 8) | dataArrayPtr[dataVar.byteOffset + extraByteOffset + arrayIndex];
        }
    }
    return out;
}

bool Pokemon::setVar(DataVarInfo dataVar, u32 newValue)
{
    return setVar(dataVar, 0, newValue);
}

bool Pokemon::setVar(DataVarInfo dataVar, int extraByteOffset, u32 newValue)
{
    if (dataVar.dataLength < 8)
    { // is less than a byte, do bitwise stuff on a single byte
      // ... but we can't assume that the data is within a single byte (thanks gen 3)
        if (dataVar.dataLength + dataVar.bitOffset > 8)
        {
            int numBytes = (dataVar.dataLength + dataVar.bitOffset) / 8 + 1;
            if (numBytes > 4)
            {
                numBytes = 4; // This avoids importing math for rounding. Silly though.
            }
            int arrayIndex;
            for (int i = 0; i < numBytes; i++)
            {
                arrayIndex = (isBigEndian ? i : numBytes - (i + 1));
                dataArrayPtr[dataVar.byteOffset + arrayIndex + extraByteOffset] &= ~((sizeToMask(dataVar.dataLength) << dataVar.bitOffset) >> (arrayIndex * 8));
                dataArrayPtr[dataVar.byteOffset + arrayIndex + extraByteOffset] |= ((newValue & sizeToMask(dataVar.dataLength)) << dataVar.bitOffset) >> (arrayIndex * 8);
            }
        }
        else
        {
            dataArrayPtr[dataVar.byteOffset + extraByteOffset] &= ~(sizeToMask(dataVar.dataLength) << dataVar.bitOffset);
            dataArrayPtr[dataVar.byteOffset + extraByteOffset] |= (newValue & sizeToMask(dataVar.dataLength)) << dataVar.bitOffset;
        }
    }
    else
    { // is larger than a byte, will have to access multiple parts of the array
        int numBytes = dataVar.dataLength / 8;
        int arrayIndex;
        for (int i = 0; i < numBytes; i++)
        {
            arrayIndex = (isBigEndian ? i : numBytes - (i + 1));
            dataArrayPtr[dataVar.byteOffset + arrayIndex + extraByteOffset] = (newValue >> (8 * ((numBytes - 1) - i)));
        }
    }
    return true;
}