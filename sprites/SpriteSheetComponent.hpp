#pragma one

#include "SpriteComponent.hpp"

#include <SDL.h>
#include <vector>

// TODO LEARN: public inheritance vs private inheritance
class SpriteSheetComponent : public SpriteComponent {

public:
    SpriteSheetComponent(float scale, struct Point position, int fps = 20):
    SpriteComponent(scale, position), fps(fps)
    { }

    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override; 
    void setTextureList(std::vector<SDL_Texture*>& textures);


private:
    float currentTexture;
    int fps;
    std::vector<SDL_Texture*> textureList;
};