#include "Gen2Pokemon.h"

Gen2Pokemon::Gen2Pokemon(PokemonTables *table)
{
    pokeTable = table;
    dataArrayPtr = dataArray;
    dataArraySize = 32;
    generation = 2;
}

#if ON_GBA
#else
void Gen2Pokemon::print(std::ostream &os)
{
    os << parentPrint()
       << "Stats: "
       << "\n\tHP: " << getStatExp(HP) << " Stat EXP, " << getDV(HP) << " DVs"
       << "\n\tAttack: " << getStatExp(ATTACK) << " Stat EXP, " << getDV(ATTACK) << " DVs"
       << "\n\tDefense: " << getStatExp(DEFENSE) << " Stat EXP, " << getDV(DEFENSE) << " DVs"
       << "\n\tSpeed: " << getStatExp(SPEED) << " Stat EXP, " << getDV(SPEED) << " DVs"
       << "\n\tSpecial Attack: " << getStatExp(SPECIAL) << " Stat EXP, " << getDV(SPECIAL) << " DVs"
       << "\n\tSpecial Defense: " << getStatExp(SPECIAL) << " Stat EXP, " << getDV(SPECIAL) << " DVs" << "\n" // Special Attack and Special Defense are the same
       << "Held Item: " << getHeldItem() << "\n"
       << "Friendship: " << getFriendship() << "\n"
       << "Pokerus: "
       << "\n\tStrain: " << getPokerusStrain()
       << "\n\tDays Remaining: " << getPokerusDaysRemaining() << "\n"
       << "Caught Data: "
       << "\n\tTime: " << getCaughtDataTime()
       << "\n\tLevel: " << getCaughtDataLevel()
       << "\n\tTrainer Gender: " << getCaughtDataGender()
       << "\n\tLocation: " << getCaughtDataLocation() << "\n";
}
#endif

const DataVarInfo
    Gen2Pokemon::g2_heldItem = {0x01, 8, 0},
    Gen2Pokemon::g2_friendship = {0x1B, 8, 0},
    Gen2Pokemon::g2_pokerusStrain = {0x1C, 4, 4},
    Gen2Pokemon::g2_pokerusDaysRemaining = {0x1C, 4, 0},
    Gen2Pokemon::g2_caughtDataTime = {0x1D, 2, 6},
    Gen2Pokemon::g2_caughtDataLevel = {0x1D, 6, 0},
    Gen2Pokemon::g2_caughtDataGender = {0x1E, 1, 7},
    Gen2Pokemon::g2_caughtDataLocation = {0x1E, 7, 0};