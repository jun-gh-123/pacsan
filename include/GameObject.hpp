#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "params.hpp"
#include "Sprite.hpp"
#include "Game.hpp"

class GameObject {
	protected:
		enum class Direction {
			UP, DOWN, LEFT, RIGHT, NONE
		};
		Sprite *sprite;
		int spriteCode;
		int spd = 4;
		Direction direction = Direction::NONE;
		Direction nextDirection = Direction::NONE;
		int getTileInDirection(Direction dir, Game *game);
		bool isAtIntersection(Game *game);
	public:
		int x, y;
		int row, col;
		double angle = 0.0f;
		double scale = 1.0f;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		void Reset(int row, int col);
		void SetSprite(int spriteCode);
		void Draw();
		bool IsColliding(GameObject *target);
};

#endif
