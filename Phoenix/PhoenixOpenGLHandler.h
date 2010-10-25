#pragma once
#ifndef _OGL_H_
#define _OGL_H_

#include "PhoenixRenderer.h"

#include <gl\gl.h>								// Header File For The OpenGL32 Library
#include <gl\glu.h>								// Header File For The GLu32 Library

namespace PhoenixCore{

class PhOpenGLHandler : public PhIRenderer
{

  private:

    GLuint	base;				// Base Display List For The Font Set

  public:

    //Universal Functions
    int		CreateGameWindow(LPCWSTR title, int _width, int _height, int bits, bool fullscreenflag, int nCmdShow);
    void	ReSizeWindow(int width, int height);
    int		Init();
    void	KillWindow();
    void	CloseRenderer();
    void	BindTexture(PhTexture* _pTexture);
    int		ClearBuffer();
    int		SwapBuffer();
    void	BuildFont(void);
    void	KillFont();
    void	Begin2D();
    void	Begin3D();

    //Blend Modes
    void	EnableBlendMode();
    void	BlendMode(blend_mode bm);
    void	DisableBlendMode();

    //Draw Functions
    void	DrawLine(Vertex2& pos1, Vertex2& pos2);
    void	DrawTriangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3);
    void	DrawRectangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3, Vertex2& pos4);
    void  DrawCube(Vertex3& pos, float size, float rotation);
    void	DrawTexture2D(PhTexture* _pTexture, Vertex2& pos);
    void	DrawText(Vertex2 _pos, const TCHAR *fmt, ...);


    //functions that need to be filled in yet
    void	Draw3DCube(Vertex2/*3*/& pos1);


    PhOpenGLHandler(){
      hRC=NULL;
      hDC=NULL;
      hWnd=NULL;
    }

    ~PhOpenGLHandler();
};

};

#endif
