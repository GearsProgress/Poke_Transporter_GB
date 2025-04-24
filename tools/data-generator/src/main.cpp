#include "pokemon_data.h"

// This application holds the various long static data arrays that Poke Transporter GB uses
// and it writes them to .bin files that can be compressed with compressZX0 later.
// it's useful to do it this way because it keeps this data easy to view, edit and document

int main(int /*argc*/, char **/*argv*/)
{
    generate_pokemon_data();
    return 0;
}