#include <random>
#include "Ghost.hpp"

void Ghost::Init(
	int spriteCode,
	int chaseRate
)
{
	this->SetSprite(spriteCode);
	this->defaultSpriteCode = spriteCode;
	this->spd = 2;
	this->mode = GhostMode::NORMAL;
	this->chaseRate = chaseRate;
}

void Ghost::Reset(
	int row, int col
)
{
	GameObject::Reset(row, col);
	this->SetMode(GhostMode::NORMAL);
	this->started = false;
}

bool Ghost::checkStart(
	int denominator,
	Game *game
)
{
	return game->pelletsEaten > game->pelletsRemaining / denominator;
}

void Ghost::Update(
	Game *game
)
{
	if (!this->started) {
		switch (this->defaultSpriteCode) {
			case SpriteCode::GHOST_RED:
				this->started = true;
				break;
			case SpriteCode::GHOST_PINK:
				this->started = checkStart(8, game);
				break;
			case SpriteCode::GHOST_CYAN:
				this->started = checkStart(4, game);
				break;
			case SpriteCode::GHOST_ORANGE:
				this->started = checkStart(2, game);
				break;
		}
		if (!this->started) {
			return;
		}
	}

	if (this->defaultSpriteCode == SpriteCode::GHOST_ORANGE) {
		if (game->pelletsEaten < game->pelletsRemaining / 2) {
			this->started = false;
			return;
		} else {
			this->started = true;
		}
	}

	// blink ghost if powerup is about to expire
	if (this->mode == GhostMode::ESCAPE) {
		if (game->powerUpTime < 180) {
			if (++this->blinkClock > 10) {
				if (this->spriteCode == SpriteCode::GHOST_ESCAPE) {
					this->SetSprite(SpriteCode::GHOST_WHITE);
				} else {
					this->SetSprite(SpriteCode::GHOST_ESCAPE);
				}
				this->blinkClock = 0;
			}
		}
	}

	switch (this->direction) {
		case Direction::UP:
			this->y -= this->spd;
			break;
		case Direction::DOWN:
			this->y += this->spd;
			break;
		case Direction::LEFT:
			this->x -= this->spd;
			break;
		case Direction::RIGHT:
			this->x += this->spd;
			break;
		default:
			break;
	}

	if (this->x % BLOCKSIZE == 0 && this->y % BLOCKSIZE == 0) {
		int row = this->y / BLOCKSIZE;
		int col = this->x / BLOCKSIZE;

		if (offscreenCheck(row, col)) {
			return;
		}

		if (this->mode == GhostMode::DEAD) {
			if (row == ROWS / 2 && col == COLS / 2) {
				this->SetMode(GhostMode::NORMAL);
			} else {
				this->direction = game->GetDirectionToGhostBase(row, col);
				this->nextDirection = this->direction;
				return;
			}
		}

		// get random next direction
		int currentTile = game->GetTile(row, col);
		int tile = getTileInDirection(this->direction, game);
		bool atIntersection = isAtIntersection(game);
		if ((currentTile != TileCode::DOOR && atIntersection) || this->direction == Direction::NONE || tile == TileCode::BLOCK || tile == TileCode::DOOR) {
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> uni(0, this->chaseRate);
			Direction dir;

			if (uni(rng) == 0) {
				dir = getRandomDirection(row, col, game);
			} else {
				if (this->mode == GhostMode::NORMAL) {
					dir = game->GetDirectionToPacsan(row, col);
				} else if (this->mode == GhostMode::ESCAPE) {
					dir = game->GetDirectionToPacsan(row, col, false);
				}
			}
			this->direction = dir;
			this->nextDirection = this->direction;
		}
	}
}

void Ghost::SetMode(
	int mode
)
{
	switch (mode) {
		case GhostMode::NORMAL:
			this->active = true;
			this->spd = 2;
			this->SetSprite(this->defaultSpriteCode);
			break;
		case GhostMode::ESCAPE:
			this->blinkClock = 0;
			this->SetSprite(SpriteCode::GHOST_ESCAPE);
			break;
		case GhostMode::DEAD:
			this->active = false;
			this->spd = 4;
			if (this->x % 4 != 0) {
				this->x += this->x % 4;
			}
			if (this->y %4 != 0) {
				this->y += this->y % 4;
			}
			this->SetSprite(SpriteCode::GHOST_DEAD);
			break;
	}
	this->mode = mode;
}
