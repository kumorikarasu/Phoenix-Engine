#include "PhoenixGlobal.h"
#include "PhoenixEntityManager.h"
#include "PhoenixEntity.h"

namespace PhoenixCore{

PhEntityManager::PhEntityManager()
{
  EntityList = new LinkedList<PhEntity>();
}

PhEntityManager::~PhEntityManager()
{
  delete this->EntityList;
}

void PhEntityManager::AddEntity(PhEntity* _pEntity)
{
  EntityList->add(_pEntity);
}

Node<PhEntity>* PhEntityManager::GetFirstNode()
{
  return this->EntityList->first();
}

void PhEntityManager::Run()
{
  Node<PhEntity>* node = EntityList->first();
  if (node->getObject() != NULL)
    while(node != NULL){
      PhEntity* ent = node->getObject();
//      if (ent->isDead()){
//        delete ent;
//        node = EntityList->remove(node);
//      }
      node = node->getNext();
    }

}

void PhEntityManager::Draw(PhIRenderer* pGDI)
{
  Node<PhEntity>* node = EntityList->first();
  if (node->getObject() != NULL)
    while(node != NULL){
      PhEntity* ent = node->getObject();
//      if (ent->isDrawable()){}

      node = node->getNext();
    }

}

};