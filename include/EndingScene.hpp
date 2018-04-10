#ifndef ENDINGSCENE_HPP
#define ENDINGSCENE_HPP

#include "Scene.hpp"

class EndingScene : public Scene {
	public:
		void Init();
		int Update(const Uint8 *keystate);
		void Draw();
};

#endif
