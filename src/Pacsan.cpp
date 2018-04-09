#include "Pacsan.hpp"

void Pacsan::Init()
{
	this->SetSprite(SpriteCode::PACSAN_OPEN);
}

void Pacsan::Reset(
	int row, int col
)
{
	GameObject::Reset(row, col);
	this->animateCount = 0;
	this->moving = false;
	this->SetSprite(SpriteCode::PACSAN_OPEN);
}

void Pacsan::Update(
	const Uint8 *keystate,
	Game *game
)
{
	if (keystate[SDL_SCANCODE_UP]) {
		this->nextDirection = Direction::UP;
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		this->nextDirection = Direction::DOWN;
	}
	if (keystate[SDL_SCANCODE_LEFT]) {
		this->nextDirection = Direction::LEFT;
	}
	if (keystate[SDL_SCANCODE_RIGHT]) {
		this->nextDirection = Direction::RIGHT;
	}

	if (this->moving) {
		this->animateCount++;
		if (this->animateCount >= 12) {
			if (this->spriteCode == SpriteCode::PACSAN_OPEN) {
				this->SetSprite(SpriteCode::PACSAN_CLOSE);
			} else {
				this->SetSprite(SpriteCode::PACSAN_OPEN);
			}
			this->animateCount = 0;
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
	}

	if (this->x % BLOCKSIZE == 0 && this->y % BLOCKSIZE == 0) {
		int row = this->row = this->y / BLOCKSIZE;
		int col = this->col = this->x / BLOCKSIZE;
		bool offscreen = false;

		game->EatPellet(row, col);

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

		if (getTileInDirection(this->nextDirection, game) != TileCode::BLOCK) {
			this->direction = this->nextDirection;
			this->nextDirection = this->direction;
			this->moving = true;
			switch (this->direction) {
				case Direction::UP:
					this->angle = 270.0f;
					break;
				case Direction::DOWN:
					this->angle = 90.0f;
					break;
				case Direction::LEFT:
					this->angle = 180.0f;
					break;
				case Direction::RIGHT:
					this->angle = 0.0f;
					break;
				default:
					this->moving = false;
					break;
			}
		} else {
			if (getTileInDirection(this->direction, game) == TileCode::BLOCK) {
				this->moving = false;
				this->SetSprite(SpriteCode::PACSAN_OPEN);
			}
		}
	}
}
