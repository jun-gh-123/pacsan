#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

class Text {
	public:
		SDL_Texture *texture;
		int x = 0, y = 0;
		int w = 0, h = 0;
		double scale = 1.0f;
		void Init(
			TTF_Font *font,
			SDL_Renderer *renderer,
			const char *text,
			Uint8 r, Uint8 g, Uint8 b
		);
		void Draw(SDL_Renderer *renderer);
};

#endif
