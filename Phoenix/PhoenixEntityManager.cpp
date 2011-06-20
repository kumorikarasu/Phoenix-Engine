#include "PhoenixGlobal.h"
#include "PhoenixEntityManager.h"
#include "PhoenixEntity.h"
#include "PhoenixRenderer.h"
#include "PhoenixSprite.h"

namespace PhoenixCore{

EntityManager::EntityManager()
{
  EntityList = new LinkedList<Entity>();
  DrawList = new LinkedList<Entity>();
}

EntityManager::~EntityManager()
{
  delete this->EntityList;
  delete this->DrawList;
}

void EntityManager::AddEntity(Entity* _pEntity)
{
  EntityList->add(_pEntity);
}

void EntityManager::AddDrawableEntity(Entity* _pEntity)
{
  EntityList->add(_pEntity);
  DrawList->add(_pEntity);
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
      ent->RunControllers();
      if (ent->isDead()){
        delete ent;
        node = EntityList->remove(node);
      }
      node = node->getNext();
    }
}

void EntityManager::Draw(IRenderer* pGDI)
{
  Node<Entity>* node = DrawList->first();
  if (node->getObject() != NULL)
    while(node != NULL){
      Entity* ent = node->getObject();
      auto t = ent->GetSprite();
      if (t->GetType() == VISUAL_IMAGE)
        pGDI->DrawTexture2D(t->GetFrame(), t->GetPosition());
      node = node->getNext();
    }
}

};