#ifndef STAGE_HPP
#define STAGE_HPP

#include "params.hpp"
#include "Sprite.hpp"

class Stage {
	private:
		SDL_Texture *texture = 0;
		int *tiles;
		int heatmap[ROWS * COLS];
	public:
		~Stage();
		void Init(SDL_Renderer *renderer, Sprite *block, int *tiles);
		bool IsBlock(int row, int col);
		void Draw(SDL_Renderer *renderer);
};

#endif
