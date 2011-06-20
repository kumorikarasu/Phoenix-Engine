
#include "PhoenixEntity.h"
#include "PhoenixController.h"

namespace PhoenixCore{
  Entity::Entity(){
    dead = false;
    pVisual = false;
    pCollision = false;
  }

  Entity::~Entity(){

  }

  //Controllers
  ///Adds a new controller to the entity, returns the controller
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

  void Entity::RunControllers(){
    for(auto it = Controllers.begin(); it < Controllers.end(); it++){
      auto e = (*it);
      e->f(this);
    }
  }

  bool Entity::isDead()
  {
    return dead;
  }

  Sprite<Texture>* Entity::GetSprite()
  {
    return pVisual;
  }

  void Entity::Kill()
  {
    dead = true;
  }

  void Entity::AssignSprite(Sprite<Texture>* sprite){
    this->pVisual = sprite;
  }
}