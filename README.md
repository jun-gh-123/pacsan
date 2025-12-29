# Build Requirements (linux, package names are for void linux)
- make
- linux build
  - g++
  - SDL2
    - SDL2, SDL2-devel
    - SDL2_image, SDL2_image-devel
    - SDL2_ttf, SDL2_ttf-devel
    - SDL2_mixer, SDL2_mixer-devel
- web build
  - emscripten
 
# Make commands
- make
  - runs 'debug-linux' which builds and runs linux build
- make debug-web
  - build and run web build
