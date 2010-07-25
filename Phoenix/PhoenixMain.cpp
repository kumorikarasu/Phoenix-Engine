#include "PhoenixWindows.h"
#include "PhoenixMain.h"
#include "PhoenixGlobal.h"
#include "PhoenixEngine.h"
#include "PhoenixConsole.h"
#include "PhoenixOpenGLHandler.h" //OpenGL (ONLY file that should have to include this (other then .cpp ofcourse))
//#include "DirectXHandler.h" //DX

#include <time.h>

//mmmm global *cough*
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

	//Render Object
	PhIRenderer* pRenderer = new PhOpenGLHandler();

	//Console Object
	PhConsole* pConsole = new PhConsole();

#ifdef _DEBUG
	DEBUGCONSOLE = pConsole;
	DEBUGCONSOLE->Log("CREATED\n",C_NORMAL); //renderer
	DEBUGCONSOLE->Log("CREATED\n",C_NORMAL); //console
#endif


	//Engine Handler
	PhEngine* pEngine = new PhEngine(pRenderer,pConsole);

	//Frame Rate
	float fps=0,ms=0;
	clock_t time_now, movement_timer = 0;

	//Create the game window
	pRenderer->CreateGameWindow(L"Phoenix Engine",1280,720,32,0,0);

	//Setup Renderer
	pRenderer->Init();

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
			time_now = clock();
			movement_timer = time_now;

			pEngine->Step(fps,input,nFrameCount);

			while (abs(time_now - clock()) < CLK_TCK/60){
				pEngine->Render();
			}

			movement_timer = clock();
			
			
			ms = ((ms + (float)movement_timer - (float)time_now) / 2);
			fps = (int)1000 / ms;
			nFrameCount++;
		}
	}
	


	//shutdown console (closes console log file, this is why this is done before the renderer, incase it fails)
	pConsole->Log("Number of unfreed memory allocations: %d",C_NORMAL,Track);


	delete pConsole;

	//delete the engine itself
	delete pEngine;

	//shutdown the render object
	pRenderer->KillWindow();
	pRenderer->CloseRenderer();
	delete pRenderer;


	delete input;

	return (msg.wParam);							// Exit The Program
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
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}