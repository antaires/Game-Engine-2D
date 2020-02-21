#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"

class TileComponent: public Component{
public:
  SDL_Texture* texture;
  SDL_Rect sourceRectangle;
  SDL_Rect destinationRectangle;
  glm::vec2 position;

  TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, std::string assetTextureId);
  ~TileComponent();

  void Update(float deltaTime) override {}

  void Render() override {}
private:
};

#endif
