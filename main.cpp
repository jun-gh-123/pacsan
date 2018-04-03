#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Sprite.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define TITLE "pacsan"
#define BLOCKSIZE 32
#define COLS 16
#define ROWS 24

const int WIDTH = BLOCKSIZE * COLS;
const int HEIGHT = BLOCKSIZE * ROWS;

SDL_Window *window = 0;
SDL_Renderer *renderer = 0;
SDL_Texture *spritesheet = 0;
Sprite block, pacsan, ghost;
bool quit = false;

bool init()
{
	if (!(SDL_Init(SDL_INIT_VIDEO) == 0))
	{
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Failed to initialize SDL_Image: %s\n", IMG_GetError());
		return false;
	}
	window = SDL_CreateWindow(
		"pacsan",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (!window)
	{
		printf("Failed to create SDL window: %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer)
	{
		printf("Failed to create SDL renderer: %s\n", SDL_GetError());
		return false;
	}

	// load sprites
	SDL_Surface *loaded = IMG_Load("assets/sprites.png");
	if (!loaded)
	{
		printf("Failed to load sprites.png: %s\n", IMG_GetError());
		return false;
	}
	spritesheet = SDL_CreateTextureFromSurface(renderer, loaded);
	SDL_FreeSurface(loaded);
	if (!spritesheet)
	{
		printf("Failed to create texture from sprites.png: %s\n", SDL_GetError());
		return false;
	}

	// init sprites
	block.Init(0, 0, BLOCKSIZE, BLOCKSIZE);
	pacsan.Init(BLOCKSIZE, 0, BLOCKSIZE, BLOCKSIZE);
	ghost.Init(3 * BLOCKSIZE, 0, BLOCKSIZE, BLOCKSIZE);
	pacsan.SetColor(255, 255, 0);

	return true;
}

void cleanup()
{
	SDL_DestroyTexture(spritesheet);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}

void loop(void *arg)
{
	// update
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}
	}

	if (quit)
	{
		#ifdef __EMSCRIPTEN__
		emscripten_cancel_main_loop();
		#endif
		return;
	}

	// render
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	SDL_RenderClear(renderer);
	pacsan.Render(50, 50, spritesheet, renderer);
	SDL_RenderPresent(renderer);
}

int main()
{
	if (init())
	{
		// loop
		#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop_arg(loop, NULL, -1, 1);
		#else
			while (!quit)
			{
				loop(NULL);
			}
		#endif
	}
	cleanup();

	return 0;
}
