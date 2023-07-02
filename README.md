## Hey you! Yes you! I have *no* idea how you found this repository. Unforunately, this is stil very much a work in progress. It's very much on it's way, but it isn't ready for release yet. Because of this, not all this information is accurate or up to date... The biggest thing I want to stress is that there are credits that I need to add still- please don't sue me, they will be there by release! Or hopefully by the end of this week. Thank you.

## About
Pokemon Mirror is a transfer tool for created to transfer Pokemon from Pokemon Red, Blue, Yellow, Gold, Silver, and Crystal to Pokemon Ruby, Sapphire, FireRed, LeafGreen, and Emerald.

This is not the first time that the gap between Generation 1/2 and 3 has been bridged. [Goppier](https://www.youtube.com/@Goppier) was the first to make the gap with a computer between the two link cables, and [Lorenzooone](https://www.youtube.com/@Lorenzooone) was able to push it further by communicating directly between the GameBoy and GameBoy Advance. However, Pokemon Mirror is the first program designed to emulate what GameFreak may have released should they persued it. Many inspirations were taken from the Pal Park, PokeTransfer Lab, and PokeTransporte to keep a "GameFreak" feeling.

_**Pokemon Transfered using Pokemon Mirror will *not* be removed from Red, Blue, Yellow, Gold Silver, or Crystal. This is not only to save on time when transfering, but also to guarentee that Pokemon are not lost and are able to be transfered again if a large update is made to the program.**_

*Currently the only release is in English. Releases supporting other languages is planned for the near future.*

## Installation
There are two releases of Pokemon Mirror: A GameBoy Advance ROM and a Wii Channel. The simplest wayt to get Pokemon HMirror up and running is to install the Wii Channel. through the Wii Homebrew Menu.. From there, you can plug your GBA into a GameCube/GBA Link cable and are set to go. If you have an alternate metod on uploading GBA Multiboot ROMS , feel free to use the GBA ROM to do that directly!

## Modifications to Transfered Pokemon
- Nature is set to the modulo of the Pokemon's EXP, just like how PokeBank handles it
- Abilities, Characteristics, and Size are randomized
- Gender, Shininess, and Unown forms are retained from previous generations
- OT name and ID are retained, but SID is set to 00000 (unless the Pokemon is shiny)
- Nicknames are retained, however some special characters have been replaced
- Language is set to match whatever the language is in Ruby, Sapphire, FireRed, LeafGreen, or Emerald
- Items are not transfered
- Level and EXP are retained, but any level greater than 100 are set to 100.
- Moves are retained. This does mean that there are some Pokemon that will have illegal movesets in Ruby, Sapphire, FireRed, LeafGreen, and Emerald. However, the program will mention these moves to the user.
- Stat Experience is erased and EVs are set to zero
- PP Ups are retained
- Pokerus is retained
- If the player is playing as Kris in Pokemon Crystal, the OT gender of the Pokemon will be set to female
- The transfered Pokemon will be caught in a Pokeball
- IVs are generated based on the Pokemon's DVs. Each DV is multiplied by two and increased by one, which is simmilar to how Pokemon HOME converts IVs when transfering from Pokemon GO.
- Met level is set to the Pokemon's current level, and met location is set to "Hatched from an Egg". When transfered to Diamond, Pearl, Platinum, HeartGold, or SoulSilver this will be replaced by "Met at Pal Park", so Pokemon in the undiscovered egg group will have no issues.
- Game of Origin is set to FireRed/LeafGreen for Pokemon transfered from Red, Blue, and Yellow. Pokemon from Gold, Silver, and Crystal will have their Game of Origin set to HeartGold/SoulSilver. This will display as "A far off land" in Ruby, Sapphire, FireRed, LeafGreen, and Emerald- much like how a Game of Origin of FireRed/LeafGreen displays in Ruby and Sapphire.
- Mew and Celebi are given Fateful Encounters so that they obey the player
- Each Pokemon will be given an Artist ribbon. This ribbon is obtainable on any Pokemon, but is rarely obtained by players. Thus it makes it a great way to identify Pokemon transfered with this method.

## Why?
One of my favorite aspects of the Pokemon franchise is the ability to send Pokemon forward into the most recent generation. Of course, this isn't possible from the Gameboy games into the Gameboy Advance era- and I want to fix that. A handful of Poeople have bridged the gap before, but Pokemon Mirror is the first tool designed to be the Pal Park, PokeTransport Lab, and PokeTransporter for Generation 1 and 2 to Generation 3.

# Credits

## Libraries used
- [libtonc](https://github.com/devkitPro/libtonc)
- [libsavgba](https://github.com/laqieer/libsavgba)
- [gba-link-connection](https://github.com/rodri042/gba-link-connection)
- [arduino-boy](https://github.com/pepijndevos/arduino-boy)
- [arduino-boy-gen-2](https://github.com/stevenchaulk/arduino-poke-gen2)

## License
All Pokémon names, sprites, names of related resources are © Nintendo/Creatures Inc./GAME FREAK Inc.

Everything else, and the programming code, is governed by the MIT license

_This project is not endorsed or supported by GameFreak or Nintendo. Please support the original developers._

## Special Mentions
A huge thank you to [Goppier](https://www.youtube.com/@Goppier) for being the first one to bridge the gap between generation 2 and generation 3 and for provide exremely useful documentation about both versions of the Link Cable, and a huge thank you to [Lorenzooone](https://www.youtube.com/@Lorenzooone) for being the direct inspiration for this project, as well as answering some questions I had during development. This project would never have happened without either of them, and I cannot thank them enough.
