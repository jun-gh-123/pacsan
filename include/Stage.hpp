#ifndef STAGE_HPP
#define STAGE_HPP

#include "params.hpp"
#include "Sprite.hpp"

class Stage {
	private:
		SDL_Texture *blocksTexture = 0;
		int tiles[ROWS * COLS];
		int heatmap[ROWS * COLS];
	public:
		~Stage();
		void LoadLevel(SDL_Renderer *renderer, Sprite *sprites, int level);
		int GetTile(int row, int col);
		void SetTile(int row, int col, int val);
		void Draw(SDL_Renderer *renderer, Sprite *sprites);
};

#endif
