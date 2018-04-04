#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "params.hpp"
#include "Sprite.hpp"
#include "Pacsan.hpp"
#include "Stage.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window = 0;
SDL_Renderer *renderer = 0;
SDL_Texture *spritesheet = 0;
Sprite sprites[4];
Pacsan pacsan;
Stage stage;
int tiles[ROWS][COLS];
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
	Sprite::spritesheet = spritesheet;
	Sprite::renderer = renderer;
	for (int i = 0; i < 4; i++)
	{
		sprites[i].Init(i * BLOCKSIZE, 0 , BLOCKSIZE, BLOCKSIZE);
	}
	sprites[SpriteCode::BLOCK].SetColor(50, 100, 255);
	sprites[SpriteCode::PACSAN_OPEN].SetColor(255, 255, 120);
	sprites[SpriteCode::PACSAN_CLOSE].SetColor(255, 255, 120);
	sprites[SpriteCode::GHOST].SetColor(255, 40, 40);

	// init tiles
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			if (c == 0 || c == COLS - 1 || r == 0 || r == ROWS - 1 || (r % 2 == 0 && c% 2 == 0))
			{
				tiles[r][c] = 1;
			}
			else
			{
				tiles[r][c] = 0;
			}
		}
	}
	tiles[ROWS / 2][0] = 0;
	tiles[ROWS / 2][COLS - 1] = 0;
	tiles[0][COLS / 2] = 0;
	tiles[ROWS - 1][COLS / 2] = 0;
	stage.Init(renderer, &sprites[SpriteCode::BLOCK], tiles);

	// init gameobjects
	GameObject::sprites = sprites;
	pacsan.Init(&stage);
	pacsan.x = BLOCKSIZE;
	pacsan.y = BLOCKSIZE;

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

	// update
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	pacsan.Update(keystate);

	// render
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	SDL_RenderClear(renderer);
	stage.Draw(renderer);
	pacsan.Draw();
	sprites[SpriteCode::GHOST].Render(BLOCKSIZE * (COLS - 2), BLOCKSIZE);

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
