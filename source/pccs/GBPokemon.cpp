#include "GBPokemon.h"

// This constructor fills all our convenience arrays
GBPokemon::GBPokemon()
{
    nicknameArrayPtr = nicknameArray;
    nicknameArraySize = 11;
    OTArrayPtr = OTArray;
    OTArraySize = 11;
    externalIndexNumberPtr = &externalIndexNumber;
    isBigEndian = true;
    generation = 0;
}

// This is used to load our data in from an array
void GBPokemon::loadData(Language nLang, byte nDataArray[], byte nNicknameArray[], byte nOTArray[], byte nExternalIndexNum)
{
    for (int i = 0; i < dataArraySize; i++)
    {
        dataArrayPtr[i] = nDataArray[i];
    }

    for (int i = 0; i < nicknameArraySize; i++)
    {
        nicknameArray[i] = nNicknameArray[i];
    }

    for (int i = 0; i < OTArraySize; i++)
    {
        OTArray[i] = nOTArray[i];
    }

    if (generation == 1)
    {
        externalIndexNumber = gen_1_index_array[nExternalIndexNum];
    }
    else
    {
        externalIndexNumber = nExternalIndexNum;
    }

    lang = nLang;
    updateValidity();
}

// This is used to easily print out a Pokemon, when using a standard C++ terminal
#if ON_GBA
#else
std::string GBPokemon::parentPrint()
{
    pokeTable->load_input_charset(generation, ENGLISH);
    std::stringstream os;
    os << "Species Index Number: " << getSpeciesIndexNumber() << "\n"
       << "Nickname: [";

    for (int i = 0; i < 10; i++)
    {
        os << "0x" << std::setfill('0') << std::setw(2) << std::right << std::hex << (int)nicknameArray[i] << (i < 9 ? ", " : "");
    }

    os << "] (";

    for (int i = 0; i < 10; i++)
    {
        os << (char)(pokeTable->input_charset[(int)nicknameArray[i]]);
    }

    os << ")" << "\n"
       << "Original Trainer: [";

    for (int i = 0; i < 7; i++)
    {
        os << "0x" << std::setfill('0') << std::setw(2) << std::right << std::hex << (int)OTArray[i] << (i < 6 ? ", " : "");
    }

    os << "] (";

    for (int i = 0; i < 7; i++)
    {
        os << (char)(pokeTable->input_charset[(int)OTArray[i]]);
    }

    os << ")" << "\n"
       << std::dec
       << "Trainer ID: " << getTrainerID() << "\n"
       << "Level: " << getLevel() << "\n"
       << "Exp: " << getExpPoints() << "\n"
       << "Moves: "
       << "\n\t" << getMove(0) << " (" << getPPTotal(0) << " PP, " << getPPUpNum(0) << " PP Ups" << ")"
       << "\n\t" << getMove(1) << " (" << getPPTotal(1) << " PP, " << getPPUpNum(1) << " PP Ups" << ")"
       << "\n\t" << getMove(2) << " (" << getPPTotal(2) << " PP, " << getPPUpNum(2) << " PP Ups" << ")"
       << "\n\t" << getMove(3) << " (" << getPPTotal(3) << " PP, " << getPPUpNum(3) << " PP Ups" << ")" << "\n"
       << "Is Shiny: " << getIsShiny() << "\n";
    return os.str();
}
#endif

u32 GBPokemon::getDV(Stat currStat)
{
    if (currStat == HP)
    {

        return ((getVar(DVs[ATTACK][generation - 1]) & 0x1) << 3) |
               ((getVar(DVs[DEFENSE][generation - 1]) & 0x1) << 2) |
               ((getVar(DVs[SPEED][generation - 1]) & 0x1) << 1) |
               ((getVar(DVs[SPECIAL][generation - 1]) & 0x1) << 0);
    }
    else
    {
        return getVar(DVs[currStat][generation - 1]);
    }
}

