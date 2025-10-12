#include <tonc.h>
#include <cstring>

#include "text_engine.h"
#include "global_frame_controller.h"
#include "pkmn_font.h"
#include "script_array.h"
#include "debug_mode.h"
#include "button_menu.h"
#include "sprite_data.h"
#include "latin_short.h"
#include "japanese_small.h"
#include "text_data_table.h"

#define TEXT_CBB 0
#define TEXT_SBB 10

script_obj curr_line;
uint char_index;
uint line_char_index;
const byte *curr_text;
bool text_exit;

// This function was separated from text_loop to reduce the scope of the text_decompression_buffer.
// if we didn't do this, the decompression_buffer would be kept on the stack (=IWRAM) for the entire duration of the
// text_loop() call. This is particularly bad because the whole mystery_gift_builder sequence is being triggered from within
// text_loop(). And there we need all the IWRAM we can muster.
// Doing it this way does mean that we need to completely restart decompression whenever we switch from dialog entry.
// but given that it requires user input to do so, I believe it's worth it and not time-critical.
// attribute noinline was used to make sure the compiler doesn't inline this code back into text_loop()
static __attribute__((noinline)) const u8* read_dialogue_text_entry(uint8_t index, u8 *output_buffer)
{
    u8 text_decompression_buffer[6144];
    const u8 *text_entry;

    text_data_table dialogue_table(text_decompression_buffer);

    dialogue_table.decompress(get_compressed_PTGB_table());

    text_entry = dialogue_table.get_text_entry(index);
    memcpy(output_buffer, text_entry, dialogue_table.get_text_entry_size(index));

    return output_buffer;
}

void init_text_engine()
{
    // Load the TTE
    // tte_init_se(3, BG_CBB(TEXT_CBB) | BG_SBB(TEXT_SBB) | BG_PRIO(0), 0, CLR_WHITE, 14, &japanese_smallFont, NULL);

    tte_init_chr4c(3,                                   // BG 0
                   BG_CBB(TEXT_CBB) | BG_SBB(TEXT_SBB), // Charblock 0; screenblock 31
                   0xF000,                              // Screen-entry offset
                   bytes2word(                          // Color attributes:
                       15,                              // Text color
                       0,                               // Shadow color
                       0,                               // Paper
                       0),                              // Special
                   CLR_WHITE,                           // White text
                   BUILD_FONT,                          // Custom font
                   NULL                                 // Use default chr4 renderer
    );
    tte_init_con();

    // tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
    // tte_set_pos(LEFT, TOP);

    pal_bg_bank[15][INK_WHITE] = CLR_WHITE;              // White
    pal_bg_bank[15][INK_DARK_GREY] = 0b0000110001100010; // Dark Grey
    // 14 will be changed to game color

    // Set default variables
    char_index = 0;
    line_char_index = 0;
    text_exit = false;
}

int text_loop(int script)
{
    // we have restricted the dialog entries to 1024 bytes in the text_helper main.py
    // so we shouldn't run into problems when we only use 1 KB to contain a text entry.
    u8 diag_entry_text_buffer[1024];
    switch (script)
    {
    case BTN_TRANSFER:
        curr_line = transfer_script_params[T_SCRIPT_START];
        break;

    case BTN_EVENTS:
        curr_line = event_script_params[E_SCRIPT_START];
        break;
    }

    curr_text = (curr_line.has_text()) ? read_dialogue_text_entry(curr_line.get_text_entry_index(), diag_entry_text_buffer) : NULL;

    REG_BG1CNT = (REG_BG1CNT && !BG_PRIO_MASK) | BG_PRIO(2); // Show Fennel
    show_text_box();
    // tte_set_margins(LEFT, TOP, RIGHT, BOTTOM);
    while (true) // This loops through all the connected script objects
    {
        if (curr_text != NULL && curr_text[char_index] != 0xFF && curr_text[char_index] != 0xFB)
        {
            tte_set_pos(LEFT, TOP);
            tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
            ptgb_write(curr_text, char_index);
        }

        wait_for_user_to_continue(false);

        line_char_index = 0;
        switch (script)
        {
        case BTN_TRANSFER:
            curr_line = transfer_script_params[text_next_obj_id(curr_line)];
            break;
        case BTN_EVENTS:
            curr_line = event_script_params[text_next_obj_id(curr_line)];
            break;
        }

        curr_text = (curr_line.has_text()) ? read_dialogue_text_entry(curr_line.get_text_entry_index(), diag_entry_text_buffer) : NULL;
        char_index = 0;

        if (text_exit)
        {
            hide_text_box();
            tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
            text_exit = false;
            return 0;
        }
    }
}

