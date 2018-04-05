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
	int *tiles
)
{
	this->tiles = tiles;
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
			if (tiles[r * COLS + c])
			{
				block->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			}
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
}

bool Stage::IsBlock(
	int row, int col
)
{
	if (row < 0 || row >= ROWS)
	{
		return false;
	}
	if (col < 0 || col >= COLS)
	{
		return false;
	}
	return this->tiles[row * COLS + col];
}

void Stage::Draw(
	SDL_Renderer *renderer
)
{
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
}
