NAME = pacsan
CC = g++
COMPILER_FLAGS = -Wall -g
LINKER_FLAGS = -lSDL2
BUILD_DIR = build
ASSETS_DIR = assets
WEB_DIR = web

.PHONY: clean

test: build
	cd $(BUILD_DIR); ./$(NAME)

test-web: web
	firefox $(WEB_DIR)/$(NAME).html

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(WEB_DIR)

build: main.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) main.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(NAME)
	cp -r $(ASSETS_DIR) $(BUILD_DIR)

web: main.cpp
	mkdir -p $(WEB_DIR)
	em++ main.cpp -s USE_SDL=2 -Os --embed-file $(ASSETS_DIR) -o $(WEB_DIR)/$(NAME).html
