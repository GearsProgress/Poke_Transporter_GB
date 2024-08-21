#include <tonc.h>
#include <vector>
#include <string>
#include "rom_data.h"

class script_var
{
public:
    script_var(u32 nValue, std::vector<script_var *> &var_list_ref, int *nCurr_loc_ptr);
    script_var(std::vector<script_var *> &var_list_ref, int *nCurr_loc_ptr);
    virtual void fill_refrences(u8 mg_array_ptr[]); // goes through all the script locations and updates them to point to the start
    virtual void set_start();                       // Add a pointer to where the start is
    u32 place_word();                               // Place the value in memory
    int *curr_loc_ptr;
    u32 value;
    std::vector<u32> location_list; // stores all the locations in the script that need to be updated
    u32 start_location_in_script;
};

class asm_var : public script_var
{
public:
    using script_var::script_var;
    void set_start();                       // Add a pointer to where the start is
    void set_start(bool nIsDirect);                       // Add a pointer to where the start is
    u8 add_reference();  // Add a location for the variable to be refrenced in the script
    u8 add_reference(int nCommand_offset);  // Add a location for the variable to be refrenced in the script
    void fill_refrences(u8 mg_array_ptr[]); // goes through all the script locations and updates them to point to the start
    u32 get_loc_in_sec30();
    bool isDirect;
};

class xse_var : public script_var
{
public:
    using script_var::script_var;
    int command_offset;    // The amount of bytes in the command before the variable
    xse_var *refrence_var; // The offset from a different location in the script. Used to point to functions through addition/subtraction
    bool has_reference_var;
    void set_start();                      // Add a pointer to where the start is
    u8 add_reference(int nCommand_offset); // Add a location for the variable to be refrenced in the script
    u8 add_reference(int nCommand_offset, xse_var *offset_from);
    void fill_refrences(u8 mg_array_ptr[]); // goes through all the script locations and updates them to point to the start
    u32 get_loc_in_sec30();
};

class textbox_var : public xse_var
{
public:
    using xse_var::xse_var;
    void set_text(std::u16string_view nText);
    void insert_text(u8 mg_array[]);
    void set_start();
    void insert_virtual_text(u8 mg_array[]);
    void set_virtual_start();
    std::u16string_view text;
};

class movement_var : public xse_var
{
public:
    using xse_var::xse_var;
    void set_movement(const int movement[], unsigned int nSize);
    void insert_movement(u8 mg_array[]);
    void set_start();
    const int *movement;
    unsigned int size;
};

class sprite_var : public xse_var
{
public:
    using xse_var::xse_var;
    void insert_sprite_data(u8 mg_array[], const unsigned int sprite_array[], unsigned int size, const unsigned short palette_array[]);
    void set_start();
};

class music_var : public xse_var
{
public:
    using xse_var::xse_var;
    void insert_music_data(u8 mg_array[], u8 blockCount, u8 priority, u8 reverb, u32 toneDataPointer);
    void set_start();
    void add_track(std::vector<byte> track);
    int numTracks;
    std::vector<u32> trackPointers;
    std::vector<std::vector<byte>> trackArrays;
};