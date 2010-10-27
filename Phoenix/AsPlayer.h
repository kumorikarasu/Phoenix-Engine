#ifndef _ASPLAYER_H_
#define _ASPLAYER_H_

#include "AsProperties.h"
#include "AsInputBuffer.h"
#include "PhoenixEntity.h"

namespace PhoenixFight{

  enum state{
    sNormal,
    sBlocking,
    sHit,
    sStun,
    sCrushed
  };

  class AsPlayer: public PhoenixCore::PhEntity
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
    AsPlayer(PhoenixCore::PhSprite* sp);
    ~AsPlayer();

    virtual void Step();
    virtual void Draw(PhoenixCore::PhIRenderer* pGDI);

    //callback function
    virtual void Collision(PhEntity* _pOther);

  };

} /*PhoenixFlight*/

#endif /*_ASPLAYER_H_*/