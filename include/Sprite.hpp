#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>

class Sprite {
	private:
		Uint8 r, g, b;
		SDL_Rect clip;
		SDL_Rect rect;
		double angle;
	public:
		static SDL_Texture *spritesheet;
		Sprite();
		void Init(int clipX, int clipY, int clipSize, int size);
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void Render(
			SDL_Renderer *renderer,
			int x, int y,
			double angle = 0.0f,
			SDL_RendererFlip flip = SDL_FLIP_NONE
		);
};

#endif
