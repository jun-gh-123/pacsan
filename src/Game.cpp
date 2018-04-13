#include <algorithm>
#include <iostream>
#include <queue>
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
	this->powerUpTime = 0;
}

void Game::NextLevel(
	SDL_Texture **blocksTexture
)
{
	this->level++;
	this->levelCleared = false;
	this->paused = false;
	this->LoadLevel(this->level, blocksTexture);
	this->powerUpTime = 0;
	gManager.HideTexts();
}

void Game::NewLife()
{
	this->paused = false;
	this->lives--;
	gManager.HideTexts();
	UpdatePathmapPacsan(this->startRow, this->startCol);
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
	UpdatePathmapPacsan(this->startRow, this->startCol);
	updatePathmap(this->pathmapGhostBase, ROWS / 2, COLS / 2);
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
		this->powerUpTime = 600;
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

void Game::printPathmap(
	int *pathmap
)
{
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int n = pathmap[r * COLS + c];
			if (n == -1 || n > 9) {
				printf("%i ", n);
			} else {
				printf(" %i ", n);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void Game::updatePathmap(
	int *pathmap,
	int r, int c
)
{
	std::fill_n(pathmap, ROWS * COLS, -1);
	std::queue<PathmapItem> queue;
	queue.push((PathmapItem){ r, c, 0 });

	while (queue.size() > 0) {
		PathmapItem pi = queue.front();
		queue.pop();
		if (pathmap[pi.row * COLS + pi.col] != -1) {
			continue;
		}
		pathmap[pi.row * COLS + pi.col] = pi.score;

		for (int i = -1; i <= 1; i += 2) {
			int row = pi.row;
			int col = pi.col;
			int row2 = pi.row + i;
			int col2 = pi.col + i;

			if (row2 < 0) {
				row2 = ROWS + row2;
			}
			if (row2 >= ROWS) {
				row2 = row2 - ROWS;
			}
			if (col2 < 0) {
				col2 = COLS + col2;
			}
			if (col2 >= COLS) {
				col2 = col2 - COLS;
			}

			if (this->tiles[row * COLS + col2] != TileCode::BLOCK) {
				if (pathmap[row * COLS + col2] == -1) {
						queue.push((PathmapItem){ row, col2, pi.score + 1 });
				}
			}
			if (this->tiles[row2 * COLS + col] != TileCode::BLOCK) {
				if (pathmap[row2 * COLS + col] == -1) {
					queue.push((PathmapItem){ row2, col, pi.score + 1 });
				}
			}
		}
	}
}

void Game::UpdatePathmapPacsan(
	int pr, int pc
)
{
	std::fill_n(pathmapPacsan, ROWS * COLS, -1);
	updatePathmap(pathmapPacsan, pr, pc);
	// printPathmap(pathmapPacsan);
}

Direction Game::getPathDirection(
	int *pathmap,
	int row, int col,
	bool chase
)
{
	int up = row - 1 < 0 ? ROWS - 1 : row - 1;
	int down = row + 1 >= ROWS ? 0 : row + 1;
	int left = col - 1 < 0 ? COLS - 1 : col - 1;
	int right = col + 1 >= COLS ? 0 : col + 1;
	Direction dir = Direction::NONE;
	int score = (chase ? 999 : -999), n;

	n = pathmap[up * COLS + col];
	if (n > -1 && (chase ? n < score : n > score)) {
		score = n;
		dir = Direction::UP;
	}
	n = pathmap[down * COLS + col];
	if (n > -1 && (chase ? n < score : n > score)) {
		score = n;
		dir = Direction::DOWN;
	}
	n = pathmap[row * COLS + left];
	if (n > -1 && (chase ? n < score : n > score)) {
		score = n;
		dir = Direction::LEFT;
	}
	n = pathmap[row * COLS + right];
	if (n > -1 && (chase ? n < score : n > score)) {
		score = n;
		dir = Direction::RIGHT;
	}
	return dir;
}

Direction Game::GetDirectionToPacsan(
	int row, int col,
	bool chase
)
{
	return getPathDirection(this->pathmapPacsan, row, col, chase);
}

Direction Game::GetDirectionToGhostBase(
	int row, int col
)
{
	return getPathDirection(this->pathmapGhostBase, row, col);
}
