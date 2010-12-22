#include "AsPlayer.h"
#include "PhoenixSprite.h"
#include "PhoenixConsole.h"


namespace PhoenixFight{

AsPlayer::AsPlayer(PhoenixCore::PhSprite* sp)
{
  sp->SetDelay(3);
  sp->LoadDirectory(_T("..\\media\\reimu\\"));
  pSprite = sp;
  pTexture = NULL;
  m_pos.x = 500;
  m_pos.y = 350;


  State = 0;

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

  unsigned long input = InputBuffer->popInput();
  if (input & DIRECTION_4 && !down){
   // m_pos.x-=6;
    //State = 2;
    //pTexture = pSprite->GetPreviousSprite();
    pTexture = pSprite->GetNextAdvancedSprite(--State);
    down = true;
  }else
  if (input & DIRECTION_6 && !down){
   // m_pos.x+=6;
    //State = 1;
    if (input & DIRECTION_4){
     // State = 0;
    }
    //pTexture = pSprite->GetNextSprite();
    pTexture = pSprite->GetNextAdvancedSprite(++State);
    down = true;
  }
  if ((input & DIRECTION_6) != DIRECTION_6 && (input & DIRECTION_4) != DIRECTION_4)
  {
   down = false;
  }
  if (input & DIRECTION_8){
   // m_pos.y-=6;
    pTexture = pSprite->GetNextAdvancedSprite(State);
  }
  if (input & DIRECTION_2){
   // m_pos.y+=6;
    pTexture = pSprite->GetNextAdvancedSprite(State);
  }

  //TODO: HITBOX LOADING HERE THEN MAKE IT BE DRAWN IN DEBUG MODE
  //pSprite->m_currentFrame.frame[pSprite->m_nSpriteFrame].everything
  //pTexture = pSprite->GetNextAdvancedSprite(State);
}

void AsPlayer::Draw(PhoenixCore::PhIRenderer* pGDI)
{
  pGDI->DrawTexture2D(pTexture,
    PhoenixCore::Vertex2(m_pos.x + pSprite->m_currentFrame.xoffset,
                         m_pos.y + pSprite->m_currentFrame.yoffset));
}


void AsPlayer::Collision(PhEntity* _pOther)
{

}

};