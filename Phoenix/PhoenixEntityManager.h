#ifndef _PHOENIXENTITYMANAGER_H_
#define _PHOENIXENTITYMANAGER_H_

#include "LinkedList.h"

class PhEntity; //PhoenixEntity.h

class PhEntityManager
{
  private:
    LinkedList<PhEntity>* EntityList;

  public:

    PhEntityManager();
    ~PhEntityManager();

    void AddEntity(PhEntity* _pEntity);
    Node<PhEntity>* GetFirstNode();

};


#endif _PHOENIXENTITYMANAGER_H_
