#ifndef GBPOKEMON_H
#define GBPOKEMON_H

#include "Pokemon.h"
#include "Gen3Pokemon.h"

class GBPokemon : public Pokemon // The class for gen 1 and 2 Pokemon, since they share some conversion functions
{
protected:
    GBPokemon();
    void updateValidity();
    // These store the data bytes
    byte nicknameArray[11];
    byte OTArray[11];
    byte externalIndexNumber;
    Language lang = (Language)0;

    static const DataVarInfo
        // All of the data info variables
        speciesIndexNumber[2],
        level[2],
        moveOne[2], moveTwo[2], moveThree[2], moveFour[2],
        trainerID[2],
        expPoints[2],
        hpStatExp[2], atkStatExp[2], defStatExp[2], speStatExp[2], spcStatExp[2],
        atkDV[2], defDV[2], speDV[2], spcDV[2],
        ppUpNumMoveOne[2], ppUpNumMoveTwo[2], ppUpNumMoveThree[2], ppUpNumMoveFour[2],
        ppNumTotalMoveOne[2], ppNumTotalMoveTwo[2], ppNumTotalMoveThree[2], ppNumTotalMoveFour[2];

    static const DataVarInfo
        // and the convenient arrays of some of the variable groups:
        *moves[4],
        *statExps[5],
        *DVs[5],
        *PPUpNums[4],
        *PPUpTotals[4];

// This is used to easily print out a Pokemon, when using a standard C++ terminal
#if ON_GBA
#else
    std::string parentPrint();
#endif

public:
    virtual void loadData(Language nLang, byte nDataArray[], byte nNicknameArray[], byte nOTArray[], byte nExternalIndexNum);

    // All of the simple getters and setters are defined here
    u32 getLevel() { return getVar(level[generation - 1]); }
    u32 getTrainerID() { return getVar(trainerID[generation - 1]); }
    u32 getExpPoints() { return getVar(expPoints[generation - 1]); }

    bool setLevel(byte newVal) { return setVar(level[generation - 1], newVal); }
    bool setOriginalTrainerID(byte newVal) { return setVar(trainerID[generation - 1], newVal); }
    bool setExpPoints(u32 newVal) { return setVar(expPoints[generation - 1], newVal); }

    // The ones that access arrays are defined here:
    u32 getMove(int moveIndex) { return getVar(moves[moveIndex][generation - 1]); }
    u32 getStatExp(Stat currStat) { return getVar(statExps[currStat][generation - 1]); }
    u32 getPPUpNum(int moveIndex) { return getVar(PPUpNums[moveIndex][generation - 1]); }
    u32 getPPTotal(int moveIndex) { return getVar(PPUpTotals[moveIndex][generation - 1]); }

    bool setMove(int moveIndex, byte newVal) { return setVar(moves[moveIndex][generation - 1], newVal); }
    bool setStatExp(Stat currStat, byte newVal) { return setVar(statExps[currStat][generation - 1], newVal); }
    bool setPPUpNum(int moveIndex, byte newVal) { return setVar(PPUpNums[moveIndex][generation - 1], newVal); }
    bool setPPTotal(int moveIndex, byte newVal) { return setVar(PPUpTotals[moveIndex][generation - 1], newVal); }

    // These are all replaced in the child classes, but give a default value or do nothing here

    // ---- Gen 1
    virtual u32 getSpeciesIndexNumber() { return getVar(*speciesIndexNumber); }
    virtual u32 getCurrentHP() { return 0; }
    virtual u32 getStatusCondition() { return 0; }
    virtual u32 getCatchRate() { return 0; }
    virtual u32 getType(int typeIndex) { return NORMAL; }

    virtual bool setSpeciesIndexNumber(byte newVal) { return setVar(*speciesIndexNumber, newVal); }
    virtual bool setCurrentHP(byte newVal) { return false; }
    virtual bool setStatusCondition(byte newVal) { return false; }
    virtual bool setCatchRate(byte newVal) { return false; }
    virtual bool setType(int typeIndex, Gen1Types newVal) { return false; }

