
This repo contains my own SDL samples which I use as starting point for other SDL projects.

I order to build all these samples the SDL, SDL_image and SDL_ttf libraries must be installed.

# MacOS
brew install sdl3
brew install sdl3_image
brew install sdl3_ttf


# Linux
apt-get install libsdl3-dev
apt-get install libsdl3-image-dev
apt-get install libsdl3-ttf-dev

pkg-config --cflags --libs sdl3
pkg-config --cflags --libs sdl3-image
pkg-config --cflags --libs sdl3-ttf


# Instructions

For the text sample, the path to the font file to use must be set on the file SDLApp.cpp:
```
    //TODO set the path to the TTF font to use
    Font myFont("/usr/share/fonts/truetype/ancient-scripts/Symbola_hint.ttf", 20);
```