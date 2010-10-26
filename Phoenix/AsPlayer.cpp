#include "AsPlayer.h"
#include "PhoenixSprite.h"

namespace PhoenixFight{

AsPlayer::AsPlayer(PhoenixCore::PhSprite* sp)
{
  pSprite = sp;
  m_pos.x = 500;
  m_pos.y = 550;


  InputBuffer = new AsInputBuffer();
  InputBuffer->SetTable('A',DIRECTION_4);
  InputBuffer->SetTable('D',DIRECTION_6);
  InputBuffer->SetTable('W',DIRECTION_8);
  InputBuffer->SetTable('S',DIRECTION_2);
}

AsPlayer::~AsPlayer(){
  if (pSprite != NULL)
    delete pSprite;

  delete InputBuffer;
}

void AsPlayer::Step()
{
  if (m_pos.y>550)
    m_pos.y = 550;

  unsigned long input = InputBuffer->popInput();
  if (input & DIRECTION_4){
    m_pos.x-=6;
  }
  if (input & DIRECTION_6){
    m_pos.x+=6;
  }
  if (input & DIRECTION_8){
    m_pos.y-=6;
  }
  if (input & DIRECTION_2){
    m_pos.y+=6;
  }


}

void AsPlayer::Draw(PhoenixCore::PhIRenderer* pGDI)
{
  pGDI->DrawTexture2D(pSprite->GetNextSprite(),m_pos);
}


void AsPlayer::Collision(PhEntity* _pOther)
{

}

};