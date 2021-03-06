
#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "PhoenixWindows.h"

namespace PhoenixCore{

class Texture;	//PhoenixTexture.h
class VBO;
#define texturetype unsigned char

class Color;		//PhoenixUtil.h
class Vertex2;		//PhoenixUtil.h
class Vertex3;    //PhoenixUtil.h

enum blend_mode{BM_ALPHA,BM_ADD,BM_SUBTRACT};

class IRenderer
{
  protected:

#ifdef WIN
    HGLRC           hRC;						// Permanent Rendering Context
    HDC             hDC;						// Private GDI Device Context
    HWND            hWnd;						// Holds Our Window Handle
    HINSTANCE       hInstance;					// Holds The Instance Of The Application
#endif

    bool bFullScreen;
    int width,height;
    int RenderMode;

  public:
    virtual int		Init() = 0;
    virtual int		CreateGameWindow(LPCWSTR title, int _width, int _height, int bits, bool fullscreenflag, int nCmdShow) = 0;
    virtual void	ReSizeWindow(int width, int height) = 0;
    virtual void	KillWindow() = 0;
    virtual void	CloseRenderer() = 0;
    virtual void	BindTexture(int texture) = 0;
    virtual void  BuildTexture(Texture* _pTexture) = 0;
    virtual int		ClearBuffer()=0;
    virtual int		SwapBuffer()=0;
    virtual void	BuildFont(void)=0;
    virtual void	KillFont()=0;
    virtual void	Begin2D()=0;
    virtual void	Begin3D()=0;
    virtual void  UpdateSize(int height, int width)=0;


    //Blend Modes
    virtual void	EnableBlendMode()=0;
    virtual void	BlendMode(blend_mode bm)=0;
    virtual void	DisableBlendMode()=0;

    //Draw Functions
    virtual void	DrawLine(Vertex2& pos1, Vertex2& pos2)=0;
    virtual void	DrawTriangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3)=0;
    virtual void	DrawRectangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3, Vertex2& pos4)=0;
    virtual void  DrawCube(Vertex3& pos, float size, float rotation, Color& c) = 0;
    virtual void	DrawText(Vertex2 _pos, const TCHAR *fmt, ...)=0;
    virtual void	DrawTexture2D(Texture* _pTexture, Vertex2& pos) = 0;
    virtual void  BeginTexture(Texture* _pTexture)=0;
    virtual void  EndTexture()=0;

    virtual void  Push2D()=0;
    virtual void  Pop2D()=0;

    //Camera Functions
    virtual void CamTranslate(float x, float y, float z) = 0;
    virtual void CamRotate(float angle, float x, float y, float z) = 0;
    virtual void CamScale(float x, float y, float z) = 0;

    //VBO
    virtual bool BuildVBO(VBO* vbo, int Type) = 0;
    virtual void DrawVBO(VBO* vbo, Vertex3 pos) = 0;

    //Getters
    int getWidth(){return width;}
    int getHeight(){return height;}

};

};
#endif
