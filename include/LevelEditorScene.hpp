#ifndef LEVELEDITORSCENE_HPP
#define LEVELEDITORSCENE_HPP

#include "params.hpp"
#include "Scene.hpp"
#include "VariableText.hpp"

class LevelEditorScene : public Scene {
	private:
		int currentLevel = 0;
		int cx = 0, cy = 0;
		VariableText<int> levelText;
		void setTileAtCursor(int tilecode);
	public:
		void Init();
		int Update();
		void Draw();
};

#endif
