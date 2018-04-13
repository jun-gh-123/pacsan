#include "LevelEditorScene.hpp"
#include "globals.hpp"

using namespace std;

void LevelEditorScene::setTileAtCursor(
	int tilecode
)
{
	int row = this->cy / BLOCKSIZE;
	int col = this->cx / BLOCKSIZE;

	if (row >= 11 && row <= 13) {
		if (col >= 6 && col <= 10) {
			return;
		}
	}

	gManager.SetTile(
		this->currentLevel,
		this->cy / BLOCKSIZE, this->cx / BLOCKSIZE,
		tilecode
	);
}

void LevelEditorScene::Init()
{
	gManager.HideTexts();
	this->currentLevel = 0;
	this->cx = 0;
	this->cy = 0;
	this->levelText.Init(&this->currentLevel);
	this->levelText.scale = 2.0f;
}

int LevelEditorScene::Update()
{
	// cursor movement
	if (gManager.IsKeyPressed(SDL_SCANCODE_LEFT)) {
		this->cx = this->cx - BLOCKSIZE >= 0 ?
			this->cx - BLOCKSIZE : WIDTH - BLOCKSIZE;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_RIGHT)) {
		this->cx = this->cx + BLOCKSIZE < WIDTH ?
			this->cx + BLOCKSIZE : 0;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_UP)) {
		this->cy = this->cy - BLOCKSIZE >= 0 ?
			this->cy - BLOCKSIZE : HEIGHT - BLOCKSIZE;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_DOWN)) {
		this->cy = this->cy + BLOCKSIZE < HEIGHT ?
			this->cy + BLOCKSIZE : 0;
	}
	// tile set
	if (gManager.IsKeyDown(SDL_SCANCODE_0)) {
		setTileAtCursor(TileCode::EMPTY);
	}
	if (gManager.IsKeyDown(SDL_SCANCODE_1)) {
		setTileAtCursor(TileCode::BLOCK);
	}
	if (gManager.IsKeyDown(SDL_SCANCODE_2)) {
		setTileAtCursor(TileCode::PELLET);
	}
	if (gManager.IsKeyDown(SDL_SCANCODE_3)) {
		setTileAtCursor(TileCode::SUPER_PELLET);
	}
	if (gManager.IsKeyDown(SDL_SCANCODE_4)) {
		setTileAtCursor(TileCode::PACSAN);
	}
	// level
	if (gManager.IsKeyPressed(SDL_SCANCODE_R)) {
		gManager.ResetLevel(this->currentLevel);
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_COMMA)) {
		this->currentLevel = this->currentLevel - 1 >= 0 ?
			this->currentLevel - 1 : gManager.NumLevels() - 1;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_PERIOD)) {
		this->currentLevel = this->currentLevel + 1 < gManager.NumLevels() ?
			this->currentLevel + 1 : 0;
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_I)) {
		gManager.InsertLevel(this->currentLevel);
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_A)) {
		this->currentLevel = gManager.AppendLevel();
	}
	if (gManager.IsKeyPressed(SDL_SCANCODE_D)) {
		this->currentLevel = gManager.DeleteLevel(this->currentLevel);
	}
	// return to opening
	if (gManager.IsKeyPressed(SDL_SCANCODE_BACKSPACE)) {
		gManager.SaveLevelsToFile("assets/levels.txt");
		return SceneCode::OPENING;
	}
	return SceneCode::EDITOR;
}

void LevelEditorScene::Draw()
{
	vector<int> *level = gManager.GetLevel(this->currentLevel);

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			int tilecode = (*level)[r * COLS + c];
			Sprite *tile = 0;
			switch (tilecode) {
				case TileCode::BLOCK:
					tile = gManager.GetSprite(SpriteCode::BLOCK);
					break;
				case TileCode::PELLET:
					tile = gManager.GetSprite(SpriteCode::PELLET);
					break;
				case TileCode::SUPER_PELLET:
					tile = gManager.GetSprite(SpriteCode::SUPER_PELLET);
					break;
				case TileCode::PACSAN:
					tile = gManager.GetSprite(SpriteCode::PACSAN_OPEN);
					break;
				case TileCode::DOOR:
					tile = gManager.GetSprite(SpriteCode::DOOR);
					break;
				default:
					break;
			}
			if (tile) {
				tile->Render(gManager.renderer, c * BLOCKSIZE, r * BLOCKSIZE);
			}
		}
	}

	const SDL_Rect cursorRect = {
		cx, cy, BLOCKSIZE, BLOCKSIZE
	};
	SDL_SetRenderDrawColor(gManager.renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(gManager.renderer, &cursorRect);
	SDL_SetRenderDrawColor(gManager.renderer, 255, 0, 0, 100);
	SDL_RenderFillRect(gManager.renderer, &cursorRect);

	const SDL_Rect ghostBaseRect = {
		6 * BLOCKSIZE,
		11 * BLOCKSIZE,
		5 * BLOCKSIZE,
		3 * BLOCKSIZE
	};
	SDL_SetRenderDrawColor(gManager.renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gManager.renderer, &ghostBaseRect);
	SDL_SetRenderDrawColor(gManager.renderer, 255, 255, 255, 100);
	SDL_RenderFillRect(gManager.renderer, &ghostBaseRect);

	this->levelText.Draw();
}
