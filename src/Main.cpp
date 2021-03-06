#include <iostream>
#include "./Constants.h"
#include "./Game.h"


int main(int argc, char* args[]){

  // INIT
  // game class responsible for game loop and rendering etc
  Game *game = new Game();
  game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

  // GAME LOOP
  while(game->IsRunning()){
    game->ProcessInput();
    game->Update();
    game->Render();
  }

  game->Destroy();

  return 0;
}
