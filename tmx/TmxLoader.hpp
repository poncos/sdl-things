#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <SDL3/SDL.h>

class TmxMapLoader {
    struct Tileset {
        u_int32_t firstGID;
        std::string name;
        std::string imagePath;
        u_int32_t tileWidth;
        u_int32_t tileHeight;
        u_int32_t tileCount;
        u_int32_t columnCount;
    };

    struct Tile {
        u_int32_t firstGID;
        u_int32_t tileID;
        u_int32_t index;
    };
    
    std::string image;
    int width;
    int height;
    int tileWidth;
    int tileHeight;

    TmxMapLoader() {};
    ~TmxMapLoader();

    void load(const std::string& tmxFilePath);
    void render(SDL_Renderer* renderer);

private:
    std::unordered_map<u_int32_t, Tileset> tilesets;
    std::vector<Tile> tileInfos;

};