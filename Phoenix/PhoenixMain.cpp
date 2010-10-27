#include "PhoenixWindows.h"
#include "PhoenixMain.h"
#include "PhoenixGlobal.h"
#include "PhoenixEngine.h"
#include "PhoenixConsole.h"
#include "PhoenixOpenGLHandler.h" //OpenGL (ONLY file that should have to include this (other then .cpp ofcourse))
#include <time.h>

using namespace PhoenixCore;

PhConsole* PhConsole::Console;
HWND hWnd = 0;


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

  //INIT ENGINE HERE

  //Init Keys
  for (int i=0;i<256;i++)
    input[i] = false;

  //All the modules we will use can all be initilised in 1 place
  Modules Mod;

  try{
  //Render Object
  Mod.pRender = new PhOpenGLHandler();

  //Console Object
  Mod.pConsole = new PhConsole();
  PhConsole::Console = Mod.pConsole;

#ifdef _DEBUG
  DEBUGCONSOLE = Mod.pConsole;
  DEBUGCONSOLE->Log(_T("CREATED\n"),C_NORMAL); //renderer
  DEBUGCONSOLE->Log(_T("CREATED\n"),C_NORMAL); //console
#endif


  //Engine Handler
  PhEngine* pEngine = new PhEngine(Mod); //we can then just pass all the modules at once


  //Frame Rate
  double fps=0,ms=0;
  long time_now, movement_timer = 0;

  //Create the game window
  hWnd = (HWND) Mod.pRender->CreateGameWindow(L"Phoenix Engine",1280,720,32,0,0);

  //Setup Renderer
  Mod.pRender->Init();

  SetTimer(hWnd,0,16,NULL);

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
      time_now = GetTickCount();
      //movement_timer = time_now;

      if (Step){
        pEngine->Step(fps,input,nFrameCount);
        Step = false;
      }
      
      //while (abs((long) (time_now - GetTickCount())) < 16){
      pEngine->Render();
      //}
      //movement_timer = clock();
      ms = abs(((ms + GetTickCount() - time_now) / 2));
      fps = abs((int)(fps + (1000 / ms)) / 2);
      if (fps > 200){
        fps = 200;
      }
      nFrameCount++;
    }
  }



  //shutdown console (closes console log file, this is why this is done before the renderer, incase it fails)
  Mod.pConsole->Log(_T("Number of unfreed memory allocations: %d"),C_NORMAL,Track);


  delete Mod.pConsole;

  //delete the engine itself
  delete pEngine;

  //shutdown the render object
  Mod.pRender->KillWindow();
  Mod.pRender->CloseRenderer();
  delete Mod.pRender;


  delete input;

  return (msg.wParam);							// Exit The Program

  }catch(exception e){
    delete Mod.pConsole;
    return 1;
  }
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

      }
      break;
    case WM_TIMER:
      {
        Step = true;
        TickCount++;
        SetTimer(hWnd,0,16,NULL);
      }
  }

  // Pass All Unhandled Messages To DefWindowProc
  return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
