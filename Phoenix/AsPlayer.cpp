#include "AsPlayer.h"
#include "PhoenixSprite.h"
#include "PhoenixConsole.h"
#include "PhoenixUtil.h"


namespace PhoenixFight{

AsPlayer::AsPlayer(PhoenixCore::PhSprite* sp)
{
  sp->SetDelay(3);
  sp->LoadDirectory(_T("..\\media\\reimu\\"));
  pSprite = sp;
  pTexture = NULL;
  m_pos.x = 3;
  m_pos.y = 2;
  nPrevX = m_pos.x;
  nPrevY = m_pos.y;


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
  float accel = 0;

  if (m_pos.y>500)
    m_pos.y = 500;

  unsigned long input = InputBuffer->popInput();
  if (input & DIRECTION_4){
    m_pos.y-=0.5f;
    //State = 2;
    //pTexture = pSprite->GetPreviousSprite();
    //pTexture = pSprite->GetNextAdvancedSprite(--State);
    //down = true;
  }
  if (input & DIRECTION_6){
    m_pos.y+=0.5f;
    //State = 1;
    if (input & DIRECTION_4){
     // State = 0;
    }
    //pTexture = pSprite->GetNextSprite();
    //pTexture = pSprite->GetNextAdvancedSprite(++State);
    //down = true;
  }
  if (input & DIRECTION_8){
    accel = 0.05f;
    //pTexture = pSprite->GetNextAdvancedSprite(State);
  }else
  if (input & DIRECTION_2){
    accel = -0.05f;
    //pTexture = pSprite->GetNextAdvancedSprite(State);
  }else{
    accel = 0;
  }

  float xn = abs(2 * m_pos.x - nPrevX) + accel;
  nPrevX = m_pos.x;
  m_pos.x = xn;

  //TODO: HITBOX LOADING HERE THEN MAKE IT BE DRAWN IN DEBUG MODE
  //pSprite->m_currentFrame.frame[pSprite->m_nSpriteFrame].everything
  //pTexture = pSprite->GetNextAdvancedSprite(State);
}

void AsPlayer::Draw(PhoenixCore::PhIRenderer* pGDI)
{
  /*
  pGDI->DrawTexture2D(pTexture,
    PhoenixCore::Vertex2(m_pos.x + pSprite->m_currentFrame.xoffset,
                         m_pos.y + pSprite->m_currentFrame.yoffset));
                         */
  pGDI->DrawCube(PhoenixCore::Vertex3(this->m_pos.x,2,this->m_pos.y),1,0,PhoenixCore::Color(0,0,1));
}


void AsPlayer::Collision(PhEntity* _pOther)
{

}

};