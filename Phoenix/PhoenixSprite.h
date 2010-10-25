#ifndef _PHOENIXSPRITE_H_
#define _PHOENIXSPRITE_H_
#include <tchar.h>
#include "PhoenixTexture.h"


namespace PhoenixCore{

class PhSprite
{
private:
  PhTextureManager* m_pTextureMan;
  int*        m_pTextures;
  int*        m_pTextureStart;
  int*        m_pTextureEnd;
  int         m_nDelay;
  int         m_nSpriteIndex;
  int         m_nSpriteLength;
  int         m_nSpriteLoadIndex;


public:
  PhSprite(PhTextureManager* _pTexMan);
  ~PhSprite();
  bool SetSize(int _size);
  void SetDelay(int _delay);
  bool AddSprite(TCHAR* _filename);
  PhTexture* GetNextSprite();
  void Init();
  
};

};

#endif