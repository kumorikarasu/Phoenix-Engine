
#ifndef _HITBOXVIEWER_H_
#define _HITBOXVIEWER_H_

#include "AsProperties.h"
#include "AsInputBuffer.h"
#include "PhoenixEntity.h"

namespace PhoenixFight{

  class AsHitBoxViewer: public PhoenixCore::PhEntity
  {
  private:
    //sCharacterProp* m_pProp;
    int State;
    PhoenixCore::Vertex2 hbtl, hbbr; //hitbox
    PhoenixCore::Vertex2 ahbt1, ahbbr; //current attacks hitbox
    int nGravity;

  public:
    AsInputBuffer*  InputBuffer;
    static const int EntityID = 101;
    bool down;
    AsHitBoxViewer(PhoenixCore::PhSprite* sp);
    ~AsHitBoxViewer();

    virtual void Step();
    virtual void Draw(PhoenixCore::PhIRenderer* pGDI);

    //callback function
    virtual void Collision(PhEntity* _pOther);

  };

} /*PhoenixFlight*/

#endif /*_HITBOXVIEWER_H_*/