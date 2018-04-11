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

void GameObject::SetSprite(
	int spriteCode
)
{
	this->spriteCode = spriteCode;
	this->sprite = &gManager.sprites[spriteCode];
}

void GameObject::Draw()
{
	if (!this->active) {
		return;
	}
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
	return target->row == this->row && target->col == this->col;
}
