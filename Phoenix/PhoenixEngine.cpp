#include "PhoenixGlobal.h"
#include "PhoenixRenderer.h"
#include "PhoenixTexture.h"
#include "PhoenixEngine.h"
#include "PhoenixUtil.h"
#include "PhoenixConsole.h"

//everything!
void PhEngine::Step(float _fps,bool _input[256], long long _nFrameCount)
{
  fps = _fps;
  input = _input;
  nFrameCount = _nFrameCount;

  //Console toggle
  if (input[192]){
    if (! pConsole->getToggle())
      pConsole->On();
    else
      pConsole->Off();

    input[192] = false;
  }


}


//go throught the list of objects that need to be rendered and render them
void PhEngine::Render()
{
  pRenderer->ClearBuffer(); //clear the screen

  pRenderer->EnableBlendMode();
  pRenderer->BlendMode(BM_ALPHA);

  //DRAW FRAME TIME
  pRenderer->DrawText(Vertex2(10,20,Color(0,1,0)),"RenderTime: %4.2f: Frame Number: %d",fps,nFrameCount);



  //DRAW SPRITES

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
  pRenderer->DrawLine(Vertex2(500,500,Color(0.0f,1.0f,0.0f)),
                      Vertex2(1,1,Color(1.0f,1.0f,0.0f)));

  pRenderer->DrawTexture2D(pTextureMan->Texture("tg332_04.tga"),Vertex2(640,360));
  pRenderer->DrawTexture2D(pTextureMan->Texture("Kumori.tga"),Vertex2(200 + nFrameCount % 200,200));

  //pRenderer->DrawTexture2D(pTextureMan->Texture("icephoenix.tga"),Vertex2(150,100));


  //END TEST



  //DRAW CONSOLE
  pConsole->Draw(pRenderer);





  pRenderer->DisableBlendMode();
  pRenderer->SwapBuffer(); //update buffers
}


//constructor
PhEngine::PhEngine(PhIRenderer* _renderer, PhConsole* _console)
{
  pConsole = _console;
  pRenderer = _renderer;
  fps = 0;
  pTextureMan = new PhTextureManager(pConsole,pRenderer);
}

//destructor
PhEngine::~PhEngine()
{

  delete pTextureMan;
}
