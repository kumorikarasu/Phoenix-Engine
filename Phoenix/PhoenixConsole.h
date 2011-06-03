#pragma once
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "PhoenixWindows.h"

#include <time.h>
#include <list>

#define MAX_LINE_LENGTH 256

namespace PhoenixCore{

  class IRenderer;


  struct sMessageLine
  {
    TCHAR m_text[MAX_LINE_LENGTH];
    int m_type;
  };

  class Console
  {
  private:
    bool m_btoggle;
    std::list<sMessageLine> m_lConsole;
    FILE *m_logfile;
    static Console* console;
    char input[MAX_LINE_LENGTH];

  public:

    enum error_type {C_NORMAL, C_ERROR, C_WARNING};

    //Outputs a line to the console and textfile
    static void Line(const TCHAR* fmt, int _type, ...);	

    //Outputs a line to the TextFile
    static void Log(const TCHAR* fmt, int _type, ...);	

    void Draw(IRenderer * GDI);

    void On(){m_btoggle=1;}
    void Off(){m_btoggle=0;}

    bool getToggle(){return m_btoggle;}

    static Console* Instance();

    void Input(bool key[]);

    Console();
    ~Console();
  };

};

#endif
