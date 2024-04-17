## About
Poké Transporter GB is a transfer tool for created to transfer Pokémon from Pokémon Red, Blue, Yellow, Gold, Silver, and Crystal to Pokémon Ruby, Sapphire, FireRed, LeafGreen, and Emerald. Poké Transporter GB is designed to emulate what GameFreak may have released should they persued it. Many inspirations were taken from the Pal Park, PokéTransfer Lab, and PokéTransporte to keep a "GameFreak" feeling.

_Poké Transporter GB WILL modify your generation 3 save file. The program is designed to not corrupt anything, but if you do not wish to modify your save file then you should bypass this experience._

_**Please note that Poké Transporter GB is still in beta, so save file backups are HIGHLY recommended before using**._

## Notes
Pokémon transfered using Poké Transporter GB will pass through Pokémon Bank and Pokémon HOME, but are not guarenteed to (and likely won't) pass PKHeX's legality filter. This will hopefully change in the future.

Pokémon Transfered using Poké Transporter GB will *not* be removed from Green, Red, Blue, Yellow, Gold Silver, or Crystal. This is not only to save on time when transfering, but also to guarentee that Pokémon are not lost and are able to be transfered again if a large update is made to the program.

Currently the only release is in English. Releases supporting other languages is planned for the near future.

Only English copies of Ruby, Sappire, FireRed, LeafGreen, and Emerald are supported at this time. However, all languages of Green, Red, Blue, Yellow, Gold Silver, and Crystal are supported! Compatibility for other languages will be added in the near future.

## Usage
Poké Transporter GB is a Multiboot program for the Game Boy Advance. There are two main ways to run the Poké Transporter GB ROM on a Game Boy Advance:
- Use a program such as FIX94's [GBA Link Cable ROM Sender](https://github.com/FIX94/gba-link-cable-rom-sender) on a GameCube or Wii running Homebrew along with a GBA GameCube Link Cable
- Upload the Multiboot ROM to a GBA Flash Cart, launch the game in Multiboot mode (often by holding L when selecting the ROM), and swap the Game Pak after the program loads.

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



A list of modifications made to transfered Pokémon can be found [here](https://github.com/Starport75/Pokemon_Mirror/blob/master/modifications.md)!

## Screenshots and Video
![Pokemon_Mirror_mb-0](https://github.com/Starport75/Pokemon_Mirror/assets/23065741/a58463c0-9067-4ec0-a8b1-d16fa14cb85e)
![Pokemon_Mirror_mb-1](https://github.com/Starport75/Pokemon_Mirror/assets/23065741/7a54892d-17a0-491e-8c68-4f6d0d796a00)
![Pokemon_Mirror_mb-2](https://github.com/Starport75/Pokemon_Mirror/assets/23065741/f6e74e7e-4f44-4359-ba2a-a524a40eb234)

![Pokemon_Mirror_mb-3](https://github.com/Starport75/Pokemon_Mirror/assets/23065741/481bac72-0d57-475c-940f-a53876eaaa3b)
![Pokemon_Mirror_mb-4](https://github.com/Starport75/Pokemon_Mirror/assets/23065741/3b5df6f8-c76e-466b-8dbd-351d7d4676d1)
![Pokemon_Mirror_mb-5](https://github.com/Starport75/Pokemon_Mirror/assets/23065741/5c98426d-9717-4c1d-89b9-4fd6bfe13b4e)

A video of Poké Transporter GB in action can be found [here](https://www.youtube.com/watch?v=72e0I003Gfg)!

## Why?
One of my favorite aspects of the Pokémon franchise is the ability to send Pokémon forward into the most recent generation. Of course, this isn't possible from the Gameboy games into the Gameboy Advance era- and I wanted to fix that. A handful of Poeople have bridged the gap before, but Poké Transporter GB is the first tool designed to transfer Pokémon like the Pal Park, PokéTransport Lab, and PokéTransporter for Generation 1 and 2 to Generation 3. A document detailing some of the design process of Poké Transporter GB can be found [here](https://carpets-allow-kwy.craft.me/EnjwBLUok7rcv8)!

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

## Open Source Code and Libraries:
- [libtonc](https://github.com/devkitPro/libtonc)
- [Pokemon Gen 3 to Gen X](https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X)
- [gba-link-connection](https://github.com/rodri042/gba-link-connection)
- [awesomegbadev](https://github.com/gbadev-org/awesome-gbadev)
- [arduino-boy-gen-2](https://github.com/stevenchaulk/arduino-poke-gen2)

## Research Resources:
- [ARM Documentation for Nintendo Homebrew](https://github.com/LunarLambda/arm-docs)
- [Pokemon Gen 3 to Gen X](https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X)

## ROM Data:
- [PokeRuby](https://github.com/pret/pokeruby)
- [PokeFireRed](https://github.com/pret/pokefirered)
- [PokeEmerald](https://github.com/pret/pokeemerald)

## Pokémon Data:
- [Bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Main_Page)
- [Serebii](https://www.serebii.net/)
- [PokeAPI](https://pokeapi.co/)
  
# Discord Community Assistance:
- [Hex Maniac Advance Development](https://discord.com/invite/x9eQuBg)
- [GBAdev](https://discord.gg/ctGSNxRkg2)
- [PRET](https://discordapp.com/invite/vdTW48Q)

## License
All Pokémon names, sprites, names of related resources are © Nintendo/Creatures Inc./GAME FREAK Inc.

Everything else, and the programming code, is governed by the MIT license

_This project is not endorsed or supported by GameFreak or Nintendo. Please support the original developers._

## Special Mentions
A huge thank you to Goppier for being the first one to bridge the gap between generation 2 and generation 3 and for provide exremely useful documentation about both versions of the Link Cable, and a huge thank you to Lorenzooone for being the direct inspiration for this project, as well as answering questions I had during development. This project would never have happened without either of them, and I cannot thank them enough.
