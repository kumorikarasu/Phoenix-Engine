#include "PhoenixWindows.h"
#include "PhoenixGlobal.h"
#include "PhoenixOpenGLHandler.h"
#include "PhoenixUtil.h"
#include "PhoenixTexture.h"

#include "stdio.h"

void PhOpenGLHandler::BindTexture(PhTexture* _pTexture){

	int depthType;

	glGenTextures(1, &(_pTexture->m_id));
	glBindTexture(GL_TEXTURE_2D, _pTexture->m_id);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear filters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	
	switch(_pTexture->GetBpp())
	{
	case 32:
		depthType = GL_RGBA;
		break;
	case 24:
	default:
		depthType = GL_RGB;
		break;
	}

	//texture blending
//	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE);

	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pTexture->m_width, pTexture->m_height, depthType, GL_UNSIGNED_BYTE, pTexture->m_data);

	glTexImage2D(GL_TEXTURE_2D, 0, depthType, _pTexture->GetWidth(), 
		_pTexture->GetHeight(), 0, depthType, GL_UNSIGNED_BYTE, _pTexture->m_data);

}


void PhOpenGLHandler::DrawTexture2D(PhTexture* _pTexture, Vertex2& pos){

	Vertex2 postopleft(pos.x - _pTexture->GetWidth() / 2,pos.y - _pTexture->GetHeight() / 2);

	//enable 2D texturing
	glEnable( GL_TEXTURE_2D );

	//bind the texture to the renderer
	glBindTexture(GL_TEXTURE_2D, _pTexture->m_id);



	//set color to default
	glColor3f(1,1,1);

	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 1.0f); glVertex3d(postopleft.x, postopleft.y,  0.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3d(postopleft.x + _pTexture->GetWidth(), postopleft.y,  0.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3d(postopleft.x + _pTexture->GetWidth(),  postopleft.y + _pTexture->GetHeight(),  0.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3d(postopleft.x,  postopleft.y + _pTexture->GetHeight(),  0.0f);	// Top Left Of The Texture and Quad
	glEnd();

	glDisable(GL_TEXTURE_2D);
	/*
	//draw the texture
	//gpDisplay->TurnOffHardwareVBO();

	glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_VERTEX_ARRAY ); 

	//glNormalPointer(GL_FLOAT, sizeof(Vertex2), &(m_verts[0].n));
	//glColorPointer(3, GL_FLOAT, sizeof(Vertex2), &(m_verts[0].c));
	//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex2), &(m_verts[0].t)); 
	//glVertexPointer(3, GL_FLOAT, sizeof(Vertex2), &(m_verts[0].p)); 

	glDrawArrays(GL_POLYGON, 0, 4);
	
	glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
*/
}


void PhOpenGLHandler::DrawLine(Vertex2& pos1, Vertex2& pos2){
	glBegin(GL_LINES);
		glColor3f(pos1.c.r,pos1.c.g,pos1.c.b);
		glVertex3f( (GLfloat) pos1.x, (GLfloat)  pos1.y, 0.0f);

		glColor3f(pos2.c.r,pos2.c.g,pos2.c.b);
		glVertex3f( (GLfloat) pos2.x, (GLfloat) pos2.y, 0.0f);
	glEnd();
}


void PhOpenGLHandler::DrawTriangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3){
	glBegin(GL_TRIANGLES);
		glColor3f(pos1.c.r,pos1.c.g,pos1.c.b);
		glVertex3f( (GLfloat) pos1.x, (GLfloat)  pos1.y, 0.0f);

		glColor3f(pos2.c.r,pos2.c.g,pos2.c.b);
		glVertex3f( (GLfloat) pos2.x, (GLfloat) pos2.y, 0.0f);

		glColor3f(pos3.c.r,pos3.c.g,pos3.c.b);
		glVertex3f( (GLfloat) pos3.x, (GLfloat) pos3.y, 0.0f);
	glEnd();
}


void PhOpenGLHandler::DrawRectangle(Vertex2& pos1, Vertex2& pos2, Vertex2& pos3, Vertex2& pos4){
	glBegin(GL_QUADS);
		glColor4f(pos1.c.r,pos1.c.g,pos1.c.b,pos1.c.a);
		glVertex3f( (GLfloat) pos1.x, (GLfloat)  pos1.y, 0.0f);

		glColor4f(pos2.c.r,pos2.c.g,pos2.c.b,pos2.c.a);
		glVertex3f( (GLfloat) pos2.x, (GLfloat) pos2.y, 0.0f);

		glColor4f(pos3.c.r,pos3.c.g,pos3.c.b,pos3.c.a);
		glVertex3f( (GLfloat) pos3.x, (GLfloat) pos3.y, 0.0f);

		glColor4f(pos4.c.r,pos4.c.g,pos4.c.b,pos4.c.a);
		glVertex3f( (GLfloat) pos4.x, (GLfloat) pos4.y, 0.0f);
	glEnd();
}

void PhOpenGLHandler::EnableBlendMode(){
	glEnable (GL_BLEND);
}

void PhOpenGLHandler::BlendMode(blend_mode bm){
	if (bm == BM_ALPHA){
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if (bm == BM_ADD){
		glBlendFunc (GL_ONE,GL_ONE);
		
	}
}

void PhOpenGLHandler::DisableBlendMode(){
	glDisable(GL_BLEND);
}


int PhOpenGLHandler::ClearBuffer(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//glTranslatef(0.0f,0.0f,-6.0f); //move into the screen so we can SEE what we draw

	/*	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();											// Done Drawing The Quad
	return TRUE;										// Keep Going
*/
	return true;
}

int	PhOpenGLHandler::SwapBuffer(){
	return SwapBuffers(hDC);
}

int PhOpenGLHandler::CreateGameWindow(LPCWSTR title, int _width, int _height, int bits, bool fullscreenflag, int nCmdShow){
	
	width = _width;
	height = _height;

	GLuint		PixelFormat;						// Holds The Results After Searching For A Match

	WNDCLASS	wc;							// Windows Class Structure
	
	DWORD		dwExStyle;						// Window Extended Style
	DWORD		dwStyle;						// Window Style

	RECT WindowRect;							// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;						// Set Left Value To 0
	WindowRect.right=(long)width;						// Set Right Value To Requested Width
	WindowRect.top=(long)0;							// Set Top Value To 0
	WindowRect.bottom=(long)height;						// Set Bottom Value To Requested Height

//	fullscreen=fullscreenflag;						// Set The Global Fullscreen Flag

	hInstance		= GetModuleHandle(NULL);			// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) WndProc;				// WndProc Handles Messages
	wc.cbClsExtra		= 0;						// No Extra Window Data
	wc.cbWndExtra		= 0;						// No Extra Window Data
	wc.hInstance		= hInstance;					// Set The Instance
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;						// No Background Required For GL
	wc.lpszMenuName		= NULL;						// We Don't Want A Menu
	wc.lpszClassName	= L"PhoenixEngine";					// Set The Class Name

	if (!RegisterClass(&wc))						// Attempt To Register The Window Class
	{
		MessageBox(NULL,L"Failed To Register The Window Class.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 0;							// Exit And Return 0
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;					// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, 0, dwExStyle);		// Adjust Window To True Requested Size

	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
				L"PhoenixEngine",				// Class Name
				title,					// Window Title
				WS_CLIPSIBLINGS |			// Required Window Style
				WS_CLIPCHILDREN |			// Required Window Style
				dwStyle,				// Selected Window Style
				0, 0,					// Window Position
				WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
				WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
				NULL,					// No Parent Window
				NULL,					// No Menu
				hInstance,				// Instance
				NULL)))					// Don't Pass Anything To WM_CREATE
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL,L"Window Creation Error.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 0;							// Return 0
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,						// Must Support Double Buffering
		PFD_TYPE_RGBA,							// Request An RGBA Format
		bits,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,						// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		16,								// 16Bit Z-Buffer (Depth Buffer)
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,							// Main Drawing Layer
		0,								// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Device Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 0;							// Return 0
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Did Windows Find A Matching Pixel Format?
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL,L"Can't Find A Suitable PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 0;							// Return 0
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))				// Are We Able To Set The Pixel Format?
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL,L"Can't Set The PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 0;							// Return 0
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return 0
	}
	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL,L"Can't Activate The GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	
	
	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);								// Sets Keyboard Focus To The Window
	ReSizeWindow(width, height);						// Set Up Our Perspective GL Screen

	return 0;
}

