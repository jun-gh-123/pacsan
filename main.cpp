#include <iostream>
#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define TITLE "pacsan"
#define BLOCKSIZE 32
#define COLS 16
#define ROWS 32

const int WIDTH = BLOCKSIZE * COLS;
const int HEIGHT = BLOCKSIZE * ROWS;

SDL_Window *window = 0;
SDL_Renderer *renderer = 0;
bool quit = false;

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
	SDL_RenderPresent(renderer);
}

int main()
{
	// init
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(
		"pacsan",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// loop
	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(loop, NULL, -1, 1);
	#else
	while (!quit)
	{
		loop(NULL);
	}
	#endif

	// exit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
