#include <iostream>
#include <vector>
#include "Game.hpp"
#include "globals.hpp"

void Game::Init()
{
	this->maxLevel = gManager.NumLevels();
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
	this->lives--;
	gManager.HideTexts();
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
	std::vector<int>* leveltiles = gManager.GetLevel(this->level);
	this->numPellets = 0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = (*leveltiles)[r * COLS + c];
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
		this->powerUpTime = 1000;
		this->onPowerUpStart();
	}
	this->tiles[row * COLS + col] = TileCode::EMPTY;

	if (!this->levelCleared && this->numPellets <= 0) {
		gManager.ShowTexts("Level cleared", "Press <space> to advance.");
		this->levelCleared = true;
		this->paused = true;
	}

	return tile;
}

void Game::Update()
{
	if (this->powerUpTime > 0) {
		this->powerUpTime--;
		if (this->powerUpTime <= 0) {
			this->onPowerUpEnd();
			this->powerUpTime = 0;
		}
	}
}
