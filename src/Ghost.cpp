#include <random>
#include "Ghost.hpp"

void Ghost::Init(
	int spriteCode
)
{
	this->SetSprite(spriteCode);
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
		int row = this->y / BLOCKSIZE;
		int col = this->x / BLOCKSIZE;

		if (offscreenCheck(row, col)) {
			return;
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
				if (game->powerUpTime <= 0) {
					dir = game->GetDirectionToPacsan(row, col);
				} else {
					dir = game->GetDirectionToPacsan(row, col, false);
				}
			}
			this->direction = dir;
			this->nextDirection = this->direction;
		}
	}
}
