#include "Text.hpp"

void Text::Init(
	TTF_Font *font,
	SDL_Renderer *renderer,
	const char *text,
	Uint8 r, Uint8 g, Uint8 b
)
{
	if (this->texture)
	{
		SDL_DestroyTexture(this->texture);
	}
	SDL_Color textColor = { r, g, b };
	SDL_Surface *loaded = TTF_RenderText_Solid(font, text, textColor);
	if (!loaded)
	{
		return;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loaded);
	if (texture)
	{
		this->texture = texture;
		this->w = loaded->w;
		this->h = loaded->h;
	}
	SDL_FreeSurface(loaded);
}

void Text::Draw(
	SDL_Renderer *renderer
)
{
	SDL_Rect dstrect = {
		this->x, this->y, this->w, this->h
	};
	SDL_RenderCopy(renderer, this->texture, NULL, &dstrect);
}
