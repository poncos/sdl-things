#include "TmxTileMap.hpp"

#include "MathDefinitions.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SDL3_image/SDL_image.h>

TmxTileMap::~TmxTileMap() {

}

void TmxTileMap::load2(const std::string& tmxFilePath) {

}

void TmxTileMap::load(const std::string& tmxFilePath) {
    std::cout << "==================== Loading tileset from file [" << tmxFilePath << "]" << std::endl;
    tmx::Map map;
    map.load(tmxFilePath);

    this->width = map.getTileCount().x;
    this->height = map.getTileCount().y;
    this->tileWidth = map.getTileSize().x;
    this->tileHeight = map.getTileSize().y;

    std::cout << "Map size: " << this->width << "x" << this->height << ", Tile size: " << this->tileWidth << "x" << this->tileHeight << std::endl;

    this->tilesets = this->parseTileset(map);
    this->tiles = this->parseTileLayers(map, this->tilesets);

    std::cout << "==================== Finished loading tileset from file [" << tmxFilePath << "]" << std::endl;
}

 std::unordered_map<u_int32_t, TmxTileMap::Tileset> TmxTileMap::parseTileset(const tmx::Map& map) {

    std::unordered_map<std::uint32_t, Tileset> tilesetMap;
    const auto& tilesets = map.getTilesets();

    if (!tilesets.empty()) {
        for (const auto& tileset : tilesets) {
        
            TmxTileMap::Tileset info {
                tileset.getFirstGID(),
                tileset.getName(),
                tileset.getImagePath(),
                tileset.getTileSize().x,
                tileset.getTileSize().y,
                tileset.getTileCount(),
                tileset.getColumnCount()
            };
            tilesetMap[info.firstGID] = info;

            std::cout << "***** Tileset with name: " << info.name << ", first GID: " << info.firstGID <<
            ", image: " << info.imagePath << std::endl;

            const auto& tiles = tileset.getTiles();
            for (const auto& tile : tiles) {
                if (!tile.className.empty() || tile.properties.size() > 0) {
                    std::cout << "\t *Tile: " << tile.className << ", " << tile.ID << ", " << tile.properties.size() << " properties." << std::endl;
                    TileType tileInfo{tileset.getFirstGID(), tileset.getFirstGID()+tile.ID, tile.className, tile.properties};
                    info.customTypes.emplace_back(tileInfo);
                }
            }
        }

    }
    return tilesetMap;
}

std::vector<TmxTileMap::Tile> TmxTileMap::parseTileLayers(const tmx::Map& map,
    const std::unordered_map<std::uint32_t, Tileset>& tilesets) {

    std::vector<Tile> tileInfos;

    const auto& layers = map.getLayers();
    for (const auto& layer : layers) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const std::vector<tmx::TileLayer::Tile>& tiles = tileLayer.getTiles();

            std::string name = tileLayer.getName();
            auto tileLayerSize = tileLayer.getSize();

            std::cout << "\t***** Tile Layer with name: " << name << ", number of tiles: " << tiles.size() << 
            ", layer Size: " << tileLayerSize.x << "x" << tileLayerSize.y <<  std::endl;

            for (std::size_t i = 0; i < tiles.size(); ++i) {
                const auto& tile = tiles[i];
                if (tile.ID != 0) {
                    std::uint32_t firstGID = this->findTilesetForTileID(tile.ID, tilesets);
                    Tile tileInfo{firstGID, tile.ID, i};
                    tileInfos.push_back(tileInfo);
                }
            }
        }
    }

    return tileInfos;
}

u_int32_t TmxTileMap::findTilesetForTileID(
        u_int32_t tileID,
        const std::unordered_map<u_int32_t, Tileset>& tilesets) {

    for (const auto& [firstGID, info] : tilesets) {
        if (tileID >= firstGID && tileID < firstGID + info.tileCount) {
            return firstGID;
        }
    }
    return -1;
}

void TmxTileMap::render(SDL_Renderer* renderer) {

    //std::cout << "Rendering map with " << this->tiles.size() << " tiles." << std::endl;

    if (this->tsTexture == nullptr) {
    this->tsTexture = createTexture(
            renderer,
            "./assets/full_custom.png"
    );
    }

    const auto tileWidthNorm = static_cast<float>(64.0f/this->tsTexture->w);
    const auto tileHeightNorm = static_cast<float>(64.0f/this->tsTexture->h);
    std::cout << "Norm Size: " << tileWidthNorm << "," << tileHeightNorm << std::endl;
    std::cout << "Texture size " <<  this->tsTexture->w << "x" << this->tsTexture->h << std::endl;

    std::vector<SDL_Vertex> vertexData;

     for (const auto& tile : this->tiles) {
        const auto& tileset = this->tilesets.at(tile.tileGID);

        const std::uint32_t localTileID = tile.tileID - tileset.firstGID;
        const std::uint32_t column = tile.index % static_cast<std::uint32_t>(this->width);
        const std::uint32_t row = tile.index / static_cast<std::uint32_t>(this->width);
        const float x0 = static_cast<float>(column * this->tileWidth);
        const float y0 = static_cast<float>(row * this->tileHeight);
        const float x1 = x0 + static_cast<float>(tileset.tileWidth);
        const float y1 = y0 + static_cast<float>(tileset.tileHeight);

        const float u0 = static_cast<float>((localTileID % tileset.columnCount) * tileset.tileWidth) / this->tsTexture->w;
        const float v0 = static_cast<float>((localTileID / tileset.columnCount) * tileset.tileHeight) / this->tsTexture->h;
        const float u1 = u0 + static_cast<float>(tileset.tileWidth) / this->tsTexture->w;
        const float v1 = v0 + static_cast<float>(tileset.tileHeight) / this->tsTexture->h;

        SDL_Vertex vtx1 = {{x0, y0}, {1.0f, 1.0f, 1.0f, 1.0f}, {u0, v0}};
        vertexData.emplace_back(vtx1);
        SDL_Vertex v2 = {{x1, y0}, {1.0f, 1.0f, 1.0f, 1.0f}, {u1, v0}};
        vertexData.emplace_back(v2);
        SDL_Vertex v3 = {{x1, y1}, {1.0f, 1.0f, 1.0f, 1.0f}, {u1, v1}};
        vertexData.emplace_back(v3);
        SDL_Vertex v4 = {{x0, y0}, {1.0f, 1.0f, 1.0f, 1.0f}, {u0, v0}};
        vertexData.emplace_back(v4);
        SDL_Vertex v5 = {{x0, y1}, {1.0f, 1.0f, 1.0f, 1.0f}, {u0, v1}};
        vertexData.emplace_back(v5);
        SDL_Vertex v6 = {{x1, y1}, {1.0f, 1.0f, 1.0f, 1.0f}, {u1, v1}};
        vertexData.emplace_back(v6);
    }

    if (!SDL_RenderGeometry(renderer, this->tsTexture, vertexData.data(), static_cast<std::int32_t>(vertexData.size()), nullptr, 0)) {
        SDL_Log("SDL_RenderGeometry failed: %s", SDL_GetError());
    }
}

SDL_Texture* createTexture(SDL_Renderer* renderer, const std::string& fileName) {

    SDL_Texture* texture = IMG_LoadTexture(renderer, fileName.c_str());
    if (!texture) {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }

    return texture;
}
