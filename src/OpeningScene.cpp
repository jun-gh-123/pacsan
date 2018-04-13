#include "OpeningScene.hpp"
#include "globals.hpp"

void OpeningScene::Init()
{
	gManager.ShowTexts("PACSAN", "Press <space> to start game.");
	this->animateCount = 0;
	this->spriteCode = SpriteCode::PACSAN_OPEN;
	this->highscoreText.Init(&gManager.highscore);
	this->highscoreText.scale = 2.0f;
}

int OpeningScene::Update()
{
	if (++this->animateCount >= 30) {
		if (this->spriteCode == SpriteCode::PACSAN_OPEN) {
			this->spriteCode = SpriteCode::PACSAN_CLOSE;
		} else {
			this->spriteCode = SpriteCode::PACSAN_OPEN;
		}
		this->animateCount = 0;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_SPACE)) {
		return SceneCode::GAME;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_E)) {
		return SceneCode::EDITOR;
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
	this->highscoreText.Draw();
}
