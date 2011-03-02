
#ifndef _PHOENIXRESOURCE_H_
#define _PHOENIXRESOURCE_H_

#include "CImg.h"

#include <map>
#include <string>
#include "PhoenixIResource.h"
#include "PhoenixOpenGLHandler.h"
#include "PhoenixTexture.h"

using namespace cimg_library;

namespace PhoenixCore
{

  class VBO;
  
  class DataFactory
  {
  public:
    static IRenderer* GD;

  private:
    template<typename _Key, typename _Ty> friend class Resource;

    //Yup...
    template<class _Ty>
    static _Ty* LoadData(std::string path) {return NULL;}
    template<> static Texture* LoadData<Texture>(std::string path); 
    template<> static VBO* LoadData<VBO>(std::string path);
  };


  template<typename _Key, typename _Ty>
  class Resource
  {
  private:
    typedef std::map<_Key, _Ty*> storageType;
    storageType resources;

    _Ty* Load(std::string path);

  public:

    template<typename _Dy> _Dy* Aquire(_Key key);
    template<typename _Dy> _Dy* Aquire(_Key key, std::string path);
  };



  ///if we know its already loaded
  template<typename _Key, typename _Ty>
  template<typename _Dy>
  _Dy* Resource<_Key,_Ty>::Aquire(_Key key)
  {
    return NULL;
  }


  
  ///if we are unsure if it is loaded or not
  template<typename _Key, typename _Ty>
  template<typename _Dy>
  _Dy* Resource<_Key,_Ty>::Aquire(_Key key, std::string path)
  {
    ///is it here already
    _Dy* obj;
    storageType::iterator it;
    it = resources.find(key);
    for (it = resources.begin(); it != resources.end(); ++it) {
      if (it->first == key) {
        obj = static_cast<_Dy*> (it -> second);
        return obj;
      }
    }

    ///load the resource...
    obj = static_cast<_Dy*>(Load(path));
    resources[key] = obj;
    return obj;
  };

  template<typename _Key, typename _Ty>
  _Ty* Resource<_Key,_Ty>::Load(std::string path)
  {
    std::string str = path.substr(path.find_last_of('.'));
    if (str.compare("png") || str.compare("jpg") || str.compare("gif") || str.compare("tga") || str.compare("bmp")) {
      return DataFactory::LoadData<Texture>(path);
    }
  }

  template<>
  static Texture* DataFactory::LoadData<Texture>(std::string path)
  {
    Texture* tex = new Texture();
    CImg<float> image = CImg<float>(path.c_str());
    tex->width = image.width();
    tex->height = image.height();
    tex->bpp = image.spectrum();
    tex->data = image.data();

    int sizeperblock = (tex->width * tex->height / tex->bpp);
    float* dat = (float*)malloc(sizeof(float) * tex->width * tex->height);
    float* sdat = dat;
    if (tex->bpp == 3)
      for(int x = 0;x < sizeperblock; x++){
        *dat++ = *(tex->data + x);
        *dat++ = *(tex->data + sizeperblock + x);
        *dat++ = *(tex->data + sizeperblock * 2 + x);
      }
    else{
      for(int x = 0;x < sizeperblock; x++){
        *dat++ = *(tex->data + x);
        *dat++ = *(tex->data + sizeperblock + x);
        *dat++ = *(tex->data + sizeperblock * 2 + x);
        *dat++ = *(tex->data + sizeperblock * 3 + x);
      }
    }

    tex->data = sdat;
    GD->BuildTexture(tex);

    free(sdat);
    return tex;
  }

  template<>
  static VBO* DataFactory::LoadData<VBO>(std::string path)
  {

    return NULL;
  }
  /*
  template<typename _Ty>
  class Resource<std::string, _Ty>
  {
  private:
    typedef std::string _Key;
    typedef std::map<_Key, _Ty*> storageType;

  public:

    ///if we know its already loaded
    template<class _Dy>
    _Ty* Aquire(_Key key)
    {
      _Ty* obj = std::map<_Key, _Ty*>::iterator it = storageType.find(key) -> second;
      if (obj != NULL){
        ///static polymorphism
        _Dy* val = static_cast<_Dy*> obj;
        return val;
      }

      ///load the resource otherwise
      LoadResource(key)
    };

    ///if we are unsure if it is loaded or not
    _Ty* Aquire(_Key key, std::string path)
    {
      return Aquire(key);
    };
  };
  i*/

}



#endif