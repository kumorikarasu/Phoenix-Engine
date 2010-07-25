#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <map>
#include <string>

class PhTexture;	//PhoenixTexture.h
class PhConsole;	//PhoenixConsole.h
class PhIRenderer;	//PhoenixRenderer.h

class PhTextureManager{
  private:
    PhConsole* pConsole;
    PhIRenderer* pRenderer;

    std::map<std::string,PhTexture*> m_TextureMap;
    int	LoadTextureTGA(const std::string & _filename, PhTexture* _pTexture);

  public:

    PhTexture*	Texture(const std::string & _filename); //Will return the texture id for using a texture, will load the texture if required
    PhTextureManager(PhConsole* _pConsole, PhIRenderer* _pRenderer){
      pConsole = _pConsole;	
      pRenderer = _pRenderer;
    };
    ~PhTextureManager();
};


class PhTexture{

  friend class PhTextureManager;

  int		m_bpp;		// color depth in bytes per pixel
  int		m_width;	// image width
  int		m_height;	// image height
  int		m_type;

  unsigned int m_iRefCount;	//Refrence counter (number of times texture has been accessed

  public:

  char*				m_data;		// image data
  unsigned int		m_id;		// texture id

  PhTexture() {};
  ~PhTexture();

  int GetBpp() const { return m_bpp; }
  int GetWidth() const { return m_width; }
  int GetHeight() const { return m_height; }
  int GetTextureId() const { return m_id; }
};


#endif
