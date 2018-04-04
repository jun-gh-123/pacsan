#ifndef PACSAN_HPP
#define PACSAN_HPP

#include "GameObject.hpp"
#include "Stage.hpp"

class Pacsan: public GameObject {
	enum class Direction {
		UP, DOWN, LEFT, RIGHT
	};

	private:
		bool moving;
		Stage *stage;
		int animateCount = 0;
		int spd = 2;
		Direction direction = Direction::RIGHT;
		Direction nextDirection = Direction::RIGHT;
	public:
		void Init(Stage *stage);
		void Update(const Uint8 *keystate);
};

#endif
