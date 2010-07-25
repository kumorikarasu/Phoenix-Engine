#pragma once
#ifndef _PhEngine_H_
#define _PhEngine_H_

//do not include the header files unless you have to
class PhIRenderer;		//PhoenixRenderer.h
class PhConsole;		//PhoenixConsol.h
class PhTextureManager;	//PhoenixTexture.h

//the main wrapper for the engine
class PhEngine{
  private:
    PhIRenderer*		pRenderer;
    PhConsole*			pConsole;
    PhTextureManager*	pTextureMan;

    bool* input;
    long long nFrameCount;
    float fps;

  public:
    PhEngine(){};
    PhEngine(PhIRenderer* _renderer, PhConsole* _console);
    ~PhEngine();

    void Step(float _fps,bool _input[256], long long _nFrameCount);
    void Render();
};




#endif
