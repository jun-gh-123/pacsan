#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

class Text {
	protected:
		SDL_Texture *texture;
		void CreateTexture(
			TTF_Font *font,
			SDL_Renderer *renderer,
			const char *text
		);
		int w = 0, h = 0;
	public:
		int x = 0, y = 0;
		float scale = 1.0f;
		Uint8 r, g, b;
		void Init(
			TTF_Font *font,
			SDL_Renderer *renderer,
			const char *text,
			Uint8 r = 255, Uint8 g = 255, Uint8 b = 255
		);
		int GetWidth();
		int GetHeight();
		void Draw(SDL_Renderer *renderer);
};

#endif
