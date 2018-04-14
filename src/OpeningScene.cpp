#include "OpeningScene.hpp"
#include "globals.hpp"

void OpeningScene::Init()
{
	gManager.ShowTexts("PACSAN", "Press <space> to start game.");
	this->animateCount = 0;
	this->spriteCode = SpriteCode::PACSAN_OPEN;
	this->highscoreText.Init(&gManager.highscore);
	this->highscoreText.scale = 2.0f;
	this->instructions.Set("Use <arrow keys> to move.", 200, 200, 200);
	this->instructions.scale = 2.0f;
	this->instructions.x = WIDTH / 2 - this->instructions.GetWidth() / 2;
	this->instructions.y = HEIGHT / 2 + 35;
	this->credit.Set("(C) PANICPUMPKIN [pansound.com/panicpumpkin]", 100, 150, 255);
	this->credit.scale = 1.5f;
	this->credit.x = WIDTH / 2 - this->credit.GetWidth() / 2;
	this->credit.y = HEIGHT - this->credit.GetHeight() - 10;
	this->creditLabel.Set("Sound/Music Credit", 100, 150, 255);
	this->creditLabel.scale = 1.75f;
	this->creditLabel.x = WIDTH / 2 - this->creditLabel.GetWidth() / 2;
	this->creditLabel.y = this->credit.y - this->creditLabel.GetHeight() - 5;
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
	this->instructions.Draw();
	this->credit.Draw();
	this->creditLabel.Draw();
}
