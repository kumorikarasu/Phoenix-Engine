#include <atlconv.h>
#include "PhoenixSprite.h"
#include "PhoenixConsole.h"
#include "PhoenixUtil.h"


namespace PhoenixCore{

bool PhSprite::SetSize(int _size)
{
  if (m_pTextures == NULL){
    m_nSpriteLength = _size;
    return 1;
  }
  return 0;
}

PhSprite::PhSprite(PhTextureManager* _pTexMan)
{
  m_pTextureMan = _pTexMan;
  m_pTextures = NULL;
  m_pTextureStart = NULL;
  m_pTextureEnd = NULL;
  m_nSpriteLoadIndex = 0;
  m_nSpriteIndex=0;
  m_nSpriteLength=0;
  m_nDelay = 3;
  m_nState = -1;
  Corrupt = false;
}

PhTexture* PhSprite::GetNextSprite()
{
  if (m_pTextures == NULL)
    return NULL;

  if (m_pTextures > m_pTextureEnd){
    m_pTextures = m_pTextureStart;
  }

  PhTexture* tex = (PhTexture*) (*m_pTextures);
  if (m_nSpriteIndex >= m_nDelay){
    m_nSpriteIndex = 0;
    m_pTextures++;
  }else{
    m_nSpriteIndex++;
  }

  return tex;
}

PhTexture* PhSprite::GetPreviousSprite()
{
  if (m_pTextures == NULL)
    return NULL;

  if (m_pTextures < m_pTextureStart){
    m_pTextures = m_pTextureEnd;
  }

  PhTexture* tex = (PhTexture*) (*m_pTextures);
  if (m_nSpriteIndex >= m_nDelay){
    m_nSpriteIndex = 0;
    m_pTextures--;
  }else{
    m_nSpriteIndex++;
  }

  return tex;
}


bool PhSprite::AddSprite(TCHAR* _filename)
{
  if (m_pTextures == NULL){
    if (m_nSpriteLength == 0)
      return false;
    m_pTextures = new int[m_nSpriteLength];
    memset(m_pTextures,0,sizeof(m_pTextures) * m_nSpriteLength);
    m_pTextureStart = m_pTextures;
  }
  if (m_nSpriteLoadIndex >= m_nSpriteLength){
    PhConsole::Console->Line(_T("Sprite Full %s"),
                            C_WARNING, _filename);
    return false;
  }

  m_pTextures[m_nSpriteLoadIndex] = (int) m_pTextureMan->Texture(_filename);
  if (m_pTextures[m_nSpriteLoadIndex] == 0){
    Corrupt = true;
    return false;
  }
  PhConsole::Console->Line(_T("Sprite Frame Added:%d"),
                          C_NORMAL, m_nSpriteLoadIndex);
  m_pTextureEnd = &m_pTextures[m_nSpriteLoadIndex];
  m_nSpriteLoadIndex++;

  return true;
}

PhSprite::~PhSprite()
{
  free(m_pTextureStart);
}

void PhSprite::SetDelay(int _delay)
{
  m_nDelay = _delay;
}

void PhSprite::Init(){
}

bool PhSprite::Drawable(){
  return !Corrupt;
}

bool PhSprite::LoadDirectory(TCHAR* _path)
{
   WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   TCHAR szDir[MAX_PATH];
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;

   if (_tcslen(_path) > MAX_PATH - 3)
     return false;

   _tcscpy(szDir, _path);
   _tcscat(szDir, _T("\\*"));

   // Find the first file in the directory.
   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) 
   {
      return false;
   } 
   
   // List all the files in the directory with some info about them.
   do
   {
     TCHAR fileext[10];
     ExtensionFromFilename(ffd.cFileName,fileext);
     if (_tcscmp(fileext,_T("tga")) == 0)
       this->m_nSpriteLength++;
   }
   while (FindNextFile(hFind, &ffd) != 0);
   FindClose(hFind);
   m_nSpriteLength++;
   Init();

