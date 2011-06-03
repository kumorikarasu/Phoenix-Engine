#ifndef _PHOENIXIRESOURCE_H_
#define _PHOENIXIRESOURCE_H_

namespace PhoenixCore
{
  class IResource
  {
  public:
    virtual int GetResourceId() const { return 0; }
  };
}


#endif
