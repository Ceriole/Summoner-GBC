#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdint.h>
#include <gb/metasprites.h>

#define OBJ_POS_SUBPIX_MAG 3
#define OBJ_POS_TO_SCRN(V) ((V) >> OBJ_POS_SUBPIX_MAG)
#define OBJ_SCRN_TO_POS(V) ((V) << OBJ_POS_SUBPIX_MAG)

#define OBJ_FLIP_NONE 0
#define OBJ_FLIP_H    1
#define OBJ_FLIP_V    2
#define OBJ_FLIP_BOTH 3

typedef struct
{
    uint8_t length, delay;
    uint8_t frames[];
} animation_t;

typedef struct
{
    uint16_t x, y;
    uint8_t tile_idx;
    animation_t* animations;
    metasprite_t** metasprites;
    uint8_t ms_idx, frame_idx, anim_idx, anim_timer;
    uint8_t flip, hide;
} object_t;

void create_object(object_t* object, uint16_t x, uint16_t y, uint8_t tile_idx, animation_t* animations, metasprite_t** metasprites);

void obj_update(object_t* object);
uint8_t obj_render(object_t* object, uint8_t oam_idx);

inline void obj_set_pos(object_t* object, uint16_t x, uint16_t y);
inline void obj_move(object_t* object, int16_t x, int16_t y);

void obj_set_anim(object_t* object, uint8_t anim_idx);

#endif // __OBJECT_H__