#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <map>
#include <string>
#include "TextureLoader.h"

namespace PhoenixCore{

  class PhTexture;	//PhoenixTexture.h
  class Console;	//PhoenixConsole.h
  class IRenderer;	//PhoenixRenderer.h

  class TextureManager
  {
  private:
    IRenderer* pRenderer;

    TextureLoader* TL;

    std::map<std::wstring, PhTexture*> m_TextureMap;


  public:

    TextureManager(Console* _pConsole, IRenderer* _pRenderer);
    ~TextureManager();

    PhTexture* Texture(TCHAR *_filename);

  };

  class PhTexture
  {

    friend class TextureManager;

    int	m_width;							// Image Width
    int	m_height;							// Image Height
    int	m_type;								// Image Type (GL_RGB, GL_RGBA)
    int	m_bpp;								// Image Color Depth In Bits Per Pixel

    // Refrence counter (number of times texture has been accessed
    unsigned int m_iRefCount;	

  public:

    //has to be public cause of how OGL access it
    unsigned int		m_id;		// texture id
    eglTexType	m_texType;	// Texture Format

    PhTexture() {};
    ~PhTexture() {};

    int GetBpp() const { return m_bpp; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    int GetTextureId() const { return m_id; }
  };

};

#endif