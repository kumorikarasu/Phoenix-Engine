#pragma warning( disable : 4244) 
#pragma warning( disable : 4996) 

#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>

namespace PhoenixCore{

#ifndef _DEBUG
#ifdef _UNICODE
  typedef wchar_t TCHAR;
#define _tcslen wcslen
#define _tcscpy wcscpy
#else
#define TCHAR char
#define _tcslen strlen
#define _tcscpy strcpy
#endif
#else
#include <tchar.h>
#endif

  class Color
  {
  public:
    float r,g,b,a;

    Color(){}
    Color(float r, float g, float b, float a)
    {this->r = r; this->g=g; this->b=b; this->a=a;}
    Color(float r, float g, float b)
    {this->r = r; this->g=g; this->b=b; this->a=1;}
    Color(float a)
    {this->r = 1; this->g=1; this->b=1; this->a=a;}

  };

  class Vertex2
  {

  public:
    float x,y;
    Color c;

    Vertex2(){};
    Vertex2(int x,int y){this->x = x; this->y = y; this->c = Color(1,1,1);}
    Vertex2(int x,int y, Color& c){this->x = x; this->y = y;this->c=c;}

    //overloading operators
    Vertex2 operator+ (const Vertex2& _t){return Vertex2(x+_t.x,y+_t.y);}
    Vertex2 operator+= (const Vertex2& _t){x+=_t.y;y+=_t.y;}
  };


  class Vertex3
  {
  public:
    float x,y,z;
    Color c;

    Vertex3(){};
    Vertex3(int x,int y, int z) 
      {this->x = x; this->y = y; this->z = z;this->c = Color(1,1,1);}
    Vertex3(float x, float y, float z)
      {this->x = x; this->y = y; this->z = z;this->c = Color(1,1,1);}
    Vertex3(int x,int y, int z, Color& c)
      {this->x = x; this->y = y; this->z = z; this->c = c;}
    //Vertex3(int x,int y, Color& c){this->x = x; this->y = y;this->c=c;}

    //overloading operators
    Vertex3 operator+ (const Vertex3& _t){return Vertex3(x+_t.x,y+_t.y,z+_t.y);}
    Vertex3 operator+= (const Vertex3& _t){x+=_t.y;y+=_t.y;z+=_t.z;}
  };

  void ExtensionFromFilename(TCHAR *szFileName, TCHAR *szExtension);
  unsigned int average(unsigned int* list, size_t size);

};


#endif
