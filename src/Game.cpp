#include <iostream>
#include "Game.hpp"
#include "levels.hpp"
#include "globals.hpp"

void Game::Init()
{
	this->maxLevel = sizeof(levels) / sizeof(*levels);
	this->level = 0;
	this->score = 0;
	this->lives = 3;
	this->levelCleared = false;
	this->paused = false;
}

void Game::NextLevel(
	SDL_Texture **blocksTexture
)
{
	this->level++;
	this->levelCleared = false;
	this->paused = false;
	this->LoadLevel(this->level, blocksTexture);
	gManager.HideTexts();
}

void Game::NewLife()
{
	this->paused = false;
	gManager.HideTexts();
	this->lives--;
}

void Game::LoadLevel(
	int level, SDL_Texture **blocksTexture
)
{
	SDL_Renderer *renderer = gManager.renderer;
	Sprite *sprites = gManager.sprites;

	if (!(*blocksTexture)) {
		(*blocksTexture) = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT
		);
	}
	SDL_SetRenderTarget(renderer, (*blocksTexture));
	SDL_SetTextureBlendMode((*blocksTexture), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Sprite *block = &sprites[SpriteCode::BLOCK];
	Sprite *door = &sprites[SpriteCode::DOOR];
	this->numPellets = 0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = levels[level][r * COLS + c];
			if (tilecode == TileCode::BLOCK) {
				block->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			} else if (tilecode == TileCode::DOOR) {
				door->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			} else if (tilecode == TileCode::PELLET || tilecode == TileCode::SUPER_PELLET) {
				this->numPellets++;
			} else if (tilecode == TileCode::PACSAN) {
				this->startRow = r;
				this->startCol = c;
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

int Game::EatPellet(
	int row, int col
)
{
	if (row < 0 || row >= ROWS) {
		return TileCode::EMPTY;
	}
	if (col < 0 || col >= COLS) {
		return TileCode::EMPTY;
	}

	int tile = this->tiles[row * COLS + col];

	if (tile == TileCode::PELLET) {
		this->score += 10;
		this->numPellets--;
	} else if (tile == TileCode::SUPER_PELLET) {
		this->score += 50;
		this->numPellets--;
	}
	this->tiles[row * COLS + col] = TileCode::EMPTY;

	if (!this->levelCleared && this->numPellets <= 0) {
		gManager.ShowTexts("Level cleared", "Press <space> to advance.");
		this->levelCleared = true;
		this->paused = true;
	}

	return tile;
}
