#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include <hUGEDriver.h>

extern hUGESong_t *current_track, *last_track;
extern uint8_t music_paused;

#define DECLARE_MUSIC(SONG) extern const void __bank_ ## SONG; extern const hUGESong_t SONG

#define music_init hUGE_init(0);
#define music_pause music_paused = TRUE
#define music_unpause music_paused = FALSE
#define music_stop music_pause; music_mute(HT_CH_MUTE); music_unpause

#define music_mute_channel(CHANNEL) if(last_music) hUGE_mute_channel(CHANNEL, HT_CH_MUTE)

void music_callback(void) NONBANKED;

void music_play(const hUGESong_t* track, uint8_t bank) NONBANKED;
void music_mute(uint8_t mute) NONBANKED;

#endif // __MUSIC_H__