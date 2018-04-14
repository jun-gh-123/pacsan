#include <random>
#include "GameObject.hpp"
#include "globals.hpp"

void GameObject::Reset(
	int row, int col
)
{
	this->active = true;
	this->x = col * BLOCKSIZE;
	this->y = row * BLOCKSIZE;
	this->direction = Direction::NONE;
	this->nextDirection = Direction::NONE;
	this->angle = 0.0f;
}

bool GameObject::isAtIntersection(
	Game *game
)
{
	int row = this->y / BLOCKSIZE;
	int col = this->x / BLOCKSIZE;

	if (this->direction == Direction::UP || this->direction == Direction::DOWN) {
		if (game->GetTile(row, col - 1) != TileCode::BLOCK) {
			return true;
		}
		if (game->GetTile(row, col + 1) != TileCode::BLOCK) {
			return true;
		}
	}
	if (this->direction == Direction::LEFT || this->direction == Direction::RIGHT) {
		if (game->GetTile(row - 1, col) != TileCode::BLOCK) {
			return true;
		}
		int tiledown = game->GetTile(row + 1, col);
		if (tiledown != TileCode::BLOCK && tiledown != TileCode::DOOR) {
			return true;
		}
	}
	return false;
}

int GameObject::getTileInDirection(
	Direction dir,
	Game *game
)
{
	int row = this->y / BLOCKSIZE;
	int col = this->x / BLOCKSIZE;

	switch (dir) {
		case Direction::UP:
			row--;
			break;
		case Direction::DOWN:
			row++;
			break;
		case Direction::LEFT:
			col--;
			break;
		case Direction::RIGHT:
			col++;
			break;
		default:
			break;
	}

	return game->GetTile(row, col);
}

bool GameObject::offscreenCheck(
	int row, int col
)
{
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
	return offscreen;
}

Direction GameObject::getRandomDirection(
	int row, int col,
	Game *game
)
{
	bool found = false;
	while (!found) {
		Direction nextDirection = (Direction) gManager.GetRandomInt(1, 4);
		int tile = getTileInDirection(nextDirection, game);
		if (tile != TileCode::BLOCK) {
			if (tile != TileCode::DOOR || (nextDirection == Direction::UP && tile == TileCode::DOOR)) {
				found = true;
				return nextDirection;
			}
		}
	}
	return Direction::NONE;
}

void GameObject::SetSprite(
	int spriteCode
)
{
	this->spriteCode = spriteCode;
	this->sprite = &gManager.sprites[spriteCode];
}

void GameObject::Draw()
{
	this->sprite->Render(
		gManager.renderer,
		this->x, this->y,
		this->angle,
		this->scale,
		this->flip
	);
}

bool GameObject::IsColliding(
	GameObject *target
)
{
	if (!target->active) {
		return false;
	}
	if (this->x + BLOCKSIZE / 2 < target->x || this->x > target->x + BLOCKSIZE / 2) {
		return false;
	}
	if (this->y + BLOCKSIZE / 2 < target->y || this->y > target->y + BLOCKSIZE / 2) {
		return false;
	}
	return true;
}
