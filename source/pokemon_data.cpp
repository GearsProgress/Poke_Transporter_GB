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