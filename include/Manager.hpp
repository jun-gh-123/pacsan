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
		vector<int> keys;
		bool textsVisible = true;
		Text header;
		Text subtext;
		bool loadLevels(const char *filepath);
	public:
		// vars
		SDL_Window *window = 0;
		SDL_Renderer *renderer = 0;
		SDL_Texture *spritesheet = 0;
		TTF_Font *font = 0;
		Sprite sprites[SpriteCode::_SIZE];
		int highscore = 0;
		// basic
		bool Init();
		void Quit();
		void RenderClear(Uint8 r, Uint8 g, Uint8 b);
		void RenderPresent();
		// text
		void HideTexts();
		void ShowTexts(const char *header, const char *subtext);
		// levels
		int NumLevels();
		vector<int>* GetLevel(int level);
		vector<int>* InsertLevel(int level);
		int AppendLevel();
		void ResetLevel(int level);
		void SetTile(int level, int row, int col, int tile);
		int DeleteLevel(int level);
		int SaveLevelsToFile(const char *filepath);
		// sprite
		Sprite* GetSprite(int spritecode);
		// keys
		void UpdateKeys(const Uint8 *keystate, int numkeys);
		bool IsKeyPressed(int scancode);
		bool IsKeyDown(int scancode);
		bool IsKeyReleased(int scancode);
		bool IsKeyUp(int scancode);
};

#endif
