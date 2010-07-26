#ifndef _PHOENIXENTITY_H_
#define _PHOENIXENTITY_H_

namespace PhoenixCore{

  class PhRenderObject;			//PhoenixRenderObject.h
  class PhCollisionObject;		//PhoenixCollisionManager.h
  class PhIRenderer;				//PhoenixRenderer.h
  class Vertex2;					//PhoenixUtil.h

  class PhEntity
  {

  public:
    const int			EntityID = 000;		//Entity ID Number

  private:
    Vertex2				m_pos,m_accel;		//position and acceleration vectors
    bool				  m_bAutoCollide;		//Tells the engine to automatically move an object outside of a collision if it detects one

    PhRenderObject*	 m_pRenderObj;		//A Pointer to a Render Object
    PhCollisionObject*	m_pColObj;			//Collision Data


  public:
    PhEntity(){}
    ~PhEntity(){}

    virtual void Step();
    virtual void Draw(PhIRenderer* pGDI);

    //callback function
    virtual void Collision(PhEntity* _pOther);

  };
}

#endif // _PHOENIXENTITY_H_
