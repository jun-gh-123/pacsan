#ifndef VARIABLE_TEXT
#define VARIABLE_TEXT

#include "Text.hpp"

template <class VarType>
class VariableText : public Text {
	protected:
		VarType prev;
		VarType *var;
	public:
		void Init(
			TTF_Font *font,
			SDL_Renderer *renderer,
			VarType *var,
			Uint8 r = 255, Uint8 g = 255, Uint8 b = 255
		);
		void Draw(TTF_Font *font, SDL_Renderer *renderer);
};

#include "VariableText.tcc"

#endif
