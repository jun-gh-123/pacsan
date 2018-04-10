#ifndef GAMEOVERSCENE_HPP
#define GAMEOVERSCENE_HPP

#include "Scene.hpp"

class GameoverScene : public Scene {
	public:
		void Init();
		int Update(const Uint8 *keystate);
		void Draw();
};

#endif
