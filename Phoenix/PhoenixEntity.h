#ifndef _PHOENIXENTITY_H_
#define _PHOENIXENTITY_H_

#include "PhoenixUtil.h"
#include "PhoenixController.h"

#include <list>
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
  class PhEntity
  {

  private:
    AsFrameData*        pFrameData;
    AsAttackData*       pAttackData;
    PhVisual*           pVisual;
    PhCollision*        pCollision;

    std::list<PhController<PhEntity>> Controllers;
    std::function<void(PhEntity* _pOther)> Collision;

  public:

    PhEntity();
    ~PhEntity();

    void AddController(std::function<int(PhEntity*)> f);
    void RemoveController(std::function<int(PhEntity*)> f);
    void RemoveController();

  };
}

#endif // _PHOENIXENTITY_H_
