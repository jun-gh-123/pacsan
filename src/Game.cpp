#include "Game.hpp"
#include "levels.hpp"

Game::~Game()
{
	if (this->blocksTexture) {
		SDL_DestroyTexture(this->blocksTexture);
	}
}

void Game::LoadLevel(
	SDL_Renderer *renderer,
	Sprite *sprites,
	int level
)
{
	if (!this->blocksTexture) {
		this->blocksTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
	}
	SDL_SetRenderTarget(renderer, this->blocksTexture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Sprite *block = &sprites[SpriteCode::BLOCK];
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = levels[level][r * COLS + c];
			if (tilecode == TileCode::BLOCK) {
				block->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			}
			this->tiles[r * COLS + c] = tilecode;
		}
	}
	SDL_SetRenderTarget(renderer, NULL);
}

int Game::GetTile(
	int row, int col
)
{
	if (row < 0 || row >= ROWS) {
		return TileCode::EMPTY;
	}
	if (col < 0 || col >= COLS) {
		return TileCode::EMPTY;
	}
	return this->tiles[row * COLS + col];
}

void Game::SetTile(
	int row, int col, int val
)
{
	if (row < 0 || row >= ROWS) {
		return;
	}
	if (col < 0 || col >= COLS) {
		return;
	}
	this->tiles[row * COLS + col] = val;
}

void Game::Draw(
	SDL_Renderer *renderer,
	Sprite *sprites
)
{
	// draw blocks
	SDL_RenderCopy(renderer, this->blocksTexture, NULL, NULL);

	// draw pellets
	Sprite *pellet = &sprites[SpriteCode::PELLET];
	Sprite *superPellet = &sprites[SpriteCode::SUPER_PELLET];
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = this->tiles[r * COLS + c];
			if (tilecode == TileCode::PELLET) {
				pellet->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			} else if (tilecode == TileCode::SUPER_PELLET) {
				superPellet->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			}
		}
	}

}
