 /* PhoenixController.h
  * (c) Sean Stacey, Feb 2011
  *
  * The controller object of the engine.
  * 
  * Entities have controllers added to them. These controllers act on the
  * object each frame. So something like an AI controller, or Input controller.
  */

#ifndef _PHOENIXCONTROLLER_H_
#define _PHOENIXCONTROLLER_H_

#include "CircularList.h"
#include <functional>

namespace PhoenixCore{

  class Entity;

  class Controller
  {
  private:
    std::function<int(Entity*)> f;
    int refCount;
    Controller* next;

  public: 
    friend class ControllerFactory;
    friend class Entity;

    Controller(std::function<int(Entity*)> f);
    int operator() (Entity* e);
    Controller* AssignEntity(Entity* e);
    void RemoveEntity(Entity* e);
  };

  // ControllerFactory Class
  // Singleton
  class ControllerFactory
  {
  private:
    static ControllerFactory* instance;
    CircularList<Controller>* List;
    CircularList<Controller>::iterator Iter;

  protected:
    ControllerFactory();
    ~ControllerFactory();

  public:
    Controller* CreateController(std::function<int(Entity*)> f);
    void GarbageCollect();

    static ControllerFactory* Instance();
  };

} /*PhoenixCore*/
#endif /*_PHOENIXCONTROLLER_H_*/