//resize the window (does not set scaling, so after initial setup, this should not be used)
void PhOpenGLHandler::ReSizeWindow(int width, int height){
	if (height==0)								// Prevent A Divide By Zero By
	{
		height=1;							// Making Height Equal One
	}

	glViewport(0, 0, width, height);		// Reset The Current Viewport

	Begin2D();
}


/*** - OpenGL Initilization
/*
/* - Returns true if succesful
*/

int PhOpenGLHandler::Init(){

	glShadeModel(GL_SMOOTH);  //enable smooth shading

	//screen colour, black
	glClearColor(0.0f,0.0f,0.0f,0.0f);


	//Depth buffer (to make sure things draw ontop of other things correctly
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // tells OGL which perspective calculations to use

	BuildFont();										// Build The Font

	return true;
}

//switch to 2D drawing
void PhOpenGLHandler::Begin2D(){
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	gluOrtho2D (0, width, height, 0);

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();							// Reset The Modelview Matrix
}

//switch to 3D drawing
void PhOpenGLHandler::Begin3D(){
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	//gluOrtho2D (0, width, height, 0);

	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glLoadIdentity();							// Reset The Modelview Matrix
}


void PhOpenGLHandler::KillWindow(){

	if (hRC)								// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,L"Release Of DC And RC Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))					// Are We Able To Delete The RC?
		{
			MessageBox(NULL,L"Release Rendering Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;							// Set RC To NULL
		}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,L"Release Device Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;							// Set DC To NULL
	}

	if (hWnd!=NULL && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;							// Set hWnd To NULL
	}

	if (!UnregisterClass(L"PhoenixEngine",hInstance))				// Are We Able To Unregister Class
	{
		MessageBox(NULL,L"Could Not Unregister Class.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;							// Set hInstance To NULL
	}
}

void PhOpenGLHandler::CloseRenderer(){

		KillFont();										// Build The Font

};

void PhOpenGLHandler::BuildFont()								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						L"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

void PhOpenGLHandler::KillFont()									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

//cannot be over 254 characters
void PhOpenGLHandler::DrawText(Vertex2 _pos, const char *fmt, ...)					// Custom GL "Print" Routine
{

	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	// Pulsing Colors Based On Text Position
	glColor3f(_pos.c.r,_pos.c.g,_pos.c.b);
	// Position The Text On The Screen
	glRasterPos2f((float)_pos.x,(float)_pos.y);

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text


	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}