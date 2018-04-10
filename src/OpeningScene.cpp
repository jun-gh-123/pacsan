#include "OpeningScene.hpp"
#include "globals.hpp"

void OpeningScene::Init()
{
	gManager.ShowTexts("PACSAN", "Press <space> to start game.");
}

int OpeningScene::Update(
	const Uint8 *keystate
)
{
	if (keystate[SDL_SCANCODE_SPACE]) {
		return SceneCode::GAME;
	}
	return SceneCode::OPENING;
}

void OpeningScene::Draw()
{
	gManager.sprites[SpriteCode::PACSAN_OPEN].Render(
		gManager.renderer,
		WIDTH / 2 - BLOCKSIZE / 2, 200
	);
}
