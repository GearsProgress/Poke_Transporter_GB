#ifndef GEN3POKEMON_H
#define GEN3POKEMON_H

#include "Pokemon.h"

class Gen3Pokemon : public Pokemon // The class for gen 3 Pokemon

{
public:
    Gen3Pokemon(PokemonTables *table);

    bool convertToGen3(Gen3Pokemon *g3p);

    u32 currRand;
    u32 getNextRand_u32();
    u32 getPrevRand_u32();
    u16 getNextRand_u16();
    u16 getPrevRand_u16();

    // These are stored internally so that they can be set by different functions
    byte internalUnownLetter;
    Nature internalNature;
    Gender internalGender;
    int internalSize;
    int internalAbility;

protected:
    // These store the data bytes
    byte dataArray[80] = {0};

    // This stores if the data is current encrypted or not
    bool isEncrypted;

    // These store the offsets of the various data substructures:
    int substructOffsets[4] = {0, 12, 24, 36};
    int currSubstructureShift = 0;

    void swapSubstructures(int indexOne, int indexTwo);

#pragma region
    // Since there is only the Pokemon parent class, we can directly define these directly
    static const DataVarInfo
        // All of the data info variables
        personalityValue,
        trainerID,
        secretID,
        nicknameLetterOne, // This is silly. Change this.
        nicknameLetterTwo,
        nicknameLetterThree,
        nicknameLetterFour,
        nicknameLetterFive,
        nicknameLetterSix,
        nicknameLetterSeven,
        nicknameLetterEight,
        nicknameLetterNine,
        nicknameLetterTen,
        language,
        isBadEgg,
        hasSpecies,
        useEggName,
        blockBoxRS,
        // unusedFlags,
        originalTrainerNameLetterOne, // This is also silly. Change this.
        originalTrainerNameLetterTwo,
        originalTrainerNameLetterThree,
        originalTrainerNameLetterFour,
        originalTrainerNameLetterFive,
        originalTrainerNameLetterSix,
        originalTrainerNameLetterSeven,
        markings,
        checksum;
    // unknown;

    static const DataVarInfo
        *nickname[10],
        *originalTrainerName[7];

    // data section G
    static const DataVarInfo
        speciesIndexNumber,
        heldItem,
        expPoints,
        ppUpNumMoveOne,
        ppUpNumMoveTwo,
        ppUpNumMoveThree,
        ppUpNumMoveFour,
        friendship;
    // unused;

    static const DataVarInfo
        *ppUpNums[4];

    // data section A
    static const DataVarInfo
        moveOne,
        moveTwo,
        moveThree,
        moveFour,
        moveOnePP,
        moveTwoPP,
        moveThreePP,
        moveFourPP;
    static const DataVarInfo
        *moves[4],
        *ppUpTotals[4];

    // data section E
    static const DataVarInfo
        hpEVs,
        attackEVs,
        defenseEVs,
        speedEVs,
        specialAttackEVs,
        specialDefenseEVs,
        coolnessCondition,
        beautyCondition,
        cutenessCondition,
        smartnessCondition,
        toughnessCondition,
        sheen;

    static const DataVarInfo
        *EVs[6],
        *contestConditions[5];

    static const DataVarInfo

        // data section M
        pokerusStrain,
        pokerusDaysRemaining,
        metLocation,
        levelMet,
        gameOfOrigin,
        pokeballCaughtIn,
        originalTrainerGender,
        hpIVs,
        attackIVs,
        defenseIVs,
        speedIVs,
        specialAttackIVs,
        specialDefenseIVs,
        isEgg,
        ability,
        coolNormalContestRibbon, // This is also very silly. Change it.
        coolSuperContestRibbon,
        coolHyperContestRibbon,
        coolMasterContestRibbon,
        beautyNormalContestRibbon,
        beautySuperContestRibbon,
        beautyHyperContestRibbon,
        beautyMasterContestRibbon,
        cuteNormalContestRibbon,
        cuteSuperContestRibbon,
        cuteHyperContestRibbon,
        cuteMasterContestRibbon,
        smartNormalContestRibbon,
        smartSuperContestRibbon,
        smartHyperContestRibbon,
        smartMasterContestRibbon,
        toughNormalContestRibbon,
        toughSuperContestRibbon,
        toughHyperContestRibbon,
        toughMasterContestRibbon,
        championRibbon,
        winningRibbon,
        victoryRibbon,
        artistRibbon,
        effortRibbon,
        battleChampionRibbon,
        regionalChampionRibbon,
        nationalChampionRibbon,
        countryRibbon,
        nationalRibbon,
        earthRibbon,
        unusedRibbons,
        fatefulEncounterObedience;

