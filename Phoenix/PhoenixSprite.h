#ifndef _PHOENIXSPRITE_H_
#define _PHOENIXSPRITE_H_
#include <tchar.h>
#include <map>
#include "PhoenixTexture.h"

namespace PhoenixCore{

class PhSprite
{
private:
  struct PhFrame{
    int nStartFrame;
    int nFrames;
    int xoffset;
    int yoffset;
  };

  PhTextureManager* m_pTextureMan;
  int*        m_pTextures;
  int*        m_pTextureStart;
  int*        m_pTextureEnd;
  int         m_nDelay;
  int         m_nSpriteIndex;
  int         m_nSpriteLength;
  int         m_nSpriteLoadIndex;
  int         m_nSpriteFrame;       ///< Current frame that is displayed noscreen
  bool        Corrupt;
  int         m_nState;             ///< Current frame state, used when switching states
  PhFrame     m_currentFrame;

  std::map<int, PhFrame> m_mapSprite;

public:
  PhSprite(PhTextureManager* _pTexMan);
  ~PhSprite();
  bool SetSize(int _size);
  void SetDelay(int _delay);
  bool AddSprite(TCHAR* _filename);
  PhTexture* GetNextSprite();
  PhTexture* GetNextAdvancedSprite(int _state);
  void Init();
  bool Drawable();
  bool LoadDirectory(TCHAR* _path);
};

};

#endif