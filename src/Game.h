#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"

class AssetManager;

class Game {
  private:
    bool isRunning;
    SDL_Window *window; // pointer to window position
  public:
    Game(); // game constructor
    ~Game(); // game destructor
    int ticksLastFrame;
    bool IsRunning() const; // can be const, because funct does not change anything
    static SDL_Renderer *renderer;
    static AssetManager* assetManager;
    void LoadLevel(int levelNumber);
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
