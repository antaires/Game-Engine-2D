#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ColliderComponent {
public:
  std::string colliderTag;
  SDL_Rect collider;
  SDL_Rect sourceRectangle;
  SDL_Rect destinationRectangle;
  TransformComponent* transform;

  ColliderComponent(std::string colliderTag, int x, int y, int w, int h){
    this->colliderTag = colliderTag;
    this->collider = {x, y, w, h};
  }

  void Initialize() override {
    if (owner->HasComponent<TransformComponent>()){
      transform = owner->GetComponent<TransformComponent>();
      sourceRectangle = {0, 0, transform->width, transform->height};
      destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
    }
  }

  void Update(float deltaTime) override {
    if (owner->HasComponent<TransformComponent>()){
      // keep collider up to date with owner transform
      collider.x = static_cast<int> tranform->position.x;
      collider.y = static_cast<int> transform->position.y;
      collider.w = transform->width * transform->scale;
      collider.h = transform->height * transform->scale;

      // colider must also respond to camera
      destinationRectangle.x = collider.x - Game::camera.x;
      destinationRectangle.y = collider.y - Game::camera.y;
    }
  }

private:
};

#endif
