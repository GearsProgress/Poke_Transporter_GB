#include <maxmod.h>
#include "sound.h"
#include "soundbank_bin.h"

static void sound_irq_handler(void)
{
    mmVBlank();
    mmFrame();
}

bool sound_init(void)
{
    irq_add(II_VBLANK, sound_irq_handler);

    mm_addr soundbank = (mm_addr)soundbank_bin;
    if (!soundbank)
    {
        return false;
    }

    mmInitDefault(soundbank, 16);
    return true;
}

void play_song(u32 song_index, bool loop)
{
    mmStart(song_index, loop ? MM_PLAY_LOOP : MM_PLAY_ONCE);
}

bool is_song_playing(void)
{
    return mmActive();
}

void stop_song(void)
{
    mmStop();
}

PTGBSFXHandle play_sound_effect(u32 sound_effect_index)
{
    return (PTGBSFXHandle)mmEffect(sound_effect_index);
}

void stop_sound_effect(PTGBSFXHandle handle)
{
    mmEffectCancel((mm_sfxhand)handle);
}

void stop_all_sound_effects(void)
{
    mmEffectCancelAll();
}

void release_sound_effect(PTGBSFXHandle handle)
{
    mmEffectRelease((mm_sfxhand)handle);
}

void play_jingle(u32 jingle_index)
{
    mmJingle(jingle_index);
}

bool is_jingle_playing(void)
{
    return mmActiveSub();
}