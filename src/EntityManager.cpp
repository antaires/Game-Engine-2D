#include "./EntityManager.h"

void EntityManager::ClearData(){
  for (auto& entity: entities){
    entity->Destroy();
  }
}

bool EntityManager::HasNoEntities(){
  return entities.size() == 0;
}

void EntityManager::Update(float deltaTime){
  for(auto& entity: entities){
    entity->Update(deltaTime);
  }
}

void EntityManager::Render(){
  for(auto& entity: entities){
    entity->Render();
  }
}

Entity& EntityManager::AddEntity(std::string entityName){
  Entity *entity = new Entity(*this, entityName);
  entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
  return entities;
}

unsigned int EntityManager::GetEntityCount() {
  // this is correct, but throws an error!
  return entities.size();
}


// TODO these functions were HW and ListAllComponents
void EntityManager::ListAllEntities() const{
  unsigned int i = 0;
  for (Entity* e : entities) {
    std::cout<<"Entity["<<i<<"]: "<<e->name<<std::endl;
    e->ListAllComponents();
    i++;
  }
}