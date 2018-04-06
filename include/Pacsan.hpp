#ifndef PACSAN_HPP
#define PACSAN_HPP

#include "GameObject.hpp"
#include "Game.hpp"

class Pacsan: public GameObject {
	private:
		bool moving;
		int animateCount = 0;
	public:
		void Init();
		void Update(const Uint8 *keystate, Stage *stage, Game *game);
};

#endif
