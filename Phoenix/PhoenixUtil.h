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
    Color(float r, float g, float b, float a){this->r = r; this->g=g; this->b=b; this->a=a;}
    Color(float r, float g, float b){this->r = r; this->g=g; this->b=b; this->a=0;}
};

class Vertex2
{

  public:
    int x,y;
    Color c;

    Vertex2(){};
    Vertex2(int x,int y){this->x = x; this->y = y;}
    Vertex2(int x,int y, Color& c){this->x = x; this->y = y;this->c=c;}

    //overloading operators
    Vertex2 operator+ (const Vertex2& _t){return Vertex2(x+_t.x,y+_t.y);}
    Vertex2 operator+= (const Vertex2& _t){x+=_t.y;y+=_t.y;}
};


class Vertex3
{

  public:
    int x,y,z;
    Color c;

    Vertex3(){};
    Vertex3(int x,int y, int z){this->x = x; this->y = y; this->z = z;}
    //Vertex3(int x,int y, Color& c){this->x = x; this->y = y;this->c=c;}

    //overloading operators
    Vertex3 operator+ (const Vertex3& _t){return Vertex3(x+_t.x,y+_t.y,z+_t.y);}
    Vertex3 operator+= (const Vertex3& _t){x+=_t.y;y+=_t.y;z+=_t.z;}
};

void ExtensionFromFilename(TCHAR *szFileName, TCHAR *szExtension);
};

#endif
