#pragma once

#ifndef _PHOENIXSPRITE_H_
#define _PHOENIXSPRITE_H_

#include <tchar.h>
#include <vector>
#include "PhoenixVisual.h"
#include "PhoenixIResource.h"
#include "PhoenixUtil.h"

namespace PhoenixCore{

  class Texture;

  template <class _Ty>
  class Sprite : public Visual<Sprite<_Ty>>, IResource
  {
  private:
    typedef typename std::vector<_Ty*> container;
    typedef typename container::iterator it;

    container textureList;
    it texturePos;
    Vertex2 pos;

  public:
    Sprite();
    ~Sprite();
    bool AddVisual(_Ty* texture);
    _Ty* GetPreviousFrame();
    _Ty* GetNextFrame();
    _Ty* GetFrame();
    _Ty* GetFrame(int frame);
    int GetLength();

    Vertex2& GetPosition(){
      return pos;
    }

    void SetPosition(Vertex2& pos){
      this->pos = pos;
    }
  };

  template<class _Ty>
  int Sprite<_Ty>::GetLength(){
    return textureList.size();
  }

  template<class _Ty>
  inline Sprite<_Ty>::Sprite() : Visual(VISUAL_NONE)
  {
    pos = Vertex2(0,0);
    texturePos = textureList.begin();
  }

  template<>
  inline Sprite<Texture>::Sprite() : Visual(VISUAL_IMAGE)
  {
    pos = Vertex2(0,0);
    texturePos = textureList.begin();
  }

  template<class _Ty>
  Sprite<_Ty>::~Sprite()
  {

  }

  template<class _Ty>
  bool Sprite<_Ty>::AddVisual(_Ty* texture)
  {
    textureList.push_back(texture);
    texturePos = textureList.begin();
    return true;
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