#include <tonc.h>

byte gen_one_pkmn_index[255];
byte gen_two_pkmn_index[255];


class Pokemon{
public:

    void Pokemon(byte gen, byte party_data[441]){
        num_of_pkmn = party_data[0x11];

        for (int i = 0; i < num_of_pkmn; i++){
        int party_offset = 20  + (i * 48);
        int ot_offset    = 308 + (i * 11);
        int name_offset  = 374 + (i * 11);
            
        switch(gen){
            case 1:
          

            break;
            case 2:
                species_index = gen_one_pkmn_index[party_data[party_offset + 0x00];
                moves[4];
                trainer_id[2];
                exp[3];
                nickname[11];
                trainer_name[11];
                pokerus;
                caught_data[2];
                level;
            break;
        }
    }

    void convert_to_gen_three(){
        byte gen_3_pkmn[80][6];
    }
private:
    byte gen;
    byte num_of_pkmn;
    byte species_index;
    byte moves[4];
    byte trainer_id[2];
    byte exp[3];
    byte nickname[11];
    byte trainer_name[11];
    byte pokerus;
    byte caught_data[2];
    byte level;

    }
};
