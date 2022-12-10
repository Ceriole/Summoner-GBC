#include <gbdk/platform.h>
#include <stdint.h>
#include <gb/metasprites.h>

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define OBJ_POS_SUBPIX_MAG 3
#define OBJ_POS_TO_SCRN(V) ((V) >> OBJ_POS_SUBPIX_MAG)
#define OBJ_SCRN_TO_POS(V) ((V) << OBJ_POS_SUBPIX_MAG)

#define BIT(B) (1 << (B))

typedef struct animation_t
{
    uint8_t length, delay;
    uint8_t frames[];
} animation_t;

typedef struct aabb_t
{
    int8_t x, y;
    uint8_t w, h;
} aabb_t;

typedef struct
{
    uint16_t x, y;
    aabb_t collision;
    uint8_t tile_idx;
    animation_t* animations;
    metasprite_t** metasprites;
    uint8_t ms_idx, frame_idx, anim_idx, anim_timer;
    uint8_t timer;
    uint8_t flip_h : 1;
    uint8_t flip_v : 1;
    uint8_t collides : 1;
    uint8_t hide : 1;
    uint8_t flash : 1;
} object_t;

void create_object(object_t* object, uint16_t x, uint16_t y, aabb_t collision, uint8_t tile_idx, animation_t* animations, metasprite_t** metasprites) NONBANKED;

void obj_update(object_t* object) NONBANKED;
uint8_t obj_render(object_t* object, uint8_t oam_idx) NONBANKED;

inline void obj_set_pos(object_t* object, uint16_t x, uint16_t y);
inline void obj_move(object_t* object, int16_t x, int16_t y);

void obj_set_anim(object_t* object, uint8_t anim_idx) NONBANKED;

uint8_t obj_intersects(object_t* obj_a, object_t* obj_b) NONBANKED;

#endif // __OBJECT_H__