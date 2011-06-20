#include "PhoenixSprite.h"
#include "PhoenixGlobal.h"
#include "PhoenixRenderer.h"
#include "PhoenixResource.h"
#include "PhoenixDataFactory.h"
#include "PhoenixEngine.h"
#include "PhoenixUtil.h"
#include "PhoenixConsole.h"
#include "PhoenixController.h"
#include "PhoenixEntity.h"
#include "PhoenixEntityManager.h"
#include "AsProperties.h"
#include "CircularList.h"
#include <tchar.h>
#include <functional>

int x,y;

using namespace PhoenixFight;
namespace PhoenixCore{

  float r = 0;
  float camx = -15,camy = 5,camz = 0;
  float camrotx = 00,camroty = 90;
  Entity* Player;


  //everything!
  void Engine::Step(double _fps, bool _input[256], long mouse, long long _nFrameCount)
  {

    if (RunOnce){

      //Sprite* sp = new Sprite(pResourceMan);

      x = 100; y = 100;
      
      Player = new Entity();

      /*
      mousex = LOWORD(mouse);
      mousey = HIWORD(mouse);
      prevmousex = mousex;
      prevmousey = mousey;
      */

      ControllerFactory::Instance()->
        CreateController([](Entity* e) -> int {
          auto p = e->GetSprite()->GetPosition();
          p.y+=10;
          p.x++;
          e->GetSprite()->SetPosition(p);
          return 0;
      })->AssignEntity(Player);

      auto PlayerSprite = new Sprite<Texture>();
      auto tex = pResourceMan->Aquire<Texture>("Player1", L"D:\\DEV\\Reimu\\data_character_reimu_attackA000.png");
      pRenderer->BuildTexture(tex);
      PlayerSprite->AddVisual(tex);
      Player->AssignSprite(PlayerSprite);


      //pEntityMan->AddEntity(Player); 
      pEntityMan->AddDrawableEntity(Player); //add entity to game

      /*
      Controller<Entity>* a = ControllerFactory<Entity>::Instance()->CreateController([](Entity* e) -> int {

      return 0;
      });
      */




      pRenderer->Begin3D();

      RunOnce = false;
    }
    ///---------------------------------------//// END INIT PHASE

    //  camz = Player->getPos().y;
    //  camx = Player->getPos().x - 10;


    fps = _fps;
    input = _input;
    nFrameCount = _nFrameCount;

    /*
    prevmousex = pRenderer->getWidth() / 2;
    prevmousey = pRenderer->getHeight()/ 2;
    mousex = LOWORD(mouse) - prevmousex + 8;
    mousey = HIWORD(mouse) - prevmousey + 30;
    */
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

    if (!pConsole->getToggle()){
      if (input['A']){
        float xrotrad, yrotrad;
        yrotrad = ((camroty - 90) / 180 * 3.141592654f);
        camx += float(sin(yrotrad)) ;
        camz -= float(cos(yrotrad)) ;
        x -= 10;
      }
      if (input['D']){
        float xrotrad, yrotrad;
        yrotrad = ((camroty + 90) / 180 * 3.141592654f);
        camx += float(sin(yrotrad)) ;
        camz -= float(cos(yrotrad)) ;
        x += 10;
      }

      if (input['W']){
        // pRenderer->CamTranslate(0,0,1);
        float xrotrad, yrotrad;
        yrotrad = (camroty / 180 * 3.141592654f);
        xrotrad = (camrotx / 180 * 3.141592654f); 
        camx += (float(sin(yrotrad)) * cos(xrotrad));
        camz -= (float(cos(yrotrad)) * cos(xrotrad));
        camy -= float(sin(xrotrad)) ;
        y -= 10;
      }

      if (input['S']){
        // pRenderer->CamTranslate(0,0,-1);
        float xrotrad, yrotrad;
        yrotrad = (camroty / 180 * 3.141592654f);
        xrotrad = (camrotx / 180 * 3.141592654f); 
        camx -= (float(sin(yrotrad)) * cos(xrotrad));
        camz += (float(cos(yrotrad)) * cos(xrotrad));
        camy += float(sin(xrotrad)) ;
        y += 10;
      }

      //pRenderer->CamRotate(mousex * 5, 0,1,0);
      /*
      camroty += mousex / 4;
      if (camroty > 360) camroty -= 360;
      if (camroty < 0) camroty += 360;
      camrotx += mousey / 4;
      if (camrotx > 90) camrotx = 90;
      if (camrotx < -90) camrotx = -90;
      /// pRenderer->CamRotate(mousey - prevmousey, 1,0,0);
      */
    }else{
      pConsole->Input(input);
    }

    //  Player->InputBuffer->pushInput(input);

    pEntityMan->Run();

    //Cleanup Phase ------------------------------------------------------/////
    //Auto Garbage collection?!? in my c++?!?
    ControllerFactory::Instance()->GarbageCollect(); 
  }


