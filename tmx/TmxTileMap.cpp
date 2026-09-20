#include "TmxTileMap.hpp"

#include "MathDefinitions.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SDL3_image/SDL_image.h>

TmxTileMap::~TmxTileMap() {

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

    for (const auto& tile : this->tiles) {
        const auto& tileset = this->tilesets[tile.tileGID];
        //std::cout << "Rendering tile with [GID,ID]["<< tile.index <<"]: [" << tile.tileGID << "," << tile.tileID << "] from tileset: " << tileset.name << std::endl;
        
        SDL_Texture* tsTexture = createTexture(
            renderer,
            tileset.imagePath
        );

        if (!tsTexture) {
            std::cout << "\tFailed to get texture for tileset image: " << tileset.imagePath << std::endl;
            continue;
        }

        // Calculate source rectangle in the texture with the image
        Vector2DI srcPos = oneDimToTwoDim(
            tile.tileID - tileset.firstGID,
            tileset.columnCount,
            tileset.tileWidth,
            tileset.tileHeight
        );

        // Calculate the destination rectangle in the screen to render
        Vector2DI destPos = oneDimToTwoDim(tile.index,
            this->width,
            this->tileWidth,
            this->tileHeight);

        SDL_FRect srcRect = {
            srcPos.x,
            srcPos.y,
            static_cast<int>(tileset.tileWidth),
            static_cast<int>(tileset.tileHeight)
        };

        SDL_FRect destRect = {
            destPos.x,
            destPos.y,
            static_cast<int>(tileset.tileWidth),
            static_cast<int>(tileset.tileHeight)    
        };
        
        //std::cout << "\tSource Rect: [" << srcRect.x << "," << srcRect.y << "," << srcRect.w << "," << srcRect.h << "]" << std::endl;
        //std::cout << "\tDest Rect:   [" << destRect.x << "," << destRect.y << "," << destRect.w << "," << destRect.h << "]" << std::endl;

        SDL_RenderTexture(renderer, tsTexture, &srcRect, &destRect);
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
