#include "PhoenixGlobal.h"
#include "PhoenixConsole.h"
#include "PhoenixUtil.h"
#include "PhoenixRenderer.h"

namespace PhoenixCore{

PhConsole::PhConsole()
{
  m_btoggle=false;
  m_logfile =	fopen("console_log.txt","a+");
  fprintf(m_logfile,"\n\nBuildVer: %d TimeStamp:%d\n",0,time(NULL));
  fclose(m_logfile);
}


PhConsole::~PhConsole()
{
//  fclose(m_logfile);	
}


void PhConsole::Draw(PhIRenderer * GDI)
{
  if (this->m_btoggle){
    GDI->DrawRectangle(Vertex2(0,0,Color(0.5f,0.5f,0.5f,0.5f)),
                       Vertex2(GDI->getWidth(),0,Color(0.5f,0.5f,0.5f,0.5f)),
                       Vertex2(GDI->getWidth(),200,Color(0.5f,0.5f,0.5f,0.5f)),
                       Vertex2(0,200,Color(0.5f,0.5f,0.5f,0.5f)));

    if (m_lConsole.size() > 0){
      list<sMessageLine>::reverse_iterator iter = m_lConsole.rbegin();

      for (int i = 8; i>0; i--){
        if (iter->m_type == C_WARNING){
          GDI->DrawTextW(Vertex2(10, 2 + i*22,Color(1.0f,1.0f,0.0f)),
                         iter->m_text);
        }else if (iter->m_type == C_ERROR){
          GDI->DrawTextW(Vertex2(10, 2 + i*22,Color(1.0f,0.0f,0.0f)),
                         iter->m_text);
        }else
          GDI->DrawTextW(Vertex2(10, 2 + i*22,Color(1.0f,1.0f,1.0f)),
                         iter->m_text);
        ++iter;
        if (iter == m_lConsole.rend())
          break;
      }
    }
  }
}


//outputs a line to ONLY the file log
void PhConsole::Log(const TCHAR* fmt, int _type, ...)
{
  sMessageLine line;
  va_list va;

  va_start(va,_type);
  vswprintf(line.m_text,fmt,va);

  //print the line
  _tcscat(line.m_text,_T("\n"));

  m_logfile =	fopen("console_log.txt","a+");
  fwprintf(m_logfile,line.m_text);
  fclose(m_logfile);

  va_end(va);

  line.m_type = _type;
}



//Outputs a line to both the screen console and the file console
void PhConsole::Line(const TCHAR* fmt, int _type, ...)
{
  sMessageLine line;
  va_list va;

  va_start(va,_type);

  vswprintf(line.m_text,fmt,va);
  line.m_type = _type;

  m_lConsole.push_back(line);

  //print the line
  _tcscat(line.m_text,_T("\n"));

  m_logfile =	fopen("console_log.txt","a+");
  fwprintf(m_logfile,line.m_text);
  fclose(m_logfile);

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

}

}