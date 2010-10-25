#include "PhoenixGlobal.h"
#include "PhoenixEntityManager.h"

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

}

Node<PhEntity>* PhEntityManager::GetFirstNode()
{
  return this->EntityList->first();
}

};