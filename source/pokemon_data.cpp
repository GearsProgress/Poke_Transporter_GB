#include "pokemon_data.h"
#include "zx0_decompressor.h"
#include "EXP_GROUPS_zx0_bin.h"
#include "GENDER_RATIO_zx0_bin.h"
#include "NUM_ABILITIES_zx0_bin.h"
#include "FIRST_MOVES_zx0_bin.h"
#include "POWER_POINTS_zx0_bin.h"
#include "EVENT_PKMN_zx0_bin.h"
#include "TYPES_zx0_bin.h"
#include "MOVESETS_zx0_bin.h"
#include "gen_1_charsets_zx0_bin.h"
#include "gen_2_charsets_zx0_bin.h"
#include "gen_3_charsets_zx0_bin.h"
#include <tonc.h>
#include <cstring>

// All data was obtained using PokeAPI
// This data won't compress very well with ZX0 (only 1 byte reduction), so we leave it uncompressed.
const byte gen_1_index_array[191] = {
    0x00, // Offset the list to remove "off by one" errors
    0x70, // Rhydon
    0x73, // Kangaskhan
    0x20, // Nidoran♂
    0x23, // Clefairy
    0x15, // Spearow
    0x64, // Voltorb
    0x22, // Nidoking
    0x50, // Slowbro
    0x02, // Ivysaur
    0x67, // Exeggutor
    0x6C, // Lickitung
    0x66, // Exeggcute
    0x58, // Grimer
    0x5E, // Gengar
    0x1D, // Nidoran♀
    0x1F, // Nidoqueen
    0x68, // Cubone
    0x6F, // Rhyhorn
    0x83, // Lapras
    0x3B, // Arcanine
    0x97, // Mew
    0x82, // Gyarados
    0x5A, // Shellder
    0x48, // Tentacool
    0x5C, // Gastly
    0x7B, // Scyther
    0x78, // Staryu
    0x09, // Blastoise
    0x7F, // Pinsir
    0x72, // Tangela
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x3A, // Growlithe
    0x5F, // Onix
    0x16, // Fearow
    0x10, // Pidgey
    0x4F, // Slowpoke
    0x40, // Kadabra
    0x4B, // Graveler
    0x71, // Chansey
    0x43, // Machoke
    0x7A, // Mr. Mime
    0x6A, // Hitmonlee
    0x6B, // Hitmonchan
    0x18, // Arbok
    0x2F, // Parasect
    0x36, // Psyduck
    0x60, // Drowzee
    0x4C, // Golem
    0xFF, // MissingNo.
    0x7E, // Magmar
    0xFF, // MissingNo.
    0x7D, // Electabuzz
    0x52, // Magneton
    0x6D, // Koffing
    0xFF, // MissingNo.
    0x38, // Mankey
    0x56, // Seel
    0x32, // Diglett
    0x80, // Tauros
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x53, // Farfetch'd
    0x30, // Venonat
    0x95, // Dragonite
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x54, // Doduo
    0x3C, // Poliwag
    0x7C, // Jynx
    0x92, // Moltres
    0x90, // Articuno
    0x91, // Zapdos
    0x84, // Ditto
    0x34, // Meowth
    0x62, // Krabby
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x25, // Vulpix
    0x26, // Ninetales
    0x19, // Pikachu
    0x1A, // Raichu
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x93, // Dratini
    0x94, // Dragonair
    0x8C, // Kabuto
    0x8D, // Kabutops
    0x74, // Horsea
    0x75, // Seadra
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x1B, // Sandshrew
    0x1C, // Sandslash
    0x8A, // Omanyte
    0x8B, // Omastar
    0x27, // Jigglypuff
    0x28, // Wigglytuff
    0x85, // Eevee
    0x88, // Flareon
    0x87, // Jolteon
    0x86, // Vaporeon
    0x42, // Machop
    0x29, // Zubat
    0x17, // Ekans
    0x2E, // Paras
    0x3D, // Poliwhirl
    0x3E, // Poliwrath
    0x0D, // Weedle
    0x0E, // Kakuna
    0x0F, // Beedrill
    0xFF, // MissingNo.
    0x55, // Dodrio
    0x39, // Primeape
    0x33, // Dugtrio
    0x31, // Venomoth
    0x57, // Dewgong
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x0A, // Caterpie
    0x0B, // Metapod
    0x0C, // Butterfree
    0x44, // Machamp
    0xFF, // MissingNo.
    0x37, // Golduck
    0x61, // Hypno
    0x2A, // Golbat
    0x96, // Mewtwo
    0x8F, // Snorlax
    0x81, // Magikarp
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x59, // Muk
    0xFF, // MissingNo.
    0x63, // Kingler
    0x5B, // Cloyster
    0xFF, // MissingNo.
    0x65, // Electrode
    0x24, // Clefable
    0x6E, // Weezing
    0x35, // Persian
    0x69, // Marowak
    0xFF, // MissingNo.
    0x5D, // Haunter
    0x3F, // Abra
    0x41, // Alakazam
    0x11, // Pidgeotto
    0x12, // Pidgeot
    0x79, // Starmie
    0x01, // Bulbasaur
    0x03, // Venusaur
    0x49, // Tentacruel
    0xFF, // MissingNo.
    0x76, // Goldeen
    0x77, // Seaking
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x4D, // Ponyta
    0x4E, // Rapidash
    0x13, // Rattata
    0x14, // Raticate
    0x21, // Nidorino
    0x1E, // Nidorina
    0x4A, // Geodude
    0x89, // Porygon
    0x8E, // Aerodactyl
    0xFF, // MissingNo.
    0x51, // Magnemite
    0xFF, // MissingNo.
    0xFF, // MissingNo.
    0x04, // Charmander
    0x07, // Squirtle
    0x05, // Charmeleon
    0x08, // Wartortle
    0x06, // Charizard
    0xFF, // MissingNo.
    0xFF, // Kabutops Fossil MissingNo.
    0xFF, // Aerodactyl Fossil MissingNo.
    0xFF, // Ghost MissingNo.
    0x2B, // Oddish
    0x2C, // Gloom
    0x2D, // Vileplume
    0x45, // Bellsprout
    0x46, // Weepinbell
    0x47, // Victreebel
};

