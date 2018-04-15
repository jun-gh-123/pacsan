NAME = pacsan
CC = g++
INCLUDE_FLAGS = -Iinclude -Isrc
DEBUG_COMPILER_FLAGS = -Wall -g
RELEASE_COMPILER_FLAGS = -O3 -DNDEBUG
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
DEBUG_DIR = debug
RELEASE_DIR = release
ASSETS_DIR = assets
SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_DIR = .obj
OBJS = $(patsubst $(SRC_DIR)/%.cpp, %, $(SRC))
EM_PORT_FLAGS = -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'
EM_HTML_TEMPLATE = html/template.html

.PHONY: clean

debug-linux: $(DEBUG_DIR)/linux
	cd $(DEBUG_DIR)/linux; ./$(NAME)
	cp $(DEBUG_DIR)/linux/assets/levels.txt assets

debug-web: $(DEBUG_DIR)/web
	firefox $(DEBUG_DIR)/web/$(NAME).html

clean-debug:
	rm -rf $(OBJ_DIR)
	rm -rf $(DEBUG_DIR)

clean-release:
	rm -rf $(RELEASE_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $< -c $(INCLUDE_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

$(DEBUG_DIR)/linux: $(patsubst %, $(OBJ_DIR)/%.o, $(OBJS)) main.cpp
	mkdir -p $(DEBUG_DIR)
	mkdir -p $(DEBUG_DIR)/linux
	$(CC) $^ $(INCLUDE_FLAGS) $(DEBUG_COMPILER_FLAGS) $(LINKER_FLAGS) -o $(DEBUG_DIR)/linux/$(NAME)
	cp -r $(ASSETS_DIR) $(DEBUG_DIR)/linux

$(DEBUG_DIR)/web: $(SRC) main.cpp
	mkdir -p $(DEBUG_DIR)
	mkdir -p $(DEBUG_DIR)/web
	em++ -g -Wall -std=c++11 $^ $(EM_PORT_FLAGS) --use-preload-plugins --preload-file $(ASSETS_DIR) $(INCLUDE_FLAGS) -o $(DEBUG_DIR)/web/$(NAME).html

$(RELEASE_DIR)/linux: $(SRC) main.cpp
	rm -rf $(RELEASE_DIR)/linux
	mkdir -p $(RELEASE_DIR)
	mkdir -p $(RELEASE_DIR)/linux
	$(CC) $^ $(INCLUDE_FLAGS) $(RELEASE_COMPILER_FLAGS) $(LINKER_FLAGS) -o $(RELEASE_DIR)/linux/$(NAME)
	cp -r $(ASSETS_DIR) $(RELEASE_DIR)/linux

$(RELEASE_DIR)/web: $(SRC) main.cpp
	rm -rf $(RELEASE_DIR)/web
	mkdir -p $(RELEASE_DIR)
	mkdir -p $(RELEASE_DIR)/web
	em++ -O3 -std=c++11 $^ $(EM_PORT_FLAGS) --use-preload-plugins --preload-file $(ASSETS_DIR) $(INCLUDE_FLAGS) -o $(RELEASE_DIR)/web/$(NAME).js
	cp $(EM_HTML_TEMPLATE) $(RELEASE_DIR)/web/index.html

gh-pages: clean-release $(RELEASE_DIR)/web
	git branch -D gh-pages
	git checkout --orphan gh-pages
	git rm -rf --cached .
	cp -a $(RELEASE_DIR)/web/. .
	git add $(shell ls $(RELEASE_DIR)/web | xargs -n 1 basename)
	git commit -m "release"
	git push -f origin gh-pages
	git checkout -f master

gdb: build-linux
	cd $(DEBUG_DIR)/linux; gdb $(NAME)

cplvls: $(DEBUG_DIR)/linux
	cp $(DEBUG_DIR)/linux/assets/levels.txt assets