bool GBPokemon::setDV(Stat currStat, byte newVal)
{
    if (currStat == HP)
    {
        return setVar(DVs[ATTACK][generation - 1], (getVar(DVs[ATTACK][generation - 1]) & 0b1110) | ((newVal >> 3) & 0x1)) &&
               setVar(DVs[DEFENSE][generation - 1], (getVar(DVs[DEFENSE][generation - 1]) & 0b1110) | ((newVal >> 2) & 0x1)) &&
               setVar(DVs[SPEED][generation - 1], (getVar(DVs[SPEED][generation - 1]) & 0b1110) | ((newVal >> 1) & 0x1)) &&
               setVar(DVs[SPECIAL][generation - 1], (getVar(DVs[SPECIAL][generation - 1]) & 0b1110) | ((newVal >> 0) & 0x1));
    }
    else
    {
        return setVar(DVs[currStat][generation - 1], newVal);
    }
}

byte GBPokemon::getUnownLetter()
{
    if (getSpeciesIndexNumber() == 201)
    {
        byte letter = 0;
        letter |= ((getDV(ATTACK) & 0b0110) >> 1) << 6;
        letter |= ((getDV(DEFENSE) & 0b0110) >> 1) << 4;
        letter |= ((getDV(SPEED) & 0b0110) >> 1) << 2;
        letter |= ((getDV(SPECIAL) & 0b0110) >> 1) << 0;
        letter = letter / 10;
        return letter;
    }
    return 255;
}

Gender GBPokemon::getGender()
{
    byte index = getSpeciesIndexNumber();
    u32 threshold = pokeTable->get_gender_threshold(index, false);

    if (threshold == 255)
    {
        return GENDERLESS;
    }
    else
    {
        if (getDV(ATTACK) <= threshold)
        {
            return FEMALE;
        }
        return MALE;
    }
}

Nature GBPokemon::getVirtualConsoleNature()
{
    return (Nature)(getExpPoints() % 25);
}

bool GBPokemon::getIsShiny()
{
    return ((getDV(ATTACK) & 0b0010) == 0b0010) &&
           getDV(DEFENSE) == 10 &&
           getDV(SPEED) == 10 &&
           getDV(SPECIAL) == 10;
}

bool GBPokemon::convertToGen3(Gen3Pokemon *newPkmn, bool sanitizeMythicals)
{
    if (!isValid)
    {
        return false;
    }

    bool valid =
        // Start with things that effect the PID
        convertSpeciesIndexNumber(newPkmn) &&
        setRequestedLetter(newPkmn) &&
        setRequestedNature(newPkmn) &&
        setRequestedGender(newPkmn) &&
        setRequestedAbility(newPkmn) &&
        setRequestedSize(newPkmn) &&

        // Then set the PID
        generatePersonalityValue(newPkmn, ABCD_U) &&

        // Then set everything else
        convertTrainerID(newPkmn) &&
        convertNickname(newPkmn) &&
        convertLanguage(newPkmn) &&
        convertMiscFlags(newPkmn) &&
        convertTrainerNickname(newPkmn) &&
        convertMarkings(newPkmn) &&
        convertItem(newPkmn) &&
        convertEXP(newPkmn) &&
        convertFriendship(newPkmn) &&
        convertMoves(newPkmn) &&
        convertEVs(newPkmn) &&
        convertContestConditions(newPkmn) &&
        convertPokerus(newPkmn) &&
        convertMetLocation(newPkmn) &&
        convertMetLevel(newPkmn) &&
        convertGameOfOrigin(newPkmn) &&
        convertPokeball(newPkmn) &&
        convertTrainerGender(newPkmn) &&
        convertIVs(newPkmn) &&
        convertRibbonsAndObedience(newPkmn) &&
        convertShininess(newPkmn);

    if (sanitizeMythicals && (getSpeciesIndexNumber() == MEW || getSpeciesIndexNumber() == CELEBI))
    {
        // Modify the required data for the event
        valid &= loadEvent(newPkmn);
    }

    newPkmn->isValid = valid;
    return valid;
};

