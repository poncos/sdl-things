#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <tmxlite/Map.hpp>
#include <tmxlite/Property.hpp>
#include <vector>
#include <SDL3/SDL.h>

class TmxTileMap {

public:

    struct TileType {
        u_int32_t tileGID;
        u_int32_t tileID;
        std::string type;

        std::vector<tmx::Property> properties;
    };

    struct Tileset {
        u_int32_t firstGID;
        std::string name;
        std::string imagePath;
        u_int32_t tileWidth;
        u_int32_t tileHeight;
        u_int32_t tileCount;
        u_int32_t columnCount;

        std::vector<TileType> customTypes;
    };

    struct Tile {
        u_int32_t tileGID;
        u_int32_t tileID;
        u_int32_t index;
    };
    
    std::string filePath;
    int width;
    int height;
    int tileWidth;
    int tileHeight;

    TmxTileMap() {};
    ~TmxTileMap();

    void load(const std::string& tmxFilePath);
    void load2(const std::string& tmxFilePath);
    void render(SDL_Renderer* renderer);

private:
    std::vector<Tile> tiles;
    std::unordered_map<u_int32_t, Tileset> tilesets;

    std::unordered_map<u_int32_t, Tileset> parseTileset(const tmx::Map& map);
    std::vector<TmxTileMap::Tile> parseTileLayers(const tmx::Map& map,
        const std::unordered_map<std::uint32_t, Tileset>& tilesets);

    SDL_Texture* tsTexture = nullptr;

    u_int32_t findTilesetForTileID(
        u_int32_t tileID,
        const std::unordered_map<u_int32_t, Tileset>& tilesets);
};

SDL_Texture* createTexture(SDL_Renderer* renderer, const std::string& fileName);