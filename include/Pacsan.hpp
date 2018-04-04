#ifndef PACSAN_HPP
#define PACSAN_HPP

#include "GameObject.hpp"

class Pacsan: public GameObject {
	enum class Direction {
		Up, Down, Left, Right
	};

	private:
		int animateCount = 0;
		int spd = 2;
		Direction direction = Direction::Right;
		Direction nextDirection = Direction::Right;
	public:
		void Update(const Uint8 *keystate);
};

#endif
