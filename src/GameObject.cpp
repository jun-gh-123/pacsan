#include "GameObject.hpp"

Sprite *GameObject::sprites = 0;

void GameObject::SetSprite(
	int spriteCode
)
{
	this->spriteCode = spriteCode;
	this->sprite = &sprites[spriteCode];
}

void GameObject::Draw()
{
	this->sprite->Render(this->x, this->y, this->angle, this->flip);
}
