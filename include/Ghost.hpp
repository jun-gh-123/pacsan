#ifndef GHOST_HPP
#define GHOST_HPP

#include "GameObject.hpp"

class Ghost : public GameObject {
	private:
		int defaultSpriteCode = 0;
		int chaseRate = 1;
		bool checkStart(
			int denominator,
			Game *game
		);
	public:
		bool started = false;
		int mode = GhostMode::NORMAL;
		void Init(int spriteCode, int chaseRate);
		void Update(Game *game);
		void Reset(int row, int col);
		void SetMode(int mode);
};

#endif