// Indexes found here: https://bulbapedia.bulbagarden.net/wiki/Experience#In_the_core_series
const u32 EXP_MAXIMUMS[6] = {
    med_fast_max,
    erratic_max,
    flux_max,
    med_slow_max,
    fast_max,
    slow_max};

const int GENDER_THRESHOLDS[2][8]{
    {-1, 2, 4, 8, 12, 14, -1, -1},
    {-1, 31, 63, 127, 191, 225, -1, -1}};

// The EVOLUTIONS table won't compress well with ZX0 (it would only save 12 bytes), so it's not worth the
// decompression runtime cost. Therefore we leave it uncompressed.
const u8 EVOLUTIONS[POKEMON_ARRAY_SIZE]{
    0,    // Offset the list to remove "off by one" errors
    0x0,  // Bulbasaur is a base evolution
    0x1,  // Ivysaur evolves from Bulbasaur
    0x2,  // Venusaur evolves from Ivysaur
    0x0,  // Charmander is a base evolution
    0x4,  // Charmeleon evolves from Charmander
    0x5,  // Charizard evolves from Charmeleon
    0x0,  // Squirtle is a base evolution
    0x7,  // Wartortle evolves from Squirtle
    0x8,  // Blastoise evolves from Wartortle
    0x0,  // Caterpie is a base evolution
    0xa,  // Metapod evolves from Caterpie
    0xb,  // Butterfree evolves from Metapod
    0x0,  // Weedle is a base evolution
    0xd,  // Kakuna evolves from Weedle
    0xe,  // Beedrill evolves from Kakuna
    0x0,  // Pidgey is a base evolution
    0x10, // Pidgeotto evolves from Pidgey
    0x11, // Pidgeot evolves from Pidgeotto
    0x0,  // Rattata is a base evolution
    0x13, // Raticate evolves from Rattata
    0x0,  // Spearow is a base evolution
    0x15, // Fearow evolves from Spearow
    0x0,  // Ekans is a base evolution
    0x17, // Arbok evolves from Ekans
    0xac, // Pikachu evolves from Pichu
    0x19, // Raichu evolves from Pikachu
    0x0,  // Sandshrew is a base evolution
    0x1b, // Sandslash evolves from Sandshrew
    0x0,  // Nidoran-f is a base evolution
    0x1d, // Nidorina evolves from Nidoran-f
    0x1e, // Nidoqueen evolves from Nidorina
    0x0,  // Nidoran-m is a base evolution
    0x20, // Nidorino evolves from Nidoran-m
    0x21, // Nidoking evolves from Nidorino
    0xad, // Clefairy evolves from Cleffa
    0x23, // Clefable evolves from Clefairy
    0x0,  // Vulpix is a base evolution
    0x25, // Ninetales evolves from Vulpix
    0xae, // Jigglypuff evolves from Igglybuff
    0x27, // Wigglytuff evolves from Jigglypuff
    0x0,  // Zubat is a base evolution
    0x29, // Golbat evolves from Zubat
    0x0,  // Oddish is a base evolution
    0x2b, // Gloom evolves from Oddish
    0x2c, // Vileplume evolves from Gloom
    0x0,  // Paras is a base evolution
    0x2e, // Parasect evolves from Paras
    0x0,  // Venonat is a base evolution
    0x30, // Venomoth evolves from Venonat
    0x0,  // Diglett is a base evolution
    0x32, // Dugtrio evolves from Diglett
    0x0,  // Meowth is a base evolution
    0x34, // Persian evolves from Meowth
    0x0,  // Psyduck is a base evolution
    0x36, // Golduck evolves from Psyduck
    0x0,  // Mankey is a base evolution
    0x38, // Primeape evolves from Mankey
    0x0,  // Growlithe is a base evolution
    0x3a, // Arcanine evolves from Growlithe
    0x0,  // Poliwag is a base evolution
    0x3c, // Poliwhirl evolves from Poliwag
    0x3d, // Poliwrath evolves from Poliwhirl
    0x0,  // Abra is a base evolution
    0x3f, // Kadabra evolves from Abra
    0x40, // Alakazam evolves from Kadabra
    0x0,  // Machop is a base evolution
    0x42, // Machoke evolves from Machop
    0x43, // Machamp evolves from Machoke
    0x0,  // Bellsprout is a base evolution
    0x45, // Weepinbell evolves from Bellsprout
    0x46, // Victreebel evolves from Weepinbell
    0x0,  // Tentacool is a base evolution
    0x48, // Tentacruel evolves from Tentacool
    0x0,  // Geodude is a base evolution
    0x4a, // Graveler evolves from Geodude
    0x4b, // Golem evolves from Graveler
    0x0,  // Ponyta is a base evolution
    0x4d, // Rapidash evolves from Ponyta
    0x0,  // Slowpoke is a base evolution
    0x4f, // Slowbro evolves from Slowpoke
    0x0,  // Magnemite is a base evolution
    0x51, // Magneton evolves from Magnemite
    0x0,  // Farfetchd is a base evolution
    0x0,  // Doduo is a base evolution
    0x54, // Dodrio evolves from Doduo
    0x0,  // Seel is a base evolution
    0x56, // Dewgong evolves from Seel
    0x0,  // Grimer is a base evolution
    0x58, // Muk evolves from Grimer
    0x0,  // Shellder is a base evolution
    0x5a, // Cloyster evolves from Shellder
    0x0,  // Gastly is a base evolution
    0x5c, // Haunter evolves from Gastly
    0x5d, // Gengar evolves from Haunter
    0x0,  // Onix is a base evolution
    0x0,  // Drowzee is a base evolution
    0x60, // Hypno evolves from Drowzee
    0x0,  // Krabby is a base evolution
    0x62, // Kingler evolves from Krabby
    0x0,  // Voltorb is a base evolution
    0x64, // Electrode evolves from Voltorb
    0x0,  // Exeggcute is a base evolution
    0x66, // Exeggutor evolves from Exeggcute
    0x0,  // Cubone is a base evolution
    0x68, // Marowak evolves from Cubone
    0xec, // Hitmonlee evolves from Tyrogue
    0xec, // Hitmonchan evolves from Tyrogue
    0x0,  // Lickitung is a base evolution
    0x0,  // Koffing is a base evolution
    0x6d, // Weezing evolves from Koffing
    0x0,  // Rhyhorn is a base evolution
    0x6f, // Rhydon evolves from Rhyhorn
    0x0,  // Chansey is a base evolution (in gen 2)
    0x0,  // Tangela is a base evolution
    0x0,  // Kangaskhan is a base evolution
    0x0,  // Horsea is a base evolution
    0x74, // Seadra evolves from Horsea
    0x0,  // Goldeen is a base evolution
    0x76, // Seaking evolves from Goldeen
    0x0,  // Staryu is a base evolution
    0x78, // Starmie evolves from Staryu
    0x0,  // Mr-mime is a base evolution (in gen 2)
    0x0,  // Scyther is a base evolution
    0xee, // Jynx evolves from Smoochum
    0xef, // Electabuzz evolves from Elekid
    0xf0, // Magmar evolves from Magby
    0x0,  // Pinsir is a base evolution
    0x0,  // Tauros is a base evolution
    0x0,  // Magikarp is a base evolution
    0x81, // Gyarados evolves from Magikarp
    0x0,  // Lapras is a base evolution
    0x0,  // Ditto is a base evolution
    0x0,  // Eevee is a base evolution
    0x85, // Vaporeon evolves from Eevee
    0x85, // Jolteon evolves from Eevee
    0x85, // Flareon evolves from Eevee
    0x0,  // Porygon is a base evolution
    0x0,  // Omanyte is a base evolution
    0x8a, // Omastar evolves from Omanyte
    0x0,  // Kabuto is a base evolution
    0x8c, // Kabutops evolves from Kabuto
    0x0,  // Aerodactyl is a base evolution
    0x0,  // Snorlax is a base evolution (in gen 2)
    0x0,  // Articuno is a base evolution
    0x0,  // Zapdos is a base evolution
    0x0,  // Moltres is a base evolution
    0x0,  // Dratini is a base evolution
    0x93, // Dragonair evolves from Dratini
    0x94, // Dragonite evolves from Dragonair
    0x0,  // Mewtwo is a base evolution
    0x0,  // Mew is a base evolution
    0x0,  // Chikorita is a base evolution
    0x98, // Bayleef evolves from Chikorita
    0x99, // Meganium evolves from Bayleef
    0x0,  // Cyndaquil is a base evolution
    0x9b, // Quilava evolves from Cyndaquil
    0x9c, // Typhlosion evolves from Quilava
    0x0,  // Totodile is a base evolution
    0x9e, // Croconaw evolves from Totodile
    0x9f, // Feraligatr evolves from Croconaw
    0x0,  // Sentret is a base evolution
    0xa1, // Furret evolves from Sentret
    0x0,  // Hoothoot is a base evolution
    0xa3, // Noctowl evolves from Hoothoot
    0x0,  // Ledyba is a base evolution
    0xa5, // Ledian evolves from Ledyba
    0x0,  // Spinarak is a base evolution
    0xa7, // Ariados evolves from Spinarak
    0x2a, // Crobat evolves from Golbat
    0x0,  // Chinchou is a base evolution
    0xaa, // Lanturn evolves from Chinchou
    0x0,  // Pichu is a base evolution
    0x0,  // Cleffa is a base evolution
    0x0,  // Igglybuff is a base evolution
    0x0,  // Togepi is a base evolution
    0xaf, // Togetic evolves from Togepi
    0x0,  // Natu is a base evolution
    0xb1, // Xatu evolves from Natu
    0x0,  // Mareep is a base evolution
    0xb3, // Flaaffy evolves from Mareep
    0xb4, // Ampharos evolves from Flaaffy
    0x2c, // Bellossom evolves from Gloom
    0x0,  // Marill is a base evolution (in gen 2)
    0xb7, // Azumarill evolves from Marill
    0x0,  // Sudowoodo is a base evolution (in gen 2)
    0x3d, // Politoed evolves from Poliwhirl
    0x0,  // Hoppip is a base evolution
    0xbb, // Skiploom evolves from Hoppip
    0xbc, // Jumpluff evolves from Skiploom
    0x0,  // Aipom is a base evolution
    0x0,  // Sunkern is a base evolution
    0xbf, // Sunflora evolves from Sunkern
    0x0,  // Yanma is a base evolution
    0x0,  // Wooper is a base evolution
    0xc2, // Quagsire evolves from Wooper
    0x85, // Espeon evolves from Eevee
    0x85, // Umbreon evolves from Eevee
    0x0,  // Murkrow is a base evolution
    0x4f, // Slowking evolves from Slowpoke
    0x0,  // Misdreavus is a base evolution
    0x0,  // Unown is a base evolution
    0x0,  // Wobbuffet is a base evolution (in gen 2)
    0x0,  // Girafarig is a base evolution
    0x0,  // Pineco is a base evolution
    0xcc, // Forretress evolves from Pineco
    0x0,  // Dunsparce is a base evolution
    0x0,  // Gligar is a base evolution
    0x5f, // Steelix evolves from Onix
    0x0,  // Snubbull is a base evolution
    0xd1, // Granbull evolves from Snubbull
    0x0,  // Qwilfish is a base evolution
    0x7b, // Scizor evolves from Scyther
    0x0,  // Shuckle is a base evolution
    0x0,  // Heracross is a base evolution
    0x0,  // Sneasel is a base evolution
    0x0,  // Teddiursa is a base evolution
    0xd8, // Ursaring evolves from Teddiursa
    0x0,  // Slugma is a base evolution
    0xda, // Magcargo evolves from Slugma
    0x0,  // Swinub is a base evolution
    0xdc, // Piloswine evolves from Swinub
    0x0,  // Corsola is a base evolution
    0x0,  // Remoraid is a base evolution
    0xdf, // Octillery evolves from Remoraid
    0x0,  // Delibird is a base evolution
    0x0,  // Mantine is a base evolution (in gen 2)
    0x0,  // Skarmory is a base evolution
    0x0,  // Houndour is a base evolution
    0xe4, // Houndoom evolves from Houndour
    0x75, // Kingdra evolves from Seadra
    0x0,  // Phanpy is a base evolution
    0xe7, // Donphan evolves from Phanpy
    0x89, // Porygon2 evolves from Porygon
    0x0,  // Stantler is a base evolution
    0x0,  // Smeargle is a base evolution
    0x0,  // Tyrogue is a base evolution
    0xec, // Hitmontop evolves from Tyrogue
    0x0,  // Smoochum is a base evolution
    0x0,  // Elekid is a base evolution
    0x0,  // Magby is a base evolution
    0x0,  // Miltank is a base evolution
    0x71, // Blissey evolves from Chansey
    0x0,  // Raikou is a base evolution
    0x0,  // Entei is a base evolution
    0x0,  // Suicune is a base evolution
    0x0,  // Larvitar is a base evolution
    0xf6, // Pupitar evolves from Larvitar
    0xf7, // Tyranitar evolves from Pupitar
    0x0,  // Lugia is a base evolution
    0x0,  // Ho-oh is a base evolution
    0x0,  // Celebi is a base evolution
    0x0,  // Treecko is a base evolution
};

