#include "pokemon_data.h"
#include <cstring>

#if USE_COMPRESSED_DATA
#include "EXP_GROUPS_lz10_bin.h"
#include "GENDER_RATIO_lz10_bin.h"
#include "NUM_ABILITIES_lz10_bin.h"
#include "FIRST_MOVES_lz10_bin.h"
#include "POWER_POINTS_lz10_bin.h"
#include "EVENT_PKMN_lz10_bin.h"
#include "TYPES_lz10_bin.h"
#include "gen_1_charsets_lz10_bin.h"
#include "gen_2_charsets_lz10_bin.h"
#include "gen_3_charsets_lz10_bin.h"
#include <tonc.h>
#endif

// All data was obtained using PokeAPI
// This data won't compress very well with ZX0 (only 1 byte reduction), so we leave it uncompressed.
const byte gen_1_index_array[191]{
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
const u32 EXP_MAXIMUMS[6]{
    med_fast_max,
    0, // erratic_max
    0, // flux_max
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

const byte MOVESETS[POKEMON_ARRAY_SIZE][32]{
    // This data is stored as 32 bytes of binary data per Pokemon, depending on if they can learn the move. Data obtained through PokeAPI
    // 0(unused) 8           16          24          32          40          48          56          64          72          80          88          96          104         112         120         128         136         144         152         160         168         176         184         192         200         208         216         224         232         240         248
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Offset the list to remove "off by one" errors
    {0b00000000, 0b00000011, 0b00000010, 0b00000000, 0b01100010, 0b00000100, 0b00000000, 0b00000000, 0b00000010, 0b01111101, 0b10000000, 0b00001000, 0b00000010, 0b10000001, 0b01000000, 0b00000000, 0b00100000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00001100, 0b00000000, 0b00111001, 0b00100110, 0b10110000, 0b00000010, 0b00010100, 0b01000000, 0b01000000}, // Bulbasaur
    {0b00000000, 0b00000011, 0b00000010, 0b00000000, 0b01100010, 0b00000100, 0b00000000, 0b00000000, 0b00000010, 0b01111101, 0b00000000, 0b00001000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001100, 0b00000000, 0b00110001, 0b00100110, 0b10100000, 0b00000010, 0b00010100, 0b01000000, 0b01000000}, // Ivysaur
    {0b00000000, 0b00000011, 0b00000010, 0b00000000, 0b01100010, 0b00000110, 0b00000000, 0b00000001, 0b00000010, 0b01111101, 0b00000000, 0b01001000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001100, 0b00000000, 0b00110001, 0b00100110, 0b10100000, 0b00000010, 0b00010100, 0b01000000, 0b01000000}, // Venusaur
    {0b00000101, 0b00100011, 0b00000000, 0b01000000, 0b00100010, 0b00001100, 0b00001100, 0b00000000, 0b00001110, 0b00000000, 0b00110000, 0b00011000, 0b00010010, 0b10001001, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b00000100, 0b00000010, 0b10010100, 0b00000000, 0b10010001, 0b00100110, 0b10100001, 0b00000001, 0b10000100, 0b01000010, 0b01010000}, // Charmander
    {0b00000101, 0b00100011, 0b00000000, 0b01000000, 0b00100010, 0b00000100, 0b00001100, 0b00000000, 0b00001110, 0b00000000, 0b00110000, 0b00011000, 0b00010010, 0b10001001, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b00000100, 0b00000010, 0b10000100, 0b00000000, 0b00010001, 0b00100110, 0b10100001, 0b00000001, 0b10000100, 0b01000000, 0b01000000}, // Charmeleon
    {0b00000101, 0b00100011, 0b01010000, 0b01000000, 0b00100010, 0b00000110, 0b00001100, 0b00000001, 0b00001110, 0b00000000, 0b00110000, 0b01011000, 0b00010010, 0b10001001, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b00000100, 0b00000010, 0b10000100, 0b00000000, 0b00010001, 0b00110110, 0b10100001, 0b00000001, 0b10000100, 0b01000000, 0b01000000}, // Charizard
    {0b00000100, 0b10000000, 0b00000000, 0b01000000, 0b01100011, 0b00001000, 0b00000011, 0b11110000, 0b00001110, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10000011, 0b00100000, 0b00000001, 0b00100000, 0b00000000, 0b01000000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000100, 0b01001000, 0b00010101, 0b00000110, 0b10100001, 0b00000101, 0b00000100, 0b10010000, 0b01000000}, // Squirtle
    {0b00000100, 0b10000000, 0b00000000, 0b01000000, 0b01100011, 0b00001000, 0b00000001, 0b11110000, 0b00001110, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10000011, 0b00000000, 0b00000001, 0b00100000, 0b00000000, 0b01000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b00010101, 0b00000110, 0b10100001, 0b00000101, 0b00000100, 0b10000000, 0b01000000}, // Wartortle
    {0b00000100, 0b10000000, 0b00000000, 0b01000000, 0b01100011, 0b00001010, 0b00000001, 0b11110001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000011, 0b00000000, 0b00000001, 0b00100000, 0b00000000, 0b01000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b00010101, 0b00000110, 0b10100001, 0b00000101, 0b00000100, 0b10000000, 0b01000000}, // Blastoise
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Caterpie
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Metapod
    {0b00000000, 0b00000000, 0b10100000, 0b00000000, 0b00000010, 0b00000000, 0b10000000, 0b00001001, 0b00000000, 0b00001111, 0b00000000, 0b00001110, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00110001, 0b00000110, 0b10110000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Butterfree
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Weedle
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Kakuna
    {0b00000000, 0b00000011, 0b00000000, 0b00000001, 0b00000010, 0b01100000, 0b00000000, 0b00000001, 0b00000000, 0b00001000, 0b00000000, 0b00001000, 0b01010010, 0b10000000, 0b00001000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00100110, 0b10100000, 0b00001000, 0b00000100, 0b01000000, 0b01000000}, // Beedrill
    {0b00000000, 0b00000000, 0b11110000, 0b00001000, 0b01000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b00000001, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b01000100, 0b01000000, 0b00010001, 0b00010110, 0b10100000, 0b00001000, 0b00000100, 0b11000000, 0b00000000}, // Pidgey
    {0b00000000, 0b00000000, 0b11110000, 0b00001000, 0b01000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b00000001, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Pidgeotto
    {0b00000000, 0b00000000, 0b11110000, 0b00001000, 0b01000010, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b00000001, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Pidgeot
    {0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b01100011, 0b00001000, 0b00000000, 0b00110000, 0b00001000, 0b00000000, 0b00000111, 0b00011000, 0b00100011, 0b10000001, 0b00001000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00101010, 0b00101000, 0b10001100, 0b00010010, 0b00000100, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00001001, 0b00000100, 0b11000001, 0b01000000}, // Rattata
    {0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b01100011, 0b00000010, 0b00000000, 0b00110001, 0b00001010, 0b00000000, 0b00000111, 0b00011000, 0b00100010, 0b10000001, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001010, 0b00101000, 0b10000100, 0b00000010, 0b10000100, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00001001, 0b00000100, 0b11000001, 0b01000000}, // Raticate
    {0b00000000, 0b00000000, 0b00010000, 0b00000001, 0b00000010, 0b00010100, 0b00000000, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b00000001, 0b00000000, 0b01000000, 0b00000001, 0b00000000, 0b00001000, 0b01001000, 0b10000100, 0b00000010, 0b11000100, 0b00000000, 0b00010011, 0b00010110, 0b10100000, 0b00001000, 0b00000100, 0b11000000, 0b00000000}, // Spearow
    {0b00000000, 0b00000000, 0b00010000, 0b00000001, 0b00000010, 0b00010100, 0b00000000, 0b00000001, 0b11000000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10000000, 0b00000001, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00010110, 0b10100000, 0b00001000, 0b00000100, 0b11000000, 0b00000000}, // Fearow
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00110010, 0b10011000, 0b00010000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b01011000, 0b00000011, 0b10000000, 0b00100000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00001010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00001001, 0b00000100, 0b11000000, 0b00010000}, // Ekans
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110010, 0b10011000, 0b00010000, 0b00000001, 0b00000010, 0b00000000, 0b00000000, 0b01011000, 0b00000011, 0b10000000, 0b00100000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11000000, 0b00000000}, // Arbok
    {0b00000100, 0b01000000, 0b00000100, 0b01000000, 0b00100011, 0b00000100, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00001111, 0b00011000, 0b01100010, 0b10000001, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Pikachu
    {0b00000100, 0b01000000, 0b00000000, 0b01000000, 0b00100011, 0b00000000, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00001111, 0b00011000, 0b00100010, 0b10000001, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Raichu
    {0b00000000, 0b00100011, 0b00000000, 0b00001000, 0b00100010, 0b10000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00101100, 0b00011000, 0b10000101, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00100110, 0b10110001, 0b00000101, 0b10000100, 0b01000000, 0b01000000}, // Sandshrew
    {0b00000000, 0b00100011, 0b00000000, 0b00001000, 0b00100010, 0b10000000, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00101100, 0b00011000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b01000000, 0b01000000}, // Sandslash
    {0b00000000, 0b00100001, 0b00000000, 0b10000000, 0b00101011, 0b10001100, 0b10100000, 0b00110000, 0b00001010, 0b00000000, 0b00000101, 0b00011000, 0b00000010, 0b10000001, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00101000, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00000000, 0b00011001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11100000, 0b01010000}, // Nidoran-f
    {0b00000000, 0b00100001, 0b00000000, 0b10000000, 0b00100011, 0b10001100, 0b00000000, 0b00110000, 0b00001010, 0b00000000, 0b00000101, 0b00011000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00101000, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11100000, 0b01000000}, // Nidorina
    {0b00000101, 0b11100001, 0b00000000, 0b11000000, 0b00100011, 0b10000010, 0b00000100, 0b01110001, 0b00001110, 0b00000000, 0b00000101, 0b01011000, 0b00000010, 0b10000001, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00001000, 0b01010001, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b11000001, 0b01000000}, // Nidoqueen
    {0b00000000, 0b00000001, 0b00000000, 0b10000011, 0b10101010, 0b10010000, 0b10100000, 0b00110000, 0b10001010, 0b00000000, 0b00000101, 0b00011100, 0b00000010, 0b10000001, 0b00001000, 0b00000000, 0b00000100, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11000000, 0b01010000}, // Nidoran-m
    {0b00000000, 0b00000001, 0b00000000, 0b10000011, 0b10100010, 0b10010000, 0b00000000, 0b00110000, 0b10001010, 0b00000000, 0b00000101, 0b00011000, 0b00000010, 0b10000001, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11000000, 0b01000000}, // Nidorino
    {0b00000101, 0b11000001, 0b00000000, 0b11000000, 0b00100110, 0b10000010, 0b00000100, 0b01110001, 0b10001110, 0b00000000, 0b00000101, 0b01011000, 0b00000010, 0b10000001, 0b00001000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00001000, 0b01010001, 0b00100110, 0b10100001, 0b10000001, 0b00000100, 0b11000001, 0b01000000}, // Nidoking
    {0b01010101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000101, 0b00000100, 0b00110000, 0b00001110, 0b00001000, 0b00000111, 0b00011010, 0b00000010, 0b10010001, 0b01010010, 0b00000010, 0b00000001, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10110001, 0b00010001, 0b00001100, 0b11001001, 0b00000000}, // Clefairy
    {0b00010101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000001, 0b00000100, 0b00110001, 0b00001110, 0b00001000, 0b00000111, 0b00011010, 0b00000010, 0b10010001, 0b01010010, 0b00000010, 0b00000001, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10110001, 0b00000001, 0b00000100, 0b11001001, 0b00000000}, // Clefable
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100011, 0b00000010, 0b00101100, 0b00000000, 0b00000000, 0b00000000, 0b00010000, 0b00011001, 0b00100010, 0b10000100, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000101, 0b00001010, 0b01000000, 0b00000000, 0b00010001, 0b00000110, 0b10110000, 0b00000001, 0b00000100, 0b01001000, 0b00000000}, // Vulpix
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00000010, 0b00001100, 0b00000001, 0b00000000, 0b00000000, 0b00010000, 0b00011000, 0b00100010, 0b10000100, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110000, 0b00000001, 0b00000100, 0b01000000, 0b00000000}, // Ninetales
    {0b01010101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000001, 0b00100100, 0b00110000, 0b00001110, 0b00001000, 0b00000111, 0b00011010, 0b00000010, 0b10000001, 0b01010000, 0b00000010, 0b00000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10110001, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Jigglypuff
    {0b00010101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000001, 0b00100100, 0b00110001, 0b00001110, 0b00001000, 0b00000111, 0b00011010, 0b00000010, 0b10000001, 0b01010000, 0b00000010, 0b00000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10110001, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Wigglytuff
    {0b00000000, 0b00000000, 0b11100000, 0b00000000, 0b00000010, 0b00001000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00100010, 0b10000100, 0b00100000, 0b00000000, 0b01000000, 0b00000100, 0b00000000, 0b00001000, 0b00001000, 0b10000110, 0b00000010, 0b01001000, 0b00000000, 0b00110001, 0b00011110, 0b10100000, 0b00001000, 0b00000100, 0b11000001, 0b00000000}, // Zubat
    {0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000010, 0b00001000, 0b10000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000011, 0b10000100, 0b00100000, 0b00000000, 0b01000000, 0b00000100, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00011110, 0b10100000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Golbat
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00010000, 0b00000000, 0b00000001, 0b00011111, 0b10000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00001000, 0b00000000, 0b00111001, 0b00000110, 0b10100000, 0b00000010, 0b00011100, 0b01000000, 0b00000000}, // Oddish
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00010000, 0b00000000, 0b00000001, 0b00001111, 0b10000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000010, 0b00001100, 0b01000000, 0b00000000}, // Gloom
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b10001010, 0b10000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b00000000}, // Vileplume
    {0b00000000, 0b00100011, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00101110, 0b00000000, 0b00011000, 0b00000011, 0b10000000, 0b01000000, 0b00000000, 0b00000000, 0b00000100, 0b00011000, 0b00001000, 0b00011000, 0b10000101, 0b00000010, 0b00001000, 0b00000000, 0b00110011, 0b00100110, 0b10100000, 0b00001010, 0b00000100, 0b01000000, 0b01000000}, // Paras
    {0b00000000, 0b00100011, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00000001, 0b00001000, 0b00101110, 0b00000000, 0b00011000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00011000, 0b00001000, 0b00011000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00100110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Parasect
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b10100000, 0b00001000, 0b00000000, 0b00001111, 0b00000000, 0b00001110, 0b00000011, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000100, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b01000000, 0b00110001, 0b00000110, 0b10100000, 0b00100000, 0b00000100, 0b01000000, 0b00000000}, // Venonat
    {0b00000000, 0b00000000, 0b10000000, 0b00000000, 0b01000010, 0b00000000, 0b10100000, 0b00001001, 0b00000000, 0b00001111, 0b00000000, 0b00001110, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000100, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b01000000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b00000000}, // Venomoth
    {0b00000000, 0b00100001, 0b00000000, 0b00001000, 0b00100010, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111000, 0b00000011, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00101100, 0b00011000, 0b10000100, 0b00000010, 0b01001100, 0b00000000, 0b00010001, 0b00000110, 0b10100010, 0b00001000, 0b00000100, 0b01000010, 0b01010000}, // Diglett
    {0b00000000, 0b00100001, 0b00000000, 0b00001000, 0b00100010, 0b00000100, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b01111000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00101100, 0b01011000, 0b10000100, 0b00000010, 0b00001100, 0b00000000, 0b00010001, 0b00000110, 0b10100010, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Dugtrio
    {0b00000010, 0b00100001, 0b00000000, 0b00000000, 0b00100010, 0b00001100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000101, 0b00011001, 0b00000011, 0b10000001, 0b00000000, 0b00000000, 0b01000100, 0b00100000, 0b00001000, 0b00101000, 0b00011000, 0b10000100, 0b00001010, 0b01000100, 0b00001000, 0b00011001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11001001, 0b00000000}, // Meowth
    {0b00000010, 0b00100001, 0b00000000, 0b00000000, 0b00100010, 0b00001110, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000101, 0b00011000, 0b00000011, 0b10000001, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00101000, 0b00011000, 0b10000100, 0b00000010, 0b01000100, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11001001, 0b00000000}, // Persian
    {0b00000100, 0b10100000, 0b00000000, 0b01000000, 0b00100011, 0b00000000, 0b00100000, 0b11111000, 0b00001110, 0b00000000, 0b00000000, 0b00011111, 0b00000011, 0b10000000, 0b01000000, 0b00000001, 0b01000000, 0b00000000, 0b00001000, 0b00101000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b01001000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000110, 0b10001000, 0b11000000}, // Psyduck
    {0b00000100, 0b10100000, 0b00000000, 0b01000000, 0b00100011, 0b00000000, 0b00100000, 0b11110001, 0b00001110, 0b00000000, 0b00000000, 0b00011100, 0b00000011, 0b10000000, 0b00000000, 0b00000001, 0b01000000, 0b00000000, 0b00001000, 0b00101000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b10001000, 0b01000000}, // Golduck
    {0b00100101, 0b11100000, 0b00000000, 0b01000000, 0b00100110, 0b00010000, 0b00000000, 0b00000000, 0b00011110, 0b00000000, 0b00000101, 0b01011000, 0b10000011, 0b10000001, 0b00001010, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00101100, 0b00001000, 0b10000100, 0b00010010, 0b00000100, 0b01000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000110, 0b11001000, 0b01010000}, // Mankey
    {0b00100101, 0b11100000, 0b00000000, 0b01000000, 0b00100110, 0b00010000, 0b00000000, 0b00000001, 0b00011110, 0b00000000, 0b00000101, 0b01011000, 0b00010011, 0b10000001, 0b00001010, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00101100, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000110, 0b11001000, 0b01000000}, // Primeape
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00101110, 0b00011010, 0b00001100, 0b00000000, 0b00000010, 0b00000000, 0b00010000, 0b00011000, 0b01000010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10001100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110000, 0b00000001, 0b00000100, 0b01100000, 0b01000000}, // Growlithe
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00001010, 0b00001100, 0b00000001, 0b00000010, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b01000100, 0b01000000}, // Arcanine
    {0b00010000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00000011, 0b11110100, 0b00000000, 0b00000000, 0b00000000, 0b00011011, 0b00000010, 0b10000001, 0b00100000, 0b00000001, 0b00000000, 0b00000000, 0b01000010, 0b00001000, 0b00001000, 0b10100100, 0b00000010, 0b00010000, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b00000000}, // Poliwag
    {0b00010100, 0b10000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000001, 0b11110000, 0b00001110, 0b00000000, 0b00000000, 0b01011011, 0b00000010, 0b10000001, 0b00000010, 0b00000001, 0b00000000, 0b00000000, 0b01000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00010100, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b01000000}, // Poliwhirl
    {0b00010100, 0b10000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000001, 0b01110001, 0b00101110, 0b00000000, 0b00000000, 0b01011011, 0b00000010, 0b10000001, 0b00000010, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10100100, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00000110, 0b10100001, 0b00000000, 0b00000100, 0b10000000, 0b01000000}, // Poliwrath
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00000000, 0b00000010, 0b00001010, 0b00001010, 0b10000000, 0b11010010, 0b00000000, 0b00000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110001, 0b00010001, 0b00000100, 0b11001001, 0b00000000}, // Abra
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00100000, 0b00001000, 0b00001100, 0b00000000, 0b00000010, 0b00001110, 0b00001010, 0b11000000, 0b01010010, 0b00000000, 0b00000010, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110001, 0b00000001, 0b00000100, 0b11001001, 0b10000000}, // Kadabra
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00100000, 0b00001001, 0b00001100, 0b00000000, 0b00000010, 0b00001110, 0b00001010, 0b11000000, 0b01010010, 0b00000000, 0b00000010, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110001, 0b00000001, 0b00000100, 0b11001001, 0b10000000}, // Alakazam
    {0b00100101, 0b11000000, 0b00000000, 0b01010000, 0b00100010, 0b00010000, 0b00000100, 0b00000000, 0b00111110, 0b00000000, 0b00000000, 0b01011000, 0b10000010, 0b10000000, 0b01001010, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b10000100, 0b01000000, 0b00010001, 0b00000110, 0b10100001, 0b00010000, 0b01000110, 0b11000000, 0b01000000}, // Machop
    {0b00100101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00010000, 0b00000100, 0b00000000, 0b00111110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000000, 0b00001010, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b10000100, 0b01000000, 0b00010001, 0b00000110, 0b10100001, 0b00000000, 0b01000110, 0b11000000, 0b01000000}, // Machoke
    {0b00100101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00010000, 0b00000100, 0b00000001, 0b00111110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000000, 0b00001010, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b10000100, 0b01000000, 0b00010001, 0b00000110, 0b10100001, 0b00000000, 0b01000110, 0b11000000, 0b01000000}, // Machamp
    {0b00000000, 0b00000011, 0b00000110, 0b00000000, 0b00010010, 0b00000000, 0b00010000, 0b00000000, 0b00000000, 0b00111111, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b00010000, 0b00000000, 0b00000000, 0b00000100, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00010010, 0b00010100, 0b01000000, 0b00000000}, // Bellsprout
    {0b00000000, 0b00000011, 0b00000110, 0b00000000, 0b00010010, 0b00000000, 0b00010000, 0b00000000, 0b00000000, 0b00111111, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000010, 0b00000100, 0b01000000, 0b00000000}, // Weepinbell
    {0b00000000, 0b00000011, 0b00000010, 0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00011001, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000010, 0b00000100, 0b01000000, 0b00000000}, // Victreebel
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00010010, 0b10000000, 0b10010000, 0b11110110, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000011, 0b10000100, 0b10100000, 0b00000001, 0b00001000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00001000, 0b00110001, 0b00000110, 0b10110000, 0b00000100, 0b00000100, 0b10010000, 0b00000000}, // Tentacool
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00010010, 0b10000000, 0b10010000, 0b11110101, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000011, 0b10000000, 0b10000000, 0b00000001, 0b00001000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00001000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b00000000}, // Tentacruel
    {0b00000101, 0b00000000, 0b00000000, 0b00000000, 0b01100010, 0b00000000, 0b00000100, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b11011000, 0b00000010, 0b10000001, 0b00000010, 0b10000010, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10100011, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Geodude
    {0b00000101, 0b00000000, 0b00000000, 0b00000000, 0b01100010, 0b00000000, 0b00000100, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b11011000, 0b00000010, 0b10000001, 0b00000010, 0b10000010, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10100011, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Graveler
    {0b00000101, 0b00000000, 0b00000000, 0b01000000, 0b01100010, 0b00000010, 0b00000100, 0b00000001, 0b00001110, 0b00000000, 0b00000000, 0b11011000, 0b00000010, 0b10000001, 0b00000010, 0b10000010, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00100110, 0b10100011, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Golem
    {0b00000000, 0b00000000, 0b00000001, 0b10000000, 0b01101111, 0b00000100, 0b00001100, 0b00000000, 0b00000010, 0b00001000, 0b00010000, 0b00001001, 0b01100010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001100, 0b00000010, 0b00000000, 0b00000000, 0b00011001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b01000000, 0b00000000}, // Ponyta
    {0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b01101011, 0b00000100, 0b00001100, 0b00000001, 0b00000010, 0b00001000, 0b00010000, 0b00001000, 0b01100010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b01000000, 0b00000000}, // Rapidash
    {0b00000000, 0b00000000, 0b00000001, 0b00000100, 0b01100010, 0b00000100, 0b00100101, 0b01110000, 0b00000010, 0b00000000, 0b00000010, 0b01011110, 0b00000010, 0b10000000, 0b00000000, 0b00000010, 0b01000100, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00010100, 0b00001000, 0b00010001, 0b00000110, 0b10110000, 0b00000001, 0b00000100, 0b11001001, 0b10000000}, // Slowpoke
    {0b00000100, 0b10000000, 0b00000000, 0b01000100, 0b01100010, 0b00000100, 0b00100101, 0b01110001, 0b00001110, 0b00000000, 0b00000010, 0b01011110, 0b00000010, 0b10000010, 0b00000000, 0b00000010, 0b01000100, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00100110, 0b10110001, 0b00000001, 0b00000100, 0b11001001, 0b01000000}, // Slowbro
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00001111, 0b00001000, 0b00000011, 0b10000000, 0b00010000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b10000001, 0b00010101, 0b01000010, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Magnemite
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b11000000, 0b00000001, 0b00000000, 0b00000000, 0b00001111, 0b00001000, 0b00000011, 0b10000000, 0b00010000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b01001000, 0b00000100, 0b00000010, 0b00000000, 0b10000001, 0b00010101, 0b01000010, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Magneton
    {0b00000000, 0b00000011, 0b10010000, 0b00001001, 0b00100010, 0b00010000, 0b00000000, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b00000001, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00011000, 0b10000111, 0b00000010, 0b00000100, 0b01000000, 0b00010011, 0b00110110, 0b10100000, 0b00000001, 0b00000100, 0b01001000, 0b00000000}, // Farfetchd
    {0b00000000, 0b00000000, 0b00010000, 0b00000001, 0b00100010, 0b00000100, 0b10000000, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00001000, 0b01110010, 0b10000000, 0b00100000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b01001000, 0b10000101, 0b00000010, 0b01000100, 0b00000000, 0b00010001, 0b00010110, 0b10100000, 0b00001000, 0b00000100, 0b01000000, 0b00000000}, // Doduo
    {0b00000000, 0b00000000, 0b00010000, 0b00000001, 0b00100010, 0b00000100, 0b00000000, 0b00000001, 0b11000000, 0b00000000, 0b00000000, 0b00001000, 0b01010010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b01001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00010110, 0b10100000, 0b00001000, 0b00000100, 0b01000000, 0b00000000}, // Dodrio
    {0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b10101010, 0b00000100, 0b00100000, 0b01110010, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00100001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00011000, 0b00010001, 0b00000110, 0b10110000, 0b00010000, 0b00000100, 0b10000000, 0b00000000}, // Seel
    {0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00101010, 0b00000100, 0b00000000, 0b01110011, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000110, 0b10110000, 0b00000000, 0b00000100, 0b10000000, 0b00000000}, // Dewgong
    {0b01000001, 0b11000000, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00100100, 0b00000000, 0b00000000, 0b00000000, 0b00000101, 0b00011000, 0b00000011, 0b10110000, 0b00100000, 0b00101010, 0b00000000, 0b00010000, 0b00000001, 0b01001000, 0b00001000, 0b10000110, 0b00000010, 0b00001100, 0b00000000, 0b00110001, 0b00001110, 0b10100001, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Grimer
    {0b01000001, 0b11000000, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00100100, 0b00000001, 0b00000010, 0b00000000, 0b00000101, 0b00011000, 0b00000011, 0b10110000, 0b00000000, 0b00001010, 0b00000000, 0b00010000, 0b00000001, 0b01001000, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00000000, 0b00110001, 0b00000110, 0b10100001, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Muk
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01001010, 0b00010000, 0b10000000, 0b01110110, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000011, 0b10000010, 0b10000000, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b01001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000100, 0b00000100, 0b10000000, 0b00000000}, // Shellder
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b10000000, 0b01110011, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000010, 0b10000010, 0b00000000, 0b00000000, 0b01010000, 0b00000000, 0b00000000, 0b01001000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b00000000}, // Cloyster
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00001011, 0b00000110, 0b10000100, 0b00100000, 0b00100000, 0b00000000, 0b00100000, 0b00000100, 0b01001000, 0b00001000, 0b10010110, 0b00001010, 0b00001000, 0b00110000, 0b00110001, 0b00001110, 0b10100000, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Gastly
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00001011, 0b00000110, 0b10000100, 0b00000000, 0b00100000, 0b00000000, 0b00100000, 0b00000000, 0b01001000, 0b00001000, 0b10010110, 0b00001010, 0b00001000, 0b00100000, 0b00110001, 0b00001110, 0b10100000, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Haunter
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00000101, 0b00001011, 0b00000110, 0b10000100, 0b00000010, 0b00100000, 0b00000000, 0b00100000, 0b00000000, 0b01001000, 0b00001000, 0b10010110, 0b00001010, 0b00001000, 0b00100000, 0b00110001, 0b00001110, 0b10100001, 0b00000000, 0b00000100, 0b11001001, 0b01000000}, // Gengar
    {0b00000000, 0b00000000, 0b00001100, 0b00000000, 0b01100010, 0b00000010, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b11011000, 0b00010011, 0b10100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000101, 0b00000010, 0b00000100, 0b00000000, 0b01010001, 0b00000110, 0b10100000, 0b01000001, 0b00000100, 0b01001000, 0b01000000}, // Onix
    {0b01000101, 0b11000000, 0b00000000, 0b01000100, 0b00100010, 0b00000000, 0b00100000, 0b00000000, 0b00001100, 0b00000000, 0b00000010, 0b00001111, 0b10000010, 0b10000000, 0b11010010, 0b00000000, 0b00000000, 0b00110000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110001, 0b00000000, 0b00000100, 0b11001001, 0b10000000}, // Drowzee
    {0b01000101, 0b11000000, 0b00000000, 0b01000100, 0b00100010, 0b00000000, 0b00100000, 0b00000001, 0b00001100, 0b00000000, 0b00000010, 0b00001111, 0b10000010, 0b10000000, 0b01010010, 0b00000000, 0b00000000, 0b00110000, 0b00001000, 0b00001000, 0b00001000, 0b10010100, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110001, 0b00000000, 0b00000100, 0b11001001, 0b10000000}, // Hypno
    {0b00000000, 0b00011011, 0b00000101, 0b00000000, 0b00100010, 0b00010000, 0b00000000, 0b01110000, 0b00000010, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10100000, 0b00100000, 0b00000000, 0b00000100, 0b00000000, 0b01000000, 0b10001000, 0b00001000, 0b10000101, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00100110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b01000000}, // Krabby
    {0b00000000, 0b00011011, 0b00000001, 0b00000000, 0b00100010, 0b00010000, 0b00000000, 0b01110001, 0b00000010, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b10001000, 0b00001000, 0b10000101, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00100110, 0b10100000, 0b00000000, 0b10000100, 0b10000000, 0b01000000}, // Kingler
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b00001000, 0b00000011, 0b10000000, 0b01000000, 0b10000000, 0b01000000, 0b00000000, 0b00001000, 0b01001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010101, 0b01000010, 0b10100000, 0b00000000, 0b00000100, 0b10010000, 0b00000000}, // Voltorb
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b01000000, 0b00000001, 0b00000000, 0b00000000, 0b00000111, 0b00001000, 0b00000011, 0b10000000, 0b01000000, 0b10000000, 0b01000000, 0b00000000, 0b00001000, 0b01001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00010101, 0b01000010, 0b10100000, 0b00000000, 0b00000100, 0b10010000, 0b00000000}, // Electrode
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b01001111, 0b00000000, 0b00001111, 0b00000010, 0b10000000, 0b01010000, 0b00000000, 0b00000000, 0b00101000, 0b00001000, 0b01001000, 0b00001000, 0b10000110, 0b00000010, 0b00001000, 0b00000000, 0b00110101, 0b00000110, 0b10100000, 0b00000000, 0b00011100, 0b01001010, 0b00000000}, // Exeggcute
    {0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000001, 0b00000010, 0b00001000, 0b00000000, 0b00001111, 0b00000010, 0b10000000, 0b01010000, 0b01000000, 0b00000000, 0b00101000, 0b00001000, 0b01001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01001000, 0b00000000}, // Exeggutor
    {0b00000101, 0b01000010, 0b00000000, 0b01000100, 0b00100111, 0b00010100, 0b00000100, 0b00110000, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00010011, 0b10000000, 0b00001000, 0b00000110, 0b00100000, 0b00000000, 0b00000000, 0b00011100, 0b00001000, 0b10000100, 0b00000010, 0b00010100, 0b00011010, 0b01010011, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b01000010, 0b01000000}, // Cubone
    {0b00000101, 0b01000010, 0b00000000, 0b01000100, 0b00100111, 0b00010100, 0b00000100, 0b00110001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00010010, 0b10000000, 0b00001000, 0b00000110, 0b00000000, 0b00000000, 0b00000000, 0b00011100, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00001010, 0b01010011, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b01000000, 0b01000000}, // Marowak
    {0b00000100, 0b00000000, 0b00000000, 0b11110000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b01001000, 0b10000010, 0b10000000, 0b00001010, 0b00000000, 0b01000000, 0b10000000, 0b00000000, 0b00001100, 0b00001000, 0b10100100, 0b00010010, 0b00000100, 0b01000000, 0b00010001, 0b00000110, 0b10100001, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Hitmonlee
    {0b00001101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b01001000, 0b01000010, 0b10000000, 0b00000010, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000011, 0b00000100, 0b00000100, 0b00010001, 0b00000110, 0b10100001, 0b00001000, 0b00000100, 0b11000000, 0b01000000}, // Hitmonchan
    {0b00000101, 0b11000011, 0b00000101, 0b01000000, 0b00110010, 0b00000000, 0b10100100, 0b01110001, 0b00001110, 0b00001000, 0b00000101, 0b01011000, 0b00000011, 0b10000001, 0b00000000, 0b00100010, 0b00000000, 0b00100000, 0b00000000, 0b00001100, 0b00001000, 0b10000110, 0b00000010, 0b00010100, 0b00001000, 0b01010101, 0b00000110, 0b10100011, 0b00000001, 0b00000100, 0b11001001, 0b01000000}, // Lickitung
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000100, 0b00001000, 0b00000000, 0b00000000, 0b00000101, 0b00001000, 0b00000011, 0b10001000, 0b00100000, 0b10011010, 0b00000000, 0b00010000, 0b00001100, 0b01001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00100000, 0b00010101, 0b00000110, 0b10101000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Koffing
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000100, 0b00000001, 0b00000000, 0b00000000, 0b00000101, 0b00001000, 0b00000010, 0b10001000, 0b00100000, 0b10011010, 0b00000000, 0b00010000, 0b00001000, 0b01001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00100000, 0b00010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Weezing
    {0b00000000, 0b00000010, 0b00000001, 0b00000011, 0b10101011, 0b00000010, 0b00000100, 0b00110000, 0b00001010, 0b00000000, 0b00000101, 0b01011000, 0b00000010, 0b10000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000110, 0b00010010, 0b10000100, 0b00001000, 0b01010101, 0b00000110, 0b10100010, 0b10000001, 0b00000100, 0b11100000, 0b01000000}, // Rhyhorn
    {0b00000101, 0b01000011, 0b00000001, 0b01000011, 0b10101011, 0b00000010, 0b00000100, 0b01110001, 0b00001110, 0b00000000, 0b00000101, 0b01011000, 0b00000010, 0b10000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b10000100, 0b00001000, 0b01010101, 0b00100110, 0b10100001, 0b10000001, 0b00000100, 0b11000000, 0b01000000}, // Rhydon
    {0b01010100, 0b00000000, 0b00000000, 0b01000000, 0b00100011, 0b00000101, 0b00000100, 0b00110001, 0b00001110, 0b00001000, 0b00000111, 0b01001010, 0b00000010, 0b10010001, 0b01000010, 0b01000010, 0b00000001, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b01010101, 0b00000111, 0b11110001, 0b00000001, 0b00000100, 0b11001001, 0b01000000}, // Chansey
    {0b00000000, 0b00000011, 0b00001110, 0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b11101111, 0b00000000, 0b00001100, 0b00000010, 0b10000000, 0b00010000, 0b00000000, 0b00001100, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000101, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01001000, 0b01000000}, // Tangela
    {0b00001101, 0b11000001, 0b00000001, 0b01000000, 0b00100011, 0b00011010, 0b00100100, 0b01110001, 0b00001110, 0b00001000, 0b00000101, 0b01011000, 0b00010010, 0b10000000, 0b00001000, 0b00000010, 0b00000000, 0b00000000, 0b00100000, 0b00001100, 0b00001000, 0b10000100, 0b00010010, 0b00000100, 0b01001000, 0b01010001, 0b00100110, 0b10110001, 0b00000001, 0b00000100, 0b11000001, 0b01000000}, // Kangaskhan
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00010000, 0b00100001, 0b11110010, 0b00000000, 0b00000000, 0b00100000, 0b00001000, 0b01000010, 0b10001000, 0b00000000, 0b00000001, 0b01000000, 0b00000000, 0b01000010, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000010, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b01000000, 0b00000101, 0b10000000, 0b00000000}, // Horsea
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00010000, 0b00000001, 0b11110001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10001000, 0b00000000, 0b00000001, 0b01000000, 0b00000000, 0b01000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000101, 0b10000000, 0b00000000}, // Seadra
    {0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b10000011, 0b00000000, 0b10000000, 0b11111000, 0b10000000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10000000, 0b00100000, 0b00000001, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b10000000, 0b00000100, 0b10000000, 0b00000000}, // Goldeen
    {0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b10000011, 0b00000000, 0b10000000, 0b01110001, 0b10000000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10000000, 0b00000000, 0b00000001, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b10000000, 0b00000100, 0b10000000, 0b00000000}, // Seaking
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b00000001, 0b11110100, 0b00000000, 0b00000000, 0b00000111, 0b00001010, 0b00000010, 0b11110000, 0b01010000, 0b00000001, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000010, 0b10100000, 0b00000100, 0b00000100, 0b10001000, 0b00000000}, // Staryu
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000001, 0b01110001, 0b00000000, 0b00000000, 0b00000111, 0b00001010, 0b00000010, 0b11000100, 0b01010000, 0b00000001, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000010, 0b10100000, 0b00000100, 0b00000100, 0b10001000, 0b00000000}, // Starmie
    {0b00010101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00001001, 0b00001100, 0b00001000, 0b00000111, 0b00001111, 0b10000010, 0b10000000, 0b11010010, 0b00000000, 0b00000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10110000, 0b00110000, 0b00000100, 0b11001001, 0b10000000}, // Mr-mime
    {0b00000000, 0b00000111, 0b01000000, 0b00000000, 0b00000010, 0b00010000, 0b00000000, 0b00000001, 0b00001000, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b01001000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00011000, 0b10000100, 0b00010010, 0b00000000, 0b00000000, 0b00010011, 0b00110110, 0b10110000, 0b00101000, 0b00000100, 0b11000000, 0b01000000}, // Scyther
    {0b01010100, 0b10000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00110001, 0b00001100, 0b00000000, 0b00000000, 0b00001010, 0b00000010, 0b10000000, 0b01010010, 0b00100000, 0b00000000, 0b00100010, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000110, 0b00000100, 0b00011000, 0b00010001, 0b00001110, 0b10100001, 0b00000000, 0b00000100, 0b10001001, 0b00000000}, // Jynx
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00010000, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00000111, 0b00001010, 0b00100011, 0b10000000, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Electabuzz
    {0b00000101, 0b01000000, 0b00000000, 0b01000000, 0b00100010, 0b00010000, 0b00001100, 0b00000001, 0b00001110, 0b00000000, 0b00000000, 0b00001010, 0b00000010, 0b10001100, 0b00000000, 0b00010010, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b01000000, 0b01000000}, // Magmar
    {0b00000000, 0b00011011, 0b00001000, 0b00000001, 0b00100010, 0b00000000, 0b00000000, 0b00000001, 0b00100110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10100000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000101, 0b00000010, 0b01000000, 0b00000000, 0b00010011, 0b00100110, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Pinsir
    {0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b01101111, 0b00000000, 0b00000100, 0b01110001, 0b00000010, 0b00001000, 0b00000101, 0b01001000, 0b00010010, 0b10000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b10000000, 0b00001000, 0b01010001, 0b00000110, 0b10100000, 0b00001001, 0b00000100, 0b11000000, 0b01000000}, // Tauros
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Magikarp
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100110, 0b00011010, 0b00000100, 0b11110001, 0b00000010, 0b00000000, 0b00100111, 0b01001000, 0b00000010, 0b10000000, 0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b01010001, 0b00000110, 0b10100000, 0b00000000, 0b00000101, 0b10000000, 0b01000000}, // Gyarados
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10100010, 0b00000111, 0b00000011, 0b11110001, 0b00000010, 0b00000000, 0b00000101, 0b00001010, 0b00000010, 0b10000100, 0b00000000, 0b00000001, 0b00000000, 0b00100000, 0b00000000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00000000, 0b01011000, 0b00010001, 0b00000110, 0b10110000, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Lapras
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Ditto
    {0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01101011, 0b00001100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00100010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000111, 0b00000010, 0b00000100, 0b00000000, 0b00011001, 0b00000110, 0b10100000, 0b00100001, 0b00000100, 0b11000001, 0b00000000}, // Eevee
    {0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01100011, 0b00001010, 0b00000001, 0b11110011, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00100010, 0b10000000, 0b00100000, 0b00000001, 0b01000000, 0b00000000, 0b00000001, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11000001, 0b00000000}, // Vaporeon
    {0b00000000, 0b00000000, 0b00000000, 0b10001000, 0b01100011, 0b00100010, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00001111, 0b00011000, 0b01100010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11000001, 0b00000000}, // Jolteon
    {0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01100011, 0b00011010, 0b00001100, 0b00000001, 0b00000000, 0b00000000, 0b00010000, 0b00011000, 0b00100010, 0b10000000, 0b00000000, 0b00010010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11000001, 0b00000000}, // Flareon
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b00000000, 0b00111001, 0b00000000, 0b00001000, 0b00000111, 0b00001010, 0b01000010, 0b11000000, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001001, 0b11001000, 0b10000100, 0b10000010, 0b00000000, 0b10001001, 0b00010001, 0b00000010, 0b10100000, 0b00000001, 0b00000100, 0b11001001, 0b00000000}, // Porygon
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00100010, 0b00011000, 0b10000001, 0b11110110, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000010, 0b10000010, 0b00100000, 0b00000001, 0b00001000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b00000001, 0b00001000, 0b01010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000010, 0b01000000}, // Omanyte
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00011000, 0b00000001, 0b11110001, 0b00000100, 0b00000000, 0b00000000, 0b00001000, 0b00000010, 0b10000010, 0b00000000, 0b00000001, 0b00011000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00001000, 0b01010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000010, 0b01000000}, // Omastar
    {0b00000000, 0b00100000, 0b00000000, 0b00001000, 0b00100010, 0b00010000, 0b00000000, 0b01110110, 0b00000001, 0b10000000, 0b00000000, 0b00011000, 0b00000010, 0b10100100, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000101, 0b00000010, 0b00000000, 0b00001000, 0b01110101, 0b00000110, 0b10100000, 0b00000100, 0b00000100, 0b10000010, 0b01000000}, // Kabuto
    {0b00000000, 0b00100011, 0b00000000, 0b01001000, 0b00100010, 0b00010000, 0b00000000, 0b01110001, 0b00000101, 0b10000000, 0b00000000, 0b00011000, 0b00000010, 0b10100000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b10000100, 0b00000010, 0b00000000, 0b00001000, 0b01110101, 0b00100110, 0b10100000, 0b00000000, 0b00000100, 0b10000010, 0b01000000}, // Kabutops
    {0b00000000, 0b00000000, 0b01110000, 0b00000000, 0b00001010, 0b00001010, 0b10000100, 0b00000001, 0b00000010, 0b00000000, 0b00000000, 0b01001000, 0b01000010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000110, 0b00000010, 0b10000000, 0b01000000, 0b01010001, 0b00010110, 0b10100000, 0b01001001, 0b00000100, 0b11000010, 0b01000000}, // Aerodactyl
    {0b00000101, 0b11000000, 0b00000000, 0b01000100, 0b01100010, 0b00000000, 0b00000100, 0b01110001, 0b00001110, 0b00001000, 0b00000101, 0b01101010, 0b00000010, 0b10000001, 0b00000010, 0b00100010, 0b00000100, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000110, 0b00000010, 0b00010100, 0b00001000, 0b01011101, 0b00000110, 0b10100001, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Snorlax
    {0b00000000, 0b00000000, 0b10010000, 0b00000000, 0b00000010, 0b00000010, 0b00000010, 0b00110001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10000000, 0b00010000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00100100, 0b00000110, 0b00000100, 0b00001000, 0b01010001, 0b00010010, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Articuno
    {0b00000000, 0b00000000, 0b00010000, 0b00000000, 0b00000010, 0b00000010, 0b00000000, 0b00000001, 0b11000000, 0b00000000, 0b00001111, 0b00001000, 0b01000010, 0b10000000, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000100, 0b01010001, 0b00010010, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Zapdos
    {0b00000000, 0b00000000, 0b01010000, 0b00000000, 0b00000010, 0b00000010, 0b00001100, 0b00000001, 0b00000000, 0b00000000, 0b00010000, 0b00001000, 0b01000010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00000001, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010001, 0b00010010, 0b10110000, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Moltres
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00110010, 0b00010000, 0b10000110, 0b01110001, 0b00000000, 0b00000000, 0b00100111, 0b00001000, 0b01000010, 0b10000000, 0b01100000, 0b00000011, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b10010001, 0b00000110, 0b10110000, 0b01000001, 0b00000101, 0b11000000, 0b00000000}, // Dratini
    {0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00110010, 0b00010000, 0b00000100, 0b01110001, 0b00000000, 0b00000000, 0b00100111, 0b00001000, 0b01000010, 0b10000000, 0b00000000, 0b00000011, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b10010001, 0b00000110, 0b10110000, 0b00000001, 0b00000101, 0b11000000, 0b00000000}, // Dragonair
    {0b00000001, 0b11000001, 0b01010100, 0b00000000, 0b00110010, 0b00010010, 0b00000100, 0b01110001, 0b00000010, 0b00000000, 0b00100111, 0b01001000, 0b01000010, 0b10000000, 0b00000000, 0b00000011, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b11010001, 0b00110110, 0b10110001, 0b00000001, 0b00000101, 0b11000000, 0b01000000}, // Dragonite
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00100110, 0b00110001, 0b00001110, 0b00001000, 0b00000111, 0b01001110, 0b00000010, 0b11000000, 0b11010010, 0b00000010, 0b01000100, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b01010001, 0b00000010, 0b10110001, 0b00000001, 0b00000100, 0b11001001, 0b11000000}, // Mewtwo
    {0b01000101, 0b11000011, 0b00010000, 0b01000000, 0b00100010, 0b00000010, 0b00000100, 0b01110001, 0b00001110, 0b00001000, 0b00000111, 0b01011010, 0b00000010, 0b10000001, 0b01010010, 0b00000011, 0b01000001, 0b00100000, 0b10001000, 0b01001100, 0b00001000, 0b10000100, 0b00000010, 0b00001100, 0b00001000, 0b01110101, 0b00110110, 0b10110001, 0b00000001, 0b00000100, 0b11001011, 0b01000000}, // Mew
    {0b00000000, 0b00000011, 0b00000010, 0b00000000, 0b01100010, 0b00000100, 0b00000000, 0b00000000, 0b00001000, 0b01011100, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b01010000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000100, 0b00000000, 0b00110001, 0b00000110, 0b10110000, 0b00000001, 0b00010100, 0b01000010, 0b00000000}, // Chikorita
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b01100010, 0b00000100, 0b00000000, 0b00000000, 0b00001010, 0b00011100, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b01010000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00110001, 0b00100110, 0b10110000, 0b00000001, 0b00010100, 0b01000000, 0b01000000}, // Bayleef
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b01100010, 0b00000100, 0b00000000, 0b00000001, 0b00001010, 0b00011100, 0b00000000, 0b01001000, 0b00000010, 0b10000000, 0b01010000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00110001, 0b00100110, 0b10110000, 0b00000001, 0b00010100, 0b01000000, 0b01000000}, // Meganium
    {0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b01100110, 0b00010000, 0b00001100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00100010, 0b10001001, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00101000, 0b00001000, 0b00001100, 0b00010010, 0b00000100, 0b01000000, 0b00010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b00000000}, // Cyndaquil
    {0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b01100010, 0b00010010, 0b00001100, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00011000, 0b00100010, 0b10001001, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00100110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Quilava
    {0b00000101, 0b01000001, 0b00000000, 0b01000000, 0b01100010, 0b00010010, 0b00001100, 0b00000001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00100010, 0b10001001, 0b00000000, 0b00000010, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00001100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00100110, 0b10100001, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Typhlosion
    {0b00000100, 0b10100011, 0b00000000, 0b01000000, 0b00100110, 0b00011000, 0b00000001, 0b11110000, 0b00001100, 0b00000000, 0b00000000, 0b00011000, 0b00010011, 0b10000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b00000100, 0b00000010, 0b10000100, 0b00001000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10100010, 0b00000000}, // Totodile
    {0b00000100, 0b10100011, 0b00000000, 0b01000000, 0b00100010, 0b00011010, 0b00000001, 0b11110000, 0b00001110, 0b00000000, 0b00000000, 0b00011000, 0b00010011, 0b10000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b00000100, 0b00000010, 0b10000100, 0b00001000, 0b00010001, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Croconaw
    {0b00000100, 0b10100011, 0b00000000, 0b01000000, 0b00100010, 0b00011010, 0b00000001, 0b11110001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00010011, 0b10000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00011000, 0b00000100, 0b00000010, 0b10000100, 0b00001000, 0b00010001, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Feraligatr
    {0b00000001, 0b11100001, 0b00000100, 0b00000000, 0b00100010, 0b00000000, 0b00000100, 0b01100000, 0b00000000, 0b00001000, 0b00000100, 0b00011000, 0b00100010, 0b10000001, 0b00001000, 0b00000000, 0b01000100, 0b00000000, 0b00000000, 0b00101000, 0b00011000, 0b10000100, 0b00010010, 0b00000100, 0b00000000, 0b00010101, 0b00100110, 0b10100001, 0b00001001, 0b00000100, 0b11000001, 0b00000000}, // Sentret
    {0b00000001, 0b11100001, 0b00000100, 0b00000000, 0b00100010, 0b00000000, 0b00000100, 0b01110001, 0b00000010, 0b00001000, 0b00000101, 0b00011000, 0b00100010, 0b10000001, 0b00000000, 0b00000000, 0b01000100, 0b00000000, 0b00000000, 0b00101000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b11000001, 0b01000000}, // Furret
    {0b00000000, 0b00000000, 0b01110000, 0b00000000, 0b01001010, 0b00000100, 0b10000000, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00001111, 0b00000010, 0b10000000, 0b00010001, 0b00000000, 0b01000000, 0b00100001, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b01000100, 0b01000000, 0b00010001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Hoothoot
    {0b00000000, 0b00000000, 0b00010000, 0b00000000, 0b01001010, 0b00000100, 0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00000000, 0b00001111, 0b00000010, 0b10000000, 0b00010000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b01000000, 0b00010001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Noctowl
    {0b00001100, 0b11000010, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b10000000, 0b00001000, 0b00000000, 0b00001000, 0b00000000, 0b00011000, 0b01000010, 0b10000000, 0b01010100, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00110101, 0b00000110, 0b10110001, 0b00100000, 0b00000100, 0b01000000, 0b00000000}, // Ledyba
    {0b00001100, 0b11000010, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b10000000, 0b00000001, 0b00000000, 0b00001000, 0b00000000, 0b00011000, 0b01000010, 0b10000000, 0b01010000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00110101, 0b00000110, 0b10110001, 0b00100000, 0b00000100, 0b01000000, 0b00000000}, // Ledian
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b10000000, 0b01100000, 0b00001000, 0b00000000, 0b00001000, 0b01000000, 0b00011010, 0b01000110, 0b10000000, 0b00000000, 0b00000000, 0b00001000, 0b00000100, 0b00001000, 0b00101000, 0b00001000, 0b11000100, 0b00000010, 0b10001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00101000, 0b00000100, 0b01000000, 0b00000000}, // Spinarak
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b10000000, 0b00000000, 0b00000001, 0b00000000, 0b00001000, 0b01000000, 0b00011010, 0b01000110, 0b10000000, 0b00000000, 0b00000000, 0b00001000, 0b00000100, 0b00001000, 0b00101000, 0b00001000, 0b11000100, 0b00000010, 0b10001000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b00000000}, // Ariados
    {0b00000000, 0b00000000, 0b01010000, 0b00000000, 0b00000010, 0b00001000, 0b10000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000011, 0b10000100, 0b00100000, 0b00000000, 0b01000000, 0b00000100, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00011110, 0b10100000, 0b00000000, 0b00000100, 0b11000001, 0b00000000}, // Crobat
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00000000, 0b10000001, 0b11110000, 0b00000000, 0b00000000, 0b00000111, 0b00001000, 0b00000011, 0b10000100, 0b00000000, 0b00000001, 0b00000100, 0b00000000, 0b01001000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b01000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b00000000}, // Chinchou
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00000000, 0b10000001, 0b11110001, 0b00000000, 0b00000000, 0b00000111, 0b00001000, 0b00000010, 0b10000100, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b01001000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000000, 0b00000000, 0b00010001, 0b01000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b00000000}, // Lanturn
    {0b00010100, 0b00000000, 0b00000000, 0b01000000, 0b00100011, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00000000, 0b00001111, 0b00001000, 0b00000010, 0b10000001, 0b01000100, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00010010, 0b00100100, 0b00000000, 0b00011101, 0b00000110, 0b11100000, 0b00010001, 0b00000100, 0b10000000, 0b00000000}, // Pichu
    {0b01000100, 0b00000000, 0b00000000, 0b01000000, 0b00100010, 0b00000001, 0b00000100, 0b00000000, 0b00001100, 0b00001000, 0b00000010, 0b00011010, 0b00000010, 0b10000001, 0b01010010, 0b00000010, 0b00000101, 0b00100000, 0b00001010, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00110100, 0b00001000, 0b00011101, 0b00000110, 0b11110000, 0b00010001, 0b00000100, 0b11001001, 0b00000000}, // Cleffa
    {0b01000100, 0b00000000, 0b00000000, 0b01000000, 0b00100010, 0b00000001, 0b00000100, 0b00000000, 0b00001100, 0b00001000, 0b00000010, 0b00011010, 0b00000010, 0b10000001, 0b01010000, 0b00000010, 0b00000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b01100100, 0b00011000, 0b00011101, 0b00000110, 0b11110000, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Igglybuff
    {0b00000100, 0b00000000, 0b00000000, 0b01000000, 0b00100010, 0b00000100, 0b00000100, 0b00000000, 0b10001100, 0b00001000, 0b00000010, 0b00001010, 0b00000010, 0b10000001, 0b01010011, 0b00000010, 0b01000001, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00100100, 0b01000000, 0b00011101, 0b00000110, 0b11110000, 0b00110000, 0b00000100, 0b11001011, 0b11000000}, // Togepi
    {0b00000100, 0b00000000, 0b00010000, 0b01000000, 0b00100010, 0b00000100, 0b00000100, 0b00000001, 0b00001100, 0b00001000, 0b00000010, 0b00001010, 0b00000010, 0b10000001, 0b01010010, 0b00000010, 0b01000001, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00100100, 0b00000000, 0b00011101, 0b00010110, 0b10110000, 0b00110000, 0b00000100, 0b11001011, 0b01000000}, // Togetic
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00010000, 0b00000000, 0b00000000, 0b11000000, 0b00001000, 0b00000010, 0b00001010, 0b00101110, 0b10000100, 0b01110000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b01000000, 0b00000000, 0b00110001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b11001001, 0b10000000}, // Natu
    {0b00000000, 0b00000000, 0b00010000, 0b00000000, 0b00000010, 0b00010000, 0b00000000, 0b00000001, 0b10000000, 0b00001000, 0b00000010, 0b00001010, 0b00001110, 0b10000100, 0b01010000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b00110001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b11001001, 0b10000000}, // Xatu
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01101010, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001111, 0b00001000, 0b00000011, 0b10000001, 0b01010000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00100010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10110000, 0b00000001, 0b00000100, 0b10000000, 0b00000000}, // Mareep
    {0b00000101, 0b01000000, 0b00000000, 0b01000000, 0b01100010, 0b00000100, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00001111, 0b00001000, 0b00000010, 0b10000001, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00100010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Flaaffy
    {0b00000101, 0b01000000, 0b00000000, 0b01000000, 0b01100010, 0b00000100, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00001111, 0b00001000, 0b00000010, 0b10000001, 0b01000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00100010, 0b00000000, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Ampharos
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b00001010, 0b10000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10110000, 0b00000010, 0b00000100, 0b01000000, 0b00000000}, // Bellossom
    {0b00000100, 0b10000000, 0b00000000, 0b01000000, 0b01100011, 0b00000000, 0b10000001, 0b11110100, 0b00000110, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10000001, 0b01000000, 0b00000001, 0b01000100, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00010100, 0b00011000, 0b00010101, 0b00000110, 0b11100001, 0b00000001, 0b00000100, 0b10000000, 0b11000000}, // Marill
    {0b00000100, 0b10000000, 0b00000000, 0b01000000, 0b01100011, 0b00000000, 0b00000001, 0b11110101, 0b00000110, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10000001, 0b00000000, 0b00000001, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b00010101, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Azumarill
    {0b00000101, 0b11000000, 0b00000100, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00011110, 0b00000000, 0b00000000, 0b11011000, 0b00000010, 0b10000001, 0b00000000, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b10000101, 0b00000010, 0b01000100, 0b00000000, 0b01010101, 0b00000110, 0b10100001, 0b00000000, 0b00000100, 0b01001000, 0b01000000}, // Sudowoodo
    {0b00010100, 0b00000000, 0b00000000, 0b01000000, 0b00100010, 0b00000000, 0b00000001, 0b01110001, 0b00001110, 0b00000000, 0b00000000, 0b01011011, 0b00000010, 0b10000001, 0b00000010, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00011000, 0b00010001, 0b00000110, 0b10100001, 0b00000000, 0b00000100, 0b10000000, 0b01000000}, // Politoed
    {0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b01000011, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11001111, 0b00000000, 0b00001100, 0b00000010, 0b10000001, 0b00010000, 0b00000000, 0b00000100, 0b00000000, 0b00001010, 0b00001000, 0b00001000, 0b00000100, 0b00100010, 0b00000000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00010000, 0b00010100, 0b01001000, 0b00000000}, // Hoppip
    {0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b01000011, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11001111, 0b00000000, 0b00001000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00001000, 0b00001000, 0b00000100, 0b00100010, 0b00000000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00010100, 0b01000000, 0b00000000}, // Skiploom
    {0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b01000011, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b11001111, 0b00000000, 0b00001000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00001000, 0b00001000, 0b00000100, 0b00100010, 0b00000000, 0b00000000, 0b00110001, 0b00000110, 0b10100000, 0b00000000, 0b00010100, 0b01000000, 0b00000000}, // Jumpluff
    {0b00010101, 0b11100001, 0b00000100, 0b01001000, 0b00100011, 0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00001000, 0b00000111, 0b00011000, 0b01000011, 0b10000001, 0b00000010, 0b00000000, 0b01000000, 0b00100000, 0b00000000, 0b00101000, 0b00001000, 0b10000100, 0b00001010, 0b00000100, 0b00000000, 0b00010001, 0b00100110, 0b10100001, 0b00101001, 0b00000100, 0b11000001, 0b01010000}, // Aipom
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b11101000, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10110000, 0b00010000, 0b00010100, 0b01000000, 0b00000000}, // Sunkern
    {0b01000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000001, 0b00000001, 0b00111000, 0b10000000, 0b00001000, 0b00000010, 0b10000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001000, 0b00000000, 0b00110001, 0b00000110, 0b10110000, 0b00000000, 0b00000100, 0b01000000, 0b00000000}, // Sunflora
    {0b00000000, 0b00000000, 0b01100000, 0b00000000, 0b01000010, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00001011, 0b00100011, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00100100, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00010010, 0b00000000, 0b01000100, 0b00110001, 0b00010110, 0b10100000, 0b00000000, 0b00000100, 0b01000001, 0b00000000}, // Yanma
    {0b00000000, 0b10000000, 0b00000100, 0b00000000, 0b00100011, 0b00000000, 0b00000011, 0b01110000, 0b00000000, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b00100000, 0b00000001, 0b00000100, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00001100, 0b00000000, 0b01010101, 0b00000110, 0b10110001, 0b00000001, 0b00000100, 0b10000010, 0b01000000}, // Wooper
    {0b00000100, 0b10000000, 0b00000100, 0b01000000, 0b00100011, 0b00000000, 0b00000011, 0b01110001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b00100000, 0b00000001, 0b00000100, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00001100, 0b00000000, 0b01010101, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b10000000, 0b01000000}, // Quagsire
    {0b00000000, 0b00000001, 0b00000000, 0b00001000, 0b01100011, 0b00000000, 0b00000000, 0b00001001, 0b00000000, 0b00000000, 0b00000000, 0b00011110, 0b00100010, 0b10000000, 0b01010000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00100100, 0b11001001, 0b00000000}, // Espeon
    {0b00000000, 0b00000001, 0b00000000, 0b00001000, 0b01100011, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00011010, 0b00100011, 0b10000100, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b01000100, 0b00000000, 0b00010001, 0b00001110, 0b10100000, 0b00001001, 0b00001100, 0b11001001, 0b00000000}, // Umbreon
    {0b00000000, 0b00000000, 0b01110000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b11000000, 0b00000000, 0b00000010, 0b00001000, 0b00000110, 0b10000100, 0b00100001, 0b00000000, 0b01000000, 0b00100001, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b01000100, 0b00011000, 0b00010001, 0b00011110, 0b10100000, 0b00001000, 0b00000100, 0b11001001, 0b00000000}, // Murkrow
    {0b00000100, 0b10000000, 0b00000000, 0b01000100, 0b01100010, 0b00000100, 0b00100101, 0b01110001, 0b00001110, 0b00000000, 0b00000010, 0b01011110, 0b00000010, 0b10000000, 0b00000000, 0b00000010, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000110, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00100110, 0b10110001, 0b00000001, 0b00000100, 0b11001001, 0b01000000}, // Slowking
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000100, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000111, 0b00001010, 0b00000011, 0b10000101, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00001100, 0b00001000, 0b00001000, 0b10000100, 0b00001010, 0b00000000, 0b00110000, 0b00010001, 0b00001110, 0b10101000, 0b00000000, 0b00000100, 0b11001001, 0b00000000}, // Misdreavus
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00000000}, // Unown
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000, 0b00000000, 0b00000000, 0b00010000, 0b00000000, 0b00000000, 0b00010000, 0b00000000}, // Wobbuffet
    {0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b01101010, 0b00000100, 0b00000000, 0b00001000, 0b00000010, 0b00000000, 0b00000111, 0b01001110, 0b01000010, 0b10000000, 0b01010000, 0b00000000, 0b01000100, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b01000000, 0b00010001, 0b00000110, 0b10100000, 0b00100001, 0b00000100, 0b11101001, 0b11010000}, // Girafarig
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01101010, 0b00100000, 0b00000000, 0b00000000, 0b00001010, 0b00001000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b01010100, 0b10000000, 0b01000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000101, 0b00000010, 0b00000001, 0b00000000, 0b01110101, 0b00000110, 0b10100000, 0b00000100, 0b00000100, 0b01000000, 0b01000000}, // Pineco
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01101010, 0b00000000, 0b00000000, 0b00000001, 0b00001010, 0b00001000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b01010100, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b10000000, 0b01110101, 0b00000110, 0b10100000, 0b00000100, 0b00000100, 0b01000000, 0b01000000}, // Forretress
    {0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00101010, 0b00001000, 0b00000100, 0b00110000, 0b00001010, 0b00001000, 0b00000111, 0b01011000, 0b00010011, 0b10000001, 0b00000100, 0b00000010, 0b00000000, 0b01100000, 0b00000000, 0b00001100, 0b00001000, 0b10000111, 0b00001010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10100000, 0b00001001, 0b00000100, 0b11001011, 0b01000000}, // Dunsparce
    {0b00000000, 0b00001111, 0b01000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b00001010, 0b00000000, 0b00000000, 0b01011000, 0b00100011, 0b10100000, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00000000, 0b00001100, 0b00011000, 0b10000100, 0b00000010, 0b01001000, 0b00000000, 0b01010001, 0b00110110, 0b10100000, 0b00000001, 0b10000100, 0b11000000, 0b01000000}, // Gligar
    {0b00000000, 0b00000001, 0b00001100, 0b00000000, 0b01100010, 0b00000010, 0b00000000, 0b00000001, 0b00000010, 0b00000000, 0b00000000, 0b11011000, 0b00010011, 0b10100001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10100000, 0b01000001, 0b00000100, 0b01100000, 0b01000000}, // Steelix
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b01101011, 0b00001010, 0b00000100, 0b00000000, 0b00001110, 0b00001000, 0b00000111, 0b01011000, 0b00010010, 0b10000001, 0b00010010, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b11001100, 0b00000000, 0b00011001, 0b00000111, 0b11100001, 0b00000000, 0b00000100, 0b11100001, 0b01000000}, // Snubbull
    {0b00000101, 0b11000000, 0b00000000, 0b01000000, 0b01101011, 0b00001010, 0b00000100, 0b00000001, 0b00001110, 0b00001000, 0b00000111, 0b01011000, 0b00010010, 0b10000001, 0b00000010, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000100, 0b00000010, 0b10001100, 0b00000000, 0b00011001, 0b00000110, 0b10100001, 0b00000001, 0b00000100, 0b11100001, 0b01000000}, // Granbull
    {0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b01001010, 0b10100000, 0b10000001, 0b11110100, 0b00000000, 0b00000000, 0b00000010, 0b00001000, 0b00000010, 0b10110001, 0b00100000, 0b00000001, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00001001, 0b00101000, 0b00010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000001, 0b00000000}, // Qwilfish
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00010000, 0b00000000, 0b00000001, 0b00001010, 0b00000000, 0b00000000, 0b00001000, 0b01100010, 0b10000000, 0b00001000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00011000, 0b10000100, 0b00000010, 0b00000000, 0b00000000, 0b01010011, 0b00110110, 0b10100000, 0b00001000, 0b10000100, 0b11000000, 0b01000000}, // Scizor
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110010, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000011, 0b00000100, 0b00000000, 0b00001000, 0b00000000, 0b00001000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b00001100, 0b00000000, 0b01010101, 0b00000110, 0b10110000, 0b00010010, 0b00000100, 0b01000000, 0b01000000}, // Shuckle
    {0b00000000, 0b00000011, 0b00000000, 0b00000011, 0b01101010, 0b00010000, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10100000, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b10000101, 0b00010010, 0b00000000, 0b00000000, 0b00010011, 0b00100110, 0b10100000, 0b10000000, 0b00000100, 0b11000000, 0b01000000}, // Heracross
    {0b00000000, 0b10100011, 0b00000000, 0b00000000, 0b00000010, 0b00011000, 0b00000000, 0b01110000, 0b00001010, 0b00000000, 0b00000000, 0b00011000, 0b01100011, 0b10000001, 0b00010000, 0b00000000, 0b01000000, 0b00100000, 0b00000000, 0b00101000, 0b00011000, 0b10000100, 0b00001010, 0b01000100, 0b01001000, 0b00010001, 0b00100110, 0b10100001, 0b00000001, 0b10000100, 0b11001001, 0b01010000}, // Sneasel
    {0b00000101, 0b11100011, 0b00000000, 0b01000000, 0b00101110, 0b00010010, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b00000010, 0b00100000, 0b01000000, 0b00000000, 0b00000000, 0b00101000, 0b00011000, 0b10000100, 0b00000010, 0b01000100, 0b00000000, 0b00010101, 0b00100110, 0b10100001, 0b00000000, 0b10000100, 0b11100000, 0b01000000}, // Teddiursa
    {0b00000101, 0b11100011, 0b00000000, 0b01000000, 0b00100110, 0b00010010, 0b00000000, 0b00000001, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b00000010, 0b00100000, 0b01000000, 0b00000000, 0b00000000, 0b00101100, 0b00011000, 0b10000100, 0b00000010, 0b01000100, 0b00000000, 0b00010101, 0b00100110, 0b10100001, 0b00000000, 0b00000100, 0b11000000, 0b01000000}, // Ursaring
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00001100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10001000, 0b00000010, 0b10100001, 0b01010000, 0b00010010, 0b00000100, 0b00000000, 0b00000001, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b00010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Slugma
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00000000, 0b00001100, 0b00000001, 0b00000010, 0b00000000, 0b00000000, 0b11001000, 0b00000010, 0b10100001, 0b01010000, 0b00010010, 0b00000100, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b01000000, 0b01000000}, // Magcargo
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01101010, 0b00001010, 0b00000010, 0b00110000, 0b00000010, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b01010000, 0b00000000, 0b00000100, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000100, 0b00000110, 0b00000100, 0b00001000, 0b01010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000010, 0b01000000}, // Swinub
    {0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b00101010, 0b00000010, 0b00000010, 0b00110001, 0b00000010, 0b00000000, 0b00000000, 0b01011000, 0b00000010, 0b10000001, 0b01010000, 0b00000000, 0b00000100, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000100, 0b00000110, 0b00000100, 0b00001000, 0b01010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b10000000, 0b01000000}, // Piloswine
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01100010, 0b00000000, 0b00000010, 0b01110100, 0b00000010, 0b00000000, 0b00000000, 0b01011010, 0b00000011, 0b11100101, 0b11010000, 0b00000000, 0b00010100, 0b00000000, 0b01000000, 0b01001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10110000, 0b00000000, 0b00000100, 0b11010011, 0b01000000}, // Corsola
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b10000101, 0b01111111, 0b00000000, 0b00000000, 0b00000010, 0b00001010, 0b00000011, 0b10000001, 0b00101000, 0b00000011, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000110, 0b00000001, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Remoraid
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000101, 0b01111111, 0b00000100, 0b00000000, 0b00000010, 0b00001010, 0b00000010, 0b10000001, 0b00001000, 0b00000011, 0b01001000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00001110, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b11000000, 0b00000000}, // Octillery
    {0b00000100, 0b00000000, 0b00010000, 0b01000000, 0b00100010, 0b00000000, 0b00000000, 0b00110010, 0b00001100, 0b00000000, 0b00000000, 0b00001000, 0b00100010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000000, 0b00000010, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00000110, 0b11100000, 0b00000100, 0b00000100, 0b10000000, 0b10000000}, // Delibird
    {0b00000000, 0b00000000, 0b01000100, 0b00000000, 0b01101010, 0b00000000, 0b10000000, 0b11110100, 0b00000000, 0b00000000, 0b00000000, 0b01001000, 0b01000010, 0b10000100, 0b00100000, 0b00000001, 0b01000000, 0b00000000, 0b01000000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000101, 0b10000000, 0b00000000}, // Mantine
    {0b00000000, 0b00000001, 0b00110000, 0b00001001, 0b00000010, 0b00010010, 0b00000000, 0b00000000, 0b11001000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b00000001, 0b00000000, 0b00001100, 0b00001000, 0b10000110, 0b00000010, 0b00000101, 0b00000000, 0b01010001, 0b00010110, 0b10100000, 0b00001000, 0b00000100, 0b01000000, 0b01000000}, // Skarmory
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00011010, 0b00001100, 0b00000000, 0b00001000, 0b00001000, 0b00010000, 0b00001000, 0b00010010, 0b10000000, 0b00000000, 0b00010010, 0b01000000, 0b00100000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00011010, 0b01001100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00001001, 0b00000100, 0b01100001, 0b01010000}, // Houndour
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00011010, 0b00001100, 0b00000001, 0b00001010, 0b00001000, 0b00000000, 0b00001000, 0b00000010, 0b10000000, 0b00000000, 0b00010010, 0b01000000, 0b00100000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b01001100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b01100001, 0b01000000}, // Houndoom
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100010, 0b00010000, 0b00000001, 0b11110001, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01000010, 0b10001000, 0b00000000, 0b00000001, 0b01000000, 0b00000000, 0b01000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000000, 0b00001000, 0b00010001, 0b00000110, 0b10100000, 0b00000000, 0b00000101, 0b10000000, 0b00000000}, // Kingdra
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01101010, 0b00000110, 0b00000000, 0b00000000, 0b00001010, 0b00000000, 0b00000000, 0b01101000, 0b00000010, 0b10000001, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000101, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b01000010, 0b01000000}, // Phanpy
    {0b00000000, 0b00000000, 0b00000000, 0b00000011, 0b00100010, 0b00000110, 0b00000000, 0b00000001, 0b00001010, 0b00000000, 0b00000000, 0b01001000, 0b00000010, 0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000101, 0b00000010, 0b00000100, 0b00000000, 0b01010101, 0b00000110, 0b10100000, 0b00000101, 0b00000100, 0b01000000, 0b01000000}, // Donphan
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01000010, 0b00000000, 0b00000000, 0b00111001, 0b00000000, 0b00001000, 0b00000111, 0b00001010, 0b01000010, 0b11000001, 0b00000000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b11001000, 0b10000100, 0b10000010, 0b00000000, 0b10001001, 0b00010001, 0b00000010, 0b10100000, 0b00000001, 0b00000100, 0b11001001, 0b00000000}, // Porygon2
    {0b00000000, 0b00000000, 0b00000001, 0b00001000, 0b01101010, 0b00011010, 0b00100000, 0b00000000, 0b00000000, 0b00001000, 0b00000111, 0b01001011, 0b00000010, 0b10000100, 0b01010000, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00001010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000001, 0b00000100, 0b11001001, 0b00000000}, // Stantler
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Smeargle
    {0b00000000, 0b00000000, 0b00000000, 0b01000000, 0b01100010, 0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b01001000, 0b00000010, 0b10000000, 0b00000000, 0b00000000, 0b01000000, 0b10000000, 0b00000000, 0b00001100, 0b00001000, 0b10100100, 0b00000011, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100000, 0b00000100, 0b00000100, 0b11000000, 0b01000000}, // Tyrogue
    {0b00000000, 0b00000000, 0b00000000, 0b01010000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00001110, 0b00000000, 0b00000000, 0b01011000, 0b01100010, 0b10000000, 0b00001000, 0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00001100, 0b00001001, 0b10000100, 0b00000010, 0b00000100, 0b00000100, 0b01010001, 0b00000110, 0b10100000, 0b00001100, 0b00000100, 0b11000000, 0b01000000}, // Hitmontop
    {0b01000100, 0b10000000, 0b00000000, 0b01000000, 0b00100010, 0b00000001, 0b00000000, 0b00110000, 0b00001100, 0b00000000, 0b00000000, 0b00001110, 0b10000010, 0b10000000, 0b01010010, 0b00100000, 0b00000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000110, 0b00100100, 0b00011000, 0b00010001, 0b00001110, 0b10100001, 0b00000000, 0b00000100, 0b10001001, 0b00000000}, // Smoochum
    {0b00100101, 0b11000000, 0b00000000, 0b01010000, 0b00100010, 0b00010000, 0b00000000, 0b00000000, 0b00001100, 0b00000000, 0b00000111, 0b00001010, 0b10100011, 0b10000000, 0b11000000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000000, 0b00000110, 0b10000000, 0b01000000}, // Elekid
    {0b00100101, 0b01000000, 0b00000000, 0b01000000, 0b00100010, 0b00010000, 0b00001100, 0b00000000, 0b00001100, 0b00000000, 0b00000000, 0b00001010, 0b00000011, 0b10001100, 0b10000000, 0b00010010, 0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b10000100, 0b00000010, 0b00000100, 0b00000000, 0b00010001, 0b00000110, 0b10100001, 0b00000001, 0b00000110, 0b01000000, 0b01000000}, // Magby
    {0b00000101, 0b11000000, 0b00000001, 0b01000000, 0b01100010, 0b00000100, 0b00000000, 0b01110001, 0b00001110, 0b00001000, 0b00000111, 0b01001000, 0b00000010, 0b10000001, 0b00000110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000110, 0b00010010, 0b00000100, 0b00001000, 0b01010101, 0b10000111, 0b11100001, 0b00000001, 0b00000100, 0b11001001, 0b01000000}, // Miltank
    {0b01010100, 0b00000000, 0b00000000, 0b01000000, 0b00100011, 0b00000101, 0b00000100, 0b00110001, 0b00001110, 0b00001000, 0b00000111, 0b01001010, 0b00000010, 0b10010001, 0b01000010, 0b01000010, 0b00000001, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b01010101, 0b00000110, 0b10110001, 0b00000001, 0b00000100, 0b11000001, 0b01000000}, // Blissey
    {0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00100010, 0b00011010, 0b00000000, 0b00000001, 0b00000010, 0b00000000, 0b00001111, 0b00011000, 0b00100010, 0b10000000, 0b00010000, 0b00000000, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010001, 0b01000010, 0b10100000, 0b00000001, 0b00000100, 0b11101000, 0b01000000}, // Raikou
    {0b00000000, 0b00000001, 0b00000001, 0b00000000, 0b00100010, 0b00011010, 0b00001100, 0b00000001, 0b00000010, 0b00001000, 0b00010000, 0b00011000, 0b00000010, 0b10000000, 0b00010000, 0b00000010, 0b01000000, 0b00000000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01010001, 0b00000010, 0b10100000, 0b00000001, 0b00000100, 0b11001000, 0b01000000}, // Entei
    {0b00000000, 0b00000001, 0b10000000, 0b00000000, 0b00100010, 0b00011010, 0b00000010, 0b11110111, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00000010, 0b10000000, 0b00010000, 0b00000001, 0b01000000, 0b00000000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00001000, 0b01010001, 0b00000010, 0b10100000, 0b00000001, 0b00000100, 0b11011000, 0b01000000}, // Suicune
    {0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00100110, 0b00011000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b01011000, 0b00000011, 0b10000000, 0b00001000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000110, 0b00000010, 0b10000100, 0b00000000, 0b11010001, 0b00000110, 0b10100000, 0b00001000, 0b00000100, 0b11100010, 0b01000000}, // Larvitar
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100110, 0b00011000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b01011000, 0b00000011, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b10000100, 0b00000000, 0b01010001, 0b00000110, 0b10100000, 0b00000000, 0b00000100, 0b11100000, 0b01000000}, // Pupitar
    {0b00000101, 0b00000001, 0b00000000, 0b01000000, 0b00100110, 0b00011010, 0b00000100, 0b01110001, 0b00001110, 0b00000000, 0b00000111, 0b01011000, 0b00000011, 0b10000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00001100, 0b00001000, 0b00000100, 0b00000010, 0b10000100, 0b00000000, 0b01010001, 0b00100110, 0b10100001, 0b00000001, 0b00000100, 0b11100000, 0b01000000}, // Tyranitar
    {0b00000000, 0b00000000, 0b10110000, 0b00000000, 0b00100010, 0b00000010, 0b00000000, 0b11110001, 0b00000010, 0b00000000, 0b00000111, 0b01001010, 0b00000010, 0b11000000, 0b01010000, 0b00000001, 0b01000000, 0b00100000, 0b00000000, 0b00001000, 0b00001000, 0b00000100, 0b01000010, 0b00000100, 0b00001000, 0b01110001, 0b00010010, 0b10110000, 0b00000001, 0b00000100, 0b11001011, 0b11000000}, // Lugia
    {0b00000000, 0b00000000, 0b10110000, 0b00000000, 0b00000010, 0b00000010, 0b00000100, 0b00000001, 0b00000010, 0b00001000, 0b00000111, 0b01001010, 0b00000010, 0b11000000, 0b01010000, 0b00000010, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00000000, 0b01110001, 0b00010010, 0b10110100, 0b00000000, 0b00000100, 0b11001011, 0b11000000}, // Ho-oh
    {0b00000000, 0b00000011, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b01001000, 0b00000000, 0b00001110, 0b00000010, 0b11000001, 0b01010010, 0b00000000, 0b01000000, 0b00100000, 0b00001000, 0b00001000, 0b00001000, 0b00000100, 0b00000010, 0b00000100, 0b00010000, 0b01110001, 0b00000011, 0b10110000, 0b00100000, 0b00000100, 0b11001011, 0b10000000}, // Celebi
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Treecko
};

