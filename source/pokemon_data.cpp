#include "pokemon_data.h"
#include <tonc.h>

const u32 EXP_TYPES[6] = {
    fast_max,
    med_fast_max,
    med_slow_max,
    slow_max};

const int GENDER_THRESHOLDS[2][8]{
    {-1, 2, 4, 8, 12, 14, -1, -1},
    {-1, 31, 63, 127, 191, 225, -1, -1}};

u32 get_max_exp(int index_num)
{
    return EXP_TYPES[EXP_MAX[index_num - 1]];
};

u8 get_gender_threshold(int index_num, bool is_gen_3)
{
    return GENDER_THRESHOLDS[is_gen_3][GENDER_RATIO[index_num - 1]];
};

// If the Pokemon has two abilities it returns a 1, since ability 1 is valid. Otherwise it returns 0
bool get_num_abilities(int index_num)
{
    return NUM_ABILITIES[index_num - 1];
};

bool can_learn_move(int pkmn_index, int move_index)
{
    byte data_byte = MOVESETS[pkmn_index - 1][move_index / 8];
    return (data_byte >> (move_index % 8)) & 0x1;
}

byte get_earliest_move(int index_num)
{
    return FIRST_MOVES[index_num - 1];
}

const u8 EXP_MAX[251] = {
    2, // Bulbasaur
    2, // Ivysaur
    2, // Venusaur
    2, // Charmander
    2, // Charmeleon
    2, // Charizard
    2, // Squirtle
    2, // Wartortle
    2, // Blastoise
    1, // Caterpie
    1, // Metapod
    1, // Butterfree
    1, // Weedle
    1, // Kakuna
    1, // Beedrill
    2, // Pidgey
    2, // Pidgeotto
    2, // Pidgeot
    1, // Rattata
    1, // Raticate
    1, // Spearow
    1, // Fearow
    1, // Ekans
    1, // Arbok
    1, // Pikachu
    1, // Raichu
    1, // Sandshrew
    1, // Sandslash
    2, // Nidoran♀
    2, // Nidorina
    2, // Nidoqueen
    2, // Nidoran♂
    2, // Nidorino
    2, // Nidoking
    0, // Clefairy
    0, // Clefable
    1, // Vulpix
    1, // Ninetales
    0, // Jigglypuff
    0, // Wigglytuff
    1, // Zubat
    1, // Golbat
    2, // Oddish
    2, // Gloom
    2, // Vileplume
    1, // Paras
    1, // Parasect
    1, // Venonat
    1, // Venomoth
    1, // Diglett
    1, // Dugtrio
    1, // Meowth
    1, // Persian
    1, // Psyduck
    1, // Golduck
    1, // Mankey
    1, // Primeape
    3, // Growlithe
    3, // Arcanine
    2, // Poliwag
    2, // Poliwhirl
    2, // Poliwrath
    2, // Abra
    2, // Kadabra
    2, // Alakazam
    2, // Machop
    2, // Machoke
    2, // Machamp
    2, // Bellsprout
    2, // Weepinbell
    2, // Victreebel
    3, // Tentacool
    3, // Tentacruel
    2, // Geodude
    2, // Graveler
    2, // Golem
    1, // Ponyta
    1, // Rapidash
    1, // Slowpoke
    1, // Slowbro
    1, // Magnemite
    1, // Magneton
    1, // Farfetch'd
    1, // Doduo
    1, // Dodrio
    1, // Seel
    1, // Dewgong
    1, // Grimer
    1, // Muk
    3, // Shellder
    3, // Cloyster
    2, // Gastly
    2, // Haunter
    2, // Gengar
    1, // Onix
    1, // Drowzee
    1, // Hypno
    1, // Krabby
    1, // Kingler
    1, // Voltorb
    1, // Electrode
    3, // Exeggcute
    3, // Exeggutor
    1, // Cubone
    1, // Marowak
    1, // Hitmonlee
    1, // Hitmonchan
    1, // Lickitung
    1, // Koffing
    1, // Weezing
    3, // Rhyhorn
    3, // Rhydon
    0, // Chansey
    1, // Tangela
    1, // Kangaskhan
    1, // Horsea
    1, // Seadra
    1, // Goldeen
    1, // Seaking
    3, // Staryu
    3, // Starmie
    1, // Mr. Mime
    1, // Scyther
    1, // Jynx
    1, // Electabuzz
    1, // Magmar
    3, // Pinsir
    3, // Tauros
    3, // Magikarp
    3, // Gyarados
    3, // Lapras
    1, // Ditto
    1, // Eevee
    1, // Vaporeon
    1, // Jolteon
    1, // Flareon
    1, // Porygon
    1, // Omanyte
    1, // Omastar
    1, // Kabuto
    1, // Kabutops
    3, // Aerodactyl
    3, // Snorlax
    3, // Articuno
    3, // Zapdos
    3, // Moltres
    3, // Dratini
    3, // Dragonair
    3, // Dragonite
    3, // Mewtwo
    2, // Mew
    2, // Chikorita
    2, // Bayleef
    2, // Meganium
    2, // Cyndaquil
    2, // Quilava
    2, // Typhlosion
    2, // Totodile
    2, // Croconaw
    2, // Feraligatr
    1, // Sentret
    1, // Furret
    1, // Hoothoot
    1, // Noctowl
    0, // Ledyba
    0, // Ledian
    0, // Spinarak
    0, // Ariados
    1, // Crobat
    3, // Chinchou
    3, // Lanturn
    1, // Pichu
    0, // Cleffa
    0, // Igglybuff
    0, // Togepi
    0, // Togetic
    1, // Natu
    1, // Xatu
    2, // Mareep
    2, // Flaaffy
    2, // Ampharos
    2, // Bellossom
    0, // Marill
    0, // Azumarill
    1, // Sudowoodo
    2, // Politoed
    2, // Hoppip
    2, // Skiploom
    2, // Jumpluff
    0, // Aipom
    2, // Sunkern
    2, // Sunflora
    1, // Yanma
    1, // Wooper
    1, // Quagsire
    1, // Espeon
    1, // Umbreon
    2, // Murkrow
    1, // Slowking
    0, // Misdreavus
    1, // Unown
    1, // Wobbuffet
    1, // Girafarig
    1, // Pineco
    1, // Forretress
    1, // Dunsparce
    2, // Gligar
    1, // Steelix
    0, // Snubbull
    0, // Granbull
    1, // Qwilfish
    1, // Scizor
    2, // Shuckle
    3, // Heracross
    2, // Sneasel
    1, // Teddiursa
    1, // Ursaring
    1, // Slugma
    1, // Magcargo
    3, // Swinub
    3, // Piloswine
    0, // Corsola
    1, // Remoraid
    1, // Octillery
    0, // Delibird
    3, // Mantine
    3, // Skarmory
    3, // Houndour
    3, // Houndoom
    1, // Kingdra
    1, // Phanpy
    1, // Donphan
    1, // Porygon2
    3, // Stantler
    0, // Smeargle
    1, // Tyrogue
    1, // Hitmontop
    1, // Smoochum
    1, // Elekid
    1, // Magby
    3, // Miltank
    0, // Blissey
    3, // Raikou
    3, // Entei
    3, // Suicune
    3, // Larvitar
    3, // Pupitar
    3, // Tyranitar
    3, // Lugia
    3, // Ho-Oh
    2, // Celebi
};
const u8 GENDER_RATIO[251] = {
    1, // Bulbasaur         [1♀:7♂]
    1, // Ivysaur           [1♀:7♂]
    1, // Venusaur          [1♀:7♂]
    1, // Charmander        [1♀:7♂]
    1, // Charmeleon        [1♀:7♂]
    1, // Charizard         [1♀:7♂]
    1, // Squirtle          [1♀:7♂]
    1, // Wartortle         [1♀:7♂]
    1, // Blastoise         [1♀:7♂]
    3, // Caterpie          [1♀:1♂]
    3, // Metapod           [1♀:1♂]
    3, // Butterfree        [1♀:1♂]
    3, // Weedle            [1♀:1♂]
    3, // Kakuna            [1♀:1♂]
    3, // Beedrill          [1♀:1♂]
    3, // Pidgey            [1♀:1♂]
    3, // Pidgeotto         [1♀:1♂]
    3, // Pidgeot           [1♀:1♂]
    3, // Rattata           [1♀:1♂]
    3, // Raticate          [1♀:1♂]
    3, // Spearow           [1♀:1♂]
    3, // Fearow            [1♀:1♂]
    3, // Ekans             [1♀:1♂]
    3, // Arbok             [1♀:1♂]
    3, // Pikachu           [1♀:1♂]
    3, // Raichu            [1♀:1♂]
    3, // Sandshrew         [1♀:1♂]
    3, // Sandslash         [1♀:1♂]
    6, // Nidoran♀          [Female Only]
    6, // Nidorina          [Female Only]
    6, // Nidoqueen         [Female Only]
    0, // Nidoran♂          [Male Only]
    0, // Nidorino          [Male Only]
    0, // Nidoking          [Male Only]
    4, // Clefairy          [3♀:1♂]
    4, // Clefable          [3♀:1♂]
    4, // Vulpix            [3♀:1♂]
    4, // Ninetales         [3♀:1♂]
    4, // Jigglypuff        [3♀:1♂]
    4, // Wigglytuff        [3♀:1♂]
    3, // Zubat             [1♀:1♂]
    3, // Golbat            [1♀:1♂]
    3, // Oddish            [1♀:1♂]
    3, // Gloom             [1♀:1♂]
    3, // Vileplume         [1♀:1♂]
    3, // Paras             [1♀:1♂]
    3, // Parasect          [1♀:1♂]
    3, // Venonat           [1♀:1♂]
    3, // Venomoth          [1♀:1♂]
    3, // Diglett           [1♀:1♂]
    3, // Dugtrio           [1♀:1♂]
    3, // Meowth            [1♀:1♂]
    3, // Persian           [1♀:1♂]
    3, // Psyduck           [1♀:1♂]
    3, // Golduck           [1♀:1♂]
    3, // Mankey            [1♀:1♂]
    3, // Primeape          [1♀:1♂]
    2, // Growlithe         [1♀:3♂]
    2, // Arcanine          [1♀:3♂]
    3, // Poliwag           [1♀:1♂]
    3, // Poliwhirl         [1♀:1♂]
    3, // Poliwrath         [1♀:1♂]
    2, // Abra              [1♀:3♂]
    2, // Kadabra           [1♀:3♂]
    2, // Alakazam          [1♀:3♂]
    2, // Machop            [1♀:3♂]
    2, // Machoke           [1♀:3♂]
    2, // Machamp           [1♀:3♂]
    3, // Bellsprout        [1♀:1♂]
    3, // Weepinbell        [1♀:1♂]
    3, // Victreebel        [1♀:1♂]
    3, // Tentacool         [1♀:1♂]
    3, // Tentacruel        [1♀:1♂]
    3, // Geodude           [1♀:1♂]
    3, // Graveler          [1♀:1♂]
    3, // Golem             [1♀:1♂]
    3, // Ponyta            [1♀:1♂]
    3, // Rapidash          [1♀:1♂]
    3, // Slowpoke          [1♀:1♂]
    3, // Slowbro           [1♀:1♂]
    7, // Magnemite         [Gender Unknown]
    7, // Magneton          [Gender Unknown]
    3, // Farfetch'd        [1♀:1♂]
    3, // Doduo             [1♀:1♂]
    3, // Dodrio            [1♀:1♂]
    3, // Seel              [1♀:1♂]
    3, // Dewgong           [1♀:1♂]
    3, // Grimer            [1♀:1♂]
    3, // Muk               [1♀:1♂]
    3, // Shellder          [1♀:1♂]
    3, // Cloyster          [1♀:1♂]
    3, // Gastly            [1♀:1♂]
    3, // Haunter           [1♀:1♂]
    3, // Gengar            [1♀:1♂]
    3, // Onix              [1♀:1♂]
    3, // Drowzee           [1♀:1♂]
    3, // Hypno             [1♀:1♂]
    3, // Krabby            [1♀:1♂]
    3, // Kingler           [1♀:1♂]
    7, // Voltorb           [Gender Unknown]
    7, // Electrode         [Gender Unknown]
    3, // Exeggcute         [1♀:1♂]
    3, // Exeggutor         [1♀:1♂]
    3, // Cubone            [1♀:1♂]
    3, // Marowak           [1♀:1♂]
    0, // Hitmonlee         [Male Only]
    0, // Hitmonchan        [Male Only]
    3, // Lickitung         [1♀:1♂]
    3, // Koffing           [1♀:1♂]
    3, // Weezing           [1♀:1♂]
    3, // Rhyhorn           [1♀:1♂]
    3, // Rhydon            [1♀:1♂]
    6, // Chansey           [Female Only]
    3, // Tangela           [1♀:1♂]
    6, // Kangaskhan        [Female Only]
    3, // Horsea            [1♀:1♂]
    3, // Seadra            [1♀:1♂]
    3, // Goldeen           [1♀:1♂]
    3, // Seaking           [1♀:1♂]
    7, // Staryu            [Gender Unknown]
    7, // Starmie           [Gender Unknown]
    3, // Mr. Mime          [1♀:1♂]
    3, // Scyther           [1♀:1♂]
    6, // Jynx              [Female Only]
    2, // Electabuzz        [1♀:3♂]
    2, // Magmar            [1♀:3♂]
    3, // Pinsir            [1♀:1♂]
    0, // Tauros            [Male Only]
    3, // Magikarp          [1♀:1♂]
    3, // Gyarados          [1♀:1♂]
    3, // Lapras            [1♀:1♂]
    7, // Ditto             [Gender Unknown]
    1, // Eevee             [1♀:7♂]
    1, // Vaporeon          [1♀:7♂]
    1, // Jolteon           [1♀:7♂]
    1, // Flareon           [1♀:7♂]
    7, // Porygon           [Gender Unknown]
    1, // Omanyte           [1♀:7♂]
    1, // Omastar           [1♀:7♂]
    1, // Kabuto            [1♀:7♂]
    1, // Kabutops          [1♀:7♂]
    1, // Aerodactyl        [1♀:7♂]
    1, // Snorlax           [1♀:7♂]
    7, // Articuno          [Gender Unknown]
    7, // Zapdos            [Gender Unknown]
    7, // Moltres           [Gender Unknown]
    3, // Dratini           [1♀:1♂]
    3, // Dragonair         [1♀:1♂]
    3, // Dragonite         [1♀:1♂]
    7, // Mewtwo            [Gender Unknown]
    7, // Mew               [Gender Unknown]
    1, // Chikorita         [1♀:7♂]
    1, // Bayleef           [1♀:7♂]
    1, // Meganium          [1♀:7♂]
    1, // Cyndaquil         [1♀:7♂]
    1, // Quilava           [1♀:7♂]
    1, // Typhlosion        [1♀:7♂]
    1, // Totodile          [1♀:7♂]
    1, // Croconaw          [1♀:7♂]
    1, // Feraligatr        [1♀:7♂]
    3, // Sentret           [1♀:1♂]
    3, // Furret            [1♀:1♂]
    3, // Hoothoot          [1♀:1♂]
    3, // Noctowl           [1♀:1♂]
    3, // Ledyba            [1♀:1♂]
    3, // Ledian            [1♀:1♂]
    3, // Spinarak          [1♀:1♂]
    3, // Ariados           [1♀:1♂]
    3, // Crobat            [1♀:1♂]
    3, // Chinchou          [1♀:1♂]
    3, // Lanturn           [1♀:1♂]
    3, // Pichu             [1♀:1♂]
    4, // Cleffa            [3♀:1♂]
    4, // Igglybuff         [3♀:1♂]
    1, // Togepi            [1♀:7♂]
    1, // Togetic           [1♀:7♂]
    3, // Natu              [1♀:1♂]
    3, // Xatu              [1♀:1♂]
    3, // Mareep            [1♀:1♂]
    3, // Flaaffy           [1♀:1♂]
    3, // Ampharos          [1♀:1♂]
    3, // Bellossom         [1♀:1♂]
    3, // Marill            [1♀:1♂]
    3, // Azumarill         [1♀:1♂]
    3, // Sudowoodo         [1♀:1♂]
    3, // Politoed          [1♀:1♂]
    3, // Hoppip            [1♀:1♂]
    3, // Skiploom          [1♀:1♂]
    3, // Jumpluff          [1♀:1♂]
    3, // Aipom             [1♀:1♂]
    3, // Sunkern           [1♀:1♂]
    3, // Sunflora          [1♀:1♂]
    3, // Yanma             [1♀:1♂]
    3, // Wooper            [1♀:1♂]
    3, // Quagsire          [1♀:1♂]
    1, // Espeon            [1♀:7♂]
    1, // Umbreon           [1♀:7♂]
    3, // Murkrow           [1♀:1♂]
    3, // Slowking          [1♀:1♂]
    3, // Misdreavus        [1♀:1♂]
    7, // Unown             [Gender Unknown]
    3, // Wobbuffet         [1♀:1♂]
    3, // Girafarig         [1♀:1♂]
    3, // Pineco            [1♀:1♂]
    3, // Forretress        [1♀:1♂]
    3, // Dunsparce         [1♀:1♂]
    3, // Gligar            [1♀:1♂]
    3, // Steelix           [1♀:1♂]
    4, // Snubbull          [3♀:1♂]
    4, // Granbull          [3♀:1♂]
    3, // Qwilfish          [1♀:1♂]
    3, // Scizor            [1♀:1♂]
    3, // Shuckle           [1♀:1♂]
    3, // Heracross         [1♀:1♂]
    3, // Sneasel           [1♀:1♂]
    3, // Teddiursa         [1♀:1♂]
    3, // Ursaring          [1♀:1♂]
    3, // Slugma            [1♀:1♂]
    3, // Magcargo          [1♀:1♂]
    3, // Swinub            [1♀:1♂]
    3, // Piloswine         [1♀:1♂]
    4, // Corsola           [3♀:1♂]
    3, // Remoraid          [1♀:1♂]
    3, // Octillery         [1♀:1♂]
    3, // Delibird          [1♀:1♂]
    3, // Mantine           [1♀:1♂]
    3, // Skarmory          [1♀:1♂]
    3, // Houndour          [1♀:1♂]
    3, // Houndoom          [1♀:1♂]
    3, // Kingdra           [1♀:1♂]
    3, // Phanpy            [1♀:1♂]
    3, // Donphan           [1♀:1♂]
    7, // Porygon2          [Gender Unknown]
    3, // Stantler          [1♀:1♂]
    3, // Smeargle          [1♀:1♂]
    0, // Tyrogue           [Male Only]
    0, // Hitmontop         [Male Only]
    6, // Smoochum          [Female Only]
    2, // Elekid            [1♀:3♂]
    2, // Magby             [1♀:3♂]
    6, // Miltank           [Female Only]
    6, // Blissey           [Female Only]
    7, // Raikou            [Gender Unknown]
    7, // Entei             [Gender Unknown]
    7, // Suicune           [Gender Unknown]
    3, // Larvitar          [1♀:1♂]
    3, // Pupitar           [1♀:1♂]
    3, // Tyranitar         [1♀:1♂]
    7, // Lugia             [Gender Unknown]
    7, // Ho-Oh             [Gender Unknown]
    7, // Celebi            [Gender Unknown]
};
const bool NUM_ABILITIES[251] = {
    0, // Bulbasaur         Overgrow
    0, // Ivysaur           Overgrow
    0, // Venusaur          Overgrow
    0, // Charmander        Blaze
    0, // Charmeleon        Blaze
    0, // Charizard         Blaze
    0, // Squirtle          Torrent
    0, // Wartortle         Torrent
    0, // Blastoise         Torrent
    0, // Caterpie          Shield Dust
    0, // Metapod           Shed Skin
    0, // Butterfree        Compound Eyes
    0, // Weedle            Shield Dust
    0, // Kakuna            Shed Skin
    0, // Beedrill          Swarm
    0, // Pidgey            Keen Eye
    0, // Pidgeotto         Keen Eye
    0, // Pidgeot           Keen Eye
    1, // Rattata           Run Away/Guts
    1, // Raticate          Run Away/Guts
    0, // Spearow           Keen Eye
    0, // Fearow            Keen Eye
    1, // Ekans             Intimidate/Shed Skin
    1, // Arbok             Intimidate/Shed Skin
    0, // Pikachu           Static
    0, // Raichu            Static
    0, // Sandshrew         Sand Veil
    0, // Sandslash         Sand Veil
    0, // Nidoran♀          Poison Point
    0, // Nidorina          Poison Point
    0, // Nidoqueen         Poison Point
    0, // Nidoran♂          Poison Point
    0, // Nidorino          Poison Point
    0, // Nidoking          Poison Point
    0, // Clefairy          Cute Charm
    0, // Clefable          Cute Charm
    0, // Vulpix            Flash Fire
    0, // Ninetales         Flash Fire
    0, // Jigglypuff        Cute Charm
    0, // Wigglytuff        Cute Charm
    0, // Zubat             Inner Focus
    0, // Golbat            Inner Focus
    0, // Oddish            Chlorophyll
    0, // Gloom             Chlorophyll
    0, // Vileplume         Chlorophyll
    0, // Paras             Effect Spore
    0, // Parasect          Effect Spore
    0, // Venonat           Compound Eyes
    0, // Venomoth          Shield Dust
    1, // Diglett           Sand Veil/Arena Trap
    1, // Dugtrio           Sand Veil/Arena Trap
    0, // Meowth            Pickup
    0, // Persian           Limber
    1, // Psyduck           Damp/Cloud Nine
    1, // Golduck           Damp/Cloud Nine
    0, // Mankey            Vital Spirit
    0, // Primeape          Vital Spirit
    1, // Growlithe         Intimidate/Flash Fire
    1, // Arcanine          Intimidate/Flash Fire
    1, // Poliwag           Water Absorb/Damp
    1, // Poliwhirl         Water Absorb/Damp
    1, // Poliwrath         Water Absorb/Damp
    1, // Abra              Synchronize/Inner Focus
    1, // Kadabra           Synchronize/Inner Focus
    1, // Alakazam          Synchronize/Inner Focus
    0, // Machop            Guts
    0, // Machoke           Guts
    0, // Machamp           Guts
    0, // Bellsprout        Chlorophyll
    0, // Weepinbell        Chlorophyll
    0, // Victreebel        Chlorophyll
    1, // Tentacool         Clear Body/Liquid Ooze
    1, // Tentacruel        Clear Body/Liquid Ooze
    1, // Geodude           Rock Head/Sturdy
    1, // Graveler          Rock Head/Sturdy
    1, // Golem             Rock Head/Sturdy
    1, // Ponyta            Run Away/Flash Fire
    1, // Rapidash          Run Away/Flash Fire
    1, // Slowpoke          Oblivious/Own Tempo
    1, // Slowbro           Oblivious/Own Tempo
    1, // Magnemite         Magnet Pull/Sturdy
    1, // Magneton          Magnet Pull/Sturdy
    1, // Farfetch'd        Keen Eye/Inner Focus
    1, // Doduo             Run Away/Early Bird
    1, // Dodrio            Run Away/Early Bird
    0, // Seel              Thick Fat
    0, // Dewgong           Thick Fat
    1, // Grimer            Stench/Sticky Hold
    1, // Muk               Stench/Sticky Hold
    0, // Shellder          Shell Armor
    0, // Cloyster          Shell Armor
    0, // Gastly            Levitate
    0, // Haunter           Levitate
    0, // Gengar            Cursed Body
    1, // Onix              Rock Head/Sturdy
    0, // Drowzee           Insomnia
    0, // Hypno             Insomnia
    1, // Krabby            Hyper Cutter/Shell Armor
    1, // Kingler           Hyper Cutter/Shell Armor
    1, // Voltorb           Soundproof/Static
    1, // Electrode         Soundproof/Static
    0, // Exeggcute         Chlorophyll
    0, // Exeggutor         Chlorophyll
    1, // Cubone            Rock Head/Lightning Rod
    1, // Marowak           Rock Head/Lightning Rod
    0, // Hitmonlee         Limber
    0, // Hitmonchan        Keen Eye
    1, // Lickitung         Own Tempo/Oblivious
    0, // Koffing           Levitate
    0, // Weezing           Levitate
    1, // Rhyhorn           Lightning Rod/Rock Head
    1, // Rhydon            Lightning Rod/Rock Head
    1, // Chansey           Natural Cure/Serene Grace
    0, // Tangela           Chlorophyll
    0, // Kangaskhan        Early Bird
    0, // Horsea            Swift Swim
    0, // Seadra            Poison Point
    1, // Goldeen           Swift Swim/Water Veil
    1, // Seaking           Swift Swim/Water Veil
    1, // Staryu            Illuminate/Natural Cure
    1, // Starmie           Illuminate/Natural Cure
    0, // Mr. Mime          Soundproof
    0, // Scyther           Swarm
    0, // Jynx              Oblivious
    0, // Electabuzz        Static
    0, // Magmar            Flame Body
    0, // Pinsir            Hyper Cutter
    0, // Tauros            Intimidate
    0, // Magikarp          Swift Swim
    0, // Gyarados          Intimidate
    1, // Lapras            Water Absorb/Shell Armor
    0, // Ditto             Limber
    0, // Eevee             Run Away
    0, // Vaporeon          Water Absorb
    0, // Jolteon           Volt Absorb
    0, // Flareon           Flash Fire
    0, // Porygon           Trace
    1, // Omanyte           Swift Swim/Shell Armor
    1, // Omastar           Swift Swim/Shell Armor
    1, // Kabuto            Swift Swim/Battle Armor
    1, // Kabutops          Swift Swim/Battle Armor
    1, // Aerodactyl        Rock Head/Pressure
    1, // Snorlax           Immunity/Thick Fat
    0, // Articuno          Pressure
    0, // Zapdos            Pressure
    0, // Moltres           Pressure
    0, // Dratini           Shed Skin
    0, // Dragonair         Shed Skin
    0, // Dragonite         Inner Focus
    0, // Mewtwo            Pressure
    0, // Mew               Synchronize
    0, // Chikorita         Overgrow
    0, // Bayleef           Overgrow
    0, // Meganium          Overgrow
    0, // Cyndaquil         Blaze
    0, // Quilava           Blaze
    0, // Typhlosion        Blaze
    0, // Totodile          Torrent
    0, // Croconaw          Torrent
    0, // Feraligatr        Torrent
    1, // Sentret           Run Away/Keen Eye
    1, // Furret            Run Away/Keen Eye
    1, // Hoothoot          Insomnia/Keen Eye
    1, // Noctowl           Insomnia/Keen Eye
    1, // Ledyba            Swarm/Early Bird
    1, // Ledian            Swarm/Early Bird
    1, // Spinarak          Swarm/Insomnia
    1, // Ariados           Swarm/Insomnia
    0, // Crobat            Inner Focus
    1, // Chinchou          Volt Absorb/Illuminate
    1, // Lanturn           Volt Absorb/Illuminate
    0, // Pichu             Static
    0, // Cleffa            Cute Charm
    0, // Igglybuff         Cute Charm
    1, // Togepi            Hustle/Serene Grace
    1, // Togetic           Hustle/Serene Grace
    1, // Natu              Synchronize/Early Bird
    1, // Xatu              Synchronize/Early Bird
    0, // Mareep            Static
    0, // Flaaffy           Static
    0, // Ampharos          Static
    0, // Bellossom         Chlorophyll
    1, // Marill            Thick Fat/Huge Power
    1, // Azumarill         Thick Fat/Huge Power
    1, // Sudowoodo         Sturdy/Rock Head
    1, // Politoed          Water Absorb/Damp
    0, // Hoppip            Chlorophyll
    0, // Skiploom          Chlorophyll
    0, // Jumpluff          Chlorophyll
    1, // Aipom             Run Away/Pickup
    0, // Sunkern           Chlorophyll
    0, // Sunflora          Chlorophyll
    1, // Yanma             Speed Boost/Compound Eyes
    1, // Wooper            Damp/Water Absorb
    1, // Quagsire          Damp/Water Absorb
    0, // Espeon            Synchronize
    0, // Umbreon           Synchronize
    0, // Murkrow           Insomnia
    1, // Slowking          Oblivious/Own Tempo
    0, // Misdreavus        Levitate
    0, // Unown             Levitate
    0, // Wobbuffet         Shadow Tag
    1, // Girafarig         Inner Focus/Early Bird
    0, // Pineco            Sturdy
    0, // Forretress        Sturdy
    1, // Dunsparce         Serene Grace/Run Away
    1, // Gligar            Hyper Cutter/Sand Veil
    1, // Steelix           Rock Head/Sturdy
    1, // Snubbull          Intimidate/Run Away
    0, // Granbull          Intimidate
    1, // Qwilfish          Poison Point/Swift Swim
    0, // Scizor            Swarm
    0, // Shuckle           Sturdy
    1, // Heracross         Swarm/Guts
    1, // Sneasel           Inner Focus/Keen Eye
    0, // Teddiursa         Pickup
    0, // Ursaring          Guts
    1, // Slugma            Magma Armor/Flame Body
    1, // Magcargo          Magma Armor/Flame Body
    0, // Swinub            Oblivious
    0, // Piloswine         Oblivious
    1, // Corsola           Hustle/Natural Cure
    0, // Remoraid          Hustle
    0, // Octillery         Suction Cups
    1, // Delibird          Vital Spirit/Hustle
    1, // Mantine           Swift Swim/Water Absorb
    1, // Skarmory          Keen Eye/Sturdy
    1, // Houndour          Early Bird/Flash Fire
    1, // Houndoom          Early Bird/Flash Fire
    0, // Kingdra           Swift Swim
    0, // Phanpy            Pickup
    0, // Donphan           Sturdy
    0, // Porygon2          Trace
    0, // Stantler          Intimidate
    0, // Smeargle          Own Tempo
    0, // Tyrogue           Guts
    0, // Hitmontop         Intimidate
    0, // Smoochum          Oblivious
    0, // Elekid            Static
    0, // Magby             Flame Body
    0, // Miltank           Thick Fat
    1, // Blissey           Natural Cure/Serene Grace
    0, // Raikou            Pressure
    0, // Entei             Pressure
    0, // Suicune           Pressure
    0, // Larvitar          Guts
    0, // Pupitar           Shed Skin
    0, // Tyranitar         Sand Stream
    0, // Lugia             Pressure
    0, // Ho-Oh             Pressure
    0, // Celebi            Natural Cure
};
const byte MOVESETS[251][32] = {
    // This data is stored as 32 bytes of binary data per Pokemon, depending on if they can learn the move. Data obtained through PokeAPI
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
};
const byte FIRST_MOVES[251] = {
    // Data obtained through PokeAPI
    0x21, // Bulbasaur       (tackle)
    0x21, // Ivysaur         (tackle)
    0x16, // Venusaur        (vine-whip)
    0x0a, // Charmander      (scratch)
    0x0a, // Charmeleon      (scratch)
    0x0a, // Charizard       (scratch)
    0x21, // Squirtle        (tackle)
    0x21, // Wartortle       (tackle)
    0x21, // Blastoise       (tackle)
    0x21, // Caterpie        (tackle)
    0x6a, // Metapod         (harden)
    0x5d, // Butterfree      (confusion)
    0x28, // Weedle          (poison-sting)
    0x6a, // Kakuna          (harden)
    0x1f, // Beedrill        (fury-attack)
    0x21, // Pidgey          (tackle)
    0x10, // Pidgeotto       (gust)
    0x10, // Pidgeot         (gust)
    0x21, // Rattata         (tackle)
    0x21, // Raticate        (tackle)
    0x2d, // Spearow         (growl)
    0x1f, // Fearow          (fury-attack)
    0x23, // Ekans           (wrap)
    0x23, // Arbok           (wrap)
    0x2d, // Pikachu         (growl)
    0x27, // Raichu          (tail-whip)
    0x0a, // Sandshrew       (scratch)
    0x0a, // Sandslash       (scratch)
    0x0a, // Nidoran-f       (scratch)
    0x0a, // Nidorina        (scratch)
    0x0a, // Nidoqueen       (scratch)
    0x2b, // Nidoran-m       (leer)
    0x2b, // Nidorino        (leer)
    0x18, // Nidoking        (double-kick)
    0x01, // Clefairy        (pound)
    0x03, // Clefable        (double-slap)
    0x34, // Vulpix          (ember)
    0x34, // Ninetales       (ember)
    0x2f, // Jigglypuff      (sing)
    0x03, // Wigglytuff      (double-slap)
    0x8d, // Zubat           (leech-life)
    0x30, // Golbat          (supersonic)
    0x47, // Oddish          (absorb)
    0x47, // Gloom           (absorb)
    0x47, // Vileplume       (absorb)
    0x0a, // Paras           (scratch)
    0x0a, // Parasect        (scratch)
    0x21, // Venonat         (tackle)
    0x21, // Venomoth        (tackle)
    0x0a, // Diglett         (scratch)
    0x0a, // Dugtrio         (scratch)
    0x0a, // Meowth          (scratch)
    0x0a, // Persian         (scratch)
    0x0a, // Psyduck         (scratch)
    0x0a, // Golduck         (scratch)
    0x0a, // Mankey          (scratch)
    0x0a, // Primeape        (scratch)
    0x2c, // Growlithe       (bite)
    0x2c, // Arcanine        (bite)
    0x91, // Poliwag         (bubble)
    0x37, // Poliwhirl       (water-gun)
    0x03, // Poliwrath       (double-slap)
    0x64, // Abra            (teleport)
    0x5d, // Kadabra         (confusion)
    0x5d, // Alakazam        (confusion)
    0x2b, // Machop          (leer)
    0x2b, // Machoke         (leer)
    0x2b, // Machamp         (leer)
    0x16, // Bellsprout      (vine-whip)
    0x16, // Weepinbell      (vine-whip)
    0x16, // Victreebel      (vine-whip)
    0x28, // Tentacool       (poison-sting)
    0x28, // Tentacruel      (poison-sting)
    0x21, // Geodude         (tackle)
    0x21, // Graveler        (tackle)
    0x21, // Golem           (tackle)
    0x21, // Ponyta          (tackle)
    0x21, // Rapidash        (tackle)
    0x21, // Slowpoke        (tackle)
    0x21, // Slowbro         (tackle)
    0x21, // Magnemite       (tackle)
    0x21, // Magneton        (tackle)
    0x40, // Farfetchd       (peck)
    0x2d, // Doduo           (growl)
    0x1f, // Dodrio          (fury-attack)
    0x1d, // Seel            (headbutt)
    0x1d, // Dewgong         (headbutt)
    0x01, // Grimer          (pound)
    0x01, // Muk             (pound)
    0x21, // Shellder        (tackle)
    0x30, // Cloyster        (supersonic)
    0x5f, // Gastly          (hypnosis)
    0x5f, // Haunter         (hypnosis)
    0x5f, // Gengar          (hypnosis)
    0x21, // Onix            (tackle)
    0x01, // Drowzee         (pound)
    0x01, // Hypno           (pound)
    0x91, // Krabby          (bubble)
    0x0b, // Kingler         (vice-grip)
    0x21, // Voltorb         (tackle)
    0x21, // Electrode       (tackle)
    0x5f, // Exeggcute       (hypnosis)
    0x5d, // Exeggutor       (confusion)
    0x2d, // Cubone          (growl)
    0x1d, // Marowak         (headbutt)
    0x18, // Hitmonlee       (double-kick)
    0x04, // Hitmonchan      (comet-punch)
    0x7a, // Lickitung       (lick)
    0x21, // Koffing         (tackle)
    0x21, // Weezing         (tackle)
    0x1e, // Rhyhorn         (horn-attack)
    0x17, // Rhydon          (stomp)
    0x01, // Chansey         (pound)
    0x84, // Tangela         (constrict)
    0x04, // Kangaskhan      (comet-punch)
    0x91, // Horsea          (bubble)
    0x2b, // Seadra          (leer)
    0x27, // Goldeen         (tail-whip)
    0x27, // Seaking         (tail-whip)
    0x21, // Staryu          (tackle)
    0x37, // Starmie         (water-gun)
    0x70, // Mr-mime         (barrier)
    0x2b, // Scyther         (leer)
    0x01, // Jynx            (pound)
    0x09, // Electabuzz      (thunder-punch)
    0x07, // Magmar          (fire-punch)
    0x0b, // Pinsir          (vice-grip)
    0x21, // Tauros          (tackle)
    0x96, // Magikarp        (splash)
    0x25, // Gyarados        (thrash)
    0x2d, // Lapras          (growl)
    0x90, // Ditto           (transform)
    0x21, // Eevee           (tackle)
    0x21, // Vaporeon        (tackle)
    0x21, // Jolteon         (tackle)
    0x21, // Flareon         (tackle)
    0x21, // Porygon         (tackle)
    0x6e, // Omanyte         (withdraw)
    0x2c, // Omastar         (bite)
    0x0a, // Kabuto          (scratch)
    0x0a, // Kabutops        (scratch)
    0x11, // Aerodactyl      (wing-attack)
    0x21, // Snorlax         (tackle)
    0x10, // Articuno        (gust)
    0x40, // Zapdos          (peck)
    0x11, // Moltres         (wing-attack)
    0x23, // Dratini         (wrap)
    0x23, // Dragonair       (wrap)
    0x23, // Dragonite       (wrap)
    0x32, // Mewtwo          (disable)
    0x01, // Mew             (pound)
    0x21, // Chikorita       (tackle)
    0x21, // Bayleef         (tackle)
    0x21, // Meganium        (tackle)
    0x21, // Cyndaquil       (tackle)
    0x21, // Quilava         (tackle)
    0x21, // Typhlosion      (tackle)
    0x0a, // Totodile        (scratch)
    0x0a, // Croconaw        (scratch)
    0x0a, // Feraligatr      (scratch)
    0x0a, // Sentret         (scratch)
    0x0a, // Furret          (scratch)
    0x21, // Hoothoot        (tackle)
    0x21, // Noctowl         (tackle)
    0x21, // Ledyba          (tackle)
    0x21, // Ledian          (tackle)
    0x28, // Spinarak        (poison-sting)
    0x28, // Ariados         (poison-sting)
    0x30, // Crobat          (supersonic)
    0x56, // Chinchou        (thunder-wave)
    0x30, // Lanturn         (supersonic)
    0x54, // Pichu           (thunder-shock)
    0x01, // Cleffa          (pound)
    0x2f, // Igglybuff       (sing)
    0x2d, // Togepi          (growl)
    0x2d, // Togetic         (growl)
    0x2b, // Natu            (leer)
    0x2b, // Xatu            (leer)
    0x21, // Mareep          (tackle)
    0x21, // Flaaffy         (tackle)
    0x21, // Ampharos        (tackle)
    0x47, // Bellossom       (absorb)
    0x21, // Marill          (tackle)
    0x21, // Azumarill       (tackle)
    0x58, // Sudowoodo       (rock-throw)
    0x03, // Politoed        (double-slap)
    0x96, // Hoppip          (splash)
    0x21, // Skiploom        (tackle)
    0x21, // Jumpluff        (tackle)
    0x0a, // Aipom           (scratch)
    0x47, // Sunkern         (absorb)
    0x01, // Sunflora        (pound)
    0x21, // Yanma           (tackle)
    0x27, // Wooper          (tail-whip)
    0x27, // Quagsire        (tail-whip)
    0x21, // Espeon          (tackle)
    0x21, // Umbreon         (tackle)
    0x40, // Murkrow         (peck)
    0x21, // Slowking        (tackle)
    0x2d, // Misdreavus      (growl)
    0xed, // Unown           (hidden-power)
    0x44, // Wobbuffet       (counter)
    0x21, // Girafarig       (tackle)
    0x21, // Pineco          (tackle)
    0x21, // Forretress      (tackle)
    0x63, // Dunsparce       (rage)
    0x28, // Gligar          (poison-sting)
    0x21, // Steelix         (tackle)
    0x21, // Snubbull        (tackle)
    0x21, // Granbull        (tackle)
    0x21, // Qwilfish        (tackle)
    0x2b, // Scizor          (leer)
    0x6e, // Shuckle         (withdraw)
    0x21, // Heracross       (tackle)
    0x0a, // Sneasel         (scratch)
    0x0a, // Teddiursa       (scratch)
    0x0a, // Ursaring        (scratch)
    0x7b, // Slugma          (smog)
    0x34, // Magcargo        (ember)
    0x21, // Swinub          (tackle)
    0x1e, // Piloswine       (horn-attack)
    0x21, // Corsola         (tackle)
    0x37, // Remoraid        (water-gun)
    0x37, // Octillery       (water-gun)
    0xd9, // Delibird        (present)
    0x21, // Mantine         (tackle)
    0x2b, // Skarmory        (leer)
    0x2b, // Houndour        (leer)
    0x2b, // Houndoom        (leer)
    0x2b, // Kingdra         (leer)
    0x21, // Phanpy          (tackle)
    0x1e, // Donphan         (horn-attack)
    0x21, // Porygon2        (tackle)
    0x21, // Stantler        (tackle)
    0xa6, // Smeargle        (sketch)
    0x21, // Tyrogue         (tackle)
    0x1b, // Hitmontop       (rolling-kick)
    0x01, // Smoochum        (pound)
    0x2b, // Elekid          (leer)
    0x34, // Magby           (ember)
    0x21, // Miltank         (tackle)
    0x01, // Blissey         (pound)
    0x2b, // Raikou          (leer)
    0x2b, // Entei           (leer)
    0x2b, // Suicune         (leer)
    0x2b, // Larvitar        (leer)
    0x2b, // Pupitar         (leer)
    0x2b, // Tyranitar       (leer)
    0x12, // Lugia           (whirlwind)
    0x12, // Ho-oh           (whirlwind)
    0x49, // Celebi          (leech-seed)
};

