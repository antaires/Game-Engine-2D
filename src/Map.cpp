#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize){
  this->textureId = textureId;
  this->scale = scale;
  this->tileSize = tileSize;
}

Map::~Map(){}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY){
  std::fstream mapFile;
  mapFile.open(filePath);

  // read character by character in file as tile numbers
  // tile number represents where the source rectangle should go on tile map to
  // load correct tile
  for(int y = 0; y < mapSizeY; ++y){
    for(int x = 0; x < mapSizeX; ++x){
      char ch;
      // character in map ex: 21 would be tile at row 2, column 1
      mapFile.get(ch);
      int sourceRectY = atoi(&ch) * tileSize; // string to init * tileSize
      mapFile.get(ch);
      int sourceRectX = atoi(&ch) * tileSize; // string to init * tileSize
      AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
      mapFile.ignore(); // skip the comma
    }
  }
  mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y){
  Entity& newTile(manager.AddEntity("Tile"));
  newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);
}