bool GBPokemon::loadEvent(Gen3Pokemon *newPkmn)
{
    bool valid =
        generatePersonalityValue(newPkmn, BACD_R) &&
        convertEVs(newPkmn) &&
        convertIVs(newPkmn);
    if (!valid)
    {
        return false;
    }
    if (getSpeciesIndexNumber() == MEW)
    {
        newPkmn->setGameOfOrigin(RUBY);
        newPkmn->setFatefulEncounterObedience(true);
        newPkmn->setMetLocation(0xFF); // Fateful Encounter
        newPkmn->setLevelMet(10);
        newPkmn->setSecretID(00000);
        if (newPkmn->getExpPoints() < 560) // 560 is level 10 for Mew
        {
            newPkmn->setExpPoints(560);
        }

        byte jpnOT[] = {0x6A, 0x95, 0x53, 0xFF, 0xFF, 0xFF, 0xFF};
        byte engOT[] = {0xBB, 0xE9, 0xE6, 0xD5, 0xFF, 0x00, 0x00};

        switch (getLanguage())
        {
        case JAPANESE:
        case KOREAN:
            newPkmn->setTrainerID(50716);
            newPkmn->setOTArray(jpnOT, 7);
            break;
        case ENGLISH:
        case FRENCH:
        case ITALIAN:
        case GERMAN:
        case SPANISH:
        default:
            newPkmn->setTrainerID(20078);
            newPkmn->setOTArray(engOT, 7);
            break;
        }
    }
    else if (getSpeciesIndexNumber() == CELEBI)
    {
        newPkmn->setGameOfOrigin(RUBY);
        newPkmn->setFatefulEncounterObedience(false);
        newPkmn->setMetLocation(0xFF); // Fateful Encounter
        newPkmn->setSecretID(0);

        byte jpnOT[] = {0x70, 0x62, 0x78, 0x7E, 0xFF, 0x00, 0x00};
        byte engOT[] = {0xA2, 0xA1, 0x00, 0xBB, 0xC8, 0xC3, 0xD0};

        switch (getLanguage())
        {
        case JAPANESE:
        case KOREAN:
            newPkmn->setLevelMet(10);
            if (newPkmn->getExpPoints() < 560) // 560 is level 10 for Celebi
            {
                newPkmn->setExpPoints(560);
            }
            newPkmn->setTrainerID(60720);
            newPkmn->setOTArray(jpnOT, 7);
            break;
        case ENGLISH:
        case FRENCH:
        case ITALIAN:
        case GERMAN:
        case SPANISH:
        default:
            newPkmn->setLanguage(ENGLISH);
            newPkmn->setLevelMet(70);
            if (newPkmn->getExpPoints() < 344960) // 344960 is level 70 for Celebi
            {
                newPkmn->setExpPoints(344960);
            }
            newPkmn->setTrainerID(10);
            newPkmn->setOTArray(engOT, 7);
            break;
        }
    }

    int val = getExpPoints();
    if (val < 560) // Mew and Celebi are both Medium Slow, 560 is level 10
    {
        setExpPoints(560);
    }
    return true;
}

void GBPokemon::updateValidity()
{
    byte currSpeciesIndexNumber = getSpeciesIndexNumber();
    isValid = ((currSpeciesIndexNumber <= CELEBI ||                          // Checks if the Pokemon is beyond the spported Pokemon, excluding Treecko for now
                (currSpeciesIndexNumber == MISSINGNO && generation == 1)) && // But keep MissingNo
               currSpeciesIndexNumber != 0 &&                                // Makes sure the Pokemon isn't a blank party space
               currSpeciesIndexNumber == externalIndexNumber &&              // Checks that the Pokemon isn't a hybrid or an egg
               getHeldItem() == 0                                            // Makes sure the current Pokemon doesn't have a held item
    );
};

bool GBPokemon::externalConvertNickname(byte outputArray[])
{
    pokeTable->load_input_charset(generation, ENGLISH);
    pokeTable->load_gen3_charset(ENGLISH);
    for (int i = 0; i < 10; i++)
    {
        outputArray[i] = pokeTable->get_gen_3_char(pokeTable->input_charset[nicknameArray[i]]);
    }
    outputArray[10] = 0xFF;
    return true;
};

