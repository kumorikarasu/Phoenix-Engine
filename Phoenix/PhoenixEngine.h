#pragma once
#ifndef _PhEngine_H_
#define _PhEngine_H_

namespace PhoenixCore{

//do not include the header files unless you have to
class PhIRenderer;		  //PhoenixRenderer.h
class PhConsole;		    //PhoenixConsol.h
class PhTextureManager;	//PhoenixTexture.h
class PhEntityManager;  //PhoenixEntityManager.h

struct Modules{
  PhIRenderer*      pRender;
  PhConsole*        pConsole;
  PhTextureManager* pTextureMan;
  PhEntityManager*  pEntityMan;
};

//the main wrapper for the engine
class PhEngine
{
  private:
    //modules, for eas of access
    PhIRenderer*		  pRenderer;
    PhTextureManager*	pTextureMan;
    PhEntityManager*  pEntityMan;
    PhConsole*        pConsole;


    float prevmousex; float mousex;
    float prevmousey; float mousey;

    bool* input;
    long long nFrameCount;
    float fps;
    bool  RunOnce;

  public:
    PhEngine(){};
    PhEngine(Modules *Module);
    ~PhEngine();

    void Step(float _fps,bool _input[256], long mouse, long long _nFrameCount);
    void Render();
};

};


#endif