   // Find the first file in the directory.
   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind) 
   {
      return false;
   } 
   
   // List all the files in the directory with some info about them.

   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         //_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
         PhConsole::Console->Line(ffd.cFileName,C_NORMAL);
      }
      else
      {
         filesize.LowPart = ffd.nFileSizeLow;
         filesize.HighPart = ffd.nFileSizeHigh;
         PhConsole::Console->Line(ffd.cFileName,C_NORMAL);
         //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
      }
      TCHAR fileext[10];
      ExtensionFromFilename(ffd.cFileName,fileext);
      if (_tcscmp(fileext,_T("tga")) == 0){
        if (_tcscmp(ffd.cFileName,_T(".")) != 0 && 
            _tcscmp(ffd.cFileName,_T("..")) != 0)
        {
          _tcscpy(szDir, _path);
          _tcscat(szDir, ffd.cFileName);
          AddSprite(szDir);
        }
      }else if(_tcscmp(fileext,_T("sprite")) == 0){
        //Info about the current sprite, lets get that shit in here ya
        FILE* fp;
        _tcscpy(szDir, _path);
        _tcscat(szDir, ffd.cFileName);
        fp = _tfopen(szDir,_T("r"));
        char buffer[500];
        memset(buffer,0,500);
        int frames, xoffset, yoffset, action, delay, startframe, flags;
        int frameCount = 0;
        while (fgets(buffer,500,fp) != NULL){
          if (*buffer != ';' && (*buffer) != 10){
            sscanf(buffer,"%d %d %d %d %d %d %d",&action, &startframe, &frames, 
                  &delay, &xoffset, &yoffset, &flags);
            PhAnimation frame;
            frame.nStartFrame = startframe;
            frame.nFrames = frames;
            frameCount += frames;
            frame.xoffset = xoffset;
            frame.yoffset = yoffset;
            frame.delay = delay;
            int totalframes = frames * delay;
            int xmove, ymove, hbtl, hbtr, hbbl, hbbr, 
                ahbtl, ahbtr, ahbbl, ahbbr;
            for (int i=0;i<totalframes;i++){
              fgets(buffer,200,fp);
              sscanf(buffer,"%d %d %d %d %d %d %d %d %d %d %d", &xmove, 
                    &ymove, &hbtl, &hbtr, &hbbl, &hbbr, &ahbtl, &ahbtr,
                    &ahbbl, &ahbbr, &flags);
              frame.frame[i].xMovement = xmove;
              frame.frame[i].yMovement = ymove;
              frame.frame[i].hbtl = hbtl;
              frame.frame[i].hbtr = hbtr;
              frame.frame[i].hbbl = hbbl;
              frame.frame[i].hbbr = hbbr;
              frame.frame[i].ahbtl = ahbtl;
              frame.frame[i].ahbtr = ahbtr;
              frame.frame[i].ahbbl = ahbbl;
              frame.frame[i].ahbbr = ahbbr;
              frame.frame[i].Flags = flags;
            }

            //insert into map
            m_mapSprite[action] = frame;
          }
        }
        fclose(fp);
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
 
   dwError = GetLastError();
   if (dwError != ERROR_NO_MORE_FILES) 
   {
     return false;
   }

   FindClose(hFind);
   return true;
}


PhTexture* PhSprite::GetNextAdvancedSprite(int _state)
{
  if (m_nState == _state){

    if (m_pTextures == NULL)
      return NULL;

    if (m_nSpriteFrame >= m_currentFrame.nFrames){
      m_nSpriteFrame = 0;
      m_pTextures = m_pTextureStart;
    }

    PhTexture* tex = (PhTexture*) m_pTextures[m_currentFrame.nStartFrame + m_nSpriteFrame];

    if (m_nSpriteIndex >= m_nDelay){
      m_nSpriteIndex = 0;
      m_nSpriteFrame++;
    }else{
      m_nSpriteIndex++;
    }

    return tex;

  }else{

    // check if the texture already exists in the map
    map<int, PhAnimation>::iterator p = m_mapSprite.find(_state);

    if( p != m_mapSprite.end() )
    {
      // found the texture, now return the reference
      m_currentFrame = p->second;
      m_nState = _state;
      m_nSpriteFrame = 0;
      m_nDelay = m_currentFrame.delay;
    }
    return GetNextAdvancedSprite(m_nState);
  }
}

};