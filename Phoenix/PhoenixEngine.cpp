#include "PhoenixGlobal.h"
#include "PhoenixRenderer.h"
#include "PhoenixTexture.h"
#include "PhoenixEngine.h"
#include "PhoenixUtil.h"
#include "PhoenixConsole.h"
#include "PhoenixEntityManager.h"
#include "PhoenixSprite.h"
#include "AsPlayer.h"
#include <tchar.h>

using namespace PhoenixFight;
namespace PhoenixCore{

float r = 0;
AsPlayer* Player;

//everything!
void PhEngine::Step(float _fps,bool _input[256], long long _nFrameCount)
{

  if (RunOnce){

    PhSprite* sp = new PhSprite(pTextureMan);
    Player = new AsPlayer(sp);

    pEntityMan->AddEntity(Player); //add entity to game

    sp->SetSize(10);
    sp->SetDelay(60);
    sp->Init();
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand000 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand001 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand002 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand003 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand004 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand005 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand006 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand007 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand008 .tga"));
    sp->AddSprite(_T("..\\media\\reimu\\data_character_reimu_stand009 .tga"));

    RunOnce = false;
  }

  fps = _fps;
  input = _input;
  nFrameCount = _nFrameCount;

  //Console toggle
  if (input[192]){
    if (! pConsole->getToggle()){
      pConsole->On();
    } else
      pConsole->Off();

    input[192] = false;
  }

  pEntityMan->Run();
}


//go throught the list of objects that need to be rendered and render them
void PhEngine::Render()
{
  pRenderer->ClearBuffer(); //clear the screen

  pRenderer->EnableBlendMode();
  pRenderer->BlendMode(BM_ALPHA);

  //pRenderer->Begin3D();
  //pRenderer->DrawCube(Vertex3(0,0,-8),r,10);
  //r+=0.15f;

//  pRenderer->Begin2D();

  pRenderer->DrawText(Vertex2(10,20,Color(0,1,0)),_T("RenderTime: %4.2f: Frame Number: %d"),fps,nFrameCount);
  //DRAW FRAME TIME
//  pRenderer->DrawText(Vertex2(10,20,Color(0,1,0)),"RenderTime: %4.2f: Frame Number: %d",fps,nFrameCount);



  //DRAW SPRITES
  pEntityMan->Draw(pRenderer);

  //TEST


  //3D
  //pRenderer->DrawTriangle(Vertex2(0,1,Color(1.0f,1.0f,0.0f)),
  //						Vertex2(-1,-1,Color(1.0f,1.0f,0.0f)),
  //						Vertex2(1,-1,Color(1.0f,1.0f,0.0f)));

  //2D (no Z buffer)
  //	for (int i=0; i < 200000; i++)
  //	pRenderer->DrawTriangle(Vertex2(i,100,Color(.0f,1.0f,0.0f)),
  //							Vertex2(200+i,200+fps,Color(1.0f,0.0f,0.0f)),
  //							Vertex2(100+i,0,Color(0.0f,0.0f,1.0f)));


  if (input[32]){
    pRenderer->DrawRectangle(Vertex2(10,10,Color(0.5f,0.5f,0.5f,0.5f)),
                             Vertex2(110,10,Color(0.5f,0.5f,0.5f,0.5f)),
                             Vertex2(110,110,Color(0.5f,0.5f,0.5f,0.5f)),
                             Vertex2(10,110,Color(0.5f,0.5f,0.5f,0.5f)));

  }
  pRenderer->DrawLine(Vertex2(0,600,Color(0.0f,1.0f,0.0f)),
                      Vertex2(1280,600,Color(1.0f,1.0f,0.0f))
                      );

//  pRenderer->DrawTexture2D(sp->GetNextSprite(),Vertex2(640,360));
  pRenderer->DrawTexture2D(pTextureMan->Texture(_T("data\\textures\\Kumori.tga")),Vertex2(200 + nFrameCount % 60,200));

 // pRenderer->DrawTexture2D(pTextureMan->Texture("icephoenix.tga"),Vertex2(150,100));


  //END TEST


  //DRAW CONSOLE
  pConsole->Draw(pRenderer);

  pRenderer->DisableBlendMode();
  pRenderer->SwapBuffer(); //update buffers
}


//constructor
PhEngine::PhEngine(Modules &Module)
{
  pConsole = Module.pConsole;
  pRenderer = Module.pRender;
  pTextureMan = Module.pTextureMan;
  pEntityMan = Module.pEntityMan;

  fps = 0;

  pTextureMan = new PhTextureManager(pConsole,pRenderer);
  pEntityMan = new PhEntityManager();

  RunOnce = true;
}

//destructor
PhEngine::~PhEngine()
{
  delete pTextureMan;
}

};