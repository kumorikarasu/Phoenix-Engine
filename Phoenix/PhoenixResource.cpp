#include "PhoenixResource.h"
#include "CImg.h"
#include "PhoenixOpenGLHandler.h"
#include "PhoenixTexture.h"

#include <gl\gl.h>								// Header File For The OpenGL32 Library
#include <gl\glu.h>								// Header File For The GLu32 Library

using namespace cimg_library;

namespace PhoenixCore
{

  template<>
  static Texture* DataFactory::LoadData<Texture>(std::string path)
  {
    Texture tex = new Texture();
    CImg<float> image = CImg<float>(path.c_str());
    tex.width = image.width();
    tex.height = image.height();
    tex.bpp = image.depth();

    int texture;
    ::glGenTextures(1,&texture); //create a new image in OGL

    tex.id = texture;
    
    ::glBindTexture(GL_TEXTURE_2D,texture);
    ::glTexEnvf( GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    //linear filtering
    ::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    ::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //wrap edges
    ::glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    ::glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    ::gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.width(), image.height(), GL_RGBA, GL_FLOAT, image.rg);

    return NULL;
  }

  template<>
  static VBO* DataFactory::LoadData<VBO>(std::string path)
  {

    return NULL;
  }

  ///if we know its already loaded
  template<typename _Key, typename _Ty>
  template<typename _Dy>
  _Dy* Resource<_Key,_Ty>::Aquire(_Key key)
  {
    _Dy* obj = static_cast<_Dy*>(std::map<_Key, _Ty*>::iterator it = storageType.find(key) -> second);
    return obj;
  }


  /*
  ///if we are unsure if it is loaded or not
  template<typename _Key, typename _Ty>
  template<typename _Dy>
  _Dy* Resource<_Key,_Ty>::Aquire(_Key key, std::string path)
  {
    ///is it here already
    _Dy* obj = static_cast<_Dy*>std::map<_Key, _Ty*>::iterator it = storageType.find(key) -> second;
    if (obj != NULL)
      return obj;

    ///load the resource...
    obj = LoadResource(path);
  };

  template<typename _Key, typename _Ty>
  _Ty* Resource<_Key,_Ty>::LoadResource(std::string path)
  {
    if (str.compare("png") || str.compare("jpg") || str.compare("gif") || str.compare("tga") || str.compare("bmp")) {
      return DataFactory::LoadData<Texture>(path);
    }
  }

  /*
  {
  std::string str = path.substr(path.find_last_of("."));
  if (str.compare("png") || str.compare("jpg") || str.compare("gif") || str.compare("tga") || str.compare("bmp"))
  {
  LoadResource<Texture>(key);
  }
  }

  template<> void* Resource::LoadResource<Texture>(std::string path)
  {
  return NULL;
  }
  */

};
