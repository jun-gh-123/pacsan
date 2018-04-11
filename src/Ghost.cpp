#include <random>
#include "Ghost.hpp"

void Ghost::Init(
	int spriteCode
)
{
	this->SetSprite(spriteCode);
	this->spd = 2;
}

void Ghost::Update(
	const Uint8 *keystate,
	Game *game
)
{
	if (!this->active) {
		return;
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
		int row = this->row = this->y / BLOCKSIZE;
		int col = this->col = this->x / BLOCKSIZE;
		bool offscreen = false;

		if (row < 0) {
			this->y = ROWS * BLOCKSIZE;
			offscreen = true;
		}
		if (row >= ROWS) {
			this->y = -BLOCKSIZE;
			offscreen = true;
		}
		if (col < 0) {
			this->x = COLS * BLOCKSIZE;
			offscreen = true;
		}
		if (col >= COLS) {
			this->x = -BLOCKSIZE;
			offscreen = true;
		}

		if (offscreen) {
			return;
		}

		// get random next direction
		int currentTile = game->GetTile(row, col);
		int tile = getTileInDirection(this->direction, game);
		bool atIntersection = isAtIntersection(game);
		if ((currentTile != TileCode::DOOR && atIntersection) || this->direction == Direction::NONE || tile == TileCode::BLOCK || tile == TileCode::DOOR) {
			bool found = false;
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> uni(0, 4);
			while (!found) {
				Direction nextDirection = (Direction) uni(rng);
				tile = getTileInDirection(nextDirection, game);
				if (tile != TileCode::BLOCK) {
					if (tile != TileCode::DOOR || (nextDirection == Direction::UP && tile == TileCode::DOOR)) {
						found = true;
						this->nextDirection = nextDirection;
					}
				}
			}

			this->direction = this->nextDirection;
			this->nextDirection = this->direction;
		}
	}
}
