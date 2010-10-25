#include "PhoenixSprite.h"

namespace PhoenixCore{

bool PhSprite::SetSize(int _size)
{
  if (m_pTextures == NULL){
    m_nSpriteLength = _size;
    return 1;
  }
  return 0;
}

PhSprite::PhSprite(PhTextureManager* _pTexMan)
{
  m_pTextureMan = _pTexMan;
  m_pTextures = NULL;
  m_pTextureStart = NULL;
  m_pTextureEnd = NULL;
  m_nSpriteLoadIndex = 0;
  m_nSpriteIndex=0;
}

bool PhSprite::AddSprite(TCHAR* _filename)
{
  if (m_pTextures == NULL){
    if (m_nSpriteLength == 0)
      return false;
    m_pTextures = (int*) malloc(m_nSpriteLength + 4);
    m_pTextureStart = m_pTextures;
  }
  if (m_nSpriteLoadIndex > m_nSpriteLength){
    return false;
  }

  (*m_pTextures) = (int) m_pTextureMan->Texture(_filename);
  m_pTextures = m_pTextures++;
  m_pTextureEnd = m_pTextures;
  m_nSpriteLoadIndex++;

  return true;
}

PhTexture* PhSprite::GetNextSprite()
{
  if (m_pTextures == NULL)
    return NULL;

  if (m_pTextures == m_pTextureEnd){
    m_pTextures = m_pTextureStart;
  }

  PhTexture* tex = (PhTexture*) (*m_pTextures);
  if (m_nSpriteIndex >= m_nDelay){
    m_nSpriteIndex = 0;
    m_pTextures++;
  }else{
    m_nSpriteIndex++;
  }

  return tex;
}

PhSprite::~PhSprite()
{
  free(m_pTextures);

}

void PhSprite::SetDelay(int _delay)
{
  m_nDelay = _delay;
}

};
