## About
Poké Transporter GB is a tool created to transfer Pokémon from Pokémon Red, Blue, Yellow, Gold, Silver, and Crystal to Pokémon Ruby, Sapphire, FireRed, LeafGreen, and Emerald. Poké Transporter GB is designed to emulate what GameFreak may have released should they persued it. Many inspirations were taken from the Pal Park, PokéTransfer Lab, and PokéTransporter to keep a "GameFreak" feeling.

_Poké Transporter GB WILL modify both your generation 3 and generation 1/2 save file. The program is designed to not corrupt anything, but if you do not wish to modify your save file then you should bypass this experience._

_**Please note that although Poké Transporter GB is no longer in beta, save file backups of both games are still recommended before using... just in case!**._

## Notes
Pokémon Transfered using Poké Transporter GB *will* be removed from Red, Blue, Yellow, Gold, Silver, or Crystal.

Currently the only release is in English. Releases supporting other languages is planned for the near future.

Currently English versions of Red, Blue, Yellow, Gold, Silver, Crystal are supported- plus English, Spanish, German, Italian, French versions of Ruby, Sapphire, FireRed, LeafGreen, and Emerald. Compatibility for other languages is currently in development and will be added in the near future.

## Usage
Poké Transporter GB is a Multiboot program for the Game Boy Advance. There are 3 main ways to run the Poké Transporter GB ROM on a Game Boy Advance:
- Use a program such as FIX94's [GBA Link Cable ROM Sender](https://github.com/FIX94/gba-link-cable-rom-sender) on a GameCube or Wii running Homebrew along with a GBA GameCube Link Cable
- Upload the Multiboot ROM to a GBA Flash Cart, launch the game in Multiboot mode (often by holding L when selecting the ROM), and swap the Game Pak after the program loads.
- Copy the loader.gba file to a GBA Flash Cart and swap the Game Pak after the program loads. This is useful for flashcarts that don't support launching multiboot roms directly. (SuperCard SD for example)

Please note that transfering Pokémon will only work with a Game Boy Color Link Cable. Game Boy Advance Link Cables will not work.

## Modifications to Transfered Pokémon

Due to limitations of the transfer process, some Pokémon will not be considered legal until they reach certain generations:

|Pokémon|Generation III|Generation IV|Generation V|Passes through Pokémon Bank|Generation VI|Generation VII+|Passes through Pokémon HOME|
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|Standard Pokémon from Generation I|No<br>(Illegal Met Location)|Yes|Yes|Yes|Yes|Yes|Yes|
|Standard Pokémon from Generation II|No<br>(Illegal Met Location, Illegal Game of Origin)|No<br>(Illegal Encounter type)|No<br>(Illegal Encounter type)|Yes|No<br>(Illegal Encounter type)|Yes|Yes|
|Legendary Pokémon from Generation I|No<br>(Illegal Met Location)|Yes|Yes|Yes|Yes|Yes|Yes|
|Legendary Pokémon from Generation II|No<br>(Illegal Met Location, Illegal Game of Origin)|No<br>(Illegal Encounter type)|No<br>(Illegal Encounter type)|Yes|No<br>(Illegal Encounter type)|Yes|Yes|
|Mew from Generation I/II|No<br>(Does not match event)|No<br>(Does not match event)|No<br>(Does not match event)|?<br>(? if Shiny)|No<br>(Does not match event)|No<br>(Does not match event)|?|
|Celebi from Generation II|No<br>(Does not match event)|No<br>(Does not match event)|No<br>(Does not match event)|?<br>(? if Shiny)|No<br>(Does not match event)|No<br>(Does not match event)|?|
|Stabilized Mew|Yes|Yes|Yes|Yes|Yes|Yes|Yes|
|Stabilized Celebi|Yes|Yes|Yes|Yes|Yes|Yes|Yes|

Due to Mew and Celebi being illegal, an option is given to the player to "stabilize" them. This will convert the Pokémon into a legal event version of the mythical Pokémon. This event will be randomly generated and will not copy any of the data from generation 1/2- ***including shininess***. The mythical Pokémon will still be removed from the generation 1/2 game.