static void load_table(u8 *table, const u8* source, bool &loadedBool)
{
    if(loadedBool)
    {
        return;
    }
    zx0_decompressor_start(table, source);
    zx0_decompressor_read(zx0_decompressor_get_decompressed_size());
    loadedBool = true;
}

PokemonTables::PokemonTables()
    : exp_groups_loaded(false)
    , gender_ratios_loaded(false)
    , num_abilities_loaded(false)
    , first_moves_loaded(false)
    , power_points_loaded(false)
    , event_pkmn_loaded(false)
    , types_loaded(false)
    , input_charset_type(0)
    , gen3_charset_type(0)
    , movesets_loaded(false)
{
}

void PokemonTables::load_exp_groups()
{
    load_table(EXP_GROUPS, EXP_GROUPS_zx0_bin, exp_groups_loaded);
}

void PokemonTables::load_gender_ratios()
{
    load_table(GENDER_RATIO, GENDER_RATIO_zx0_bin, gender_ratios_loaded);
}

void PokemonTables::load_num_abilities()
{
    load_table((uint8_t*)NUM_ABILITIES, NUM_ABILITIES_zx0_bin, num_abilities_loaded);
}

void PokemonTables::load_first_moves()
{
    load_table(FIRST_MOVES, FIRST_MOVES_zx0_bin, first_moves_loaded);
}

