#include "GameScene.hpp"

void GameScene::Init()
{
	this->game.Init();
	this->game.LoadLevel(this->game.level, &this->blocksTexture);
	gManager.HideTexts();

	// init game objects
	pacsan.Init();
	pacsan.Reset(this->game.startRow, this->game.startCol);
	for (int i = 0; i < 4; i++) {
		ghosts[i].Init(SpriteCode::GHOST_RED + i);
		ghosts[i].Reset(ROWS / 2, COLS / 2);
	}

	// init vartexts
	scoreText.Init(&this->game.score);
	scoreText.scale = 2.0f;
}

int GameScene::Update(
	const Uint8 *keystate
)
{
	if (!this->game.paused) {
		pacsan.Update(keystate, &this->game);

		bool collided = false;
		for (int i = 0; i < 4 && !collided; i++) {
			ghosts[i].Update(keystate, &this->game);
			if (pacsan.IsColliding(&ghosts[i])) {
				collided = true;
			}
		}
		if (collided) {
			if (this->game.lives <= 0) {
				return SceneCode::GAMEOVER;
			}
			gManager.ShowTexts("DEAD", "Press <space> to continue.");
			this->game.paused = true;
		}
	} else {
		if (keystate[SDL_SCANCODE_SPACE]) {
			if (this->game.levelCleared) {
				this->game.NextLevel(&(this->blocksTexture));
			} else {
				this->game.NewLife();
			}
			this->pacsan.Reset(this->game.startRow, this->game.startCol);
			for (int i = 0; i < 4; i++) {
				ghosts[i].Reset(ROWS / 2, COLS / 2);
			}
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
}
