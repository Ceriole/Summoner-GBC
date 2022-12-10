#include "object.h"

#include <string.h>

void create_object(object_t* object, uint16_t x, uint16_t y, aabb_t collision, uint8_t tile_idx, animation_t* animations, metasprite_t** metasprites) NONBANKED
{
    memset(object, 0, sizeof(object_t));
    object->x = x;
    object->y = y;
    object->collision = collision;
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
    if(object->timer)
        object->timer--;
}

uint8_t obj_render(object_t* object, uint8_t oam_idx) NONBANKED
{
    const metasprite_t* current_sprite = object->metasprites[object->ms_idx];
    if(object->hide || object->flash || (object->timer / 2) % 2)
        hide_metasprite(current_sprite, oam_idx);
    else
    {
        if(object->flip_h && object->flip_v)
            oam_idx = move_metasprite_hvflip(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y));
        else if(object->flip_h)
            oam_idx = move_metasprite_hflip(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y));
        else if(object->flip_v)
            oam_idx = move_metasprite_vflip(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y));
        else
            oam_idx = move_metasprite(current_sprite, object->tile_idx, oam_idx, OBJ_POS_TO_SCRN(object->x), OBJ_POS_TO_SCRN(object->y));
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

void obj_set_anim(object_t* object, uint8_t anim_idx) NONBANKED
{
    if(object->anim_idx == anim_idx)
        return;
    object->anim_timer = object->animations[anim_idx].delay;
    object->frame_idx = 0;
    object->ms_idx = object->animations[anim_idx].frames[0];
    object->anim_idx = anim_idx;
}

uint8_t obj_intersects(object_t* obj_a, object_t* obj_b) NONBANKED
{
    if(obj_a == obj_b)
        return 0;
    if(!obj_a->collides || !obj_b->collides)
        return 0;
    aabb_t* bb_a = &obj_a->collision;
    aabb_t* bb_b = &obj_b->collision;
    uint16_t a_x_min = obj_a->x + bb_a->x,  a_y_min = obj_a->y + bb_a->y;
    uint16_t b_x_min = obj_b->x + bb_b->x,  b_y_min = obj_b->y + bb_b->y; 
    uint16_t a_x_max = a_x_min + bb_a->w,   a_y_max = a_y_min + bb_a->h;
    uint16_t b_x_max = b_x_min + bb_b->w,   b_y_max = b_y_min + bb_b->h;
    return a_x_min < a_x_max && a_x_max > b_x_min && a_y_min < a_y_max && a_y_max > b_y_min;
    /*
    if(a_x_min < a_x_max && a_x_max > b_x_min)
    {
        if(a_y_min < a_y_max && a_y_max > b_y_min)
        {
            return 1;
        }
        return 0;
    }
    return 0;
    */
}