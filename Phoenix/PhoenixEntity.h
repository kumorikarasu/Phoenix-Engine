#ifndef _PHOENIXENTITY_H_
#define _PHOENIXENTITY_H_

#include "PhoenixUtil.h"
#include "PhoenixSprite.h"
#include "PhoenixRenderer.h"

namespace PhoenixCore{

  class PhRenderObject;			//PhoenixRenderObject.h
  class PhCollisionObject;		//PhoenixCollisionManager.h
  class PhIRenderer;				//PhoenixRenderer.h
  class Vertex2;					//PhoenixUtil.h

  class PhEntity
  {

  protected:
    Vertex2				m_pos, m_accel;		//position and acceleration vectors
    bool				  m_bAutoCollide;		//Tells the engine to automatically move an object outside of a collision if it detects one
    bool          m_isDead;         //Tells the engine to remove an object on the next possible pass

    PhRenderObject*	    m_pRenderObj;		//A Pointer to a Render Object
    PhCollisionObject*	m_pColObj;			//Collision Data

    PhSprite* pSprite;     //A pointer to a Sprite Render Object (for sprites)

  public:
    static const int EntityID = 100;		//Entity ID Number
    bool isDead(){return m_isDead;}

    PhEntity(){
      m_isDead = 0;
      m_pos.x = 0;
      m_pos.y = 0;
    }

    virtual void Step() = 0;
    virtual void Draw(PhIRenderer* pGDI){
      pGDI->DrawTexture2D(pSprite->GetNextSprite(),m_pos);
    }

    //callback function
    virtual void Collision(PhEntity* _pOther) = 0;

  };
}

#endif // _PHOENIXENTITY_H_
