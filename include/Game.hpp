#ifndef GAME_HPP
#define GAME_HPP

#include <functional>
#include <vector>
#include <SDL2/SDL.h>
#include "params.hpp"

using namespace std;

class Game {
	private:
		int heatmap[ROWS * COLS];
	public:
		int tiles[ROWS * COLS];
		bool paused = false;
		int lives = 3;
		int score = 0;
		int numPellets = 0;
		int level = 0, maxLevel;
		int startRow, startCol;
		bool levelCleared = false;
		int powerUpTime = 0;
		std::function<void()> onPowerUpStart = 0;
		std::function<void()> onPowerUpEnd = 0;

		void Init();
		void NextLevel(SDL_Texture **blocksTexture);
		void NewLife();
		void LoadLevel(int level, SDL_Texture **blocksTexture);
		int GetTile(int row, int col);
		void SetTile(int row, int col, int val);
		int EatPellet(int row, int col);
		void Update();
};

#endif
