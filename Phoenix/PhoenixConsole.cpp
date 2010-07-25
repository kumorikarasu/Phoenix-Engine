#include "PhoenixGlobal.h"
#include "PhoenixConsole.h"
#include "PhoenixUtil.h"
#include "PhoenixRenderer.h"


PhConsole::PhConsole(){
  m_btoggle=false;
  m_logfile =	fopen("console_log.txt","a+");
  fprintf(m_logfile,"\n\nBuildVer: %d TimeStamp:%d\n",0,time(NULL));
}



PhConsole::~PhConsole(){
  fclose(m_logfile);	
}

void PhConsole::Draw(PhIRenderer * GDI){
  if (this->m_btoggle){
    GDI->DrawRectangle(Vertex2(0,0,Color(0.5f,0.5f,0.5f,0.5f)),
                       Vertex2(GDI->getWidth(),0,Color(0.5f,0.5f,0.5f,0.5f)),
                       Vertex2(GDI->getWidth(),200,Color(0.5f,0.5f,0.5f,0.5f)),
                       Vertex2(0,200,Color(0.5f,0.5f,0.5f,0.5f)));
  }
}

//outputs a line to ONLY the file log
void PhConsole::Log(const char* fmt, int _type, ...){
  sMessageLine line;
  va_list va;

  va_start(va,_type);
  vsprintf(line.m_text,fmt,va);

  //print the line
  fprintf(m_logfile,line.m_text);

  va_end(va);

  if (_type==C_WARNING){

  }
}



//Outputs a line to both the screen console and the file console
void PhConsole::Line(const char* fmt, int _type, ...){
  sMessageLine line;
  va_list va;

  va_start(va,_type);

  vsprintf(line.m_text,fmt,va);


  m_lConsole.push_back(line);

  fprintf(m_logfile,line.m_text);

  va_end(va);

  /*	va_list va;
      va_start(va, fmt);

      DWORD size = MultiByteToWideChar(CP_ACP,0,fmt,-1,NULL,0);
      wchar_t* sBuff = NULL;
      wchar_t* fm;
      fm = new wchar_t[size];
      MultiByteToWideChar(CP_ACP,0,fmt,-1,fm,size);

      vswprintf(sBuff,fm, va);

      PString tBuff = reinterpret_cast < const wchar_t* > (sBuff);
      delete sBuff,fm;

      va_end(va);
      line.m_text = tBuff;
      line.m_type = _type;
      m_lConsole.push_back(line);
      */

  if (_type==C_WARNING){

  }
}
