#include <iostream>
#include <fstream>
#include <utility>
#include "Manager.hpp"

using namespace std;

bool Manager::loadLevels(
	const char *filepath
)
{
	ifstream levelsFile(filepath);
	if (levelsFile.is_open()) {
		char ch;
		int i = 0;
		int count = 0;
		this->levels.push_back(vector<int>());
		while (levelsFile.get(ch)) {
			if (ch == '\n') {
				if (count == ROWS * COLS && levelsFile.peek() != EOF) {
					i++;
					this->levels.push_back(vector<int>());
					count = 0;
				}
			} else if (ch != ' ') {
				int n = ch - '0';
				this->levels[i].push_back(n);
				count++;
			}
		}
	} else {
		return false;
	}
	levelsFile.close();
	return true;
}

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

	// load levels
	if (!loadLevels("assets/levels.txt")) {
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
	if (this->textsVisible) {
		// draw texts
		this->header.Draw();
		this->subtext.Draw();
	}

	SDL_RenderPresent(this->renderer);
}

void Manager::HideTexts()
{
	this->textsVisible = false;
}

void Manager::ShowTexts(
	const char *headerstr,
	const char *subtextstr
)
{
	this->textsVisible = true;
	this->header.Set(headerstr);
	this->subtext.Set(subtextstr, 200, 200, 200);

	this->header.scale = 4.0f;
	this->subtext.scale = 2.0f;

	int totalHeight = this->header.GetHeight() + this->subtext.GetHeight();

	this->header.x = WIDTH / 2 - this->header.GetWidth() / 2;
	this->header.y = HEIGHT / 2 - totalHeight / 2;

	this->subtext.x = WIDTH / 2 - this->subtext.GetWidth() / 2;
	this->subtext.y = this->header.y + this->header.GetHeight();
}

int Manager::NumLevels()
{
	return this->levels.size();
}

vector<int>* Manager::GetLevel(
	int level
)
{
	return &(this->levels[level]);
}
