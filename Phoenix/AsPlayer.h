#ifndef _ASPLAYER_H_
#define _ASPLAYER_H_

#include "AsProperties.h"
#include "PhoenixEntity.h"

namespace PhoenixFight{

  class AsPlayer: public PhoenixCore::PhEntity
  {
  private:
    sCharacterProp* m_pProp;
    AsInputBuffer   InputBuffer;

    virtual void Step();
    virtual void Draw(PhoenixCore::PhIRenderer* pGDI);

    //callback function
    virtual void Collision(PhEntity* _pOther);
  };

} /*PhoenixFlight*/

#endif /*_ASPLAYER_H_*/