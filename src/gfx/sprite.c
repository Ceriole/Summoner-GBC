#include "sprite.h"

#include <string.h>

void create_sprite(sprite_t* spr, uint8_t x, uint8_t y, uint8_t tile_idx, const animation_t** animations, const metasprite_t** metasprites) NONBANKED
{
	memset(spr, 0, (uint8_t) sizeof(sprite_t));
	spr->x = x;
	spr->y = y;
	spr->animations = animations;
	spr->metasprites = metasprites;
	spr->anim_timer = animations[0]->frames[0].delay;
	spr->ms_idx = animations[0]->frames[0].ms_idx;
	spr->tile_idx = tile_idx;
}

void spr_update(sprite_t* spr)
{
	const animation_t* curr_anim = spr->animations[spr->anim_idx];
	if(spr->anim_timer == 0)
	{
		spr->frame_idx++;
		if(spr->frame_idx == curr_anim->length)
			spr->frame_idx = 0;
		const animframe_t* curr_frame = &curr_anim->frames[spr->frame_idx];
		spr->anim_timer = curr_frame->delay;
		spr->ms_idx = curr_frame->ms_idx;
	}
	else
		spr->anim_timer--;
	spr->timer++;
}

volatile extern uint16_t global_timer;
uint8_t spr_render(sprite_t* spr, uint8_t oam_idx) NONBANKED
{
	const metasprite_t* current_sprite = spr->metasprites[spr->ms_idx];
	if(spr->hide || (spr->flash && ((global_timer / 2) % 2)))
		return 0;

	if(spr->flip_h && spr->flip_v)
		return move_metasprite_hvflip(current_sprite, spr->tile_idx, oam_idx, spr->x, spr->y);
	if(spr->flip_h)
		return move_metasprite_hflip(current_sprite, spr->tile_idx, oam_idx, spr->x, spr->y);
	if(spr->flip_v)
		return move_metasprite_vflip(current_sprite, spr->tile_idx, oam_idx, spr->x, spr->y);
	
	return move_metasprite(current_sprite, spr->tile_idx, oam_idx, spr->x, spr->y);
}

inline void spr_set_pos(sprite_t* spr, uint8_t x, uint8_t y)
{
	spr->x = x;
	spr->y = y;
}

inline void spr_move(sprite_t* spr, int8_t x, int8_t y)
{
	spr->x += x;
	spr->y += y;
}

void spr_set_anim(sprite_t* spr, uint8_t anim_idx) NONBANKED
{
	if(spr->anim_idx == anim_idx)
		return;
	const animation_t* base_anim = spr->animations[anim_idx];
	const animframe_t* base_frames = base_anim->frames;
	spr->frame_idx = 0;
	spr->anim_timer = base_frames->delay;
	spr->ms_idx = base_frames->ms_idx;
	spr->anim_idx = anim_idx;
}