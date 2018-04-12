#include <random>
#include "Ghost.hpp"

void Ghost::Init(
	int spriteCode
)
{
	this->SetSprite(spriteCode);
	this->defaultSpriteCode = spriteCode;
	this->spd = 2;
	this->mode = GhostMode::NORMAL;
}

void Ghost::Reset(
	int row, int col
)
{
	GameObject::Reset(row, col);
	this->SetMode(GhostMode::NORMAL);
}

void Ghost::Update(
	const Uint8 *keystate,
	Game *game
)
{
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
			std::uniform_int_distribution<int> uni(0, 5);
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
			this->SetSprite(this->defaultSpriteCode);
			break;
		case GhostMode::ESCAPE:
			this->SetSprite(SpriteCode::GHOST_ESCAPE);
			break;
		case GhostMode::DEAD:
			this->active = false;
			this->SetSprite(SpriteCode::GHOST_DEAD);
			break;
	}
	this->mode = mode;
}
