#pragma once
#ifndef _PhEngine_H_
#define _PhEngine_H_

namespace PhoenixCore{

//do not include the header files unless you have to
class PhIRenderer;		//PhoenixRenderer.h
class PhConsole;		//PhoenixConsol.h
class PhTextureManager;	//PhoenixTexture.h

struct Modules{
  PhIRenderer*      pRender;
  PhConsole*        pConsole;
  PhTextureManager* pTextureMan;
};

//the main wrapper for the engine
class PhEngine
{
  private:
    PhIRenderer*		pRenderer;
    PhConsole*			pConsole;
    PhTextureManager*	pTextureMan;

    bool* input;
    long long nFrameCount;
    float fps;

  public:
    PhEngine(){};
    PhEngine(Modules Module);
    ~PhEngine();

    void Step(float _fps,bool _input[256], long long _nFrameCount);
    void Render();
};

};


#endif
