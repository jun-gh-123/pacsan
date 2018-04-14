#ifndef GAMEOVERSCENE_HPP
#define GAMEOVERSCENE_HPP

#include "Scene.hpp"
#include "VariableText.hpp"

class GameoverScene : public Scene {
	private:
		VariableText<int> scoretext;
	public:
		void Init();
		int Update();
		void Draw();
};

#endif
