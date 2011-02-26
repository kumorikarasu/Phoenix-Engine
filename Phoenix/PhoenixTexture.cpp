#include "PhoenixGlobal.h"
#include "PhoenixTexture.h"
#include "PhoenixConsole.h"
#include "PhoenixRenderer.h"
#include <tchar.h>
#include <atlconv.h>

using namespace std;
namespace PhoenixCore{

// checks if the texture has be loaded already, if it has,
// it returns it, otherwise it attempts to load it
PhTexture* TextureManager::Texture(TCHAR* _filename)
{

  //the texture pointer we will return
  PhTexture* pTexture = NULL;

  // check if the texture already exists in the map
  map<wstring,PhTexture*>::iterator p = m_TextureMap.find(wstring(_filename));

  if( p != m_TextureMap.end() )
  {
    // found the texture, now return the reference
    pTexture = p->second;
    //pTexture->m_iRefCount++;

    return pTexture;
  }

  // if texture doesn't exist in the map, load it into memory
  pTexture = new PhTexture();

  // create another function to determine what type of texture it is,
  // currently just support uncompressed TGA
  glTexture tex;
  if (! TL->LoadTextureFromDisk(_filename,&tex)){
    Console::Line(_T("Unable to load %s"),C_ERROR,_filename);
    TL->FreeTexture(&tex);
    delete pTexture;
    pTexture = NULL;
  }else{
    pTexture->m_bpp = tex.Bpp;
    pTexture->m_height = tex.Height;
    pTexture->m_id = tex.TextureID;
    pTexture->m_type = tex.Type;
    pTexture->m_texType = tex.TexType;
    pTexture->m_width = tex.Width;
  }

  //add texture to map
  m_TextureMap[_filename] = pTexture;

  //load the texture into video memory
  pRenderer->BuildTexture(pTexture);

  //return the texture pointer
  return pTexture;

}

TextureManager::~TextureManager()
{

  //delete all textures that have been loaded
  map<wstring,PhTexture*>::iterator iter = m_TextureMap.begin();
  glTexture tex;

  while(iter != m_TextureMap.end()){
    if (iter->second != NULL){
      tex.Bpp = iter->second->GetBpp();
      tex.Height = iter->second->GetHeight();
      tex.TextureID = iter->second->GetTextureId();
      tex.TexType = iter->second->m_texType;
      tex.Type = iter->second->m_type;
      tex.Width = iter->second->GetWidth();
      TL->FreeTexture(&tex);
    }
    iter++;
  }

  //clear the array
  this->m_TextureMap.empty();
  delete TL;
}

TextureManager::TextureManager(Console* _pConsole, IRenderer* _pRenderer)
{
  pRenderer = _pRenderer;

  TL = new TextureLoader();
  TL->SetAlphaMatch(true,0,120,136);
  TL->SetHighQualityTextures(true);
}

};