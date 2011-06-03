#ifndef _PHOENIXRESOURCE_H_
#define _PHOENIXRESOURCE_H_


#include <map>
#include <string>

namespace PhoenixCore
{
  class IRenderer;

  template<typename _Key, typename _Ty>
  class Resource
  {
  public:
    ~Resource();

    template<typename _Dy> _Dy* Aquire(_Key key);
    template<typename _Dy> _Dy* Aquire(_Key key, std::wstring path);

    void AssignRenderer(IRenderer* GD);

  private:
    typedef std::map<_Key, _Ty*> storageType;
    storageType resources;

    _Ty* Load(std::wstring path);
  };
}

#endif