#if USE_COMPRESSED_DATA
#else
const u16 gen_1_charsets[4][256]{
    // gen_1_Jpn_char_array
    {
        0x20,
        0x30A4,
        0x30F4,
        0x30A8,
        0x30AA,
        0x30AC,
        0x30AE,
        0x30B0,
        0x30B2,
        0x30B4,
        0x30B6,
        0x30B8,
        0x30BA,
        0x30BC,
        0x30BE,
        0x30C0,
        0x20,
        0x30C5,
        0x30C7,
        0x30C9,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30D0,
        0x30D3,
        0x30D6,
        0x30DC,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30A3,
        0x3042,
        0x3044,
        0x3094,
        0x3048,
        0x304A,
        0x304C,
        0x304E,
        0x3050,
        0x3052,
        0x3054,
        0x3056,
        0x3058,
        0x305A,
        0x305C,
        0x305E,
        0x3060,
        0x3062,
        0x3065,
        0x3067,
        0x3069,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x3070,
        0x3073,
        0x3076,
        0x3079,
        0x307C,
        0x307E,
        0x30D1,
        0x30D4,
        0x30D7,
        0x30DD,
        0x3071,
        0x3074,
        0x3077,
        0x307A,
        0x307D,
        0x307E,
        0x20,
        0x20,
        0x20,
        0x3082,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0xFF1A,
        0x3043,
        0x3045,
        0x300C,
        0x300D,
        0x300E,
        0x300F,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x30A2,
        0x30A4,
        0x30A6,
        0x30A8,
        0x30AA,
        0x30AB,
        0x30AD,
        0x30AF,
        0x30B1,
        0x30B3,
        0x30B5,
        0x30B7,
        0x30B9,
        0x30BB,
        0x30BD,
        0x30BF,
        0x30C1,
        0x30C4,
        0x30C6,
        0x30C8,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30CF,
        0x30D2,
        0x30D5,
        0x30DB,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30E1,
        0x30E2,
        0x30E4,
        0x30E6,
        0x30E8,
        0x30E9,
        0x30EB,
        0x30EC,
        0x30ED,
        0x30EF,
        0x30F2,
        0x30F3,
        0x30C3,
        0x30E3,
        0x30E5,
        0x30E7,
        0x30A3,
        0x3042,
        0x3044,
        0x3046,
        0x3048,
        0x304A,
        0x304B,
        0x304D,
        0x304F,
        0x3051,
        0x3053,
        0x3055,
        0x3057,
        0x3059,
        0x305B,
        0x305D,
        0x20,
        0x3061,
        0x3064,
        0x3066,
        0x3068,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x306F,
        0x3072,
        0x3075,
        0x3078,
        0x307B,
        0x307E,
        0x307F,
        0x3080,
        0x3081,
        0x3082,
        0x3084,
        0x3086,
        0x3088,
        0x3089,
        0x30EA,
        0x308B,
        0x308C,
        0x308D,
        0x308F,
        0x3092,
        0x3093,
        0x3063,
        0x3083,
        0x50,
        0x4D,
        0x30FC,
        0x309C,
        0x309B,
        0x3F,
        0x21,
        0x3002,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x5186,
        0xD7,
        0x2E,
        0x2F,
        0x30A9,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_1_Eng_char_array
    {
        0x2400,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x2018,
        0x2019,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x2554,
        0x2550,
        0x2557,
        0x2551,
        0x255A,
        0x255D,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE9,
        0x64,
        0x6C,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x72,
        0x6D,
        0x3F,
        0x21,
        0x2E,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_1_FreGer_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x2018,
        0x2019,
        0x201C,
        0x201D,
        0x30FB,
        0x22EF,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xDF,
        0xE7,
        0x20,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xEB,
        0xEF,
        0xE2,
        0xF4,
        0xFB,
        0xEA,
        0xEE,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x63,
        0x64,
        0x6A,
        0x6C,
        0x6D,
        0x6E,
        0x70,
        0x73,
        0x73,
        0x74,
        0x75,
        0x79,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x2B,
        0x20,
        0x3F,
        0x21,
        0x2E,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_1_ItaSpa_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x2018,
        0x2019,
        0x201C,
        0x201D,
        0x30FB,
        0x22EF,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xC0,
        0xC1,
        0x20,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xC8,
        0xC9,
        0xCC,
        0xCD,
        0xD1,
        0xD2,
        0xD3,
        0xD9,
        0xDA,
        0xE1,
        0xEC,
        0xED,
        0xF1,
        0xF2,
        0xF3,
        0xFA,
        0xBA,
        0x26,
        0x64,
        0x6C,
        0x6D,
        0x72,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0xBF,
        0xA1,
        0x3F,
        0x21,
        0x2E,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    }};
const u16 gen_2_charsets[4][256]{
    // gen_2_Jpn_char_array
    {
        0x3F,
        0x30A4,
        0x30F4,
        0x30A8,
        0x30AA,
        0x30AC,
        0x30AE,
        0x30B0,
        0x30B2,
        0x30B4,
        0x30B6,
        0x30B8,
        0x30BA,
        0x30BC,
        0x30BE,
        0x30C0,
        0x30C2,
        0x30C5,
        0x30C7,
        0x30C9,
        0x2A,
        0x2A,
        0x2A,
        0x30CD,
        0x30CE,
        0x30D0,
        0x30D3,
        0x30D6,
        0x30DC,
        0x2A,
        0x2A,
        0x2A,
        0x30A3,
        0x3042,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x304C,
        0x304E,
        0x3050,
        0x3052,
        0x3054,
        0x3056,
        0x3058,
        0x305A,
        0x305C,
        0x305E,
        0x3060,
        0x3062,
        0x3065,
        0x3067,
        0x3069,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x3070,
        0x3073,
        0x3076,
        0x3079,
        0x307C,
        0x2A,
        0x30D1,
        0x30D4,
        0x30D7,
        0x30DD,
        0x3071,
        0x3074,
        0x3077,
        0x307A,
        0x307D,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x3082,
        0x2A,
        0x2A,
        0x19E,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x20,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x300C,
        0x300D,
        0x300E,
        0x300F,
        0x30FB,
        0x22EF,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x30A2,
        0x30A4,
        0x30A6,
        0x30A8,
        0x30AA,
        0x30AB,
        0x30AD,
        0x30AF,
        0x30B1,
        0x30B3,
        0x30B5,
        0x30B7,
        0x30B9,
        0x30BB,
        0x30BD,
        0x30BF,
        0x30C1,
        0x30C4,
        0x30C6,
        0x30C8,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30CF,
        0x30D2,
        0x30D5,
        0x30DB,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30E1,
        0x30E2,
        0x30E4,
        0x30E6,
        0x30E8,
        0x30E9,
        0x30EB,
        0x30EC,
        0x30ED,
        0x30EF,
        0x30F2,
        0x30F3,
        0x30C3,
        0x30E3,
        0x30E5,
        0x30E7,
        0x30A3,
        0x3042,
        0x3044,
        0x3046,
        0x3048,
        0x304A,
        0x304B,
        0x304D,
        0x304F,
        0x3051,
        0x3053,
        0x3055,
        0x3057,
        0x3059,
        0x305B,
        0x305D,
        0x305F,
        0x3061,
        0x3064,
        0x3066,
        0x3068,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x306F,
        0x3072,
        0x3075,
        0x3078,
        0x307B,
        0x307E,
        0x307F,
        0x3080,
        0x3081,
        0x3082,
        0x3084,
        0x3086,
        0x3088,
        0x3089,
        0x30EA,
        0x308B,
        0x308C,
        0x308D,
        0x308F,
        0x3092,
        0x3093,
        0x3063,
        0x3083,
        0x3085,
        0x3087,
        0x30FC,
        0x309C,
        0x309B,
        0x3F,
        0x21,
        0x3002,
        0x30A1,
        0x30A5,
        0x30A7,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x5186,
        0xD7,
        0x2E,
        0x2F,
        0x30A9,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_2_Eng_char_array
    {
        0x3F,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x20,
        0x20,
        0x20,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x20,
        0x71,
        0x72,
        0x20,
        0x20,
        0x20,
        0x20,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x72,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2588,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x50,
        0x4B,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x2550,
        0x2557,
        0x2551,
        0x255A,
        0x255D,
        0x2420,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x64,
        0x6C,
        0x6D,
        0x72,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xD83E,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x20,
        0x20,
        0x3F,
        0x21,
        0x2E,
        0x26,
        0xE9,
        0xD83E,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_2_FreGer_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x50,
        0x4B,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xDF,
        0xE7,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xEB,
        0xEF,
        0xE2,
        0xF4,
        0xFB,
        0xEA,
        0xEE,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x63,
        0x64,
        0x6A,
        0x6C,
        0x6D,
        0x6E,
        0x70,
        0x73,
        0x73,
        0x74,
        0x75,
        0x79,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0x2B,
        0x20,
        0x3F,
        0x21,
        0x2E,
        0x26,
        0xE9,
        0x20,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    },
    // gen_2_ItaSpa_char_array
    {
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x19E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x25B2,
        0x20,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x56,
        0x53,
        0x4C,
        0x4D,
        0x3A,
        0x3043,
        0x3045,
        0x50,
        0x4B,
        0x201C,
        0x201D,
        0x30FB,
        0x2026,
        0x3041,
        0x3047,
        0x3049,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x28,
        0x29,
        0x3A,
        0x3B,
        0x28,
        0x29,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0xE0,
        0xE8,
        0xE9,
        0xF9,
        0xC0,
        0xC1,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0xC8,
        0xC9,
        0xCC,
        0xCD,
        0xD1,
        0xD2,
        0xD3,
        0xD9,
        0xDA,
        0xE1,
        0xEC,
        0xED,
        0xF1,
        0xF2,
        0xF3,
        0xFA,
        0xBA,
        0x26,
        0x64,
        0x6C,
        0x6D,
        0x72,
        0x73,
        0x74,
        0x76,
        0x20,
        0x20,
        0x50,
        0x4D,
        0x2D,
        0xBF,
        0xA1,
        0x3F,
        0x21,
        0x2E,
        0x26,
        0xE9,
        0x20,
        0x25B7,
        0x25B6,
        0x25BC,
        0x2642,
        0x20,
        0xD7,
        0x2E,
        0x2F,
        0x2C,
        0x2640,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
    }};
const u16 gen_3_charsets[2][256]{
    // gen_3_Jpn_char_array
    {
        0x20,
        0x3042,
        0x3044,
        0x3046,
        0x3048,
        0x304A,
        0x304B,
        0x304D,
        0x304F,
        0x3051,
        0x3053,
        0x3055,
        0x3057,
        0x3059,
        0x305B,
        0x305D,
        0x305F,
        0x3061,
        0x3064,
        0x3066,
        0x3068,
        0x306A,
        0x306B,
        0x306C,
        0x306D,
        0x306E,
        0x306F,
        0x3072,
        0x3075,
        0x3078,
        0x307B,
        0x307E,
        0x307F,
        0x3080,
        0x3081,
        0x3082,
        0x3084,
        0x3086,
        0x3088,
        0x3089,
        0x308A,
        0x308B,
        0x308C,
        0x308D,
        0x308F,
        0x3092,
        0x3093,
        0x3041,
        0x3043,
        0x3045,
        0x3047,
        0x3049,
        0x3083,
        0x3085,
        0x3087,
        0x304C,
        0x304E,
        0x3050,
        0x3052,
        0x3054,
        0x3056,
        0x3058,
        0x305A,
        0x305C,
        0x305E,
        0x3060,
        0x3062,
        0x3065,
        0x3067,
        0x3069,
        0x3070,
        0x3073,
        0x3076,
        0x3079,
        0x307C,
        0x3071,
        0x3074,
        0x3077,
        0x307A,
        0x307D,
        0x3063,
        0x30A2,
        0x30A4,
        0x30A6,
        0x30A8,
        0x30AA,
        0x30AB,
        0x30AD,
        0x30AF,
        0x30B1,
        0x30B3,
        0x30B5,
        0x30B7,
        0x30B9,
        0x30BB,
        0x30BD,
        0x30BF,
        0x30C1,
        0x30C4,
        0x30C6,
        0x30C8,
        0x30CA,
        0x30CB,
        0x30CC,
        0x30CD,
        0x30CE,
        0x30CF,
        0x30D2,
        0x30D5,
        0x30D8,
        0x30DB,
        0x30DE,
        0x30DF,
        0x30E0,
        0x30E1,
        0x30E2,
        0x30E4,
        0x30E6,
        0x30E8,
        0x30E9,
        0x30EA,
        0x20,
        0x30EC,
        0x30ED,
        0x30EF,
        0x30F2,
        0x30F3,
        0x30A1,
        0x30A3,
        0x30A5,
        0x30A7,
        0x30A9,
        0x30E3,
        0x30E5,
        0x30E7,
        0x30AC,
        0x30AE,
        0x30B0,
        0x30B2,
        0x30B4,
        0x30B6,
        0x30B8,
        0x30BA,
        0x30BC,
        0x30BE,
        0x30C0,
        0x30C2,
        0x30C5,
        0x30C7,
        0x30C9,
        0x30D0,
        0x30D3,
        0x30D6,
        0x30D9,
        0x30DC,
        0x30D1,
        0x30D4,
        0x30D7,
        0x30DA,
        0x30DD,
        0x30C3,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
        0xFF01,
        0xFF1F,
        0x3002,
        0x30FC,
        0x30FB,
        0x30FB,
        0x300E,
        0x300F,
        0x300C,
        0x300D,
        0x2642,
        0x2640,
        0x5186,
        0x2E,
        0xD7,
        0x2F,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x25B6,
        0x3A,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0x2B06,
        0x2B07,
        0x2B05,
        0x15E,
        0x23C,
        0x206,
        0x1B2,
        0x147,
        0x19E,
    },
    // gen_3_Intern_char_array
    {
        0x20,
        0xC0,
        0xC1,
        0xC2,
        0xC7,
        0xC8,
        0xC9,
        0xCA,
        0xCB,
        0xCC,
        0x20,
        0xCE,
        0xCF,
        0xD2,
        0xD3,
        0xD4,
        0x152,
        0xD9,
        0xDA,
        0xDB,
        0xD1,
        0xDF,
        0xE0,
        0xE1,
        0x20,
        0xE7,
        0xE8,
        0xE9,
        0xEA,
        0xEB,
        0xEC,
        0x20,
        0xEE,
        0xEF,
        0xF2,
        0xF3,
        0xF4,
        0x153,
        0xF9,
        0xFA,
        0xFB,
        0xF1,
        0xBA,
        0xAA,
        0x1D49,
        0x26,
        0x2B,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x3D,
        0x3B,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x25AF,
        0xBF,
        0xA1,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xCD,
        0x25,
        0x28,
        0x29,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xE2,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0xED,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2B07,
        0x2B05,
        0x27A1,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x2A,
        0x1D49,
        0x3C,
        0x3E,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x20,
        0x2B3,
        0x30,
        0x31,
        0x32,
        0x33,
        0x34,
        0x35,
        0x36,
        0x37,
        0x38,
        0x39,
        0x21,
        0x3F,
        0x2E,
        0x2D,
        0x30FB,
        0x2026,
        0x201C,
        0x201D,
        0x2018,
        0x2019,
        0x2642,
        0x2640,
        0x20,
        0x2C,
        0xD7,
        0x2F,
        0x41,
        0x42,
        0x43,
        0x44,
        0x45,
        0x46,
        0x47,
        0x48,
        0x49,
        0x4A,
        0x4B,
        0x4C,
        0x4D,
        0x4E,
        0x4F,
        0x50,
        0x51,
        0x52,
        0x53,
        0x54,
        0x55,
        0x56,
        0x57,
        0x58,
        0x59,
        0x5A,
        0x61,
        0x62,
        0x63,
        0x64,
        0x65,
        0x66,
        0x67,
        0x68,
        0x69,
        0x6A,
        0x6B,
        0x6C,
        0x6D,
        0x6E,
        0x6F,
        0x70,
        0x71,
        0x72,
        0x73,
        0x74,
        0x75,
        0x76,
        0x77,
        0x78,
        0x79,
        0x7A,
        0x25B6,
        0x3A,
        0xC4,
        0xD6,
        0xDC,
        0xE4,
        0xF6,
        0xFC,
        0x20,
        0x20,
        0x20,
        0x15E,
        0x23C,
        0x206,
        0x1B2,
        0x147,
        0x19E,
    }};
#endif

static void load_table(u8 *table, const u8 *source, bool &loadedBool)
{
    if (loadedBool)
    {
        return;
    }
#if USE_COMPRESSED_DATA
    LZ77UnCompWram(source, table);
#endif
    loadedBool = true;
}

PokemonTables::PokemonTables()
    : exp_groups_loaded(false), gender_ratios_loaded(false), num_abilities_loaded(false), first_moves_loaded(false), power_points_loaded(false), event_pkmn_loaded(false), types_loaded(false), input_charset_type(0), gen3_charset_type(0)
{
}

void PokemonTables::load_exp_groups()
{
#if USE_COMPRESSED_DATA
    load_table(EXP_GROUPS, EXP_GROUPS_lz10_bin, exp_groups_loaded);
#endif
}

void PokemonTables::load_gender_ratios()
{
#if USE_COMPRESSED_DATA
    load_table(GENDER_RATIO, GENDER_RATIO_lz10_bin, gender_ratios_loaded);
#endif
}

void PokemonTables::load_num_abilities()
{
#if USE_COMPRESSED_DATA
    load_table((uint8_t *)NUM_ABILITIES, NUM_ABILITIES_lz10_bin, num_abilities_loaded);
#endif
}

void PokemonTables::load_first_moves()
{
#if USE_COMPRESSED_DATA
    load_table(FIRST_MOVES, FIRST_MOVES_lz10_bin, first_moves_loaded);
#endif
}

void PokemonTables::load_power_points()
{
#if USE_COMPRESSED_DATA
    load_table(POWER_POINTS, POWER_POINTS_lz10_bin, power_points_loaded);
#endif
}

void PokemonTables::load_event_pkmn()
{
#if USE_COMPRESSED_DATA
    load_table((uint8_t *)EVENT_PKMN, EVENT_PKMN_lz10_bin, event_pkmn_loaded);
#endif
}

void PokemonTables::load_types()
{
#if USE_COMPRESSED_DATA
    load_table((uint8_t *)TYPES, TYPES_lz10_bin, types_loaded);
#endif
}

void PokemonTables::load_input_charset(byte gen, Language lang)
{
    const u8 desired_charset = (gen << 4) | (lang);
    if (input_charset_type == desired_charset)
    {
        return;
    }
    load_localized_charset(input_charset, gen, lang);
    input_charset_type = desired_charset;
}

void PokemonTables::load_gen3_charset(Language lang)
{
    // transform lang into the value that would get stored in gen3_charset_index
    if (lang == KOREAN)
    {
        lang = JAPANESE;
    }
    else if (lang != JAPANESE)
    {
        lang = ENGLISH;
    }

    if (gen3_charset_type == lang)
    {
        return;
    }

    load_localized_charset(gen3_charset, 3, lang);
    gen3_charset_type = lang;
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
    if (index_num == 0x115) // Hardcode Treecko - dumb, but it works
    {
        return 0; // Treecko only has one ability;
    }
    load_num_abilities();
    return NUM_ABILITIES[index_num];
}

bool PokemonTables::can_learn_move(int pkmn_index, int move_index)
{
    if (move_index == 0)
    {
        return false;
    }
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
static const u8 localization_charset_indices[]{
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

void load_localized_charset(u16 *output_char_array, byte gen, Language lang)
{
    u8 generation_charsets[2048];
    const u8 *input_data;
    // in the localization_charset_indices list,
    // gen 1 starts first and every gen has 7 entries (1 per language)
    // however, the language values are 1-based, so we need to convert to 0-based
    const u8 lang_index = localization_charset_indices[(gen - 1) * 7 + (lang - 1)];

#if USE_COMPRESSED_DATA
    switch (gen)
    {
    case 1:
        input_data = gen_1_charsets_lz10_bin;
        break;
    case 2:
        input_data = gen_2_charsets_lz10_bin;
        break;
    case 3:
        input_data = gen_3_charsets_lz10_bin;
        break;
    default:
        // Invalid generation, return without doing anything
        return;
    }

    LZ77UnCompWram(input_data, generation_charsets);
#else
    switch (gen)
    {
    case 1:
        memcpy(generation_charsets, gen_1_charsets, 4 * 256);
        break;
    case 2:
        memcpy(generation_charsets, gen_2_charsets, 4 * 256);
        break;
    case 3:
        memcpy(generation_charsets, gen_3_charsets, 4 * 256);
        break;
    default:
        // Invalid generation, return without doing anything
        return;
    }

#endif

    memcpy(output_char_array, generation_charsets + (lang_index * 256 * sizeof(u16)), 256 * sizeof(u16)); // copy the charset into the output array
}

byte get_char_from_charset(const u16 *charset, u16 input_char)
{
    u16 i = 0;
    while (i < 256)
    {
        if (charset[i] == input_char)
        {
            return i;
        }
        ++i;
    }
    return 0;
}