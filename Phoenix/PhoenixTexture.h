#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <map>
#include <string>
#include "TextureLoader.h"

namespace PhoenixCore{

  class DataFactory;

  class Texture
  {
    friend class DataFactory;
    
    int	width;							// Image Width
    int	height;							// Image Height
    int	type;								// Image Type (GL_RGB, GL_RGBA)
    int	bpp;								// Image Color Depth In Bits Per Pixel

    // Refrence counter (number of times texture has been accessed
    unsigned int refCount;	

  public:

    //has to be public cause of how OGL access it
    unsigned int		id;		// texture id

    Texture() {};
    ~Texture() {};

    int GetBpp() const { return bpp; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetTextureId() const { return id; }
  };
};

#endif