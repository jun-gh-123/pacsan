// standard libraries
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#include <emscripten.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

// project libraries
#include "params.hpp"
#include "Manager.hpp"
#include "Game.hpp"
#include "Pacsan.hpp"
#include "Ghost.hpp"
#include "Text.hpp"
#include "VariableText.hpp"

// globals
Manager gManager;

Game game;
Pacsan pacsan;
Ghost ghosts[4];
VariableText<int> scoreText;
bool quit = false;

bool init()
{
	if (!gManager.Init()) {
		return false;
	}
	scoreText.Init(&game.score);
	scoreText.scale = 2.0f;

	// init game
	game.Init();

	// init gameobjects
	pacsan.Init();
	pacsan.Reset(game.startRow, game.startCol);
	for (int i = 0; i < 4; i++) {
		ghosts[i].Init(SpriteCode::GHOST_RED + i);
		ghosts[i].Reset(ROWS / 2, COLS / 2);
	}

	return true;
}

void loop(void *arg)
{
	// update
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
			if (game.paused && e.key.keysym.sym == SDLK_z) {
				if (game.levelCleared) {
					game.NextLevel();
				} else {
					game.NewLife();
				}
				pacsan.Reset(game.startRow, game.startCol);
				for (int i = 0; i < 4; i++) {
					ghosts[i].Reset(ROWS / 2, COLS / 2);
				}
			}
		}
	}
	if (quit) {
		#ifdef __EMSCRIPTEN__
		emscripten_cancel_main_loop();
		#endif
		return;
	}

	if (!game.paused) {
		// update
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		pacsan.Update(keystate, &game);

		bool collided = false;
		for (int i = 0; i < 4 && !collided; i++) {
			ghosts[i].Update(keystate, &game);
			if (pacsan.IsColliding(&ghosts[i])) {
				collided = true;
			}
		}
		if (collided) {
			game.SetTexts("DEAD", "");
			game.paused = true;
		}
	}

	// render
	gManager.RenderClear(0, 0, 0);
	game.Draw();
	pacsan.Draw();
	for (int i = 0; i < 4; i++) {
		ghosts[i].Draw();
	}
	scoreText.Draw();
	gManager.RenderPresent();
}

int main()
{
	if (init()) {
		// loop
		#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop_arg(loop, NULL, -1, 1);
		#else
			while (!quit) {
				loop(NULL);
			}
		#endif
	}
	gManager.Quit();

	return 0;
}
