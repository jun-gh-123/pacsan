#include <SDL2/SDL.h>

class Sprite {
	private:
		Uint8 r, g, b;
		SDL_Rect clip;
		double angle;
	public:
		Sprite();
		void Init(int clipX, int clipY, int clipSize, int size);
		void SetColor(Uint8 r, Uint8 g, Uint8 b);
		void Render(int x, int y, SDL_Texture *spritesheet, SDL_Renderer *renderer);
};
