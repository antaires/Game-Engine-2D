#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "./TextureManager.h"
#include "./EntityManager.h"
#include<map>
#include<string>

class AssetManager {
private:
  EntityManager* manager;
  std::map<std::string, SDL_Texture*> textures; // key, values list of textures I'm manging with asset manager
public:
  AssetManager(EntityManager* manager);
  ~AssetManager();
  void ClearData(); // between levels
  void AddTexture(std::string textureId, const char* filePath);
  SDL_Texture* GetTexture(std::string textureId);
};

#endif
