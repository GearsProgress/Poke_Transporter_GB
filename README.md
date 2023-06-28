## About this repo

Pokemon Mirror is a transfer tool for created to transfer Pokemon from Pokemon Red, Blue, Yellow, Gold, Silver, and Crystal to Pokemon Ruby, Sapphire, FireRed, LeafGreen, and Emerald.

Emphasis is being put on making a program that is as easy to use and stays as accurate as possible to what a true Generation One and Two transfer tool made by the Pokemon Developers would be.

*Currently the only release is in English. Releasing other languages is planned for the near future.*

### Modifications to Transfered Pokemon
- Nature is set to the modulo of the Pokemon's EXP, just like how PokeBank handles it
- Abilities, Characteristics, and Size are randomized
- Gender, Shininess, and Unown forms are retained from previous generations
- OT name and ID are retained, but SID is set to 00000 (unless the Pokemon is shiny)
- Nicknames are retained, however some special characters have been replaced
- Language is set to match whatever the language is in Ruby, Sapphire, FireRed, LeafGreen, or Emerald
- Items are not transfered
- Level is retained, but EXP is truncated to match the current level. Any levels above 100 are brought back to 100.
- Moves are retained. This does mean that there are some Pokemon that will have illegal movesets in Ruby, Sapphire, FireRed, LeafGreen, and Emerald. However, the program will mention these moves to the user.
- Stat Experience is erased and EVs are set to zero
- PP Ups are retained
- Pokerus is retained
- If the player is playing as Kris in Pokemon Crystal, the OT gender of the Pokemon will be set to female
- The transfered Pokemon will be caught in a Pokeball
- IVs are generated based on the Pokemon's DVs. Each DV is multiplied by two and adds one, which is simmilar to how Pokemon HOME converts IVs when transfering from Pokemon GO.
- Met level is set to the Pokemon's current level, and met location is set to "Hatched from an Egg". When transfered to Diamond, Pearl, Platinum, HeartGold, or SoulSilver this will be replaced by "Met at Pal Park", so Pokemon in the undiscovered egg group will have no issues.
- Game of Origin is set to FireRed/LeafGreen for Pokemon transfered from Red, Blue, and Yellow. Pokemon from Gold, Silver, and Crystal will have their Game of Origin set to HeartGold/SoulSilver. This will display as "A far off land" in Ruby, Sapphire, FireRed, LeafGreen, and Emerald- much like how a Game of Origin of FireRed/LeafGreen displays in Ruby and Sapphire.
- Mew and Celebi are given Fateful Encounters so that they obey the player
- Each Pokemon will be given an Artist ribbon. This ribbon is obtainable on any Pokemon, but is rarely obtained by players.

### Why?

One of my favorite aspects of the Pokemon franchise is the ability to send Pokemon forward into the most recent generation. Of course, this isn't possible from the Gameboy games into the Gameboy Advance era- and I want to fix that. Other people have created tools, but my goal is to make one that is the most accurate and least "homebrew-y"


_This project is not endorsed or supported by GameFreak or Nintendo. Please support the original developers._