int text_next_obj_id(script_obj current_line)
{
    if (current_line.get_cond_id() == 0)
    {
        return current_line.get_true_index();
    }
    else
    {
        const bool ret = run_conditional(current_line.get_cond_id());
        VBlankIntrWait(); // this is needed to handle interrupts
        if (ret)
        {
            return current_line.get_true_index();
        }
        return current_line.get_false_index();
    }
}

void show_text_box()
{
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(1);
}

void hide_text_box()
{
    REG_BG2CNT = (REG_BG2CNT & ~BG_PRIO_MASK) | BG_PRIO(3);
}

void set_text_exit()
{
    text_exit = true;
    key_poll(); // This removes the "A Hit" when exiting the text
}

// Implement a version that just writes the whole string
int ptgb_write(const byte *text, bool instant)
{
    return ptgb_write(text, instant, 9999); // This is kinda silly but it'll work.
}

// Re-implementing TTE's "tte_write" to use the gen 3 character encoding chart
int ptgb_write(const byte *text, bool instant, int length)
{
    instant = instant || INSTANT_TEXT_SPEED;
    if (text == NULL)
        return 0;

    uint ch, gid;
    char *str = (char *)text;
    TTC *tc = tte_get_context();
    TFont *font;
    int num = 0;

/*
    if (curr_text[char_index] == 0xFB) // This will need to be moved
    {
        line_char_index += char_index;
        line_char_index++;
        // Low key kinda scuffed, but it works to split the string
        curr_text = &curr_line.get_text()[line_char_index];
    }
*/
    while ((ch = *str) != 0xFF && num < length)
    {
        if (get_frame_count() % 2 == 0 || key_held(KEY_B) || key_held(KEY_A) || instant)
        {
            str++;
            switch (ch)
            {
            case 0xFB:
                if (DISPLAY_CONTROL_CHAR)
                {
                    tc->drawgProc(0xB9);
                }
                wait_for_user_to_continue(true);
                break;
            case 0xFE:
                if (DISPLAY_CONTROL_CHAR)
                {
                    tc->drawgProc(0xEF);
                }
                tc->cursorY += tc->font->charH;
                tc->cursorX = tc->marginLeft;
                break;
            default:

                // Get glyph index and call renderer
                font = tc->font;
                gid = ch - font->charOffset;
                if (tc->charLut)
                    gid = tc->charLut[gid];

                // Character wrap
                int charW = font->widths ? font->widths[gid] : font->charW;

                // We don't want this tbh- all of the newlines should deal with moving to the next line
                /* if (tc->cursorX + charW > tc->marginRight)
                {
                    tc->cursorY += 10; // font->charH;
                    tc->cursorX = tc->marginLeft;
                } */

                // Draw and update position
                tc->drawgProc(gid);
                tc->cursorX += charW;
            }
            num += 1;
        }
        if (get_curr_flex_background() == BG_FENNEL && !instant)
        {
            fennel_speak(((num / 4) % 4) + 1);
        }
        if (!instant)
        {
            global_next_frame();
        }
    }

    // Return characters used (PONDER: is this really the right thing?)
    return 0; // str - text;
}
// This is mostly used for debug stuff, I shouldn't rely it on it much.
int ptgb_write_debug(const u16* charset, const char *text, bool instant)
{
    byte temp_holding[256];
    int i;
    for (i = 0; i < 256; i++)
    {
        if (text[i] == '\0')
        {
            temp_holding[i] = 0xFF;
            i = 256;
        }
        else if (text[i] == '\n')
        {
            temp_holding[i] = 0xFE;
        }
        else
        {
            temp_holding[i] = get_char_from_charset(charset, text[i]);
        }
    }
    return ptgb_write(temp_holding, instant);
}

// Adding this to avoid compiler issues temporarilly
int ptgb_write(const char *text)
{
    return 0;
}

void wait_for_user_to_continue(bool clear_text)
{
    if (get_curr_flex_background() == BG_FENNEL)
    {
        if (get_missingno_enabled())
        {
            fennel_speak(0);
            fennel_blink(4);
        }
        else
        {
            fennel_speak(0);
        }
    }
    while (!(key_hit(KEY_A) || key_hit(KEY_B) || curr_text == NULL))
    {
        global_next_frame();
    }
    if (clear_text)
    {
        tte_erase_rect(LEFT, TOP, RIGHT, BOTTOM);
        tte_set_pos(LEFT, TOP);
    }
}