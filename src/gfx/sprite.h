#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <gbdk/platform.h>
#include <stdint.h>
#include <gb/metasprites.h>

#define BIT(B) (1 << (B))

typedef struct animframe_t
{
    uint8_t ms_idx, delay;
} animframe_t;

typedef struct animation_t
{
    uint8_t length;
    animframe_t frames[];
} animation_t;

typedef struct
{
    uint8_t x, y;
    uint8_t tile_idx;
    const animation_t** animations;
    const metasprite_t** metasprites;
    uint8_t ms_idx, frame_idx, anim_idx, anim_timer;
    uint8_t timer;
    uint8_t flip_h : 1, flip_v : 1;
    uint8_t hide : 1;
    uint8_t flash : 1;
} sprite_t;

void create_sprite(sprite_t* spr, uint8_t x, uint8_t y, uint8_t tile_idx, const animation_t** animations, const metasprite_t** metasprites) NONBANKED;

void spr_update(sprite_t* spr) NONBANKED;
uint8_t spr_render(sprite_t* spr, uint8_t oam_idx) NONBANKED;

inline void spr_set_pos(sprite_t* spr, uint8_t x, uint8_t y);
inline void spr_move(sprite_t* spr, int8_t x, int8_t y);

void spr_set_anim(sprite_t* spr, uint8_t anim_idx) NONBANKED;

#endif // __SPRITE_H__