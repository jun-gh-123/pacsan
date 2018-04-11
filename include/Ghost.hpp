#ifndef GHOST_HPP
#define GHOST_HPP

#include "GameObject.hpp"

class Ghost : public GameObject {
	public:
		void Init(int spriteCode);
		void Update(const Uint8 *keystate, Game *game);
};

#endif