void PokemonTables::load_power_points()
{
    load_table(POWER_POINTS, POWER_POINTS_zx0_bin, power_points_loaded);
}

void PokemonTables::load_event_pkmn()
{
    load_table((uint8_t*)EVENT_PKMN, EVENT_PKMN_zx0_bin, event_pkmn_loaded);
}

void PokemonTables::load_types()
{
    load_table((uint8_t*)TYPES, TYPES_zx0_bin, types_loaded);
}

void PokemonTables::load_input_charset(byte gen, byte lang)
{
    const u8 desired_charset = (gen << 4) | (lang);
    if(input_charset_type == desired_charset)
    {
        return;
    }
    load_localized_charset(input_charset, gen, lang);
    input_charset_type = desired_charset;
}

void PokemonTables::load_gen3_charset(byte lang)
{
    // transform lang into the value that would get stored in gen3_charset_index
    if(lang == KOR_ID)
    {
        lang = JPN_ID;
    }
    else if(lang != JPN_ID)
    {
        lang = ENG_ID;
    }

    if(gen3_charset_type == lang)
    {
        return;
    }

    load_localized_charset(gen3_charset, 3, lang);
    gen3_charset_type = lang;
}

void PokemonTables::load_movesets()
{
    load_table((uint8_t*)MOVESETS, MOVESETS_zx0_bin, movesets_loaded);
}

