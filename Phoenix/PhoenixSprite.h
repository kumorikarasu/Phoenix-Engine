#ifndef _PHOENIXSPRITE_H_
#define _PHOENIXSPRITE_H_
#include <tchar.h>
#include <vector>
#include "PhoenixVisual.h"
#include "PhoenixIResource.h"

namespace PhoenixCore{

  template <class _Ty>
  class Sprite : public Visual<Sprite<_Ty>>, IResource
  {
  private:
    typedef typename std::vector<_Ty*> container;
    typedef typename container::iterator it;

    container textureList;
    it texturePos;

  public:
    Sprite();
    ~Sprite();
    bool AddSprite(_Ty* texture);
    _Ty* GetPreviousFrame();
    _Ty* GetNextFrame();
    _Ty* GetFrame();
    _Ty* GetFrame(int frame);
    int GetLength();
  };

  template<class _Ty>
  int Sprite<_Ty>::GetLength(){
    return textureList.size();
  }

  template<class _Ty>
  Sprite<_Ty>::Sprite()
  {
    texturePos = textureList.begin();
  }

  template<class _Ty>
  Sprite<_Ty>::~Sprite()
  {

  }

  template<class _Ty>
  bool Sprite<_Ty>::AddSprite(_Ty* texture)
  {
    textureList.push_back(texture);
    texturePos = textureList.begin();
  }

  template<class _Ty>
  _Ty* Sprite<_Ty>::GetPreviousFrame()
  {
    if (texturePos != textureList.begin()){
      ++texturePos;
      return *texturePos;
    }
    return NULL;
  }

  template<class _Ty>
  _Ty* Sprite<_Ty>::GetNextFrame()
  {
    if (texturePos != textureList.end()){
      ++texturePos;
      return *texturePos;
    }
    return NULL;
  }

  template<class _Ty>
  _Ty* Sprite<_Ty>::GetFrame()
  {
    return *texturePos;
  }

  //Sets the position pointer to that frame and returns it
  template<class _Ty>
  _Ty* Sprite<_Ty>::GetFrame(int frame)
  {
    if (frame < textureList.size()){
      texturePos = textureList.begin() + frame;
      return *texturePos;
    }

    return NULL;
  }
};

#endif