  //go throught the list of objects that need to be rendered and render them
  void Engine::Render()
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

    //Mouse look
    //pRenderer->CamRotate(camrotx,1.0,0.0,0.0);
    //pRenderer->CamRotate(camroty,0.0,1.0,0.0);
    //WASD Movement
    pRenderer->CamTranslate(-camx,-camy,-camz);

    //TEST

    //3D
    /*
    for(int i = 0;i<1000;i++){
      for (int j = 0; j < 60; j+=4){
        pRenderer->DrawCube(Vertex3(i * 2,0,j,Color(1.0f,1.0f,0.0f)),0,0,Color(1, (i - 1) % 2, (i - 1) % 2));
        pRenderer->DrawCube(Vertex3(i * 2,0,j + 2,Color(1.0f,1.0f,0.0f)),0,0,Color(1, i % 2, i % 2));
      }
    }
    */
    pRenderer->DrawCube(Vertex3(16,10,13,Color(1.0f,1.0f,0.0f)),0,0,Color(1,1,0));
    pRenderer->DrawCube(Vertex3(13,10,16,Color(1.0f,1.0f,0.0f)),0,0,Color(1,0,1));
    pRenderer->DrawCube(Vertex3(16,10,16,Color(1.0f,1.0f,0.0f)),0,0,Color(0,0,1));

    float fvViewMatrix[ 16 ]; 
   // glGetFloatv( GL_MODELVIEW_MATRIX, fvViewMatrix );



    /*
    auto vbo = pResourceMan->Aquire<VBO>("razuleVBO",L"C:\\untitled.obj");
    if (! vbo->HasBeenCreated()){
      pRenderer->BuildVBO(vbo, VBO::STATIC_DRAW);
    }
    pRenderer->DrawVBO(vbo, Vertex3());
    */


    pRenderer->Push2D();

    pEntityMan->Draw(pRenderer);

    auto id = pResourceMan->Aquire<Texture>("testkey",L"C:\\test.png");
    if (!id->isBound()) pRenderer->BuildTexture(id);

   // pRenderer->DrawTexture2D(id,Vertex2(x,y));


    pRenderer->DrawText(Vertex2(10,20,Color(0,1,0)),_T("FPS: %3.0f"),fps);

    //for (int i = 0; i < 16; i+=4)
    //  pRenderer->DrawText(Vertex2(10,40 + i * 8,Color(0,1,0)),_T("%.3f,%.3f,%.3f,%.3f"),fvViewMatrix[i],fvViewMatrix[i + 1],fvViewMatrix[i + 2],fvViewMatrix[i + 3]);


    //DRAW SPRITES

    //2D (no Z buffer)
    //	for (int i=0; i < 200000; i++)
    //	pRenderer->DrawTriangle(Vertex2(i,100,Color(.0f,1.0f,0.0f)),
    //							Vertex2(200+i,200+fps,Color(1.0f,0.0f,0.0f)),
    //							Vertex2(100+i,0,Color(0.0f,0.0f,1.0f)));

    if (id != 0)
      pRenderer->BeginTexture(id);

    if (input[32]){
      pRenderer->DrawRectangle(
        Vertex2(100,100,Color(1)),
        Vertex2(410,100,Color(0)),
        Vertex2(410,410,Color(1)),
        Vertex2(100,410,Color(0)));
    }

    pRenderer->EndTexture();
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
  Engine::Engine(Modules *Module)
  {
    pConsole = Module->pConsole;
    pRenderer = Module->pRender;
    pEntityMan = Module->pEntityMan;

    //setup factory objects
    pResourceMan = new Resource<std::string, IResource>();
    pResourceMan->AssignDataFactory(new DataFactory());

    fps = 0;

    pEntityMan = new EntityManager();

    RunOnce = true;

    pRenderer->Begin2D();
    pRenderer->Begin3D();

  }

  //destructor
  Engine::~Engine()
  {
  }

};