u32 PokemonTables::get_max_exp(int index_num)
{
    load_exp_groups();
    int exp_group = EXP_GROUPS[index_num];
    u32 exp_max = EXP_MAXIMUMS[exp_group];
    u32 test = exp_max;
    return test;
}

u8 PokemonTables::get_gender_threshold(int index_num, bool is_gen_3)
{
    load_gender_ratios();
    return GENDER_THRESHOLDS[is_gen_3][GENDER_RATIO[index_num]];
}

// If the Pokemon has two abilities it returns a 1, since ability 1 is valid. Otherwise it returns 0
bool PokemonTables::get_num_abilities(int index_num)
{
    load_num_abilities();
    return NUM_ABILITIES[index_num];
}

bool PokemonTables::can_learn_move(int pkmn_index, int move_index)
{
    load_movesets();
    byte data_byte = MOVESETS[pkmn_index][move_index / 8];
    data_byte |= MOVESETS[EVOLUTIONS[pkmn_index]][move_index / 8];             // add in the previous evolution's moves (if they exist)
    data_byte |= MOVESETS[EVOLUTIONS[EVOLUTIONS[pkmn_index]]][move_index / 8]; // add in the first evolution's moves (if they exist)
    return (data_byte >> (7 - (move_index % 8))) & 0x1;
}

