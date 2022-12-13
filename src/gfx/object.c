#include "object.h"

#include <string.h>

void create_object(object_t* object, uint16_t x, uint16_t y, aabb_t collision, uint8_t tile_idx, const animation_t** animations, const metasprite_t** metasprites) NONBANKED
{
	memset(object, 0, (uint8_t) sizeof(object_t));
	object->x = x;
	object->y = y;
	object->collision = collision;
	object->animations = animations;
	object->metasprites = metasprites;
	object->anim_timer = animations[0]->frames[0].delay;
	object->ms_idx = animations[0]->frames[0].ms_idx;
	object->tile_idx = tile_idx;
}

void obj_update(object_t* object)
{
	const animation_t* curr_anim = object->animations[object->anim_idx];
	if(object->anim_timer == 0)
	{
		object->frame_idx++;
		if(object->frame_idx == curr_anim->length)
			object->frame_idx = 0;
		const animframe_t* curr_frame = &curr_anim->frames[object->frame_idx];
		object->anim_timer = curr_frame->delay;
		object->ms_idx = curr_frame->ms_idx;
	}
	else
		object->anim_timer--;
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
		const uint8_t obj_scr_x = OBJ_POS_TO_SCRN(object->x);
		const uint8_t obj_scr_y = OBJ_POS_TO_SCRN(object->y);
		if(object->flip_h && object->flip_v)
			oam_idx += move_metasprite_hvflip(current_sprite, object->tile_idx, oam_idx, obj_scr_x, obj_scr_y);
		else if(object->flip_h)
			oam_idx += move_metasprite_hflip(current_sprite, object->tile_idx, oam_idx, obj_scr_x, obj_scr_y);
		else if(object->flip_v)
			oam_idx += move_metasprite_vflip(current_sprite, object->tile_idx, oam_idx, obj_scr_x, obj_scr_y);
		else
			oam_idx += move_metasprite(current_sprite, object->tile_idx, oam_idx, obj_scr_x, obj_scr_y);
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
	const animation_t* base_anim = object->animations[anim_idx];
	const animframe_t* base_frames = base_anim->frames;
	object->frame_idx = 0;
	object->anim_timer = base_frames->delay;
	object->ms_idx = base_frames->ms_idx;
	object->anim_idx = anim_idx;
}

uint8_t obj_intersects(object_t* obj_a, object_t* obj_b) NONBANKED
{
	if(obj_a == NULL || obj_b == NULL)
		return FALSE;
	if(obj_a == obj_b)
		return FALSE;
	if(!obj_a->collides || !obj_b->collides)
		return FALSE;
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