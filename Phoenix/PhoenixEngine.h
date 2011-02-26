//Disable Conversion from Int to Float Warning
#pragma warning ( disable : 4244)

#pragma once
#ifndef _Engine_H_
#define _Engine_H_

namespace PhoenixCore{

//do not include the header files unless you have to
class IRenderer;		  //PhoenixRenderer.h
class Console;		    //PhoenixConsol.h
class TextureManager;	//PhoenixTexture.h
class EntityManager;  //PhoenixEntityManager.h

struct Modules{
  IRenderer*      pRender;
  Console*        pConsole;
  TextureManager* pTextureMan;
  EntityManager*  pEntityMan;
};

//the main wrapper for the engine
class Engine
{
  private:
    //modules, for eas of access
    IRenderer*		  pRenderer;
    TextureManager*	pTextureMan;
    EntityManager*  pEntityMan;
    Console*        pConsole;


    float prevmousex; float mousex;
    float prevmousey; float mousey;

    bool* input;
    long long nFrameCount;
    float fps;
    bool  RunOnce;

  public:
    Engine(){};
    Engine(Modules *Module);
    ~Engine();

    void Step(float _fps,bool _input[256], long mouse, long long _nFrameCount);
    void Render();
};

};


#endif
