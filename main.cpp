// standard libraries
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL2/SDL_ttf.h>

// project libraries
#include "params.hpp"
#include "Manager.hpp"
#include "Scene.hpp"
#include "OpeningScene.hpp"
#include "GameScene.hpp"
#include "GameoverScene.hpp"
#include "EndingScene.hpp"
#include "LevelEditorScene.hpp"

// globals
Manager gManager;
int sceneCodeCurrent = SceneCode::OPENING;
Scene *scene;
OpeningScene opening;
GameScene game;
GameoverScene gameover;
EndingScene ending;
LevelEditorScene editor;
bool quit = false;

void setScene(int sceneCode) {
	switch (sceneCode) {
		case SceneCode::OPENING:
			scene = &opening;
			break;
		case SceneCode::GAME:
			scene = &game;
			break;
		case SceneCode::GAMEOVER:
			scene = &gameover;
			break;
		case SceneCode::ENDING:
			scene = &ending;
			break;
		case SceneCode::EDITOR:
			scene = &editor;
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

void loop()
{
	// update
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		#ifndef __EMSCRIPTEN__
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
		}
		#endif
	}
	if (quit) {
		return;
	}

	int numkeys = 0;
	const Uint8 *keystate = SDL_GetKeyboardState(&numkeys);
	gManager.UpdateKeys(keystate, numkeys);
	int sceneCode = scene->Update();
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
			emscripten_set_main_loop(loop, 0, 1);
		#else
			while (!quit) {
				loop();
			}
		#endif
	}
	gManager.Quit();

	return 0;
}
