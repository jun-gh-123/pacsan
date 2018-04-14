#include "EndingScene.hpp"
#include "globals.hpp"

void EndingScene::Init()
{
	gManager.ShowTexts("YOU WIN", "Press <enter> to continue.");
	gManager.PlaySound(SoundCode::YOUWIN);
	this->scoretext.Init(&gManager.lastscore);
	this->scoretext.scale = 4.0f;
	this->scoretext.x = WIDTH / 2 - this->scoretext.GetWidth() / 2;
	this->scoretext.y = 3 * HEIGHT / 4 - this->scoretext.GetHeight() / 2;
}

int EndingScene::Update()
{
	if (gManager.IsKeyPressed(SDL_SCANCODE_RETURN)) {
		gManager.StopAllAudio();
		return SceneCode::OPENING;
	}
	return SceneCode::ENDING;
}

void EndingScene::Draw() {
	this->scoretext.Draw();
}
