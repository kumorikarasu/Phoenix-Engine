#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <map>
#include <string>
#include "PhoenixIResource.h"
namespace PhoenixCore{

  class DataFactory;

  class Texture : public IResource
  {
    friend class DataFactory;
    friend class OpenGLHandler;
    
    int	width;							// Image Width
    int	height;							// Image Height
    int	type;								// Image Type (GL_RGB, GL_RGBA)
    int	bpp;								// Image Color Depth In Bits Per Pixel

    unsigned int		id;		// texture id
    bool            bound;

    // Refrence counter (number of times texture has been accessed
    unsigned int refCount;	
    unsigned char* data;


  public:

    //has to be public cause of how OGL access it

    Texture() {
      bound = false;
    };

    ~Texture() {
      if (data != NULL)
        delete data;
    };

    int GetBpp() const { return bpp; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetResourceId() const { return id; }
    unsigned char* GetData() const { return data; }
    bool isBound() const { return bound; }
  };
};

#endif