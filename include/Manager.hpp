#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <random>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "params.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

using namespace std;

class Manager {
	private:
		vector<vector<int>> levels;
		vector<int> keys;
		bool textsVisible = true;
		random_device rd;
		Text header;
		Text subtext;
		bool loadLevels(const char *filepath);
		bool loadAudio(int id, const char *filepath, bool isSound = true);
		Mix_Chunk *sound[SoundCode::_SIZE];
		Mix_Music *music[MusicCode::_SIZE];
	public:
		// vars
		SDL_Window *window = 0;
		SDL_Renderer *renderer = 0;
		SDL_Texture *spritesheet = 0;
		TTF_Font *font = 0;
		Sprite sprites[SpriteCode::_SIZE];
		int highscore = 0;
		int lastscore = 0;
		// basic
		bool Init();
		void Quit();
		void RenderClear(Uint8 r, Uint8 g, Uint8 b);
		void RenderPresent();
		int GetRandomInt(int min, int max);
		void LogScore(int score);
		// text
		void HideTexts();
		void ShowTexts(const char *header, const char *subtext);
		// levels
		int NumLevels();
		vector<int>* GetLevel(int level);
		vector<int>* InsertLevel(int level);
		int AppendLevel();
		void ResetLevel(int level);
		void SetTile(int level, int row, int col, int tile);
		int DeleteLevel(int level);
		int SaveLevelsToFile(const char *filepath);
		// sprite
		Sprite* GetSprite(int spritecode);
		// audio
		void StopAllAudio();
		void PlaySound(int id);
		void PlayMusic(int id);
		void StopMusic();
		// keys
		void UpdateKeys(const Uint8 *keystate, int numkeys);
		bool IsKeyPressed(int scancode);
		bool IsKeyDown(int scancode);
		bool IsKeyReleased(int scancode);
		bool IsKeyUp(int scancode);
};

#endif
