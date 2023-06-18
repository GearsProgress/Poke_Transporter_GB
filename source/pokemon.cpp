#include <tonc.h>

#define SPECIES_INDEX ((gen == 1) ? 0x01 : 0x02)
#define MOVE_ONE
#define MOVE_TWO
#define MOVE_THREE
#define MOVE_FOUR
#define OT_TID
#define EXP
//#define IV_DATA
#define LEVEL
#define 




class Pokemon{
public:
    byte pkmn_data[64];
    int gen;

    Pokemon(int generation){
        gen = generation;
    }

    void convert_to_gen_three(){
        byte new_pkmn[100];



    }

    byte get(){
        return TEST;
    }
};