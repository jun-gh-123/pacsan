#ifndef PARAMS_HPP
#define PARAMS_HPP

#define TITLE "pacsan"
#define BLOCKSIZE 32
#define COLS 17
#define ROWS 25
#define WIDTH BLOCKSIZE * COLS
#define HEIGHT BLOCKSIZE * ROWS

namespace SceneCode {
	enum {
		OPENING = 0,
		GAME,
		GAMEOVER,
		ENDING
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
		GHOST_ESCAPE,
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

#endif
