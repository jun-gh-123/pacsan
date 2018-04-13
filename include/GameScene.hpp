#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "params.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"
#include "Pacsan.hpp"
#include "Ghost.hpp"
#include "VariableText.hpp"

class GameScene : public Scene {
	private:
		SDL_Texture *blocksTexture = 0;
		Game game;
		Pacsan pacsan;
		Ghost ghosts[4];
		int countdown, countdownclock;
		VariableText<int> scoreText;
		VariableText<int> livesText;
		VariableText<int> countdownText;
		void resetGameObjects();
		void onPowerUpStart();
		void onPowerUpEnd();
	public:
		void Init();
		int Update();
		void Draw();
};


#endif
