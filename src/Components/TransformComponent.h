#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../constants.h"


class TransformComponent: public Component {
  public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;

    int windowWidth;
    int windowHeight;

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s){
      position = glm::vec2(posX, posY);
      velocity = glm::vec2(velX, velY);
      width = w;
      height = h;
      scale = s;
      name = "Transform Component";
    }

    void Initialize() override {
    }

    void Update(float deltaTime) override {
       int tempX = position.x + velocity.x * deltaTime;
       int tempY = position.y + velocity.y * deltaTime;

       if (tempX > WINDOW_WIDTH){
         position.x = 0;
       } else {
         position.x = tempX;
       }

       if (tempY > WINDOW_HEIGHT){
         position.y = 0;
       } else {
         position.y = tempY;
       }
    }

    void Render() override {
    }
};

#endif TRANSFORMCOMPONENT_H
