#include "CImg.h"
#include "PhoenixResource.h"



namespace PhoenixCore
{

  IRenderer* DataFactory::GD = NULL;


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