bool GBPokemon::generatePersonalityValue(Gen3Pokemon *newPkmn, RNGMethod rng)
{
    newPkmn->currRand = getPureRand();
    u32 pid = 0;
    u16 seedA = 0;
    u16 seedB = 0;
    do
    {
        if (rng == ABCD_U)
        {
            seedA = newPkmn->getNextRand_u16();
            seedB = newPkmn->getNextRand_u16();
            pid = seedA | (seedB << 16);
        }
        else if (rng == BACD_R)
        {
            newPkmn->currRand &= 0xFFFF; // Restrict the seed to 16 bits
            seedA = newPkmn->getNextRand_u16();
            seedB = newPkmn->getNextRand_u16();
            pid = seedB | (seedA << 16);
        }
        newPkmn->setPersonalityValue(pid);
        // std::cout << "Testing PID: " << std::hex << pid << "\n";
        /*
        std::cout << "PV: " << newPkmn->getPersonalityValue() << "\n"
                  << "Letter: " << newPkmn->getUnownLetter() << " | " << getUnownLetter() << "\n"
                  << "Nature: " << newPkmn->getNature() << " | " << getVirtualConsoleNature() << "\n"
                  << "Gender: " << newPkmn->getGender() << " | " << getGender() << "\n";
                  */
    } while (!(
        newPkmn->getAbilityFromPersonalityValue() == newPkmn->internalAbility &&
        newPkmn->getUnownLetter() == newPkmn->internalUnownLetter &&
        newPkmn->getNature() == newPkmn->internalNature &&
        newPkmn->getGender() == newPkmn->internalGender &&
        newPkmn->getSize() == newPkmn->internalSize));
    return true;
};

bool GBPokemon::convertTrainerID(Gen3Pokemon *newPkmn)
{
    newPkmn->setTrainerID(getTrainerID());
    return true;
}

bool GBPokemon::convertNickname(Gen3Pokemon *newPkmn)
{
    pokeTable->load_input_charset(generation, ENGLISH);
    pokeTable->load_gen3_charset(ENGLISH);
    for (int i = 0; i < 10; i++)
    {
        newPkmn->setNicknameLetter(i, pokeTable->get_gen_3_char(pokeTable->input_charset[nicknameArray[i]]));
    }
    return true;
};

bool GBPokemon::convertLanguage(Gen3Pokemon *newPkmn)
{
    newPkmn->setLanguage(getLanguage());
    return true;
}

bool GBPokemon::convertMiscFlags(Gen3Pokemon *newPkmn)
{
    newPkmn->setIsBadEgg(false);
    newPkmn->setHasSpecies(true);
    newPkmn->setUseEggName(false);
    newPkmn->setIsEgg(false);
    return true;
}

bool GBPokemon::convertTrainerNickname(Gen3Pokemon *newPkmn)
{
    pokeTable->load_input_charset(1, ENGLISH);
    pokeTable->load_gen3_charset(ENGLISH);

    for (int i = 0; i < 6; i++)
    {
        newPkmn->setOTLetter(i, pokeTable->get_gen_3_char(pokeTable->input_charset[OTArray[i]]));
    }

    return true;
};

bool GBPokemon::convertMarkings(Gen3Pokemon *newPkmn)
{
    newPkmn->setMarkings(0b0000);
    return true;
}

bool GBPokemon::convertSpeciesIndexNumber(Gen3Pokemon *newPkmn)
{
    switch (getSpeciesIndexNumber())
    {
    case TREECKO:
        newPkmn->setSpeciesIndexNumber(0x115);
        break;
    case MISSINGNO:
        newPkmn->setSpeciesIndexNumber(PORYGON);
        break;
    default:
        newPkmn->setSpeciesIndexNumber(getSpeciesIndexNumber());
        break;
    }
    return true;
}

bool GBPokemon::convertItem(Gen3Pokemon *newPkmn)
{
#if ACCESS_POKEDEX
#include "save_data_manager.h"
    if (!is_caught(newPkmn->getSpeciesIndexNumber()))
    {
        newPkmn->setHeldItem(RARE_CANDY);
        set_caught(newPkmn->getSpeciesIndexNumber());
    }
    else
    {
        newPkmn->setHeldItem(NONE);
    }
#else
    newPkmn->setHeldItem(NONE);
#endif
    return true;
}

