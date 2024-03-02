#include <tonc.h>
#include <vector>
#include <string>

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
    u8 add_reference();                     // Add a location for the variable to be refrenced in the script
    void fill_refrences(u8 mg_array_ptr[]); // goes through all the script locations and updates them to point to the start
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
};

class textbox_var : public xse_var
{
public:
using xse_var::xse_var;
    void set_text(std::u16string_view text);
    void insert_text(u8 mg_array[]);
    std::u16string_view text;
};