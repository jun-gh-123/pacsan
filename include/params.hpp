#ifndef PARAMS_HPP
#define PARAMS_HPP

#define TITLE "pacsan"
#define BLOCKSIZE 32
#define COLS 17
#define ROWS 25
#define WIDTH BLOCKSIZE * COLS
#define HEIGHT BLOCKSIZE * ROWS

namespace SpriteCode {
	enum {
		BLOCK = 0,
		PACSAN_OPEN,
		PACSAN_CLOSE,
		GHOST_CHASE,
		GHOST_ESCAPE,
		PELLET,
		SUPER_PELLET
	};
};

namespace TileCode {
	enum {
		EMPTY = 0,
		BLOCK,
		PELLET,
		SUPER_PELLET,
		PACSAN
	};
};

#endif
