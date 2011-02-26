#include "PhoenixGlobal.h"
#include "PhoenixEntityManager.h"
#include "PhoenixEntity.h"

namespace PhoenixCore{

EntityManager::EntityManager()
{
  EntityList = new LinkedList<Entity>();
}

EntityManager::~EntityManager()
{
  delete this->EntityList;
}

void EntityManager::AddEntity(Entity* _pEntity)
{
  EntityList->add(_pEntity);
}

Node<Entity>* EntityManager::GetFirstNode()
{
  return this->EntityList->first();
}

void EntityManager::Run()
{
  Node<Entity>* node = EntityList->first();
  if (node->getObject() != NULL)
    while(node != NULL){
      Entity* ent = node->getObject();
//      if (ent->isDead()){
//        delete ent;
//        node = EntityList->remove(node);
//      }
      node = node->getNext();
    }

}

void EntityManager::Draw(IRenderer* pGDI)
{
  Node<Entity>* node = EntityList->first();
  if (node->getObject() != NULL)
    while(node != NULL){
      Entity* ent = node->getObject();
//      if (ent->isDrawable()){}

      node = node->getNext();
    }

}

};