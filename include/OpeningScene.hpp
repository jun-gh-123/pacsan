#ifndef OPENINGSCENE_HPP
#define OPENINGSCENE_HPP

#include "Scene.hpp"

class OpeningScene : public Scene {
	private:
		int animateCount;
		int spriteCode;
	public:
		void Init();
		int Update(const Uint8 *keystate);
		void Draw();
};

#endif
