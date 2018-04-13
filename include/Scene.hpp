#ifndef SCENE_HPP
#define SCENE_HPP

#include <SDL2/SDL.h>

class Scene {
	public:
		virtual void Init() = 0;
		virtual int Update() = 0;
		virtual void Draw() = 0;
};

#endif