    static const DataVarInfo
        *IVs[6],
        *ribbons[31];
#pragma endregion

    // This is used to easily print out a Pokemon, when using a standard C++ terminal
#if ON_GBA
#else
public:
    void print(std::ostream &os);
    std::string printDataArray(bool encrypedData);
#endif

public:
    // All of the simple getters and setters are defined here
    u32 getPersonalityValue() { return getVar(personalityValue); }
    u32 getTrainerID() { return getVar(trainerID); }
    u32 getSecretID() { return getVar(secretID); }
    u32 getLanguage() { return getVar(language); }
    u32 getIsBadEgg() { return getVar(isBadEgg); }
    u32 getHasSpecies() { return getVar(hasSpecies); }
    u32 getUseEggName() { return getVar(useEggName); }
    u32 getBlockBoxRS() { return getVar(blockBoxRS); }
    u32 getMarkings() { return getVar(markings); }
    u32 getChecksum() { return getVar(checksum); }
    u32 getSpeciesIndexNumber() { return getVar(speciesIndexNumber, substructOffsets[SUB_G]); }
    u32 getHeldItem() { return getVar(heldItem, substructOffsets[SUB_G]); }
    u32 getExpPoints() { return getVar(expPoints, substructOffsets[SUB_G]); }
    u32 getFriendship() { return getVar(friendship, substructOffsets[SUB_G]); }
    u32 getSheen() { return getVar(sheen, substructOffsets[SUB_E]); }
    u32 getPokerusStrain() { return getVar(pokerusStrain, substructOffsets[SUB_M]); }
    u32 getPokerusDaysRemaining() { return getVar(pokerusDaysRemaining, substructOffsets[SUB_M]); }
    u32 getMetLocation() { return getVar(metLocation, substructOffsets[SUB_M]); }
    u32 getLevelMet() { return getVar(levelMet, substructOffsets[SUB_M]); }
    u32 getGameOfOrigin() { return getVar(gameOfOrigin, substructOffsets[SUB_M]); }
    u32 getPokeballCaughtIn() { return getVar(pokeballCaughtIn, substructOffsets[SUB_M]); }
    u32 getOriginalTrainerGender() { return getVar(originalTrainerGender, substructOffsets[SUB_M]); }
    u32 getIsEgg() { return getVar(isEgg, substructOffsets[SUB_M]); }
    u32 getAbility() { return getVar(ability, substructOffsets[SUB_M]); }
    u32 getFatefulEncounterObedience() { return getVar(fatefulEncounterObedience, substructOffsets[SUB_M]); }

    bool setTrainerID(u32 newVal) { return setVar(trainerID, newVal); }
    bool setSecretID(u32 newVal) { return setVar(secretID, newVal); }
    bool setLanguage(u32 newVal) { return setVar(language, newVal); }
    bool setIsBadEgg(u32 newVal) { return setVar(isBadEgg, newVal); }
    bool setHasSpecies(u32 newVal) { return setVar(hasSpecies, newVal); }
    bool setUseEggName(u32 newVal) { return setVar(useEggName, newVal); }
    bool setBlockBoxRS(u32 newVal) { return setVar(blockBoxRS, newVal); }
    bool setMarkings(u32 newVal) { return setVar(markings, newVal); }
    bool setChecksum(u32 newVal) { return setVar(checksum, newVal); }
    bool setSpeciesIndexNumber(u32 newVal) { return setVar(speciesIndexNumber, substructOffsets[SUB_G], newVal); }
    bool setHeldItem(Item newVal) { return setVar(heldItem, substructOffsets[SUB_G], newVal); }
    bool setExpPoints(u32 newVal) { return setVar(expPoints, substructOffsets[SUB_G], newVal); }
    bool setFriendship(u32 newVal) { return setVar(friendship, substructOffsets[SUB_G], newVal); }
    bool setSheen(u32 newVal) { return setVar(sheen, substructOffsets[SUB_E], newVal); }
    bool setPokerusStrain(u32 newVal) { return setVar(pokerusStrain, substructOffsets[SUB_M], newVal); }
    bool setPokerusDaysRemaining(u32 newVal) { return setVar(pokerusDaysRemaining, substructOffsets[SUB_M], newVal); }
    bool setMetLocation(u32 newVal) { return setVar(metLocation, substructOffsets[SUB_M], newVal); }
    bool setLevelMet(u32 newVal) { return setVar(levelMet, substructOffsets[SUB_M], newVal); }
    bool setGameOfOrigin(Game newVal) { return setVar(gameOfOrigin, substructOffsets[SUB_M], newVal); }
    bool setPokeballCaughtIn(u32 newVal) { return setVar(pokeballCaughtIn, substructOffsets[SUB_M], newVal); }
    bool setOriginalTrainerGender(u32 newVal) { return setVar(originalTrainerGender, substructOffsets[SUB_M], newVal); }
    bool setIsEgg(u32 newVal) { return setVar(isEgg, substructOffsets[SUB_M], newVal); }
    bool setFatefulEncounterObedience(u32 newVal) { return setVar(fatefulEncounterObedience, substructOffsets[SUB_M], newVal); }