bool GBPokemon::convertEXP(Gen3Pokemon *newPkmn)
{
    // As per Poke Transporter, the level will be based on the level value, not the EXP
    // Make sure Level is not over 100

    int speciesIndex = getSpeciesIndexNumber();
    int currLevel = getLevel();
    if (currLevel > 100)
    {
        currLevel = 100;
    }

    // Truncate the EXP down to the current level
    pokeTable->load_exp_groups();
    switch (pokeTable->EXP_GROUPS[speciesIndex])
    {
    case EXP_FAST:
        newPkmn->setExpPoints((4 * (currLevel * currLevel * currLevel)) / 5);
        break;

    default: // MissingNo is the only one that should hit default, so match it to Porygon
    case EXP_MED_FAST:
        newPkmn->setExpPoints(currLevel * currLevel * currLevel);
        break;

    case EXP_MED_SLOW:
        newPkmn->setExpPoints(((6 * currLevel * currLevel * currLevel) / 5) - (15 * currLevel * currLevel) + (100 * currLevel) - 140);
        break;

    case EXP_SLOW:
        newPkmn->setExpPoints((5 * (currLevel * currLevel * currLevel)) / 4);
        break;
    }
    return true;
};

bool GBPokemon::convertFriendship(Gen3Pokemon *newPkmn)
{
    newPkmn->setFriendship(70);
    return true;
}

