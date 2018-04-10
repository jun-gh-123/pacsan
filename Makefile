NAME = pacsan
CC = g++
INCLUDE_FLAGS = -Iinclude -Isrc
COMPILER_FLAGS = -Wall -g
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
BUILD_DIR = build
ASSETS_DIR = assets
SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_DIR = .obj
OBJS = $(patsubst $(SRC_DIR)/%.cpp, %, $(SRC))
EM_SDL_FLAGS = -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'

.PHONY: clean

desktop: build-desktop
	cd $(BUILD_DIR)/desktop; ./$(NAME)

web: build-web
	firefox $(BUILD_DIR)/web/$(NAME).html

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $< -c $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

build-desktop: $(patsubst %, $(OBJ_DIR)/%.o, $(OBJS)) main.cpp
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/desktop
	$(CC) $^ $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/desktop/$(NAME)
	cp -r $(ASSETS_DIR) $(BUILD_DIR)/desktop

build-web: main.cpp
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/web
	em++ -O2 -std=c++11 main.cpp $(SRC) $(EM_SDL_FLAGS) --embed-file $(ASSETS_DIR) $(INCLUDE_FLAGS) -o $(BUILD_DIR)/web/$(NAME).html
