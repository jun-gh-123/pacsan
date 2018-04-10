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
#include "Scene.hpp"
#include "OpeningScene.hpp"
#include "GameScene.hpp"

// globals
Manager gManager;

int sceneCodeCurrent = SceneCode::OPENING;
Scene *scene;
OpeningScene opening;
GameScene game;
bool quit = false;

void setScene(int sceneCode) {
	switch (sceneCode) {
		case SceneCode::OPENING:
			scene = &opening;
			break;
		case SceneCode::GAME:
			scene = &game;
			break;
		case SceneCode::ENDING:
			// todo
			break;
	}
	scene->Init();
	sceneCodeCurrent = sceneCode;
}

bool init()
{
	if (!gManager.Init()) {
		return false;
	}
	setScene(SceneCode::OPENING);

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
		}
	}
	if (quit) {
		#ifdef __EMSCRIPTEN__
		emscripten_cancel_main_loop();
		#endif
		return;
	}

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	int sceneCode = scene->Update(keystate);
	if (sceneCode != sceneCodeCurrent) {
		setScene(sceneCode);
	}

	// render
	gManager.RenderClear(0, 0, 0);
	scene->Draw();
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