    // ---- Gen 2
    virtual u32 getHeldItem() { return 0; }    // no item
    virtual u32 getFriendship() { return 70; } // default friendship - make this different for Pikachu in Yellow???
    virtual u32 getPokerusStrain() { return 0; }
    virtual u32 getPokerusDaysRemaining() { return 0; }
    virtual u32 getCaughtDataTime() { return 0; }
    virtual u32 getCaughtDataLevel() { return 0; }
    virtual u32 getCaughtDataGender() { return 0; }
    virtual u32 getCaughtDataLocation() { return 0; }

    virtual bool setHeldItem(byte newVal) { return false; } // This could *technically* be seen as setting the catch rate but...
    virtual bool setFriendship(byte newVal) { return false; }
    virtual bool setPokerusStrain(byte newVal) { return false; }
    virtual bool setPokerusDaysRemaining(byte newVal) { return false; }
    virtual bool setCaughtDataTime(byte newVal) { return false; }
    virtual bool setCaughtDataLevel(byte newVal) { return false; }
    virtual bool setCaughtDataGender(byte newVal) { return false; }
    virtual bool setCaughtDataLocation(byte newVal) { return false; }

    // These all have special implementations
    u32 getDV(Stat currStat);
    bool setDV(Stat currStat, byte newVal);

    // These is virtual so it can be overwitten in Gen 1

    // These aren't direct variables, but they're useful to have
    Language getLanguage() { return lang; };
    byte getUnownLetter();
    Gender getGender();
    Nature getVirtualConsoleNature();
    bool getIsShiny();
    bool externalConvertNickname(byte outputArray[]);

    // And this is for all the conversion stuff
    bool convertToGen3(Gen3Pokemon *newPkmn, bool sanitizeMythicals);
    bool loadEvent(Gen3Pokemon *newPkmn);

    bool generatePersonalityValue(Gen3Pokemon *newPkmn, RNGMethod rng);
    bool convertTrainerID(Gen3Pokemon *newPkmn);
    bool convertNickname(Gen3Pokemon *newPkmn);
    bool convertLanguage(Gen3Pokemon *newPkmn);
    bool convertMiscFlags(Gen3Pokemon *newPkmn);
    bool convertTrainerNickname(Gen3Pokemon *newPkmn);
    bool convertMarkings(Gen3Pokemon *newPkmn);
    // Data
    bool convertSpeciesIndexNumber(Gen3Pokemon *newPkmn);
    bool convertItem(Gen3Pokemon *newPkmn);
    bool convertEXP(Gen3Pokemon *newPkmn);
    bool convertFriendship(Gen3Pokemon *newPkmn);
    bool convertMoves(Gen3Pokemon *newPkmn);
    bool convertEVs(Gen3Pokemon *newPkmn);
    bool convertContestConditions(Gen3Pokemon *newPkmn);
    bool convertPokerus(Gen3Pokemon *newPkmn);
    bool convertMetLocation(Gen3Pokemon *newPkmn);
    bool convertMetLevel(Gen3Pokemon *newPkmn);
    bool convertGameOfOrigin(Gen3Pokemon *newPkmn);
    bool convertPokeball(Gen3Pokemon *newPkmn);
    bool convertTrainerGender(Gen3Pokemon *newPkmn);
    bool convertIVs(Gen3Pokemon *newPkmn);
    bool convertAbilityFlag(Gen3Pokemon *newPkmn);
    bool convertRibbonsAndObedience(Gen3Pokemon *newPkmn);
    bool convertShininess(Gen3Pokemon *newPkmn);
    // Extra
    bool setRequestedLetter(Gen3Pokemon *newPkmn);
    bool setRequestedNature(Gen3Pokemon *newPkmn);
    bool setRequestedGender(Gen3Pokemon *newPkmn);
    bool setRequestedAbility(Gen3Pokemon *newPkmn);
    bool setRequestedSize(Gen3Pokemon *newPkmn);
};

#endif