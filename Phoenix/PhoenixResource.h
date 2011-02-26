
#ifndef _PHOENIXRESOURCE_H_
#define _PHOENIXRESOURCE_H_

#include <map>

namespace PhoenixCore
{
  class Resource
  {
  private:
    typedef std::map<std::string , void*> storageType;

    int Load(void* Data);




  };
}

#endif