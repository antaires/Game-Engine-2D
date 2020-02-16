#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdio.h>
#include <iostream>
#include <stdio.h>

class Entity;

class Component {
  public:
    Entity* owner;
    std::string name;
    virtual ~Component() {}
    virtual void Initialize() {}
    virtual void Update(float deltaTime){}
    virtual void Render() {}
};

#endif
