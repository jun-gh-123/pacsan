#include <iostream>
#include "Game.hpp"
#include "levels.hpp"
#include "globals.hpp"

Game::~Game()
{
	if (this->blocksTexture) {
		SDL_DestroyTexture(this->blocksTexture);
	}
}

void Game::Init()
{
	this->maxLevel = sizeof(levels) / sizeof(*levels);
	this->level = 0;
	this->LoadLevel(this->level);
	this->SetTexts("PAC-SAN", "this is a subtext");
}

void Game::SetTexts(
	const char *headerstr,
	const char *subtextstr
)
{
	this->header.Set(headerstr);
	this->subtext.Set(subtextstr);

	this->header.scale = 4.0f;
	this->header.x = WIDTH / 2 - this->header.GetWidth() / 2;
	this->header.y = HEIGHT / 2 - this->header.GetHeight() / 2;

	this->subtext.scale = 2.0f;
	this->subtext.x = WIDTH / 2 - this->subtext.GetWidth() / 2;
	this->subtext.y = this->header.y + this->header.GetHeight();
}

void Game::NextLevel()
{
	this->level++;
	if (this->level >= this->maxLevel) {
		this->SetTexts("THE END", "You beat the game.");
	} else {
		this->levelCleared = false;
		this->paused = false;
		this->LoadLevel(this->level);
		this->SetTexts("", "");
	}
}

void Game::NewLife()
{
	this->paused = false;
	this->SetTexts("", "");
	this->lives--;
}

void Game::LoadLevel(
	int level
)
{
	SDL_Renderer *renderer = gManager.renderer;
	Sprite *sprites = gManager.sprites;

	if (!this->blocksTexture) {
		this->blocksTexture = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT
		);
	}
	SDL_SetRenderTarget(renderer, this->blocksTexture);
	SDL_SetTextureBlendMode(this->blocksTexture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Sprite *block = &sprites[SpriteCode::BLOCK];
	this->numPellets = 0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = levels[level][r * COLS + c];
			if (tilecode == TileCode::BLOCK) {
				block->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
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
		this->SetTexts("Level cleared", "Press 'z' to advance.");
		this->levelCleared = true;
		this->paused = true;
	}

	return tile;
}

void Game::Draw()
{
	SDL_Renderer *renderer = gManager.renderer;
	Sprite *sprites = gManager.sprites;

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

	// draw texts
	this->header.Draw();
	this->subtext.Draw();
}
