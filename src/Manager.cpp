#include <iostream>
#include "Manager.hpp"

bool Manager::Init()
{
	if (!(SDL_Init(SDL_INIT_VIDEO) == 0)) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("Failed to initialize SDL_Image: %s\n", IMG_GetError());
		return false;
	}
	if (!(TTF_Init() == 0)) {
		printf("Failed to inialize SDL_ttf: %s\n", TTF_GetError());
		return false;
	}
	window = SDL_CreateWindow(
		"pacsan",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (!window) {
		printf("Failed to create SDL window: %s\n", SDL_GetError());
		return false;
	}
	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer) {
		printf("Failed to create SDL renderer: %s\n", SDL_GetError());
		return false;
	}

	// load font, init texts
	font = TTF_OpenFont("assets/8bitOperatorPlus8-Regular.ttf", 14);
	if (!font) {
		printf("Failed to load font: %s\n", TTF_GetError());
		return false;
	}

	// load sprites
	SDL_Surface *loaded = IMG_Load("assets/sprites.png");
	if (!loaded) {
		printf("Failed to load sprites.png: %s\n", IMG_GetError());
		return false;
	}
	spritesheet = SDL_CreateTextureFromSurface(renderer, loaded);
	SDL_FreeSurface(loaded);
	if (!spritesheet) {
		printf("Failed to create texture from sprites.png: %s\n", SDL_GetError());
		return false;
	}

	// init sprites
	Sprite::spritesheet = spritesheet;
	int x = 0;
	for (int i = 0; i < SpriteCode::_SIZE; i++) {
		sprites[i].Init(x * BLOCKSIZE, 0 , BLOCKSIZE, BLOCKSIZE);
		if (i < SpriteCode::GHOST_RED || i >= SpriteCode::GHOST_ORANGE) {
			x++;
		}
	}
	sprites[SpriteCode::BLOCK].SetColor(50, 100, 255);
	sprites[SpriteCode::PACSAN_OPEN].SetColor(255, 255, 120);
	sprites[SpriteCode::PACSAN_CLOSE].SetColor(255, 255, 120);
	sprites[SpriteCode::GHOST_RED].SetColor(255, 95, 95);
	sprites[SpriteCode::GHOST_PINK].SetColor(255, 180, 255);
	sprites[SpriteCode::GHOST_CYAN].SetColor(0, 255, 255);
	sprites[SpriteCode::GHOST_ORANGE].SetColor(255, 180, 80);

	return true;
}

void Manager::Quit()
{
	SDL_DestroyTexture(spritesheet);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

void Manager::RenderClear(
	Uint8 r, Uint8 g, Uint8 b
)
{
	SDL_SetRenderDrawColor(this->renderer, r, g, b, 0xff);
	SDL_RenderClear(this->renderer);
}

void Manager::RenderPresent()
{
	SDL_RenderPresent(this->renderer);
}
