#ifndef ENTITY_H
#define ENTITY_H

#include "./EntityManager.h"
#include "./Component.h"
#include "./Constants.h"
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include <iostream>
#include <stdio.h>

class Component;
class EntityManager;

class Entity {
  private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;

  public:
    std::string name;
    LayerType layer;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name, LayerType layer);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;
    void ListAllComponents() const;

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args){
      T* newComponent(new T(std::forward<TArgs>(args)...));
      newComponent->owner = this;
      components.emplace_back(newComponent);
      componentTypeMap[&typeid(*newComponent)] = newComponent; // map of all components by type
      newComponent->Initialize();
      return *newComponent;
    }

    template<typename T>
    T* GetComponent(){
      // caste to correct type
      return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }

    template<typename T>
    bool HasComponent(){
      // TODO can this func be const ?
      if (componentTypeMap[&typeid(T)]){
        return true;
      }
      return false;
    }

};

#endif
