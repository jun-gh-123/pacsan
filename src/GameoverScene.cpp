#include "GameoverScene.hpp"
#include "globals.hpp"

void GameoverScene::Init()
{
	gManager.ShowTexts("GAMEOVER", "Press <enter> to continue.");
}

int GameoverScene::Update()
{
	if (gManager.IsKeyPressed(SDL_SCANCODE_RETURN)) {
		return SceneCode::OPENING;
	}
	return SceneCode::GAMEOVER;
}

void GameoverScene::Draw() {
	// do nothing
}
