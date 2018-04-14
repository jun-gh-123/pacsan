#include "GameoverScene.hpp"
#include "globals.hpp"

void GameoverScene::Init()
{
	gManager.ShowTexts("GAMEOVER", "Press <enter> to continue.");
	gManager.PlaySound(SoundCode::GAMEOVER);
	this->scoretext.Init(&gManager.lastscore);
	this->scoretext.scale = 4.0f;
	this->scoretext.x = WIDTH / 2 - this->scoretext.GetWidth() / 2;
	this->scoretext.y = 3 * HEIGHT / 4 - this->scoretext.GetHeight() / 2;
}

int GameoverScene::Update()
{
	if (gManager.IsKeyPressed(SDL_SCANCODE_RETURN)) {
		gManager.StopAllAudio();
		return SceneCode::OPENING;
	}
	return SceneCode::GAMEOVER;
}

void GameoverScene::Draw() {
	this->scoretext.Draw();
}
