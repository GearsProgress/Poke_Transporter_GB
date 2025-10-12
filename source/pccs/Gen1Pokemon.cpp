#include "Gen1Pokemon.h"

Gen1Pokemon::Gen1Pokemon(PokemonTables *table)
{
    pokeTable = table;
    dataArrayPtr = dataArray;
    dataArraySize = 33;
    generation = 1;
}

#if ON_GBA
#else
void Gen1Pokemon::print(std::ostream &os)
{
    os << parentPrint()
       << "Stats: "
       << "\n\tHP: " << getStatExp(HP) << " Stat EXP, " << getDV(HP) << " DVs"
       << "\n\tAttack: " << getStatExp(ATTACK) << " Stat EXP, " << getDV(ATTACK) << " DVs"
       << "\n\tDefense: " << getStatExp(DEFENSE) << " Stat EXP, " << getDV(DEFENSE) << " DVs"
       << "\n\tSpeed: " << getStatExp(SPEED) << " Stat EXP, " << getDV(SPEED) << " DVs"
       << "\n\tSpecial: " << getStatExp(SPECIAL) << " Stat EXP, " << getDV(SPECIAL) << " DVs" << "\n"
       << "Types: "
       << "\n\t" << getType(0)
       << "\n\t" << getType(1) << "\n"
       << "Current HP: " << getCurrentHP() << "\n"
       << "Status Condition: " << getStatusCondition() << "\n"
       << "Catch Rate: " << getCatchRate() << "\n";
}
#endif

u32 Gen1Pokemon::getSpeciesIndexNumber()
{
    return gen_1_index_array[getVar(speciesIndexNumber[1])];
}

bool Gen1Pokemon::setSpeciesIndexNumber(byte newVal)
{
    for (int i = 0; i < 191; i++)
    {
        if (gen_1_index_array[i] == newVal)
        {
            return setVar(speciesIndexNumber[1], newVal);
        }
    }
    return setVar(speciesIndexNumber[1], newVal);
}

const DataVarInfo
    Gen1Pokemon::g1_currentHP = {0x01, 16, 0},
    Gen1Pokemon::g1_statusCondition = {0x04, 8, 0},
    Gen1Pokemon::g1_typeOne = {0x05, 8, 0},
    Gen1Pokemon::g1_typeTwo = {0x06, 8, 0},
    Gen1Pokemon::g1_catchRate = {0x07, 8, 0};

const DataVarInfo
    *Gen1Pokemon::g1_types[2] =
        {
            &Gen1Pokemon::g1_typeOne,
            &Gen1Pokemon::g1_typeTwo,
};