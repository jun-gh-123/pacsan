#include "Text.hpp"
#include "globals.hpp"

void Text::CreateTexture(
	TTF_Font *font,
	SDL_Renderer *renderer,
	const char *text
)
{
	if (this->texture) {
		SDL_DestroyTexture(this->texture);
	}
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Surface *loaded = TTF_RenderText_Solid(font, text, textColor);
	if (!loaded) {
		return;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loaded);
	if (texture) {
		this->texture = texture;
		this->w = loaded->w;
		this->h = loaded->h;
	}
	SDL_FreeSurface(loaded);
}

void Text::Set(
	const char *text,
	Uint8 r, Uint8 g, Uint8 b
)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->CreateTexture(gManager.font, gManager.renderer, text);
}

int Text::GetWidth()
{
	return (int)(this->w * this->scale);
}

int Text::GetHeight()
{
	return (int)(this->h * this->scale);
}

void Text::Draw()
{
	SDL_Rect dstrect = {
		this->x, this->y,
		this->GetWidth(), this->GetHeight()
	};
	SDL_SetTextureColorMod(this->texture, this->r, this->g, this->b);
	SDL_RenderCopy(gManager.renderer, this->texture, NULL, &dstrect);
}
