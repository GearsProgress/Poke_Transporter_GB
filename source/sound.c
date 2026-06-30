#include <maxmod.h>
#include "sound.h"
#include "soundbank_bin.h"

//#define INCLUDE_SOUND


static void sound_irq_handler(void)
{
    #ifdef INCLUDE_SOUND
    mmVBlank();
    mmFrame();
    #endif
}

bool sound_init(void)
{
    #ifdef INCLUDE_SOUND
    irq_add(II_VBLANK, sound_irq_handler);

    mm_addr soundbank = (mm_addr)soundbank_bin;
    if (!soundbank)
    {
        return false;
    }

    mmInitDefault(soundbank, 16);
    return true;
    #endif
}

void play_song(u32 song_index, bool loop)
{
    #ifdef INCLUDE_SOUND
    mmStart(song_index, loop ? MM_PLAY_LOOP : MM_PLAY_ONCE);
    #endif
}

bool is_song_playing(void)
{
    #ifdef INCLUDE_SOUND
    return mmActive();
    #endif
}

void stop_song(void)
{
    #ifdef INCLUDE_SOUND
    mmStop();
    #endif
}

PTGBSFXHandle play_sound_effect(u32 sound_effect_index)
{
    #ifdef INCLUDE_SOUND
    return (PTGBSFXHandle)mmEffect(sound_effect_index);
    #endif
}

void stop_sound_effect(PTGBSFXHandle handle)
{
    #ifdef INCLUDE_SOUND
    mmEffectCancel((mm_sfxhand)handle);
    #endif
}

void stop_all_sound_effects(void)
{
    #ifdef INCLUDE_SOUND
    mmEffectCancelAll();
    #endif
}

void release_sound_effect(PTGBSFXHandle handle)
{
    #ifdef INCLUDE_SOUND
    mmEffectRelease((mm_sfxhand)handle);
    #endif
}

void play_jingle(u32 jingle_index)
{
    #ifdef INCLUDE_SOUND
    mmJingle(jingle_index);
    #endif
}

bool is_jingle_playing(void)
{
    #ifdef INCLUDE_SOUND
    return mmActiveSub();
    #endif
}