#ifndef _PHOENIXENTITY_H_
#define _PHOENIXENTITY_H_

#include "PhoenixUtil.h"

#include <vector>
#include <functional>

namespace PhoenixCore
{
  class Vertex2;					//PhoenixUtil.h
  class Texture;
  class Controller;
  template <class _Ty> class Sprite;

  //The Components
  //Mandatory
  template<class _Ty> class Visual;
  class Collision;

  //Game Specific
  class AsFrameData;
  class AsAttackData;

  //The Controller
  class Entity
  {

  private:
    bool dead;

    AsFrameData*      pFrameData;
    AsAttackData*     pAttackData;
    Sprite<Texture>*           pVisual;
    Collision*        pCollision;

    std::vector<Controller*> Controllers;
    std::function<void(Entity* _pOther)> Collision;

  public:

    Entity();
    ~Entity();

    Controller* AddController(Controller* c);
    void RemoveController(Controller* c);
    void RunControllers();
    void RemoveController();
    bool isDead();
    void Kill();
    Sprite<Texture>* GetSprite();
    void AssignSprite(Sprite<Texture>* sprite);
  };
}

#endif // _PHOENIXENTITY_H_
