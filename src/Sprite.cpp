#include "Sprite.hpp"

Sprite::Sprite()
{
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->angle = 0.0f;
}

void Sprite::Init(
	int clipX,
	int clipY,
	int clipSize,
	int size
)
{
	this->clip.x = clipX;
	this->clip.y = clipY;
	this->clip.w = clipSize;
	this->clip.h = clipSize;
}

void Sprite::SetColor(
	Uint8 r, Uint8 g, Uint8 b
)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Sprite::Render(
	int x,
	int y,
	SDL_Texture *spritesheet,
	SDL_Renderer *renderer
)
{
	SDL_Rect dstrect = {
		x,
		y,
		this->clip.w,
		this->clip.h
	};
	SDL_SetTextureColorMod(spritesheet, this->r, this->g, this->b);
	SDL_RenderCopyEx(renderer, spritesheet, &this->clip, &dstrect, this->angle, NULL, SDL_FLIP_NONE);
}
