#ifndef GAME_HPP
#define GAME_HPP

#include "params.hpp"
#include "Sprite.hpp"

class Game {
	private:
		SDL_Texture *blocksTexture = 0;
		int tiles[ROWS * COLS];
		int heatmap[ROWS * COLS];
	public:
		int lives = 3;
		int score = 0;
		~Game();
		void LoadLevel(SDL_Renderer *renderer, Sprite *sprites, int level);
		int GetTile(int row, int col);
		void SetTile(int row, int col, int val);
		void Draw(SDL_Renderer *renderer, Sprite *sprites);
};

#endif
