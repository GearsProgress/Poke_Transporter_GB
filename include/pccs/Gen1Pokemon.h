#ifndef GEN1POKEMON_H
#define GEN1POKEMON_H

#include "GBPokemon.h"

class Gen1Pokemon : public GBPokemon // The class for gen 1 Pokemon
{
public:
    Gen1Pokemon(PokemonTables *table);
    byte dataArray[33];

    u32 getSpeciesIndexNumber();
    u32 getCurrentHP() { return getVar(g1_currentHP); }
    u32 getStatusCondition() { return getVar(g1_statusCondition); }
    u32 getCatchRate() { return getVar(g1_catchRate); }
    u32 getType(int typeIndex) { return getVar(*g1_types[typeIndex]); }

    bool setSpeciesIndexNumber(byte newVal);
    bool setCurrentHP(byte newVal) { return setVar(g1_currentHP, newVal); }
    bool setStatusCondition(byte newVal) { return setVar(g1_statusCondition, newVal); }
    bool setCatchRate(byte newVal) { return setVar(g1_catchRate, newVal); }
    bool setType(int typeIndex, Gen1Types newVal) { return setVar(*g1_types[typeIndex], newVal); }

protected:
    static const DataVarInfo
        // Gen 1 specific data
        g1_currentHP,
        g1_statusCondition,
        g1_typeOne, g1_typeTwo,
        g1_catchRate,
        *g1_types[2];

#if ON_GBA
#else
    void print(std::ostream &os);
#endif
};

#endif