#include "Pacsan.hpp"

void Pacsan::Update(
	const Uint8 *keystate
)
{
	this->animateCount++;
	if (this->animateCount >= 8)
	{
		if (this->spriteCode == SpriteCode::PACSAN_OPEN)
		{
			this->SetSprite(SpriteCode::PACSAN_CLOSE);
		}
		else
		{
			this->SetSprite(SpriteCode::PACSAN_OPEN);
		}
		this->animateCount = 0;
	}

	if (keystate[SDL_SCANCODE_UP])
	{
		this->nextDirection = Direction::Up;
	}
	if (keystate[SDL_SCANCODE_DOWN])
	{
		this->nextDirection = Direction::Down;
	}
	if (keystate[SDL_SCANCODE_LEFT])
	{
		this->nextDirection = Direction::Left;
	}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		this->nextDirection = Direction::Right;
	}

	switch (this->direction)
	{
		case Direction::Up:
			this->y -= this->spd;
			this->angle = 270.0f;
			break;
		case Direction::Down:
			this->y += this->spd;
			this->angle = 90.0f;
			break;
		case Direction::Left:
			this->x -= this->spd;
			this->angle = 180.0f;
			break;
		case Direction::Right:
			this->x += this->spd;
			this->angle = 0.0f;
			break;
	}
	if (this->x % BLOCKSIZE == 0 && this->y % BLOCKSIZE == 0)
	{
		this->direction = this->nextDirection;
		this->nextDirection = this->direction;
	}
}
