#include "TmxTileMap.hpp"

#include "MathDefinitions.hpp"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SDL3_image/SDL_image.h>

TmxTileMap::~TmxTileMap() {
    
    for (auto& layerRenderData : this->renderData) {
        if (layerRenderData.texture != nullptr) {
            SDL_DestroyTexture(layerRenderData.texture);
            layerRenderData.texture = nullptr;
        }
    }
}

void TmxTileMap::load(const std::string& tmxFilePath, u_int32_t layerIndex) {
    std::cout << "==================== Loading tileset from file [" << tmxFilePath << "]" << std::endl;
    tmx::Map map;
    map.load(tmxFilePath);

    const auto& tilesets = map.getTilesets();
    const auto& layers = map.getLayers();

    assert(layers.size() > layerIndex);
    assert(layers[layerIndex]->getType() == tmx::Layer::Type::Tile);

    const auto& tileLayer = layers[layerIndex]->getLayerAs<tmx::TileLayer>();
    std::vector<LayerRenderData> tmpRenderData;

    for (const auto& tileset : tilesets) {

        std::vector<SDL_Vertex> vertexData;
        const auto& tiles = tileLayer.getTiles();
        
        float uNorm = static_cast<float>(tileset.getTileSize().x) / tileset.getImageSize().x;
        float vNorm = static_cast<float>(tileset.getTileSize().y) / tileset.getImageSize().y;

        std::cout << "Processing tileset: uNorm= " << uNorm << ", vNorm: " << vNorm << std::endl;

        for (std::size_t i = 0; i < tiles.size(); ++i) {
            
            const auto& tile = tiles[i];
            
            
            if (tile.ID == 0 || !this->isTileIDWithinTileset(tile.ID, tileset))
                continue;

            Vector2DI srcPos = oneDimToTwoDim(
                tile.ID - tileset.getFirstGID(),
                tileset.getColumnCount(),
                tileset.getTileSize().x,
                tileset.getTileSize().y
            );

            Vector2DI destPos = oneDimToTwoDim(
                i,
                map.getTileCount().x,
                tileset.getTileSize().x,
                tileset.getTileSize().y);
            
            float u = static_cast<float>(srcPos.x) / tileset.getImageSize().x;
            float v = static_cast<float>(srcPos.y) / tileset.getImageSize().y;

            std::cout << "Processing tile with ID " << tile.ID << "] at index " << i <<
                " u: " << u << ", v: " << v << ", SrcPos: "<<std::endl;


            SDL_Vertex vertex = {{destPos.x, destPos.y}, {1.0f, 1.0f, 1.0f, 1.0f}, {u, v}};
            vertexData.emplace_back(vertex);
            vertex = {{destPos.x, destPos.y + map.getTileSize().y}, {1.0f, 1.0f, 1.0f, 1.0f}, {u, v + vNorm}};
            vertexData.emplace_back(vertex);
            vertex = {{destPos.x + map.getTileSize().x, destPos.y + map.getTileSize().y}, {1.0f, 1.0f, 1.0f, 1.0f}, {u + uNorm, v + vNorm}};
            vertexData.emplace_back(vertex);
            vertex = {{destPos.x, destPos.y}, {1.0f, 1.0f, 1.0f, 1.0f}, {u, v}};
            vertexData.emplace_back(vertex);
            vertex = {{destPos.x + map.getTileSize().x, destPos.y}, {1.0f, 1.0f, 1.0f, 1.0f}, {u + uNorm, v}};
            vertexData.emplace_back(vertex);
            vertex = {{destPos.x + map.getTileSize().x, destPos.y + map.getTileSize().y}, {1.0f, 1.0f, 1.0f, 1.0f}, {u + uNorm, v + vNorm}};
            vertexData.emplace_back(vertex);
        }

        LayerRenderData layerData = {
            vertexData, tileset.getImagePath(), nullptr
        };

        tmpRenderData.emplace_back(layerData);
    }

    this->renderData.swap(tmpRenderData);
}

bool TmxTileMap::isTileIDWithinTileset(u_int32_t tileID, const tmx::Tileset& tileset) {
    return (tileID >= tileset.getFirstGID() && tileID < tileset.getFirstGID() + tileset.getTileCount());
}

void TmxTileMap::render(SDL_Renderer* renderer) {

    for (auto& layerRenderData : this->renderData) {
        // TODO workaround for this sample only
        if (layerRenderData.texture == nullptr) {
            layerRenderData.texture = createTexture(renderer, layerRenderData.textureImagePath);
        }

        if (!SDL_RenderGeometry(renderer, layerRenderData.texture, layerRenderData.vertexData.data(), static_cast<std::int32_t>(layerRenderData.vertexData.size()), nullptr, 0)) {
            SDL_Log("SDL_RenderGeometry failed: %s", SDL_GetError());
        }
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
