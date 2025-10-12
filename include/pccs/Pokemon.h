#ifndef POKEMON_H
#define POKEMON_H

#include "pokemon_data.h"

#if ON_GBA
#else
#include <iostream>
#include <sstream>
#include <iomanip>
#endif

#if !USE_EXTERNALDATA
// #include "pokemonData.h"
#endif

#if USE_CPP_RAND
#else
#include "random.h"
#endif

// Avoid having to import math
inline u32 sizeToMask(int len)
{
    u32 out = 1;
    for (int i = 0; i < len; i++)
    {
        out *= 2;
    }
    return (out - 1);
}

inline u32 getPureRand() // Gets a random number from the device itself
{
#if USE_CPP_RAND
    srand(time(0));
    return rand() << 16 | rand();
#else
    return get_rand_u32();
#endif
}

// FNV-1a 32-bit hash function for byte arrays
inline u32 fnv1a_hash(unsigned char *data, size_t length)
{
    const uint32_t fnv_prime = 0x01000193;
    const uint32_t fnv_offset_basis = 0x811C9DC5;
    uint32_t hash = fnv_offset_basis;

    for (size_t i = 0; i < length; ++i)
    {
        hash ^= data[i];
        hash *= fnv_prime;
    }
    return hash;
}

class Pokemon // The base Pokemon class
{
public:
    Pokemon();
    virtual ~Pokemon() {};
    virtual u32 getSpeciesIndexNumber();

#if ON_GBA
#else
    virtual void print(std::ostream &os)
    {
        os << "This is a base Pokemon, it has no info!";
    };

    friend std::ostream &operator<<(std::ostream &os, Pokemon &p)
    {
        p.print(os);
        return os;
    }
#endif

    int dataArraySize;
    int nicknameArraySize;
    int OTArraySize;

    //  Will be set by child classes
    byte *dataArrayPtr;
    byte *nicknameArrayPtr;
    byte *OTArrayPtr;
    byte *externalIndexNumberPtr;

    // This is extra information that's nice to hold on to
    int generation = 0;
    bool isValid;

protected:
    PokemonTables *pokeTable;

    bool isBigEndian;

    u32 getVar(DataVarInfo dataVar);
    u32 getVar(DataVarInfo dataVar, int extraByteOffset);

    bool setVar(DataVarInfo dataVar, u32 newValue);
    bool setVar(DataVarInfo dataVar, int extraByteOffset, u32 newValue);
};

#endif
