#ifndef GAME_HPP
#define GAME_HPP

#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "params.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Manager.hpp"

class Game {
	private:
		SDL_Texture *blocksTexture = 0;
		int tiles[ROWS * COLS];
		int heatmap[ROWS * COLS];
		Text header;
		Text subtext;
	public:
		bool paused = false;
		int lives = 3;
		int score = 0;
		int numPellets = 0;
		int level = 0, maxLevel;
		int startRow, startCol;
		bool levelCleared = false;
		~Game();
		void Init();
		void SetTexts(const char *header, const char *subtext);
		void NextLevel();
		void LoadLevel(int level);
		int GetTile(int row, int col);
		void SetTile(int row, int col, int val);
		int EatPellet(int row, int col);
		void Draw();
};

#endif
