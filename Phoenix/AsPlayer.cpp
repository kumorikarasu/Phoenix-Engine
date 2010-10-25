#include "AsPlayer.h"
#include "PhoenixSprite.h"

namespace PhoenixFight{

AsPlayer::AsPlayer(PhoenixCore::PhSprite* sp)
{
  pSprite = sp;
  m_pos.x = 500;
  m_pos.y = 550;
}

AsPlayer::~AsPlayer(){
  if (pSprite != NULL)
    delete pSprite;
}

void AsPlayer::Step()
{
  if (m_pos.y>550)
    m_pos.y = 550;

  //InputBuffer->


}


void AsPlayer::Draw(PhoenixCore::PhIRenderer* pGDI)
{
  pGDI->DrawTexture2D(pSprite->GetNextSprite(),m_pos);
}


void AsPlayer::Collision(PhEntity* _pOther)
{

}

};