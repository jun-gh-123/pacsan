#include "EndingScene.hpp"
#include "globals.hpp"

void EndingScene::Init()
{
	gManager.ShowTexts("YOU WIN", "Press <enter> to continue.");
}

int EndingScene::Update()
{
	if (gManager.IsKeyPressed(SDL_SCANCODE_RETURN)) {
		return SceneCode::OPENING;
	}
	return SceneCode::ENDING;
}

void EndingScene::Draw() {
	// do nothing
}
