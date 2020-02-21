#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"

Map::Map(std::string textureId, int scale, int tileSize){
  this->textureId = textureId;
  this->scale = scale;
  this->tileSize = tileSize;
}

Map::~Map(){}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY){
  // TODO: read the map tile definitions from .map file
}

void Map::AddTile(int sourceX, int sourceY, int x, int y){
  // TODO: add new tile entity in the game scene
}
