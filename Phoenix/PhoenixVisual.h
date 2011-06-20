#ifndef _PHOENIXVISUAL_H_
#define _PHOENIXVISUAL_H_

#include <vector>

namespace PhoenixCore{
#define VISUAL_IMAGE 1
#define VISUAL_ANIMATION 2
#define VISUAL_VBO 3
#define VISUAL_NONE 4

  template<class _Ty>
  class Visual{
  private:
    int Type;

    std::vector<_Ty*> Display;
  public:
    
    Visual(){}

    Visual(int _Type){
      Type = _Type;
    }
    void AddVisual(_Ty* Visual){
      Display.push_back(visual);
    }

    std::vector<_Ty*>& GetVisual(){
      return Display;
    }

    int GetType(){
      return Type;
    }
  };
};

#endif 