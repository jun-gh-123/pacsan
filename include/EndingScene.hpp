#ifndef ENDINGSCENE_HPP
#define ENDINGSCENE_HPP

#include "Scene.hpp"
#include "VariableText.hpp"

class EndingScene : public Scene {
	private:
		VariableText<int> scoretext;
	public:
		void Init();
		int Update();
		void Draw();
};

#endif
