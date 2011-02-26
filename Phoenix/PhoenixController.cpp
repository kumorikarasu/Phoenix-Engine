#include "PhoenixController.h"
#include "CircularList.h"
#include "PhoenixEntity.h"
#include <iterator>

namespace PhoenixCore{

  Controller::Controller(std::function<int(Entity*)> f)
  {
    refCount = 0;
    this->f = f;
  }

  int Controller::operator() (Entity* e)
  {
    return f(e);
  }

  Controller* Controller::AssignEntity(Entity* e)
  {
    e->AddController(this);
    return this;
  }

  void Controller::RemoveEntity(Entity* e)
  {
    e->RemoveController(this);

  }

  ControllerFactory::ControllerFactory()
  {
    List = new CircularList<Controller>();
    Iter = List->GetIterator();
  }

  ControllerFactory::~ControllerFactory()
  {

  }

  Controller* ControllerFactory::CreateController(
                std::function<int(Entity*)> f)
  {
    Controller* c = new Controller(f);
    List->Add(c);
    return c;
  }

  void ControllerFactory::GarbageCollect()
  {
    if (! List->Empty()){
      if ((*Iter) == NULL || Iter.Modified())
        Iter = List->GetIterator();

      if (Iter->refCount == 0){
        delete (*Iter);
        Iter = List->Remove(Iter);
      }else{
        ++Iter;
      }
    }
  }
  
  //Singleton pattarn
  ControllerFactory* ControllerFactory::instance = 0;
  ControllerFactory* ControllerFactory::Instance()
  {
    if (instance == NULL)
      instance = new ControllerFactory();
    return instance;
  }

} /* PhoenixCore */