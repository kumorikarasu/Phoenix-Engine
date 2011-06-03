
#pragma once
#ifndef _VBO_H_
#define _VBO_H_

#include <map>
#include <vector>
#include <string>
#include "PhoenixIResource.h"

#define texturetype unsigned char

#define GL_STREAM_DRAW_ARB                0x88E0
#define GL_STREAM_READ_ARB                0x88E1
#define GL_STREAM_COPY_ARB                0x88E2
#define GL_STATIC_DRAW_ARB                0x88E4
#define GL_STATIC_READ_ARB                0x88E5
#define GL_STATIC_COPY_ARB                0x88E6
#define GL_DYNAMIC_DRAW_ARB               0x88E8
#define GL_DYNAMIC_READ_ARB               0x88E9
#define GL_DYNAMIC_COPY_ARB               0x88EA

namespace PhoenixCore{

  struct V3{
    float x,y,z;
  };

  struct VI3{
    int x,y,z;
  };

  class DataFactory;

  class VBO : public IResource
  {
    friend class DataFactory;

    std::vector<V3> vertex;
    std::vector<V3> texturecords;
    std::vector<VI3> faces;
    bool created;
    int size;
    int facesize;
    float* data;
    int* face;

  public:
    enum Type{
      STREAM_DRAW = 0x88E0,
      STREAM_READ,
      STREAM_COPY,
      STATIC_DRAW = 0x88E4,
      STATIC_READ,
      STATIC_COPY,
      DYNAMIC_DRAW = 0x88E8,
      DYNAMIC_READ,
      DYNAMIC_COPY
    };

    int id;
    int faceid;

    int GetResourceId(){return id;}
    int GetIndexesID(){return faceid;}
    int GetIndexesSize(){return facesize;}
    int GetSize(){return size;}
    bool HasBeenCreated(){return created;}
    void Create(){created = true;}
    float* GetData(){return data;}
    int* GetIndexes(){return face;}

    std::vector<V3> GetVertexVector(){
      return vertex;}
    VBO(){created = false;}
  };
}
#endif 