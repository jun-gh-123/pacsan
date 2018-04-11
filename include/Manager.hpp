#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "params.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

using namespace std;

class Manager {
	private:
		vector<vector<int>> levels;
		bool textsVisible = true;
		Text header;
		Text subtext;
		bool loadLevels(const char *filepath);
	public:
		SDL_Window *window = 0;
		SDL_Renderer *renderer = 0;
		SDL_Texture *spritesheet = 0;
		TTF_Font *font = 0;
		Sprite sprites[SpriteCode::_SIZE];
		int highscore = 0;

		bool Init();
		void Quit();
		void RenderClear(Uint8 r, Uint8 g, Uint8 b);
		void RenderPresent();
		void HideTexts();
		void ShowTexts(const char *header, const char *subtext);
		int NumLevels();
		vector<int>* GetLevel(int level);
};

#endif
