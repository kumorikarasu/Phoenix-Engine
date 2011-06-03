#ifndef _PHOENIXENTITYMANAGER_H_
#define _PHOENIXENTITYMANAGER_H_

namespace PhoenixCore{

#include "LinkedList.h"

  class Entity; //PhoenixEntity.h

  class EntityManager
  {
  private:
    LinkedList<Entity>* EntityList;

  public:

    EntityManager();
    ~EntityManager();

    void AddEntity(Entity* _pEntity);
    Node<Entity>* GetFirstNode();
    void Run();
    void Draw(IRenderer* pGDI);

  };
}

#endif _PHOENIXENTITYMANAGER_H_
