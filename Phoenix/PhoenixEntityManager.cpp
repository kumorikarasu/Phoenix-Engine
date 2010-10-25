#include "PhoenixGlobal.h"
#include "PhoenixEntityManager.h"


PhEntityManager::PhEntityManager()
{
  EntityList = new PhoenixCore::LinkedList<PhoenixCore::PhEntity>();
}

PhEntityManager::~PhEntityManager()
{
  delete this->EntityList;
}

void PhEntityManager::AddEntity(PhEntity* _pEntity)
{

}

Node<PhEntity>* PhEntityManager::GetFirstNode()
{
  return this->EntityList->first();
}