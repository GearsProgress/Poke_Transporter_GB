#ifndef POKEMON_H
#define POKEMON_H

#include <tonc.h>
#include "random.h"
#include "global_frame_controller.h"
#include "gb_rom_values/eng_gb_rom_values.h"

#define POKEMON_SIZE 80

// How much trade data is sent for each langauge and generation,
// sarts at OT name and ends after the 3 buffer bytes

struct Simplified_Pokemon
{
    byte dex_number;
    byte met_level;
    byte nickname[10];
    bool is_valid;
    bool is_transferred;
    bool is_shiny;
    int unown_letter;
    bool is_missingno;
};

class Pokemon
{
public:
    Pokemon();
    void generate_pkmn(int index, byte *party_data, const GB_ROM curr_rom);
    // void load_data(int index, const byte *party_data, int game, int lang);
    void convert_to_gen_three(bool simplified, bool stabilize_mythical, GB_ROM curr_rom);
    // void copy_from_to(const byte *source, byte *destination, int size, bool reverse_endian);
    void alocate_data_chunks(byte *G, byte *A, byte *E, byte *M, byte *gen_3_data);
    void insert_data(byte *first, byte *second, byte *third, byte *fourth, byte *gen_3_pkmn);
    byte get_gen_3_data(int index);
    byte *get_full_gen_3_array();
    byte get_unencrypted_data(int index);
    byte *convert_text(byte *text_array, int size, int gen, int lang);
    u32 generate_pid_save_iv(byte pid_species_index, byte nature, byte *pid_dvs);
    u32 generate_pid_iv_match(byte pid_species_index, byte nature, byte *pid_dvs);
    byte rand_reverse_mod(byte modulo_divisor, byte target_mod);
    byte get_rand_gender_byte(byte index_num, byte attack_DVs);
    byte get_dex_number();
    bool get_validity();
    bool get_is_new();
    bool get_is_shiny();
    Simplified_Pokemon get_simple_pkmn();
    u8 get_letter_from_pid(u32 pid);
    u8 get_nature_from_pid(u32 pid);
    u8 get_gender_from_pid(u32 pid);
    void set_to_event(byte nature);
    int num_in_box;
    int index_in_box;
    bool is_missingno = false;

private:
    // u8 gen = 2;
    bool trainer_gender;
    u8 language;
    u8 species_index_party;  // The species ID stored in the party. Really only used for egg detection
    u8 species_index_struct; // The species ID stored in the pkmn strucutre. The main one to use.
    u8 moves[4];
    u16 trainer_id;
    u16 secret_id;
    u32 exp;
    u8 nickname[10];
    u8 trainer_name[7];
    u8 pokerus;
    // u16 origins_info;
    u8 met_level;
    u8 item;
    // u8 gen_3_pkmn[80];
    u8 unencrypted_data[49];  // Contains the 48 GAEM u8s, along with the modulo int
    u32 pid;
    // u8 blank_word[4] = {0};
    // u8 data_section_G[12];
    // u8 data_section_A[12];
    // u8 data_section_E[12];
    // u8 data_section_M[12];
    hword checksum;
    // u8 encryption_key[4];
    hword origin_info = 0;
    bool is_shiny = false;
    u8 pp_values[4];
    u8 pp_bonus[4];
    u8 pure_pp_values[4];
    u8 dvs[2];
    u8 ivs[6];
    u32 ribbons;
    u32 iv_egg_ability;
    u8 unown_letter = -1;
    bool is_valid;
    bool is_new = false;
    // int box_size;
};

#endif
