#include "AsPlayer.h"
#include "PhoenixSprite.h"
#include "PhoenixConsole.h"


namespace PhoenixFight{

AsPlayer::AsPlayer(PhoenixCore::PhSprite* sp)
{
  pSprite = sp;
  sp->SetDelay(3);
  pTexture = NULL;
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
  if (m_pos.y>500)
    m_pos.y = 500;

  State = 0;
  unsigned long input = InputBuffer->popInput();
  if (input & DIRECTION_4){
    m_pos.x-=6;
    State = 2;
  }
  if (input & DIRECTION_6){
    m_pos.x+=6;
    State = 1;
    if (input & DIRECTION_4){
      State = 0;
    }
  }
  if (input & DIRECTION_8){
    m_pos.y-=6;
  }
  if (input & DIRECTION_2){
    m_pos.y+=6;
  }

  //pTexture = pSprite->GetNextAdvancedSprite(State);
  pTexture = pSprite->GetNextSprite();
}

void AsPlayer::Draw(PhoenixCore::PhIRenderer* pGDI)
{
  pGDI->DrawTexture2D(pTexture,m_pos);
}


void AsPlayer::Collision(PhEntity* _pOther)
{

}

};