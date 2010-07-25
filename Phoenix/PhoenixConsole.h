#pragma once
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "PhoenixWindows.h"
#include "PhoenixMain.h"

#include "PhoenixRenderer.h"
#include <time.h>
#include <list>

class PhIRenderer;

enum error_type {C_NORMAL, C_ERROR, C_WARNING};

struct sMessageLine{
	char m_text[256];
	int m_type;
};

class PhConsole{
		
	bool m_btoggle;
	std::list<sMessageLine> m_lConsole;
	FILE *m_logfile;

public:
	void Line(const char* fmt, int _type, ...);	//Outputs a line to the console and textfile
	void Log(const char* fmt, int _type, ...);	//Outputs a line to the TextFile

	void Draw(PhIRenderer * GDI);

	void On(){m_btoggle=1;}
	void Off(){m_btoggle=0;}
	
	bool getToggle(){return m_btoggle;}

	PhConsole();
	~PhConsole();
};


#endif