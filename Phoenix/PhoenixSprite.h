#ifndef _PHOENIXSPRITE_H_
#define _PHOENIXSPRITE_H_
#include <tchar.h>
#include <map>
#include "PhoenixTexture.h"

namespace PhoenixCore{

  /*
class Sprite
{
private:

  struct PhFrame{
    int xMovement;
    int yMovement;
    int hbtl;
    int hbtr;
    int hbbl;
    int hbbr;
    int ahbtl;
    int ahbtr;
    int ahbbl;
    int ahbbr;
    int Flags;
  };

  struct PhAnimation{
    int nStartFrame;
    int nFrames;
    int xoffset;
    int yoffset;
    int delay;
    PhFrame frame[300];
  };


  TextureManager* m_pTextureMan;
  int*        m_pTextures;
  int*        m_pTextureStart;
  int*        m_pTextureEnd;
  int         m_nDelay;
  int         m_nSpriteIndex;
  int         m_nSpriteLength;
  int         m_nSpriteLoadIndex;
  int         m_nSpriteFrame; // Current frame that is displayed noscreen
  bool        Corrupt;
  int         m_nState;       // Current frame state, used when switching states

  std::map<int, PhAnimation> m_mapSprite;

public:
  PhAnimation     m_currentFrame;

  Sprite(TextureManager* _pTexMan);
  ~Sprite();
  bool SetSize(int _size);
  void SetDelay(int _delay);
  bool AddSprite(TCHAR* _filename);
  PhTexture* GetPreviousSprite();
  PhTexture* GetNextSprite();
  PhTexture* GetNextAdvancedSprite(int _state);
  void Init();
  bool Drawable();
  bool LoadDirectory(TCHAR* _path);

};
i*/
};

#endif