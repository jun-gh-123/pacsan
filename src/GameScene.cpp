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
}

void GameScene::onPowerUpStart()
{
	for (int i = 0; i < 4; i++) {
		if (ghosts[i].started && ghosts[i].active) {
			ghosts[i].SetMode(GhostMode::ESCAPE);
		}
	}
}

void GameScene::onPowerUpEnd()
{
	for (int i = 0; i < 4; i++) {
		if (ghosts[i].active) {
			ghosts[i].SetMode(GhostMode::NORMAL);
		}
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
}

int GameScene::Update()
{
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
				ghosts[collided].SetMode(GhostMode::DEAD);
				this->game.score += 100;
			} else {
				if (this->game.lives <= 1) {
					if (this->game.score > gManager.highscore) {
						gManager.highscore = this->game.score;
					}
					return SceneCode::GAMEOVER;
				}
				gManager.ShowTexts("DEAD", "Press <space> to continue.");
				this->game.paused = true;
			}
		}
	} else {
		if (gManager.IsKeyPressed(SDL_SCANCODE_SPACE)) {
			if (this->game.levelCleared) {
				if (this->game.level + 1 >= this->game.maxLevel) {
					if (this->game.score > gManager.highscore) {
						gManager.highscore = this->game.score;
					}
					return SceneCode::ENDING;
				}
				this->game.NextLevel(&(this->blocksTexture));
			} else {
				this->game.NewLife();
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

	this->pacsan.Draw();
	for (int i = 0; i < 4; i++) {
		this->ghosts[i].Draw();
	}
	this->scoreText.Draw();
	this->livesText.x = WIDTH - this->livesText.GetWidth();
	this->livesText.Draw();
}
