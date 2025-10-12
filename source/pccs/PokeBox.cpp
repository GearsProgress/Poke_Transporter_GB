#include "PokeBox.h"
#include <string>

#if ON_GBA
#include "global_frame_controller.h"
#include "text_engine.h"
#endif

PokeBox::PokeBox()
{
    nullMon = new Pokemon();
}

PokeBox::PokeBox(PokemonTables *nTable)
{
    table = nTable;
}

void PokeBox::setTable(PokemonTables *nTable)
{
    table = nTable;
}

bool PokeBox::addPokemon(Pokemon *currPkmn)
{
    if (currIndex < 30)
    {
        boxStorage[currIndex] = currPkmn;
        currIndex++;
        return true;
    }
    return false;
}

Pokemon *PokeBox::getPokemon(int index)
{
    if (index < currIndex)
    {
        return boxStorage[index];
    }
    return nullMon;
}

GBPokemon *PokeBox::getGBPokemon(int index)
{
    Pokemon *currPkmn = getPokemon(index);
    GBPokemon *currGBPkmn = (GBPokemon *)currPkmn;
    return currGBPkmn;
}

Gen3Pokemon *PokeBox::getGen3Pokemon(int index)
{
    Pokemon *currPkmn = getPokemon(index);
    Gen3Pokemon *currGen3Pkmn = (Gen3Pokemon *)currPkmn;
    currGen3Pkmn->updateSecurityData();
    return currGen3Pkmn;
}

bool PokeBox::removePokemon(int index)
{
    if (index < currIndex)
    {
        for (int i = index; i < currIndex; i++)
        {
            boxStorage[i] = boxStorage[i + 1];
        }
        currIndex -= 1;
        return true;
    }
    return false;
}

// This is used to load our data in from an array
void PokeBox::loadData(int generation, Language nLang, byte nDataArray[])
{
    if (nLang != ENGLISH)
    {
        return; // Other languages are not supported yet
    }
    for (int pkmnIndex = 0; pkmnIndex < nDataArray[0]; pkmnIndex++)
    {
        GBPokemon *newPkmn = nullptr;
        if (generation == 1)
        {
            newPkmn = new Gen1Pokemon(table);
        }
        else if (generation == 2)
        {
            newPkmn = new Gen2Pokemon(table);
        }

        int externalIDOffset = 1;
        int dataOffset = externalIDOffset + (20 * 1) + 1;
        int trainerNameOffset = dataOffset + (20 * newPkmn->dataArraySize);
        int nicknameOffset = trainerNameOffset + (20 * newPkmn->OTArraySize);

        externalIDOffset += pkmnIndex * 1;
        dataOffset += pkmnIndex * newPkmn->dataArraySize;
        trainerNameOffset += pkmnIndex * newPkmn->OTArraySize;
        nicknameOffset += pkmnIndex * newPkmn->nicknameArraySize;

        newPkmn->loadData(
            nLang,
            &nDataArray[dataOffset],        // Pokemon Data
            &nDataArray[nicknameOffset],    // Nickname
            &nDataArray[trainerNameOffset], // Trainer Name
            nDataArray[externalIDOffset]    // External ID Number
        );

        addPokemon(newPkmn);
    }
}

void PokeBox::convertPkmn(int index)
{
    Gen3Pokemon *convertedPkmn = new Gen3Pokemon(table);
    Pokemon *basePkmn = getPokemon(index);
    GBPokemon *oldPkmn = (GBPokemon *)(basePkmn);

    oldPkmn->convertToGen3(convertedPkmn, stabilize_mythical);
    delete boxStorage[index];
    boxStorage[index] = convertedPkmn;
}

void PokeBox::convertAll()
{
    for (int i = 0; i < currIndex; i++)
    {
        convertPkmn(i);
    }
}

int PokeBox::getNumInBox()
{
    return currIndex;
}

int PokeBox::getNumValid()
{
    int numValid = 0;
    for (int i = 0; i < currIndex; i++)
    {
        if (getPokemon(i)->isValid)
        {
            numValid++;
        }
    }
    return numValid;
}

#if ON_GBA
#else
std::string PokeBox::printDataArray()
{
    std::stringstream ss;
    for (int i = 0; i < currIndex; i++)
    {
        if (boxStorage[i]->generation == 3)
        {
            ss << ((Gen3Pokemon *)boxStorage[i])->printDataArray(true) << "\n";
        }
    }
    return ss.str();
}
#endif