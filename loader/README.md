This folder contains a Proof of Concept to load PokeTransporter GB WITHOUT doing the whole multiboot ritual.

It works by embedding the multiboot rom that is generated from the main project build into a separate "normal" gba rom.
And this loader rom will just copy the multiboot rom to EWRAM and jump to the right entrypoint to launch it.

This allows the user to simply launch the loader from a simple flashcart, such as a supercard SD.
After PokeTransporter GB is loaded, the user should be able to swap out the flashcart and insert the Pokémon cartridge.