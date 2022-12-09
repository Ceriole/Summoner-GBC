#include "object.h"

#include <string.h>

void create_object(object_t* object, uint16_t x, uint16_t y, uint8_t tile_idx, animation_t* animations, metasprite_t** metasprites)
{
    memset(object, 0, sizeof(object_t));
    object->x = x;
    object->y = y;
    object->animations = animations;
    object->metasprites = metasprites;
    object->anim_timer = object->animations[0].delay;
    object->ms_idx = object->animations[0].frames[0];
    object->tile_idx = tile_idx;
}

void obj_update(object_t* object)
{
    animation_t* curr_anim = &object->animations[object->anim_idx];
    if(object->anim_timer == 0)
    {
        object->anim_timer = curr_anim->delay;
        object->frame_idx++;
        if(object->frame_idx == curr_anim->length)
            object->frame_idx = 0;
        object->ms_idx = curr_anim->frames[object->frame_idx];
    }
    object->anim_timer--;
}

uint8_t obj_render(object_t* object, uint8_t oam_idx)
{
    metasprite_t* current_sprite = object->metasprites[object->ms_idx];
    if(object->hide)
        hide_metasprite(current_sprite, oam_idx);
    else
    {
        switch (object->flip)
        {
        default:
        case OBJ_FLIP_NONE: oam_idx = move_metasprite(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y)); break;
        case OBJ_FLIP_H:    oam_idx = move_metasprite_hflip(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y)); break;
        case OBJ_FLIP_V:    oam_idx = move_metasprite_vflip(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y)); break;
        case OBJ_FLIP_BOTH: oam_idx = move_metasprite_hvflip(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y)); break;
        }
    }
    return oam_idx;
}

inline void obj_set_pos(object_t* object, uint16_t x, uint16_t y)
{
    object->x = x;
    object->y = y;
}

inline void obj_move(object_t* object, int16_t x, int16_t y)
{
    object->x += x;
    object->y += y;
}

void obj_set_anim(object_t* object, uint8_t anim_idx)
{
    if(object->anim_idx == anim_idx)
        return;
    object->anim_timer = object->animations[anim_idx].delay;
    object->frame_idx = 0;
    object->ms_idx = object->animations[anim_idx].frames[0];
    object->anim_idx = anim_idx;
}