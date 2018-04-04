NAME = pacsan
CC = g++
INCLUDE_FLAGS = -Iinclude
COMPILER_FLAGS = -Wall -g
LINKER_FLAGS = -lSDL2 -lSDL2_image
BUILD_DIR = build
ASSETS_DIR = assets
SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name '*.cpp')

.PHONY: clean

desktop: build-desktop
	cd $(BUILD_DIR)/desktop; ./$(NAME)

web: build-web
	firefox $(BUILD_DIR)/web/$(NAME).html

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BUILD_DIR)

build-desktop: main.cpp
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/desktop
	$(CC) main.cpp $(SRC) $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/desktop/$(NAME)
	cp -r $(ASSETS_DIR) $(BUILD_DIR)/desktop

build-web: main.cpp
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/web
	em++ main.cpp $(SRC) -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -O2 -std=c++11 --embed-file $(ASSETS_DIR) $(INCLUDE_FLAGS) -o $(BUILD_DIR)/web/$(NAME).html
