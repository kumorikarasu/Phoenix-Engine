#ifndef _PHOENIXENTITY_H_
#define _PHOENIXENTITY_H_

#include "PhoenixUtil.h"
#include "PhoenixController.h"

#include <vector>
#include <functional>

namespace PhoenixCore
{
  class Vertex2;					//PhoenixUtil.h

  //The Components
  //Mandatory
  class PhVisual;
  class PhCollision;

  //Game Specific
  class AsFrameData;
  class AsAttackData;

  //The Controller
  class Entity
  {

  private:
    bool dead;

    AsFrameData*        pFrameData;
    AsAttackData*       pAttackData;
    PhVisual*           pVisual;
    PhCollision*        pCollision;

    std::vector<Controller*> Controllers;
    std::function<void(Entity* _pOther)> Collision;

  public:

    Entity();
    ~Entity();

    Controller* AddController(Controller* c);
    void RemoveController(Controller* c);
    void RemoveController();
    bool isDead();
    void Kill();

  };
}

#endif // _PHOENIXENTITY_H_