byte PokemonTables::get_earliest_move(int index_num)
{
    load_first_moves();
    return FIRST_MOVES[index_num];
}

byte PokemonTables::get_gen_3_char(u16 input_char)
{
    return get_char_from_charset(gen3_charset, input_char);
}

// This table indicates the index of each specific charset in their generations' charsets file
static const u8 localization_charset_indices[]
{
    0, // gen 1 JPN
    1, // gen 1 ENG
    2, // gen 1 FR/GER
    2, // gen 1 FR/GER
    3, // gen 1 ITA/SPA
    3, // gen 1 ITA/SPA
    0, // gen 1 KOR -> JPN (unused in gen 1)
    0, // gen 2 JPN
    1, // gen 2 ENG
    2, // gen 2 FR/GER
    2, // gen 2 FR/GER
    3, // gen 2 ITA/SPA
    3, // gen 2 ITA/SPA
    0, // gen 2 KOR -> JPN
    0, // gen 3 JPN
    1, // gen 3 International
    1, // gen 3 International
    1, // gen 3 International
    1, // gen 3 International
    1, // gen 3 International
    0, // gen 3 KOR -> JPN
};

void load_localized_charset(u16 *output_char_array, byte gen, byte lang)
{
    u8 generation_charsets[2048];
    const u8 *input_data;

    // in the localization_charset_indices list,
    // gen 1 starts first and every gen has 7 entries (1 per language)
    // however, the language values are 1-based, so we need to convert to 0-based
    const u8 lang_index = localization_charset_indices[(gen - 1) * 7 + (lang - 1)];

    switch(gen)
    {
    case 1:
        input_data = gen_1_charsets_zx0_bin;
        break;
    case 2:
        input_data = gen_2_charsets_zx0_bin;
        break;
    case 3:
        input_data = gen_3_charsets_zx0_bin;
        break;
    default:
        // Invalid generation, return without doing anything
        return;
    }

    zx0_decompressor_start(generation_charsets, input_data);
    zx0_decompressor_read(zx0_decompressor_get_decompressed_size());

    memcpy(output_char_array, generation_charsets + (lang_index * 256 * sizeof(u16)), 256 * sizeof(u16)); // copy the charset into the output array   
}

byte get_char_from_charset(const u16 *charset, u16 input_char)
{
    u16 i = 0;
    while(i < 256)
    {
        if (charset[i] == input_char)
        {
            return i;
        }
        ++i;
    }
    return 0;
}