    // The ones that access arrays are defined here:
    u32 getPPUpNum(int moveIndex) { return getVar(*ppUpNums[moveIndex], substructOffsets[SUB_G]); }
    u32 getMove(int moveIndex) { return getVar(*moves[moveIndex], substructOffsets[SUB_A]); }
    u32 getPPTotal(int moveIndex) { return getVar(*ppUpTotals[moveIndex], substructOffsets[SUB_A]); }
    u32 getEV(Stat currStat) { return getVar(*EVs[currStat], substructOffsets[SUB_E]); }
    u32 getContestCondition(Condition currCondition) { return getVar(*contestConditions[currCondition], substructOffsets[SUB_E]); }
    u32 getIV(Stat currStat) { return getVar(*IVs[currStat], substructOffsets[SUB_M]); }
    u32 getRibbons(Ribbon currRibbon) { return getVar(*ribbons[currRibbon], substructOffsets[SUB_M]); }
    u32 getNicknameLetter(int index) { return getVar(*nickname[index]); };
    u32 getOTLetter(int index) { return getVar(*originalTrainerName[index]); };

    bool setPPUpNum(int moveIndex, u32 newVal) { return setVar(*ppUpNums[moveIndex], substructOffsets[SUB_G], newVal); }
    bool setMove(int moveIndex, u32 newVal) { return setVar(*moves[moveIndex], substructOffsets[SUB_A], newVal); }
    bool setPPTotal(int moveIndex, u32 newVal) { return setVar(*ppUpTotals[moveIndex], substructOffsets[SUB_A], newVal); }
    bool setEV(Stat currStat, u32 newVal) { return setVar(*EVs[currStat], substructOffsets[SUB_E], newVal); }
    bool setContestCondition(Condition currCondition, u32 newVal) { return setVar(*contestConditions[currCondition], substructOffsets[SUB_E], newVal); }
    bool setIV(Stat currStat, u32 newVal) { return setVar(*IVs[currStat], substructOffsets[SUB_M], newVal); }
    bool setRibbons(Ribbon currRibbon, u32 newVal) { return setVar(*ribbons[currRibbon], substructOffsets[SUB_M], newVal); }
    bool setNicknameLetter(int index, u32 newVal) { return setVar(*nickname[index], newVal); };
    bool setOTLetter(int index, u32 newVal) { return setVar(*originalTrainerName[index], newVal); };

    bool setPersonalityValue(u32 newVal);
    bool setAbility(u32 newVal);

    // This is used to load our data in from an array and decrypt it
    void loadData(byte incomingArray[]);

    // And then some general functions
    void decryptSubstructures();

    void encryptSubstructures();

    void updateChecksum();

    void updateSubstructureShift();

    void resetSubstructureShift();

    void updateSecurityData();

    byte getUnownLetter();
    Nature getNature();
    Gender getGender();
    int getAbilityFromPersonalityValue();
    int getSize();

    bool getIsShiny();

    bool setNicknameArray(byte nameArr[], int nameArrSize);
    bool setOTArray(byte nameArr[], int nameArrSize);
};

#endif