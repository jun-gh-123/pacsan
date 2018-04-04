#include "Stage.hpp"

Stage::~Stage()
{
	if (this->texture)
	{
		SDL_DestroyTexture(this->texture);
	}
}

void Stage::Init(
	SDL_Renderer *renderer,
	Sprite *block,
	int tiles[ROWS][COLS]
)
{
	if (!this->texture)
	{
		this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	}
	SDL_SetRenderTarget(renderer, this->texture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			this->tiles[r][c] = tiles[r][c];
			if (tiles[r][c])
			{
				block->Render(c * BLOCKSIZE, r * BLOCKSIZE);
			}
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
}

bool Stage::IsBlock(
	int row, int col
)
{
	return this->tiles[row][col];
}

void Stage::Draw(
	SDL_Renderer *renderer
)
{
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
}
