#include "PhoenixUtil.h"
#include "PhoenixWindows.h"
#include "PhoenixMain.h"
#include "PhoenixGlobal.h"
#include "PhoenixEngine.h"
#include "PhoenixConsole.h"
#include "PhoenixIResource.h"
#include "PhoenixResource.h"
//OpenGL (ONLY file that should have to include this (other then .cpp ofcourse))
#include "PhoenixOpenGLHandler.h" 
#include <time.h>

#define FPSSAMPLESIZE 512

using namespace PhoenixCore;

Modules* Mod;
HWND hWnd = 0;
long mouse;

bool Step = true;
bool*	input = new bool[256];

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
                    HINSTANCE	hPrevInstance,		// Previous Instance
                    LPSTR		lpCmdLine,			// Command Line Parameters
                    int			nCmdShow)			// Window Show State
{

  MSG		msg	;									
  bool	done = false;	
  int		drawRes = 0;

  long long	nFrameCount = 0;
  unsigned int actualfps[FPSSAMPLESIZE] = {0};
  int index = 0;

  //INIT ENGINE HERE

  //Init Keys
  for (int i=0;i<256;i++)
    input[i] = false;

  //All the modules we will use can all be initilised in 1 place
  Mod = (Modules*) malloc(sizeof(Modules));

  try{
    //Render Object
    Mod->pRender = new OpenGLHandler();

    //Console Object
    Mod->pConsole = Console::Instance();

#ifdef _DEBUG
#endif

    //Engine Handler
    Engine* pEngine = new Engine(Mod); //we can then just pass all the modules at once


    //Frame Rate
    double fps=0,ms=0;
    long time_now, movement_timer = 0;

    //Create the game window
    hWnd = (HWND) Mod->pRender->CreateGameWindow(L"Phoenix Engine",1280,720,32,0,0);

    //Setup Renderer
    Mod->pRender->Init();

    SetTimer(hWnd,0,16,NULL);

    if (GetFocus())
      SetCursorPos(1280/2,720/2);

    //Main loop
    while(!done)									
    {
      if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
      {
        if (msg.message==WM_QUIT)				
          done=TRUE;							
        else									
        {
          TranslateMessage(&msg);				
          DispatchMessage(&msg);				
        }
      }
      else
      {
        nFrameCount++;
        time_now = GetTickCount();
        //movement_timer = time_now;

        if (Step){
          pEngine->Step(average(actualfps, FPSSAMPLESIZE),input,mouse,nFrameCount);
          Step = false;
        }
        
        //while (abs((long) (time_now - GetTickCount())) < 16){
        pEngine->Render();
        if (GetFocus())
          SetCursorPos(1280/2,720/2);
        //}
        //movement_timer = clock();
        ms = abs(((ms + GetTickCount() - time_now) / 2));
        actualfps[index] = abs((int)((1000 / ms)));
        if (actualfps[index] > 2000)
          actualfps[index] = 2000;
        index++;
        if (index >= FPSSAMPLESIZE)
          index = 0;
      }
    }

    //shutdown console (closes console log file, this is why this is done before the renderer, incase it fails)
    Mod->pConsole->Log(_T("Number of unfreed memory allocations: %d"),Console::C_NORMAL,Track);

    //delete the engine itself
    delete pEngine;

    //shutdown the render object
    Mod->pRender->KillWindow();
    Mod->pRender->CloseRenderer();
    delete Mod->pRender;


    delete input;
    free(Mod);

    return (msg.wParam);							// Exit The Program

  }catch(const std::exception& e){
    delete Mod->pConsole;
    free(Mod);
  }

  return 1;
}



LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
                          UINT	uMsg,			// Message For This Window
                          WPARAM	wParam,			// Additional Message Information
                          LPARAM	lParam)			// Additional Message Information
{
  switch (uMsg)									// Check For Windows Messages
  {
    case WM_ACTIVATE:							// Watch For Window Activate Message
      {
        if (!HIWORD(wParam))					// Check Minimization State
        {

        }
        else									// Otherwise
        {

        }

        return 0;								// Return To The Message Loop
      }
      break;
    case WM_SYSCOMMAND:							// Intercept System Commands
      {
        switch (wParam)							// Check System Calls
        {
          case SC_SCREENSAVE:					// Screensaver Trying To Start?
          case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
            return 0;							// Prevent From Happening
        }
        break;									// Exit
      }
      break;
    case WM_CLOSE:								// Did We Receive A Close Message?
      {
        PostQuitMessage(0);						// Send A Quit Message
        return 0;								// Jump Back
      }
      break;
    case WM_KEYDOWN:							// Is A Key Being Held Down?
      {
        input[wParam] = true;

        if (VK_F10 == wParam || VK_ESCAPE == wParam){
          PostQuitMessage(0);
          return 0;
        }

      }
      break;
    case WM_KEYUP:								// Has A Key Been Released?
      {
        input[wParam] = false;

      }
      break;
    case WM_SIZE:								// Resize The OpenGL Window
      {
        Mod->pRender->UpdateSize(HIWORD(lParam),LOWORD(lParam));
      }
      break;
    case WM_TIMER:
      {
        Step = true;
        TickCount++;
        /*
        if (TickCount % 16 == 8){
          SetTimer(hWnd,0,17,NULL);
        }else{
          SetTimer(hWnd,0,16,NULL);
        }
        */
          SetTimer(hWnd,0,30,NULL);
      }
      break;
    case WM_MOUSEMOVE:
      {
        mouse = lParam;
      }
  }

  // Pass All Unhandled Messages To DefWindowProc
  return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
