#include <functional>
#include <iostream>
#include "GameScene.hpp"

void GameScene::resetGameObjects()
{

	pacsan.Reset(this->game.startRow, this->game.startCol);
	ghosts[0].Reset(ROWS / 2 - 2, COLS / 2);
	ghosts[1].Reset(ROWS / 2, COLS / 2);
	ghosts[2].Reset(ROWS / 2, COLS / 2 - 1);
	ghosts[3].Reset(ROWS / 2, COLS / 2 + 1);
	this->countdown = 3;
	this->countdownclock = 0;

	gManager.StopAllAudio();
	this->stageMusicId = gManager.GetRandomInt(MusicCode::BGM1, MusicCode::BGM3);
	gManager.PlaySound(SoundCode::STAGE_START);
	this->game.powerUpTime = 0;
}

void GameScene::onPowerUpStart()
{
	for (int i = 0; i < 4; i++) {
		if (ghosts[i].started && ghosts[i].active) {
			ghosts[i].SetMode(GhostMode::ESCAPE);
		}
	}
	if (this->game.powerUpTime == 0) {
		gManager.PlayMusic(MusicCode::POWERUP);
	}
}

void GameScene::onPowerUpEnd()
{
	for (int i = 0; i < 4; i++) {
		if (ghosts[i].active) {
			ghosts[i].SetMode(GhostMode::NORMAL);
		}
	}
	if (!this->game.paused) {
		gManager.PlayMusic(this->stageMusicId);
	}
}

void GameScene::Init()
{
	this->game.Init();
	this->game.LoadLevel(this->game.level, &this->blocksTexture);
	this->game.onPowerUpStart = std::bind(&GameScene::onPowerUpStart, this);
	this->game.onPowerUpEnd = std::bind(&GameScene::onPowerUpEnd, this);

	gManager.HideTexts();

	// init game objects
	pacsan.Init();
	ghosts[0].Init(SpriteCode::GHOST_RED, 20);
	ghosts[1].Init(SpriteCode::GHOST_PINK, 10);
	ghosts[2].Init(SpriteCode::GHOST_CYAN, 1);
	ghosts[3].Init(SpriteCode::GHOST_ORANGE, 5);
	resetGameObjects();

	// init vartexts
	scoreText.Init(&this->game.score);
	scoreText.scale = 2.0f;
	livesText.Init(&this->game.lives);
	livesText.scale = 2.0f;
	countdownText.Init(&this->countdown);
	countdownText.scale = 8.0f;
}

int GameScene::Update()
{
	if (this->countdownclock < 180) {
		this->countdownclock++;
		if (this->countdownclock % 60 == 0) {
			this->countdown--;
		}
		if (this->countdownclock == 180) {
			gManager.PlayMusic(this->stageMusicId);
		}
		return SceneCode::GAME;
	}

	if (gManager.IsKeyPressed(SDL_SCANCODE_BACKSPACE)) {
		return SceneCode::OPENING;
	}

	this->game.Update();

	if (gManager.IsKeyPressed(SDL_SCANCODE_S)) {
		if (this->game.level + 1 >= this->game.maxLevel) {
			this->game.level = -1;
		}
		this->game.NextLevel(&(this->blocksTexture));
		resetGameObjects();
	}

	if (!this->game.paused) {
		pacsan.Update(&this->game);

		int collided = -1;
		for (int i = 0; i < 4 && collided == -1; i++) {
			ghosts[i].Update(&this->game);
			if (pacsan.IsColliding(&ghosts[i])) {
				collided = i;
			}
		}
		if (collided > -1) {
			if (ghosts[collided].mode == GhostMode::ESCAPE) {
				gManager.PlaySound(SoundCode::EAT_GHOST);
				ghosts[collided].SetMode(GhostMode::DEAD);
				this->game.score += 200;
			} else {
				gManager.StopMusic();
				gManager.PlaySound(SoundCode::DIED);
				gManager.ShowTexts("YOU DIED", "Press <space> to restart.");
				this->game.paused = true;
			}
		}
	} else {
		if (gManager.IsKeyPressed(SDL_SCANCODE_SPACE)) {
			if (this->game.levelCleared) {
				if (this->game.level + 1 >= this->game.maxLevel) {
					this->game.score += (this->game.lives - 1) * 5000;
					gManager.LogScore(this->game.score);
					return SceneCode::ENDING;
				}
				this->game.NextLevel(&(this->blocksTexture));
			} else {
				this->game.NewLife();
				if (this->game.lives <= 0) {
					gManager.LogScore(this->game.score);
					return SceneCode::GAMEOVER;
				}
			}
			resetGameObjects();
		}
	}

	return SceneCode::GAME;
}

void GameScene::Draw()
{
	SDL_Renderer *renderer = gManager.renderer;
	Sprite *sprites = gManager.sprites;

	// draw blocks
	if (this->game.powerUpTime == 0) {
		SDL_SetTextureColorMod(this->blocksTexture, 50, 100, 255);
	} else {
		if (this->game.blinkOn) {
			SDL_SetTextureColorMod(this->blocksTexture, 255, 150, 200);
		} else {
			SDL_SetTextureColorMod(this->blocksTexture, 255, 50, 100);
		}
	}
	SDL_RenderCopy(renderer, this->blocksTexture, NULL, NULL);

	// draw pellets
	Sprite *pellet = &sprites[SpriteCode::PELLET];
	Sprite *superPellet = &sprites[SpriteCode::SUPER_PELLET];
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = this->game.tiles[r * COLS + c];
			if (tilecode == TileCode::PELLET) {
				pellet->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			} else if (tilecode == TileCode::SUPER_PELLET) {
				superPellet->Render(renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		this->ghosts[i].Draw();
	}
	this->pacsan.Draw();
	this->scoreText.Draw();
	this->livesText.x = WIDTH - this->livesText.GetWidth();
	this->livesText.Draw();
	if (this->countdown > 0) {
		this->countdownText.x = WIDTH / 2 - this->countdownText.GetWidth() / 2;
		this->countdownText.y = HEIGHT / 2 - this->countdownText.GetHeight() / 2;

		const SDL_Rect rect = {
			this->countdownText.x - 3,
			this->countdownText.y - 3,
			this->countdownText.GetWidth(),
			this->countdownText.GetHeight()
		};

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		SDL_RenderFillRect(renderer, &rect);
		this->countdownText.Draw();
	}
}
