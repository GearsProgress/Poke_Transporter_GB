## Quickstart

> _"I want to make GBA homebrew, where do I begin?"_


1) [Install devkitARM](https://devkitpro.org/wiki/Getting_Started) for your system.

2) [Read Tonc](https://www.coranac.com/tonc/text/) to learn all about GBA programming!  
    * You can skip _"Setting up a development environment"_ because we did that in step 1.

3) Clone this repo and run `make` in your terminal.
    * If you used the graphical installer on Windows for step 1, you should use the _MSYS2_ terminal for this step.


## About this repo

This is a minimal GBA example project using libtonc instead of libgba.

The commit history exists to document the process of converting a _libgba_ example to a _libtonc_ example.

### Why?

devkitPro provides two general-purpose libraries: _libgba_ and _libtonc_. Of the two, I recommend _libtonc_, because it has better documentation and more features (it's part of the accompanying material to the excellent Tonc tutorial).

The trouble here is that all the GBA examples are using _libgba_, and converting the _libgba_ template to use _libtonc_ is non-trivial for those who are just getting started.