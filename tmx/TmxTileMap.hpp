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
    TmxTileMap() {};
    ~TmxTileMap();

    TmxTileMap(const TmxTileMap&) = delete;
    TmxTileMap& operator=(const TmxTileMap&) = delete;

    void load(const std::string& tmxFilePath, u_int32_t layerIndex);
    void render(SDL_Renderer* renderer);

private:
    bool isTileIDWithinTileset(u_int32_t tileID, const tmx::Tileset& tileset);

    struct LayerRenderData {
        std::vector<SDL_Vertex> vertexData;
        std::string textureImagePath;
        SDL_Texture* texture = nullptr;
    };

    std::vector<LayerRenderData> renderData;
};

SDL_Texture* createTexture(SDL_Renderer* renderer, const std::string& fileName);