#include <string>
#include "VariableText.hpp"
#include "globals.hpp"

template <class VarType>
void VariableText<VarType>::Init(
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
	this->CreateTexture(gManager.font, gManager.renderer, str.c_str());
}

template <class VarType>
void VariableText<VarType>::Draw()
{
	if (*this->var != this->prev) {
		std::string str = std::to_string(*this->var);
		this->CreateTexture(gManager.font, gManager.renderer, str.c_str());
	}
	Text::Draw();
}

