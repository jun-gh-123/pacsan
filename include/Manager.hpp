#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "Sprite.hpp"

class Manager {
	public:
		SDL_Window *window = 0;
		SDL_Renderer *renderer = 0;
		SDL_Texture *spritesheet = 0;
		TTF_Font *font = 0;
		Sprite sprites[8];
		bool Init();
		void Quit();
};

#endif
