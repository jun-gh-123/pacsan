#ifndef STAGE_HPP
#define STAGE_HPP

#include "params.hpp"
#include "Sprite.hpp"

class Stage {
	private:
		SDL_Texture *texture = 0;
		int tiles[ROWS][COLS];
	public:
		~Stage();
		void Init(SDL_Renderer *renderer, Sprite *block, int tiles[ROWS][COLS]);
		bool IsBlock(int row, int col);
		void Draw(SDL_Renderer *renderer);
};

#endif
