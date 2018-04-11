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
		bool skipdown = false;
		SDL_Texture *blocksTexture = 0;
		Game game;
		Pacsan pacsan;
		Ghost ghosts[4];
		VariableText<int> scoreText;
		VariableText<int> livesText;
		void resetGameObjects();
		void onPowerUpStart();
		void onPowerUpEnd();
	public:
		void Init();
		int Update(const Uint8 *keystate);
		void Draw();
};


#endif
