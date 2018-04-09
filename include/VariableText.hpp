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
			VarType *var,
			Uint8 r = 255, Uint8 g = 255, Uint8 b = 255
		);
		void Draw();
};

#include "VariableText.tcc"

#endif
