#include <string>
#include "VariableText.hpp"

template <class VarType>
void VariableText<VarType>::Init(
	TTF_Font *font,
	SDL_Renderer *renderer,
	VarType *var,
	Uint8 r, Uint8 g, Uint8 b
)
{
	this->var = var;
	this->prev = *var;
	this->r = r;
	this->g = g;
	this->b = b;
	std::string str = std::to_string(*this->var);
	this->CreateTexture(font, renderer, str.c_str());
}

template <class VarType>
void VariableText<VarType>::Draw(
	TTF_Font *font,
	SDL_Renderer *renderer
)
{
	if (*this->var != this->prev) {
		std::string str = std::to_string(*this->var);
		this->CreateTexture(font, renderer, str.c_str());
	}
	Text::Draw(renderer);
}

