#include "PhoenixGlobal.h"
#include "PhoenixRenderer.h"
#include "PhoenixTexture.h"
#include "PhoenixEngine.h"
#include "PhoenixUtil.h"
#include "PhoenixConsole.h"
#include "PhoenixEntityManager.h"
#include "PhoenixSprite.h"
#include "AsPlayer.h"
#include "AsHitBoxViewer.h"
#include <tchar.h>

using namespace PhoenixFight;
namespace PhoenixCore{

float r = 0;
float camx = -15,camy = 5,camz = 0;
float camrotx = 00,camroty = 90;

AsPlayer* Player;

//everything!
void PhEngine::Step(float _fps, bool _input[256], long mouse, long long _nFrameCount)
{

  if (RunOnce){

    PhSprite* sp = new PhSprite(pTextureMan);
    Player = new AsPlayer(sp);

    
    mousex = LOWORD(mouse);
    mousey = HIWORD(mouse);
    prevmousex = mousex;
    prevmousey = mousey;

    pEntityMan->AddEntity(Player); //add entity to game

    pRenderer->Begin3D();

    RunOnce = false;
  }

  camz = Player->getPos().y;
  camx = Player->getPos().x - 10;

  fps = _fps;
  input = _input;
  nFrameCount = _nFrameCount;

  prevmousex = pRenderer->getWidth() / 2;
  prevmousey = pRenderer->getHeight()/ 2;
  mousex = LOWORD(mouse) - prevmousex + 8;
  mousey = HIWORD(mouse) - prevmousey + 30;
 /// mousex = ((mousex / ((pRenderer->getWidth() - 30) / 2)) - 1.0112);
 /// mousey = ((mousey / ((pRenderer->getHeight() + 30) / 2)) - 1 + 0.12f);

  //Console toggle
  if (input[192]){
    if (! pConsole->getToggle()){
      pConsole->On();
    } else
      pConsole->Off();

    input[192] = false;
  }
  /*
  if (input['A']){
    float xrotrad, yrotrad;
    yrotrad = ((camroty - 90) / 180 * 3.141592654f);
    camx += float(sin(yrotrad)) ;
    camz -= float(cos(yrotrad)) ;
  }
  if (input['D']){
    float xrotrad, yrotrad;
    yrotrad = ((camroty + 90) / 180 * 3.141592654f);
    camx += float(sin(yrotrad)) ;
    camz -= float(cos(yrotrad)) ;
  }
  if (input['W']){
    // pRenderer->CamTranslate(0,0,1);
    float xrotrad, yrotrad;
    yrotrad = (camroty / 180 * 3.141592654f);
    xrotrad = (camrotx / 180 * 3.141592654f); 
    camx += (float(sin(yrotrad)) * cos(xrotrad));
    camz -= (float(cos(yrotrad)) * cos(xrotrad));
    camy -= float(sin(xrotrad)) ;
  }

  if (input['S']){
    // pRenderer->CamTranslate(0,0,-1);
    float xrotrad, yrotrad;
    yrotrad = (camroty / 180 * 3.141592654f);
    xrotrad = (camrotx / 180 * 3.141592654f); 
    camx -= (float(sin(yrotrad)) * cos(xrotrad));
    camz += (float(cos(yrotrad)) * cos(xrotrad));
    camy += float(sin(xrotrad)) ;
  }
  */

    //pRenderer->CamRotate(mousex * 5, 0,1,0);
    camroty += mousex / 4;
    if (camroty > 360) camroty -= 360;
    if (camroty < 0) camroty += 360;
    camrotx += mousey / 4;
    if (camrotx > 90) camrotx = 90;
    if (camrotx < -90) camrotx = -90;
 /// pRenderer->CamRotate(mousey - prevmousey, 1,0,0);

  Player->InputBuffer->pushInput(input);

  pEntityMan->Run();
}


//go throught the list of objects that need to be rendered and render them
void PhEngine::Render()
{ //int probug = 0; //pConsole->Log(_T("DRAW %d"),C_NORMAL,probug++); //3

  pRenderer->ClearBuffer(); //clear the screen

  pRenderer->EnableBlendMode();
  pRenderer->BlendMode(BM_ALPHA);

  //pRenderer->CamTranslate(0,0,1);

  //pRenderer->Begin3D();
  //pRenderer->DrawCube(Vertex3(0,0,-8),r,10);
  //r+=0.15f;

//  pRenderer->Begin2D();

  //DRAW FRAME TIME
//  pRenderer->DrawText(Vertex2(10,20,Color(0,1,0)),"RenderTime: %4.2f: Frame Number: %d",fps,nFrameCount);

    glRotatef(camrotx,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glRotatef(camroty,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-camx,-camy,-camz); //translate the screen to the position of our camera

  //TEST

  //pRenderer->Begin3D();

  //3D
  for(int i = 0;i<1000;i++){
    for (int j = 0; j < 20; j+=4){
      pRenderer->DrawCube(Vertex3(i * 2,0,j,Color(1.0f,1.0f,0.0f)),0,0,Color(1, (i - 1) % 2, (i - 1) % 2));
      pRenderer->DrawCube(Vertex3(i * 2,0,j + 2,Color(1.0f,1.0f,0.0f)),0,0,Color(1, i % 2, i % 2));
    }
  }
  /*
  pRenderer->DrawCube(Vertex3(6,0,3,Color(1.0f,1.0f,0.0f)),0,0,Color(1,1,0));
  pRenderer->DrawCube(Vertex3(3,0,6,Color(1.0f,1.0f,0.0f)),0,0,Color(1,0,1));
  pRenderer->DrawCube(Vertex3(6,0,6,Color(1.0f,1.0f,0.0f)),0,0,Color(0,0,1));
  */

  float fvViewMatrix[ 16 ]; 
  glGetFloatv( GL_MODELVIEW_MATRIX, fvViewMatrix );

  pEntityMan->Draw(pRenderer);
  
  pRenderer->Push2D();

  pRenderer->DrawText(Vertex2(10,20,Color(0,1,0)),_T("FPS: %3.0f"),fps);

  for (int i = 0; i < 16; i+=4)
    pRenderer->DrawText(Vertex2(10,40 + i * 8,Color(0,1,0)),_T("%.3f,%.3f,%.3f,%.3f"),fvViewMatrix[i],fvViewMatrix[i + 1],fvViewMatrix[i + 2],fvViewMatrix[i + 3]);


  //DRAW SPRITES

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
 // pRenderer->DrawTexture2D(pTextureMan->Texture(_T("data\\textures\\Kumori.tga")),Vertex2(200 + nFrameCount % 60,200));

 // pRenderer->DrawTexture2D(pTextureMan->Texture("icephoenix.tga"),Vertex2(150,100));


  //END TEST


  //DRAW CONSOLE
  pConsole->Draw(pRenderer);

  pRenderer->Pop2D();

  pRenderer->DisableBlendMode();
  pRenderer->SwapBuffer(); //update buffers
}


//constructor
PhEngine::PhEngine(Modules *Module)
{
  pConsole = Module->pConsole;
  pRenderer = Module->pRender;
  pTextureMan = Module->pTextureMan;
  pEntityMan = Module->pEntityMan;

  fps = 0;

  pTextureMan = new PhTextureManager(pConsole,pRenderer);
  pEntityMan = new PhEntityManager();

  RunOnce = true;

  pRenderer->Begin2D();
  pRenderer->Begin3D();

}

//destructor
PhEngine::~PhEngine()
{
  delete pTextureMan;
}

};