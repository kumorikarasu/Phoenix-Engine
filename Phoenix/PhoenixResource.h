#ifndef _PHOENIXRESOURCE_H_
#define _PHOENIXRESOURCE_H_


#include <map>
#include <string>

namespace PhoenixCore
{
  class IRenderer;
  class DataFactory;

  template<typename _Key, typename _Ty>
  class Resource
  {
  public:
    ~Resource();

    template<typename _Dy> _Dy* Aquire(_Key key, std::wstring path);
    template<typename _Dy> _Dy* Aquire(_Key key);

    template<typename _Dy> _Dy* Add(_Key key, _Ty* obj);

    void AssignDataFactory(DataFactory* DF);

  private:
    typedef std::map<_Key, _Ty*> storageType;
    storageType resources;

    _Ty* Load(std::wstring path);
	DataFactory* DF;
  };

  template<typename _Key, typename _Ty>
  void Resource<_Key,_Ty>::AssignDataFactory(DataFactory* DF){
	  this->DF = DF;
  }

  ///if we know its already loaded
  template<typename _Key, typename _Ty>
  template<typename _Dy>
  _Dy* Resource<_Key,_Ty>::Aquire(_Key key)
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

    return NULL;
  }

  ///Adds the object to the collection
  template<typename _Key, typename _Ty>
  template<typename _Dy>
  _Dy* Resource<_Key, _Ty>::Add(_Key key, _Ty* obj){
    _Ty* o = Aquire<_Ty>(key);
    if (o == NULL) resources[key] = obj;
    return static_cast<_Dy*> (obj);
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
      return DF->LoadData<Texture>(path);
    }
    if (str.compare(L"obj") == 0){
      return DF->LoadData<VBO>(path);
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

#endif