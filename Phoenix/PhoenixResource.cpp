#include "PhoenixResource.h"
#include "PhoenixDataFactory.h"
#include "PhoenixUtil.h"

namespace PhoenixCore{

  template<typename _Key, typename _Ty>
  void Resource<_Key,_Ty>::AssignRenderer(IRenderer* GD){
    DataFactory::GD = GD;
  }

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
  _Dy* Resource<_Key,_Ty>::Aquire(_Key key, std::wstring path)
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
  _Ty* Resource<_Key,_Ty>::Load(std::wstring path)
  {
    std::wstring str = path.substr(path.find_last_of('.') + 1);
    if (str.compare(L"png") == 0) {
      return DataFactory::LoadData<Texture<texturetype>>(path);
    }
    if (str.compare(L"obj") == 0){
      return DataFactory::LoadData<VBO>(path);
    }
    return NULL;
  }

  template<typename _Key, typename _Ty>
  Resource<_Key,_Ty>::~Resource()
  {
    storageType::iterator it;
    it = resources.begin();
    for(; it != resources.end(); ++it){
      delete (*it).second;
    }
  }

}