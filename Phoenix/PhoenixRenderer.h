
#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "PhoenixWindows.h"

namespace PhoenixCore{

class PhTexture;	//PhoenixTexture.h
class Color;		//PhoenixUtil.h
class Vertex2;		//PhoenixUtil.h
class Vertex3;    //PhoenixUtil.h

enum blend_mode{BM_ALPHA,BM_ADD,BM_SUBTRACT};

class PhIRenderer
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

  public:
    virtual int		Init() = 0;
    virtual int		CreateGameWindow(LPCWSTR title, int _width, int _height, int bits, bool fullscreenflag, int nCmdShow) = 0;
    virtual void	ReSizeWindow(int width, int height) = 0;
    virtual void	KillWindow() = 0;
    virtual void	CloseRenderer() = 0;
    virtual void	BindTexture(PhTexture* _pTexture) = 0;
    virtual int		ClearBuffer()=0;
    virtual int		SwapBuffer()=0;
    virtual void	BuildFont(void)=0;
    virtual void	KillFont()=0;
    virtual void	Begin2D()=0;
    virtual void	Begin3D()=0;


    //Blend Modes
    virtual void	EnableBlendMode()=0;
    virtual void	BlendMode(blend_mode bm)=0;
    virtual void	DisableBlendMode()=0;

    //Draw Functions
    virtual void	DrawLine(Vertex2& pos1, Vertex2& pos2)=0;
    virtual void	DrawTriangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3)=0;
    virtual void	DrawRectangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3, Vertex2& pos4)=0;
    virtual void  DrawCube(Vertex3& pos, float size, float rotation)=0;
    virtual void	DrawText(Vertex2 _pos, const char *fmt, ...)=0;
    virtual void	DrawTexture2D(PhTexture* _pTexture, Vertex2& pos) = 0;



    //Getters
    int getWidth(){return width;}
    int getHeight(){return height;}

};

};
#endif