const std::string_view NAMES[251]{
    "Bulbasaur",
    "Ivysaur",
    "Venusaur",
    "Charmander",
    "Charmeleon",
    "Charizard",
    "Squirtle",
    "Wartortle",
    "Blastoise",
    "Caterpie",
    "Metapod",
    "Butterfree",
    "Weedle",
    "Kakuna",
    "Beedrill",
    "Pidgey",
    "Pidgeotto",
    "Pidgeot",
    "Rattata",
    "Raticate",
    "Spearow",
    "Fearow",
    "Ekans",
    "Arbok",
    "Pikachu",
    "Raichu",
    "Sandshrew",
    "Sandslash",
    "Nidoran<",
    "Nidorina",
    "Nidoqueen",
    "Nidoran>",
    "Nidorino",
    "Nidoking",
    "Clefairy",
    "Clefable",
    "Vulpix",
    "Ninetales",
    "Jigglypuff",
    "Wigglytuff",
    "Zubat",
    "Golbat",
    "Oddish",
    "Gloom",
    "Vileplume",
    "Paras",
    "Parasect",
    "Venonat",
    "Venomoth",
    "Diglett",
    "Dugtrio",
    "Meowth",
    "Persian",
    "Psyduck",
    "Golduck",
    "Mankey",
    "Primeape",
    "Growlithe",
    "Arcanine",
    "Poliwag",
    "Poliwhirl",
    "Poliwrath",
    "Abra",
    "Kadabra",
    "Alakazam",
    "Machop",
    "Machoke",
    "Machamp",
    "Bellsprout",
    "Weepinbell",
    "Victreebel",
    "Tentacool",
    "Tentacruel",
    "Geodude",
    "Graveler",
    "Golem",
    "Ponyta",
    "Rapidash",
    "Slowpoke",
    "Slowbro",
    "Magnemite",
    "Magneton",
    "Farfetch'd",
    "Doduo",
    "Dodrio",
    "Seel",
    "Dewgong",
    "Grimer",
    "Muk",
    "Shellder",
    "Cloyster",
    "Gastly",
    "Haunter",
    "Gengar",
    "Onix",
    "Drowzee",
    "Hypno",
    "Krabby",
    "Kingler",
    "Voltorb",
    "Electrode",
    "Exeggcute",
    "Exeggutor",
    "Cubone",
    "Marowak",
    "Hitmonlee",
    "Hitmonchan",
    "Lickitung",
    "Koffing",
    "Weezing",
    "Rhyhorn",
    "Rhydon",
    "Chansey",
    "Tangela",
    "Kangaskhan",
    "Horsea",
    "Seadra",
    "Goldeen",
    "Seaking",
    "Staryu",
    "Starmie",
    "Mr. Mime",
    "Scyther",
    "Jynx",
    "Electabuzz",
    "Magmar",
    "Pinsir",
    "Tauros",
    "Magikarp",
    "Gyarados",
    "Lapras",
    "Ditto",
    "Eevee",
    "Vaporeon",
    "Jolteon",
    "Flareon",
    "Porygon",
    "Omanyte",
    "Omastar",
    "Kabuto",
    "Kabutops",
    "Aerodactyl",
    "Snorlax",
    "Articuno",
    "Zapdos",
    "Moltres",
    "Dratini",
    "Dragonair",
    "Dragonite",
    "Mewtwo",
    "Mew",
    "Chikorita",
    "Bayleef",
    "Meganium",
    "Cyndaquil",
    "Quilava",
    "Typhlosion",
    "Totodile",
    "Croconaw",
    "Feraligatr",
    "Sentret",
    "Furret",
    "Hoothoot",
    "Noctowl",
    "Ledyba",
    "Ledian",
    "Spinarak",
    "Ariados",
    "Crobat",
    "Chinchou",
    "Lanturn",
    "Pichu",
    "Cleffa",
    "Igglybuff",
    "Togepi",
    "Togetic",
    "Natu",
    "Xatu",
    "Mareep",
    "Flaaffy",
    "Ampharos",
    "Bellossom",
    "Marill",
    "Azumarill",
    "Sudowoodo",
    "Politoed",
    "Hoppip",
    "Skiploom",
    "Jumpluff",
    "Aipom",
    "Sunkern",
    "Sunflora",
    "Yanma",
    "Wooper",
    "Quagsire",
    "Espeon",
    "Umbreon",
    "Murkrow",
    "Slowking",
    "Misdreavus",
    "Unown",
    "Wobbuffet",
    "Girafarig",
    "Pineco",
    "Forretress",
    "Dunsparce",
    "Gligar",
    "Steelix",
    "Snubbull",
    "Granbull",
    "Qwilfish",
    "Scizor",
    "Shuckle",
    "Heracross",
    "Sneasel",
    "Teddiursa",
    "Ursaring",
    "Slugma",
    "Magcargo",
    "Swinub",
    "Piloswine",
    "Corsola",
    "Remoraid",
    "Octillery",
    "Delibird",
    "Mantine",
    "Skarmory",
    "Houndour",
    "Houndoom",
    "Kingdra",
    "Phanpy",
    "Donphan",
    "Porygon2",
    "Stantler",
    "Smeargle",
    "Tyrogue",
    "Hitmontop",
    "Smoochum",
    "Elekid",
    "Magby",
    "Miltank",
    "Blissey",
    "Raikou",
    "Entei",
    "Suicune",
    "Larvitar",
    "Pupitar",
    "Tyranitar",
    "Lugia",
    "Ho-Oh",
    "Celebi",
};