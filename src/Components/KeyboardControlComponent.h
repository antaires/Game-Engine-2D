#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlComponent: public Component {
public:
  std::string upKey;
  std::string downKey;
  std::string leftKey;
  std::string rightKey;
  std::string shootKey;
  TransformComponent *transform;
  SpriteComponent *sprite;

  KeyboardControlComponent(){}

  KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey){
    this->upKey = GetSDLKeyStringCode(upKey);
    this->rightKey = GetSDLKeyStringCode(rightKey);
    this->downKey = GetSDLKeyStringCode(downKey);
    this->leftKey = GetSDLKeyStringCode(leftKey);
    this->shootKey = GetSDLKeyStringCode(shootKey);
  }

  std::string GetSDLKeyStringCode(std::string key){
    // translate key into SDL codes
    if (key.compare("up") == 0)    return "1073741906";
    if (key.compare("down") == 0)  return "1073741905";
    if (key.compare("left") == 0)  return "1073741904";
    if (key.compare("right") == 0) return "1073741903";
    if (key.compare("space") == 0) return "32";
    // gets ASCII codes conversion to int of key
    return std::to_string(static_cast<int>(key[0]));
  }

  void Initialize() override {
    transform = owner->GetComponent<TransformComponent>();
    sprite = owner->GetComponent<SpriteComponent>();
  }

  void Update(float deltaTime) override {

  }

private:
};

#endif
