#ifndef _PHOENIXCONTROLLER_H_
#define _PHOENIXCONTROLLER_H_
#include <functional>
#include "CircularList.h"

namespace PhoenixCore{

  template<class _Ty>
  class PhController
  {
  private:
    std::function<int(_Ty*)> f;
    int refCount;
    PhController* next;

  public: 
    template<class _Ty> friend class PhControllerFactory;

    PhController(std::function<int(_Ty*)> f)
    {
      refCount = 1;
      this->f = f;
    }

    PhController operator() (_Ty* e)
    {
      f(e);
    }
    void free(){
      --refCount;
    }
  };

  template<class _Ty>
  class PhControllerFactory
  {
  private:
    static PhControllerFactory* instance;
    CircularList<_Ty*> List;

  public:
    PhControllerFactory()
    {
    }

    PhController* CreateController(std::function<int(_Ty*)> f)
    {
      PhController<_Ty>* c = new PhController<_Ty>(f);
      controllers.push_back(c);
    }

    void GarbageCollect()
    {
      /*
      if (endController != currentController){
        ++currentController;
        if ((*currentController)->refCount == 0)
          delete (*currentController);
      }else{
        currentController = controllers.begin();
        endController = controllers.end();
      }
      */

    }

    PhControllerFactory* Instance()
    {
      if (!instance)
        instance = new PhControllerFactory<_Ty>();
      return instance;
    }
  };
} /*PhoenixCore*/
#endif /*_PHOENIXCONTROLLER_H_*/