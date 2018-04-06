#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "params.hpp"
#include "Sprite.hpp"
#include "Stage.hpp"

class GameObject {
	protected:
		enum class Direction {
			UP, DOWN, LEFT, RIGHT, NONE
		};
		Sprite *sprite;
		int spriteCode;
		int spd = 2;
		Direction direction = Direction::NONE;
		Direction nextDirection = Direction::NONE;
	public:
		static Sprite *sprites;
		int x, y;
		double angle = 0.0f;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		virtual void Init() = 0;
		void SetSprite(int spriteCode);
		void Draw(SDL_Renderer *renderer);
};

#endif
