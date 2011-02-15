#ifndef _PHOENIXENTITY_H_
#define _PHOENIXENTITY_H_

#include "PhoenixUtil.h"
#include "PhoenixSprite.h"
#include "PhoenixRenderer.h"

#include <list>

namespace PhoenixCore
{
  class Vertex2;					//PhoenixUtil.h

  //The Components
  //Mandatory
  class PhVisual;
  class PhCollision;

  //Game Specific
  class AsFrameData;
  class AsAttackData;

  //The Controller
  class PhController;

  class PhEntity
  {

  private:
    Vertex2				pos, m_accel;		//position and acceleration vectors
    bool				  bAutoCollide;		//Tells the engine to automatically move an object outside of a collision if it detects one
    bool          Dead;         //Tells the engine to remove an object on the next possible pass

    AsFrameData*        pFrameData;
    AsAttackData*       pAttackData;
    PhVisual*           pVisual;
    PhCollision*        pCollision;

    std::list<PhController*> Controllers;

    PhTexture* pTexture;
    PhSprite* pSprite;     //A pointer to a Sprite Render Object (for sprites)

  public:
    bool isDead(){return Dead;}
    bool isDrawable(){return pSprite != NULL ? pSprite->Drawable() : false;}

    PhEntity();
    ~PhEntity();

    //callback function
    void (*Collision)(PhEntity* _pOther);
  };
}

#endif // _PHOENIXENTITY_H_
