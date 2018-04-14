#ifndef GAME_HPP
#define GAME_HPP

#include <functional>
#include <SDL2/SDL.h>
#include "params.hpp"

using namespace std;

typedef struct {
	int row;
	int col;
	int score;
} PathmapItem;

class Game {
	private:
		int pathmapGhostBase[ROWS * COLS];
		int pathmapPacsan[ROWS * COLS];
		Direction getPathDirection(
			int *pathmap,
			int r, int c,
			bool chase = true,
			bool blockDoor = false
		);
		void updatePathmap(int *pathmap, int r, int c);
		void printPathmap(int *pathmap);
	public:
		int tiles[ROWS * COLS];
		bool paused = false;
		int lives = 3;
		int score = 0;
		int pelletsRemaining = 0;
		int pelletsEaten = 0;
		int level = 0, maxLevel;
		int startRow, startCol;
		bool levelCleared = false;
		int powerUpTime = 0;
		int blinkClock = 0;
		bool blinkOn = false;
		std::function<void()> onPowerUpStart = 0;
		std::function<void()> onPowerUpEnd = 0;

		void Init();
		void NextLevel(SDL_Texture **blocksTexture);
		void NewLife();
		void LoadLevel(int level, SDL_Texture **blocksTexture);
		void UpdatePathmapPacsan(int row, int col);
		int GetTile(int row, int col);
		void SetTile(int row, int col, int val);
		int EatPellet(int row, int col);
		void Update();
		Direction GetDirectionToPacsan(int row, int col, bool chase = true);
		Direction GetDirectionToGhostBase(int row, int col);
};

#endif
