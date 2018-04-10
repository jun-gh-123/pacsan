#include "GameoverScene.hpp"
#include "globals.hpp"

void GameoverScene::Init()
{
	gManager.ShowTexts("GAMEOVER", "Press <space> to continue.");
}

int GameoverScene::Update(
	const Uint8 *keystate
)
{
	if (keystate[SDL_SCANCODE_SPACE]) {
		return SceneCode::OPENING;
	}
	return SceneCode::GAMEOVER;
}

void GameoverScene::Draw() {
	// do nothing
}
