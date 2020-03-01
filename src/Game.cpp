#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Map.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Map* map;

Game::Game() {
  this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height){
  // create all SDL inits / flow

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr<< "Error Initializing SDL" << std::endl;
    return;
  }
  window = SDL_CreateWindow(
    NULL
    , SDL_WINDOWPOS_CENTERED
    , SDL_WINDOWPOS_CENTERED
    , width
    , height
    , SDL_WINDOW_BORDERLESS
  );
  if (!window){
    std::cerr<<"Error Creating SDL Window" << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1 , 0);
  if (!renderer){
    std::cerr<<"Error Creating SDL Renderer" << std::endl;
    return;
  }

  LoadLevel(0);

  isRunning = true;
  return;
}

void Game::LoadLevel(int levelNumber){
  // add entities and add components to the entities
  assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str()); // not animated
  assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str()); // animated
  assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str()); // animated
  assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());

  map = new Map("jungle-tiletexture", 2, 32); // scale 1, tile size is 32 pixels
  map->LoadMap("./assets/tilemaps/jungle.map", 25, 20); // get character map of level design

  // PLAYER
  Entity& chopperEntity(manager.AddEntity("chopper", PLAYER_LAYER));
  chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
  chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false); // name, number of columns = number of frames, speed
  chopperEntity.AddComponent<KeyboardControlComponent>("up", "right","down","left", "space");

  // start including entities and also components to them
  // TEST static tank image
  Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
  tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
  tankEntity.AddComponent<SpriteComponent>("tank-image");

  Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
  radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
  radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

  // TEST
  manager.ListAllEntities();
}

void Game::ProcessInput(){
  SDL_PollEvent(&event);
  switch(event.type){
    case SDL_QUIT: {// clicking 'x button ' on window
      isRunning = false;
      break;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        isRunning = false;
      }
    }
    default: {
      break;
    }
  }
}

void Game::Update(){
  // wait until FRAME_TARGET_TIME reached since last frame
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

  // delta time is difference in ticks from last frame converted to seconds
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

  // clamp to max value - set max deltaTime, in case of debugging or delay (a large value will time travel!)
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

  // sets the new ticks for the current frame to be used in the next pass
  ticksLastFrame = SDL_GetTicks();

  // use delta time to update my game objects
  manager.Update(deltaTime);

}

void Game::Render(){
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer); // clear back buffer

  if (manager.HasNoEntities()){
    return;
  }
  manager.Render();

  SDL_RenderPresent(renderer); // swap buffers and render
}

void Game::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
