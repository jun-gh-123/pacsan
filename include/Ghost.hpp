#ifndef GHOST_HPP
#define GHOST_HPP

#include "GameObject.hpp"

class Ghost : public GameObject {
	private:
		int defaultSpriteCode = 0;
	public:
		int mode = GhostMode::NORMAL;
		void Init(int spriteCode);
		void Update(const Uint8 *keystate, Game *game);
		void Reset(int row, int col);
		void SetMode(int mode);
};

#endif