bool GBPokemon::convertMoves(Gen3Pokemon *newPkmn)
{
    Species speciesIndexNum = (Species)getSpeciesIndexNumber();
    // Check that the moves are valid
    if ((speciesIndexNum != SMEARGLE) &&
        (speciesIndexNum != MISSINGNO) &&
        (speciesIndexNum != TREECKO)) // Ignore Smeargle, MissingNo, and Treecko
    {
        for (int i = 0; i < 4; i++)
        {
            if (pokeTable->can_learn_move(speciesIndexNum, getMove(i)))
            {
                newPkmn->setMove(i, getMove(i));       // Add the move
                newPkmn->setPPUpNum(i, getPPUpNum(i)); // Add the PP Bonuses
            }
        }
    }

    // Make sure it has at least one move
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        count += (newPkmn->getMove(i) != 0);
    }
    if (count == 0)
    {
        newPkmn->setMove(0, pokeTable->get_earliest_move(speciesIndexNum));
    }

    // Bubble valid moves to the top
    int i, j;
    bool swapped;
    for (i = 0; i < 3; i++)
    {
        swapped = false;
        for (j = 0; j < 3 - i; j++)
        {
            if (newPkmn->getMove(j) == 0 && newPkmn->getMove(j + 1) != 0)
            {
                // Move the move *and* PP bonus up if there is a blank space
                newPkmn->setMove(j, newPkmn->getMove(j + 1));
                newPkmn->setPPUpNum(j, newPkmn->getPPUpNum(j + 1));
                newPkmn->setMove(j + 1, 0);
                newPkmn->setPPUpNum(j + 1, 0);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }

    // Restore the PP values
    pokeTable->load_power_points();
    for (int i = 0; i < 4; i++)
    {
        int move = newPkmn->getMove(i);
        newPkmn->setPPTotal(i, pokeTable->POWER_POINTS[move] + ((pokeTable->POWER_POINTS[move] / 5) * newPkmn->getPPUpNum(i)));
    }

    return true;
};

bool GBPokemon::convertEVs(Gen3Pokemon *newPkmn)
{
    for (int i = 0; i < 6; i++)
    {
        newPkmn->setEV((Stat)i, 0);
    }
    return true;
};

bool GBPokemon::convertContestConditions(Gen3Pokemon *newPkmn)
{
    for (int i = 0; i < 5; i++)
    {
        newPkmn->setContestCondition((Condition)i, 0);
    }
    newPkmn->setSheen(0);
    return true;
};

bool GBPokemon::convertPokerus(Gen3Pokemon *newPkmn)
{
    newPkmn->setPokerusStrain(getPokerusStrain());
    newPkmn->setPokerusDaysRemaining(getPokerusDaysRemaining());
    return true;
}

bool GBPokemon::convertMetLocation(Gen3Pokemon *newPkmn)
{
    newPkmn->setMetLocation(0xFF); // A fateful encounter
    return true;
}

bool GBPokemon::convertMetLevel(Gen3Pokemon *newPkmn)
{
    newPkmn->setLevelMet(getLevel());
    return true;
}

bool GBPokemon::convertGameOfOrigin(Gen3Pokemon *newPkmn)
{
    switch (generation)
    {
    case 1:
        newPkmn->setGameOfOrigin(FIRERED);
        break;

    case 2:
        newPkmn->setGameOfOrigin(HEARTGOLD);
        break;

    default:
        return false;
    }
    return true;
}

bool GBPokemon::convertPokeball(Gen3Pokemon *newPkmn)
{
    if (getSpeciesIndexNumber() == MISSINGNO)
    {
        newPkmn->setPokeballCaughtIn(MASTER);
    }
    else
    {
        newPkmn->setPokeballCaughtIn(POKE);
    }

    return true;
}

bool GBPokemon::convertTrainerGender(Gen3Pokemon *newPkmn)
{
    newPkmn->setOriginalTrainerGender(getCaughtDataGender());
    return true;
};

bool GBPokemon::convertIVs(Gen3Pokemon *newPkmn)
{
    u16 currRand;

    currRand = newPkmn->getNextRand_u16();
    newPkmn->setIV(HP, (currRand >> 0) & 0b11111);
    newPkmn->setIV(ATTACK, (currRand >> 5) & 0b11111);
    newPkmn->setIV(DEFENSE, (currRand >> 10) & 0b11111);
    currRand = newPkmn->getNextRand_u16();
    newPkmn->setIV(SPEED, (currRand >> 0) & 0b11111);
    newPkmn->setIV(SPECIAL_ATTACK, (currRand >> 5) & 0b11111);
    newPkmn->setIV(SPECIAL_DEFENSE, (currRand >> 10) & 0b11111);

    return true;
};

bool GBPokemon::convertAbilityFlag(Gen3Pokemon *newPkmn)
{
    newPkmn->setAbility(newPkmn->getPersonalityValue() & 0b1);
    return true;
}

bool GBPokemon::convertRibbonsAndObedience(Gen3Pokemon *newPkmn)
{
    Species speciesIndexNumber = (Species)getSpeciesIndexNumber();
    if (speciesIndexNumber == MEW || speciesIndexNumber == CELEBI)
    {
        newPkmn->setFatefulEncounterObedience(true);
    }
    return true;
};

bool GBPokemon::setRequestedLetter(Gen3Pokemon *newPkmn)
{
    newPkmn->internalUnownLetter = getUnownLetter();
    return true;
};

bool GBPokemon::setRequestedNature(Gen3Pokemon *newPkmn)
{
    newPkmn->internalNature = getVirtualConsoleNature();
    return true;
};

bool GBPokemon::setRequestedGender(Gen3Pokemon *newPkmn)
{
    newPkmn->internalGender = getGender();
    return true;
};

bool GBPokemon::setRequestedAbility(Gen3Pokemon *newPkmn)
{
    newPkmn->internalAbility = 255;
    return true;
};

bool GBPokemon::setRequestedSize(Gen3Pokemon *newPkmn)
{
    newPkmn->internalSize = 255;
    return true;
};

bool GBPokemon::convertShininess(Gen3Pokemon *newPkmn)
{
    byte nickname[10] = {};
    byte trainerName[7] = {};

    for (int i = 0; i < 10; i++)
    {
        nickname[i] = newPkmn->getNicknameLetter(i);
    }

    for (int i = 0; i < 7; i++)
    {
        trainerName[i] = newPkmn->getOTLetter(i);
    }

    if ((getSpeciesIndexNumber() == 52) &&
        fnv1a_hash(trainerName, 7) == 1342961308 &&
        (fnv1a_hash(nickname, 7) == 1515822901 || fnv1a_hash(nickname, 8) == 2671449886))
    {
        for (int i = 1; i <= 4; i++)
        {
            setDV((Stat)i, 15);
        }
    }

    u16 shinyTest = newPkmn->getTrainerID() ^
                    (newPkmn->getPersonalityValue() >> 0 & 0xFFFF) ^
                    (newPkmn->getPersonalityValue() >> 16 & 0xFFFF);

    if (getIsShiny())
    { // Make shiny
        newPkmn->setSecretID(shinyTest);
    }
    else
    { // Make sure it isn't shiny
        if (shinyTest < 8)
        { // It became shiny, fix that
            newPkmn->setSecretID(51691);
        }
        else
        {
            newPkmn->setSecretID(0);
        }
    }
    return true;
};

const DataVarInfo
    GBPokemon::speciesIndexNumber[2] = {{0x00, 8, 0}, {0x00, 8, 0}},
    GBPokemon::level[2] = {{0x03, 8, 0}, {0x1F, 8, 0}},
    GBPokemon::moveOne[2] = {{0x08, 8, 0}, {0x02, 8, 0}},
    GBPokemon::moveTwo[2] = {{0x09, 8, 0}, {0x03, 8, 0}},
    GBPokemon::moveThree[2] = {{0x0A, 8, 0}, {0x04, 8, 0}},
    GBPokemon::moveFour[2] = {{0x0B, 8, 0}, {0x05, 8, 0}},
    GBPokemon::trainerID[2] = {{0x0C, 16, 0}, {0x06, 16, 0}},
    GBPokemon::expPoints[2] = {{0x0E, 24, 0}, {0x08, 24, 0}},
    GBPokemon::hpStatExp[2] = {{0x11, 16, 0}, {0x0B, 16, 0}},
    GBPokemon::atkStatExp[2] = {{0x13, 16, 0}, {0x0D, 16, 0}},
    GBPokemon::defStatExp[2] = {{0x15, 16, 0}, {0x0F, 16, 0}},
    GBPokemon::speStatExp[2] = {{0x17, 16, 0}, {0x11, 16, 0}},
    GBPokemon::spcStatExp[2] = {{0x19, 16, 0}, {0x13, 16, 0}},
    GBPokemon::atkDV[2] = {{0x1B, 4, 4}, {0x15, 4, 4}},
    GBPokemon::defDV[2] = {{0x1B, 4, 0}, {0x15, 4, 0}},
    GBPokemon::speDV[2] = {{0x1C, 4, 4}, {0x16, 4, 4}},
    GBPokemon::spcDV[2] = {{0x1C, 4, 0}, {0x16, 4, 0}},
    GBPokemon::ppUpNumMoveOne[2] = {{0x1D, 2, 6}, {0x17, 2, 6}},
    GBPokemon::ppNumTotalMoveOne[2] = {{0x1D, 6, 0}, {0x17, 6, 0}},
    GBPokemon::ppUpNumMoveTwo[2] = {{0x1E, 2, 6}, {0x18, 2, 6}},
    GBPokemon::ppNumTotalMoveTwo[2] = {{0x1E, 6, 0}, {0x18, 6, 0}},
    GBPokemon::ppUpNumMoveThree[2] = {{0x1F, 2, 6}, {0x19, 2, 6}},
    GBPokemon::ppNumTotalMoveThree[2] = {{0x1F, 6, 0}, {0x19, 6, 0}},
    GBPokemon::ppUpNumMoveFour[2] = {{0x20, 2, 6}, {0x1A, 2, 6}},
    GBPokemon::ppNumTotalMoveFour[2] = {{0x20, 6, 0}, {0x1A, 6, 0}};

const DataVarInfo
    *GBPokemon::moves[4] = {
        GBPokemon::moveOne,
        GBPokemon::moveTwo,
        GBPokemon::moveThree,
        GBPokemon::moveFour,
},
    *GBPokemon::statExps[5] = {
        GBPokemon::hpStatExp,
        GBPokemon::atkStatExp,
        GBPokemon::defStatExp,
        GBPokemon::speStatExp,
        GBPokemon::spcStatExp,
},
    *GBPokemon::DVs[5] = {
        GBPokemon::atkDV, // This is wrong, but it will never be accessed anyway.
        GBPokemon::atkDV,
        GBPokemon::defDV,
        GBPokemon::speDV,
        GBPokemon::spcDV,
},
    *GBPokemon::PPUpNums[4] = {
        GBPokemon::ppUpNumMoveOne,
        GBPokemon::ppUpNumMoveTwo,
        GBPokemon::ppUpNumMoveThree,
        GBPokemon::ppUpNumMoveFour,
},
    *GBPokemon::PPUpTotals[4] = {
        GBPokemon::ppNumTotalMoveOne,
        GBPokemon::ppNumTotalMoveTwo,
        GBPokemon::ppNumTotalMoveThree,
        GBPokemon::ppNumTotalMoveFour,
};