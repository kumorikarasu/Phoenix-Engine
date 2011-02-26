
#include "PhoenixEntity.h"

namespace PhoenixCore{
  Entity::Entity(){
    dead = false;
  }
  Entity::~Entity(){

  }

  //Controllers
  ///Adds a new controller to the entity, returns the entity
  Controller* Entity::AddController(Controller* c)
  {
    Controllers.push_back(c);
    c->refCount++;
    return c;
  }

  void Entity::RemoveController(Controller* c)
  {
    auto it = Controllers.begin();
    for(;it < Controllers.end();++it)
    {
      if (*it == c){
        Controllers.erase(it);
      }
    }
    c->refCount--;
  }

  ///Removes all controllers
  void Entity::RemoveController()
  {
    auto it = Controllers.begin();
    for(;it < Controllers.end();++it)
      (*it)->refCount--;

    Controllers.clear();
  }

  bool Entity::isDead()
  {
    return dead;
  }
  void Entity::Kill()
  {
    dead = true;
  }
}