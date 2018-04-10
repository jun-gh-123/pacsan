#include "EndingScene.hpp"
#include "globals.hpp"

void EndingScene::Init()
{
	gManager.ShowTexts("YOU WIN", "Good job. Press <enter> to continue.");
}

int EndingScene::Update(
	const Uint8 *keystate
)
{
	if (keystate[SDL_SCANCODE_RETURN]) {
		return SceneCode::OPENING;
	}
	return SceneCode::ENDING;
}

void EndingScene::Draw() {
	// do nothing
}
