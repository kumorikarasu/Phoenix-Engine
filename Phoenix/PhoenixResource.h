
#ifndef _PHOENIXRESOURCE_H_
#define _PHOENIXRESOURCE_H_

#include <map>

namespace PhoenixCore
{

  class IResource;
  class Texture;
  class VBO;
  
  class DataFactory
  {
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
    _Ty* LoadResource(std::string path);

  public:

    template<typename _Dy> _Dy* Aquire(_Key key);
    template<typename _Dy> _Dy* Aquire(_Key key, std::string path);
  };

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
      LoadResource(key);
    };

    ///if we are unsure if it is loaded or not
    _Ty* Aquire(_Key key, std::string path)
    {
      return AquireResource(key);
    };
  };


}



#endif