#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "params.hpp"
#include "Sprite.hpp"

class GameObject {
	protected:
		Sprite *sprite;
		int spriteCode;
	public:
		static Sprite *sprites;
		int x, y;
		int row, col;
		double angle = 0.0f;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		void Init(int spriteCode);
		void SetSprite(int spriteCode);
		virtual void Update(const Uint8 *keystate) = 0;
		void Draw();
};

#endif
