#ifndef OPENINGSCENE_HPP
#define OPENINGSCENE_HPP

#include "Scene.hpp"
#include "VariableText.hpp"

class OpeningScene : public Scene {
	private:
		int animateCount;
		int spriteCode;
		VariableText<int> highscoreText;
		Text instructions;
	public:
		void Init();
		int Update();
		void Draw();
};

#endif
