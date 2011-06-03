
#include "PhoenixResource.cpp"
#include "PhoenixDataFactory.h"

namespace PhoenixCore{
  //Templates are gay....
  Resource<std::string, IResource> inclusion;
  void Create(){ 
    //This function is never actuall ran, its here for the linker to
    //find the template functions
    inclusion.Aquire<Texture<texturetype>>(NULL, NULL);
    inclusion.Aquire<VBO>(NULL, NULL);
    inclusion.AssignRenderer(NULL);
  }
}