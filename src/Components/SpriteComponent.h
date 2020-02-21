#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

class SpriteComponent: public Component {
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        bool isAnimated;
        int numFrames;
        int animationSpeed;
        bool isFixed; // doesn't matter what happens with camera or players, always stay in same screen position (text / labels)
        std::map<std::string, Animation> animations; // track animations (facing up, down etc)
        std::string currentAnimationName;
        unsigned int animationIndex = 0;

    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(const char* assetTextureId) { // filepath is assetTextureId
            // no animations
            isAnimated = false;
            isFixed = false;
            SetTexture(assetTextureId);
        }

        SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirection, bool isFixed){
            // for animations
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->animationSpeed = animationSpeed;
            this->isFixed = isFixed;

            if(hasDirection){
              // create up, down, left, right animation frames --- index
              Animation downAnimation = Animation(0, numFrames, animationSpeed);
              Animation rightAnimation = Animation(1, numFrames, animationSpeed);
              Animation leftAnimation = Animation(2, numFrames, animationSpeed);
              Animation upAnimation = Animation(3, numFrames, animationSpeed);

              // add animations to map
              animations.emplace("DownAnimation", downAnimation);
              animations.emplace("RightAnimation", rightAnimation);
              animations.emplace("LeftAnimation", leftAnimation);
              animations.emplace("UpAnimation", upAnimation);

              this->animationIndex = 0;
              this->currentAnimationName = "DownAnimation";

            } else {
              Animation singleAnimation = Animation(0, numFrames, animationSpeed);
              animations.emplace("singleAnimation", singleAnimation);
              this->animationIndex = 0;
              this->currentAnimationName = "singleAnimation";
            }

            Play(this->currentAnimationName);
            SetTexture(id);

        }

        void Play(std::string currentAnimationName){
            // sets all variables to play the chosen animation frame
            this->numFrames = animations[currentAnimationName].numFrames;
            this->animationIndex = animations[currentAnimationName].index;
            this->animationSpeed = animations[currentAnimationName].animationSpeed;
            this->currentAnimationName = currentAnimationName;
        }

        void SetTexture(std::string assetTextureId) {
            texture = Game::assetManager->GetTexture(assetTextureId);
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle.x = 0;
            sourceRectangle.y = 0;
            sourceRectangle.w = transform->width;
            sourceRectangle.h = transform->height;
        }

        void Update(float deltaTime) override {
            if (isAnimated){
              // move to next frame (horizontal - x - movement is animation, loops on sprite width)
              sourceRectangle.x = sourceRectangle.w * (static_cast<int>(SDL_GetTicks() / animationSpeed) % numFrames);
            }
            sourceRectangle.y = animationIndex * transform->height; // index is which row on sprite spritesheet
            destinationRectangle.x = static_cast<int>(transform->position.x);
            destinationRectangle.y = static_cast<int>(transform->position.y);
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
        }
};

#endif
