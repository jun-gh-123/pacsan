#ifndef PARAMS_HPP
#define PARAMS_HPP

#define TITLE "pacsan"
#define BLOCKSIZE 32
#define COLS 17
#define ROWS 25
#define WIDTH BLOCKSIZE * COLS
#define HEIGHT BLOCKSIZE * ROWS

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

namespace SceneCode {
	enum {
		OPENING = 0,
		GAME,
		GAMEOVER,
		ENDING,
		EDITOR
	};
};

namespace SpriteCode {
	enum {
		BLOCK = 0,
		PACSAN_OPEN,
		PACSAN_CLOSE,
		GHOST_RED,
		GHOST_PINK,
		GHOST_CYAN,
		GHOST_ORANGE,
		GHOST_WHITE,
		GHOST_ESCAPE,
		GHOST_DEAD,
		PELLET,
		SUPER_PELLET,
		DOOR,
		_SIZE
	};
};

namespace TileCode {
	enum {
		EMPTY = 0,
		BLOCK,
		PELLET,
		SUPER_PELLET,
		PACSAN,
		DOOR
	};
};

namespace GhostMode {
	enum {
		NORMAL = 0,
		ESCAPE,
		DEAD
	};
};

namespace KeyState {
	enum {
		UP = 0,
		RELEASE = 1,
		PRESS = 2,
		DOWN = 4
	};
};

const int LEVEL_TEMPLATE[ROWS * COLS] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 1, 1, 5, 1, 1, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

#endif
