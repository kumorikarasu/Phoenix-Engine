#pragma once
#ifndef _DATAFACTORY_H_
#define _DATAFACTORY_H_

#include <map>
#include <string>
#include <png.h>
#include "PhoenixUtil.h"
#include "PhoenixIResource.h"
#include "PhoenixOpenGLHandler.h"
#include "PhoenixTexture.h"
#include "PhoenixVBO.h"
#include "PhoenixConsole.h"

namespace PhoenixCore{

  typedef unsigned char uchar;


  class DataFactory
  {
  public:
  private:
    template<typename _Key, typename _Ty> friend class Resource;

    //Yup...
    template<class _Ty>
    static _Ty* LoadData(std::wstring path) {return NULL;}
    template<> static Texture* LoadData<Texture>(std::wstring path); 
    template<> static VBO* LoadData<VBO>(std::wstring path);

    static bool loadPngImage(const wchar_t *name, int &outWidth, int &outHeight,
                             int &outBpp, bool &outHasAlpha, GLubyte **outData);

    static bool loadObjModel(const wchar_t *name, std::vector<V3>& vertex, std::vector<VI3>& indexes);
  };

  template<>
  static Texture* DataFactory::LoadData<Texture>(std::wstring path)
  {
    Texture* tex;
    TCHAR extention[10];
    ExtensionFromFilename((TCHAR*) path.c_str(), extention);

    if (wcscmp(extention, L"png") == 0){
      bool alphachan;
      tex = new Texture();
      if (!loadPngImage(path.c_str(), tex->width, tex->height, tex->bpp, alphachan, &tex->data)){
        Console::Instance()->Line(L"Texture %s", Console::C_WARNING, path.c_str());
        return NULL;
      }else{
        Console::Instance()->Line(L"Texture %s", Console::C_NORMAL, path.c_str());
      }
      return tex;
    }
    return NULL;
  }

  template<>
  static VBO* DataFactory::LoadData<VBO>(std::wstring path)
  {
    VBO* vbo;
    TCHAR extention[10];
    ExtensionFromFilename((TCHAR*) path.c_str(), extention);

    if (wcscmp(extention, L"obj") == 0){
      vbo = new VBO();
      loadObjModel(path.c_str(), vbo->vertex, vbo->faces);
      vbo->size = vbo->vertex.size();
      vbo->facesize = vbo->faces.size();
      vbo->data = (float*)&(vbo->vertex[0]);
      vbo->face = (int*)&(vbo->faces[0]);

      return vbo;
    }

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