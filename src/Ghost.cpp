#include <random>
#include "Ghost.hpp"

void Ghost::Init()
{
	this->spd = 2;
	this->SetSprite(SpriteCode::GHOST_CHASE);
}

void Ghost::Update(
	const Uint8 *keystate,
	Stage *stage
)
{
	switch (this->direction)
	{
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
	}

	if (this->x % BLOCKSIZE == 0 && this->y % BLOCKSIZE == 0)
	{
		int row = this->y / BLOCKSIZE;
		int col = this->x / BLOCKSIZE;
		bool offscreen = false;

		if (row < 0)
		{
			this->y = ROWS * BLOCKSIZE;
			offscreen = true;
		}
		if (row >= ROWS)
		{
			this->y = -BLOCKSIZE;
			offscreen = true;
		}
		if (col < 0)
		{
			this->x = COLS * BLOCKSIZE;
			offscreen = true;
		}
		if (col >= COLS)
		{
			this->x = -BLOCKSIZE;
			offscreen = true;
		}

		if (offscreen)
		{
			return;
		}

		// get random next direction
		bool found = false;
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(0, 4);
		while (!found)
		{
			int nextrow = row;
			int nextcol = col;
			Direction nextDirection = (Direction) uni(rng);

			switch (nextDirection)
			{
				case Direction::UP:
					nextrow--;
					break;
				case Direction::DOWN:
					nextrow++;
					break;
				case Direction::LEFT:
					nextcol--;
					break;
				case Direction::RIGHT:
					nextcol++;
					break;
			}

			if (stage->GetTile(nextrow, nextcol) != TileCode::BLOCK)
			{
				found = true;
				this->nextDirection = nextDirection;
			}
		}

		this->direction = this->nextDirection;
		this->nextDirection = this->direction;
	}
}
