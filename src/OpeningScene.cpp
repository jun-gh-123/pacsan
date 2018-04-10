#include "OpeningScene.hpp"
#include "globals.hpp"

void OpeningScene::Init()
{
	gManager.ShowTexts("PACSAN", "Press <space> to start game.");
	this->animateCount = 0;
	this->spriteCode = SpriteCode::PACSAN_OPEN;
}

int OpeningScene::Update(
	const Uint8 *keystate
)
{
	if (++this->animateCount >= 30) {
		if (this->spriteCode == SpriteCode::PACSAN_OPEN) {
			this->spriteCode = SpriteCode::PACSAN_CLOSE;
		} else {
			this->spriteCode = SpriteCode::PACSAN_OPEN;
		}
		this->animateCount = 0;
	}
	if (keystate[SDL_SCANCODE_SPACE]) {
		return SceneCode::GAME;
	}
	return SceneCode::OPENING;
}

void OpeningScene::Draw()
{
	int y = 300;
	int centerX = WIDTH / 2 - 2 * BLOCKSIZE / 3;
	gManager.sprites[this->spriteCode].Render(
		gManager.renderer, centerX, y, 0.0f, 1.5f
	);
}
