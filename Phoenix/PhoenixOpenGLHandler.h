#pragma once
#ifndef _OGL_H_
#define _OGL_H_

#include "PhoenixRenderer.h"

#include <gl\gl.h>								// Header File For The OpenGL32 Library
#include <gl\glu.h>								// Header File For The GLu32 Library

namespace PhoenixCore{

class OpenGLHandler : public IRenderer
{

  private:

    GLuint	base;				// Base Display List For The Font Set
    int oldheight,oldwidth;


  public:

    //Universal Functions
    int		CreateGameWindow(LPCWSTR title, int _width, int _height, int bits, bool fullscreenflag, int nCmdShow);
    void	ReSizeWindow(int width, int height);
    int		Init();
    void	KillWindow();
    void	CloseRenderer();
    void	BindTexture(int texture);
    void  BuildTexture(Texture* _pTexture);
    int		ClearBuffer();
    int		SwapBuffer();
    void	BuildFont(void);
    void	KillFont();
    void	Begin2D();
    void	Begin3D();
    void  UpdateSize(int height, int width);

    //Blend Modes
    void	EnableBlendMode();
    void	BlendMode(blend_mode bm);
    void	DisableBlendMode();

    //Draw Functions
    void	DrawLine(Vertex2& pos1, Vertex2& pos2);
    void	DrawTriangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3);
    void	DrawRectangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3, Vertex2& pos4);
    void  DrawCube(Vertex3& pos, float size, float rotation, Color& c);
    void	DrawTexture2D(Texture* _pTexture, Vertex2& pos);
    void	DrawText(Vertex2 _pos, const TCHAR *fmt, ...);

    void  Push2D();
    void  Pop2D();

    //Camera Functions
    virtual void CamTranslate(float x, float y, float z);
    virtual void CamRotate(float angle,float  x, float y, float z);
    virtual void CamScale(float x, float y, float z);


    OpenGLHandler(){
      hRC=NULL;
      hDC=NULL;
      hWnd=NULL;
    }

    ~OpenGLHandler();
};

};

#endif
