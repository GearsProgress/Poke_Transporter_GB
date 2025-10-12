#ifndef GEN2POKEMON_H
#define GEN2POKEMON_H

#include "GBPokemon.h"

class Gen2Pokemon : public GBPokemon // The class for gen 2 Pokemon
{
public:
    Gen2Pokemon(PokemonTables *table);
    byte dataArray[32];

    u32 getHeldItem() { return getVar(g2_heldItem); }
    u32 getFriendship() { return getVar(g2_friendship); }
    u32 getPokerusStrain() { return getVar(g2_pokerusStrain); }
    u32 getPokerusDaysRemaining() { return getVar(g2_pokerusDaysRemaining); }
    u32 getCaughtDataTime() { return getVar(g2_caughtDataTime); }
    u32 getCaughtDataLevel() { return getVar(g2_caughtDataLevel); }
    u32 getCaughtDataGender() { return getVar(g2_caughtDataGender); }
    u32 getCaughtDataLocation() { return getVar(g2_caughtDataLocation); }

    bool setHeldItem(byte newVal) { return setVar(g2_heldItem, newVal); }
    bool setFriendship(byte newVal) { return setVar(g2_friendship, newVal); }
    bool setPokerusStrain(byte newVal) { return setVar(g2_pokerusStrain, newVal); }
    bool setPokerusDaysRemaining(byte newVal) { return setVar(g2_pokerusDaysRemaining, newVal); }
    bool setCaughtDataTime(byte newVal) { return setVar(g2_caughtDataTime, newVal); }
    bool setCaughtDataLevel(byte newVal) { return setVar(g2_caughtDataLevel, newVal); }
    bool setCaughtDataGender(byte newVal) { return setVar(g2_caughtDataGender, newVal); }
    bool setCaughtDataLocation(byte newVal) { return setVar(g2_caughtDataLocation, newVal); }

protected:
    static const DataVarInfo
        g2_heldItem,
        g2_friendship,
        g2_pokerusStrain,
        g2_pokerusDaysRemaining,
        g2_caughtDataTime,
        g2_caughtDataLevel,
        g2_caughtDataGender,
        g2_caughtDataLocation;

#if ON_GBA
#else
    void print(std::ostream &os);
#endif
};

#endif