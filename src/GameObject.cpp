#include "GameObject.hpp"

Sprite *GameObject::sprites = 0;

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
	this->sprite = &sprites[spriteCode];
}

void GameObject::Draw(
	SDL_Renderer *renderer
)
{
	this->sprite->Render(
		renderer,
		this->x, this->y,
		this->angle,
		this->flip
	);
}
