#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <gbdk/platform.h>
#include <gb/gb.h>
#include <stdint.h>

#include <hUGEDriver.h>

extern hUGESong_t *current_track, *last_track;
extern uint8_t music_paused;

#define DECLARE_MUSIC(SONG) extern const void __bank_ ## SONG; extern const hUGESong_t SONG

#define MUSIC_INIT hUGE_init(0)
#define MUSIC_PLAY(TRACK, BNK) music_play(TRACK, BNK)
#define MUSIC_MUTE(MUTE) music_mute(MUTE)
#define MUSIC_PAUSE music_paused = TRUE
#define MUSIC_UNPAUSE music_paused = FALSE
#define MUSIC_STOP MUSIC_PAUSE; music_mute(HT_CH_MUTE); MUSIC_UNPAUSE

#define music_mute_channel(CHANNEL) if(last_music) hUGE_mute_channel(CHANNEL, HT_CH_MUTE)

void music_callback(void) NONBANKED;

void music_play(const hUGESong_t* track, uint8_t bank) NONBANKED;
void music_mute(uint8_t mute) NONBANKED;

#endif // __MUSIC_H__