A full list of modifications made to transfered Pokémon can be found [here](https://github.com/Starport75/Pokemon_Mirror/blob/master/modifications.md)!

## Screenshots and Video

![Poke_Transporter_GB_mb-0](https://github.com/user-attachments/assets/d80083ec-3e30-416a-ac0d-5f4e61084e59)
![Poke_Transporter_GB_mb-1](https://github.com/user-attachments/assets/5df1e697-8549-4cac-8e1b-324eff987a29)
![Poke_Transporter_GB_mb-5](https://github.com/user-attachments/assets/e7893a65-5f9f-4a50-95ba-8499c78794aa)

![Poke_Transporter_GB_mb-2](https://github.com/user-attachments/assets/f548df32-ce87-48f1-ab01-3ae488e6a789)
![Poke_Transporter_GB_mb-4](https://github.com/user-attachments/assets/502685b1-ea63-42c1-81d9-e5848bbc5716)
![Poke_Transporter_GB_mb-7](https://github.com/user-attachments/assets/141acf23-c330-498b-811a-8d611df01a72)


A video showcasing Poké Transporter GB can be found [here](https://www.youtube.com/watch?v=47A6p2hH2gU), and a video detailing some of the development process can be found [here](https://youtu.be/9mSkGhEYBkg)!

## Why?
One of my favorite aspects of the Pokémon franchise is the ability to send Pokémon forward into the most recent generation. Of course, this isn't possible from the Gameboy games into the Gameboy Advance era- and I wanted to fix that. A handful of people have bridged the gap before, but Poké Transporter GB is the first tool designed to transfer Pokémon like the Pal Park, PokéTransport Lab, and PokéTransporter for Generation 1 and 2 to Generation 3. Documentation detailing the design process of Poké Transporter GB can be found [here](https://www.austinthomasweber.com/poke-transporter-gb)!

# Credits
## Inspired by the works of:
- [Goppier](https://www.youtube.com/@Goppier)
- [Lorenzooone](https://www.youtube.com/@Lorenzooone)
- [im a blisy](https://www.youtube.com/c/imablisy)
- [RETIRE](https://www.youtube.com/@RETIREglitch)

## Programs used:
- [HexManiacAdvance](https://github.com/haven1433/HexManiacAdvance)
- [PKHeX](https://github.com/kwsch/PKHeX)
- [WC3Tool](https://github.com/projectpokemon/Gen3-WCTool)
- [Usenti](https://www.coranac.com/projects/usenti/)
- [RNGReporter](https://github.com/Admiral-Fish/RNGReporter)

## Open Source Code and Libraries:
- [libtonc](https://github.com/devkitPro/libtonc)
- [Pokemon Gen 3 to Gen X](https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X)
- [gba-link-connection](https://github.com/rodri042/gba-link-connection)
- [awesomegbadev](https://github.com/gbadev-org/awesome-gbadev)
- [arduino-boy-gen-2](https://github.com/stevenchaulk/arduino-poke-gen2)

## Research Resources:
- [ARM Documentation for Nintendo Homebrew](https://github.com/LunarLambda/arm-docs)
- [Pokemon Gen 3 to Gen X](https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X)
- [Smogon's Practical Guides to RNG Abuse](https://www.smogon.com/ingame/rng/)

## ROM Data:
- [PokeRuby](https://github.com/pret/pokeruby)
- [PokeFireRed](https://github.com/pret/pokefirered)
- [PokeEmerald](https://github.com/pret/pokeemerald)
- [PokeRed](https://github.com/pret/pokered)
- [PokeYellow](https://github.com/pret/pokeyellow)
- [PokeGold](https://github.com/pret/pokegold)
- [PokeCrystal](https://github.com/pret/pokecrystal)

## Pokémon Data:
- [Bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Main_Page)
- [Serebii](https://www.serebii.net/)
- [PokeAPI](https://pokeapi.co/)
- [Glitch City Wiki](https://glitchcity.wiki/wiki/Main_Page)
  
# Discord Community Assistance:
- [Hex Maniac Advance Development](https://discord.com/invite/x9eQuBg)
- [GBAdev](https://discord.gg/ctGSNxRkg2)
- [PRET](https://discordapp.com/invite/vdTW48Q)
- [Glitch City Research Institute](https://discord.com/invite/EA7jxJ6)

# Custom Graphics:
- [LJ Birdman](https://x.com/LJSTAR_)

# Gen 2 Icon Sprite Artists:
- [LuigiTKO](https://x.com/LuigiTKO)
- [GuiAbel](https://x.com/guiabel/)
- [SourApple](https://github.com/SoupPotato)

# Arbitrary Code Execution Assistance:
- [TimoVM](https://x.com/Timo_VM)
- [MrCheeze](https://x.com/mrcheeze_)

## License
All Pokémon names, sprites, names of related resources are © Nintendo/Creatures Inc./GAME FREAK Inc.

Everything else, and the programming code, is governed by the MIT license

_This project is not endorsed or supported by GameFreak or Nintendo. Please support the original developers._

## Special Mentions
A huge thank you to Goppier for being the first one to bridge the gap between generation 2 and generation 3 and for providing extremely useful documentation about both versions of the Link Cable, and a huge thank you to Lorenzooone for being the direct inspiration for this project, as well as answering questions I had during development. This project would never have happened without either of them, and I cannot thank them enough.
