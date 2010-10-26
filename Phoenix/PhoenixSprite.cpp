#include <atlconv.h>
#include "PhoenixSprite.h"
#include "PhoenixConsole.h"


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
  Corrupt = false;
}

bool PhSprite::AddSprite(TCHAR* _filename)
{
  if (m_pTextures == NULL){
    if (m_nSpriteLength == 0)
      return false;
    m_pTextures = new int[m_nSpriteLength];
    m_pTextureStart = m_pTextures;
  }
  if (m_nSpriteLoadIndex >= m_nSpriteLength){
    PhConsole::Console->Line(_T("Sprite Full %s"),C_WARNING, _filename);
    return false;
  }

  m_pTextures[m_nSpriteLoadIndex] = (int) m_pTextureMan->Texture(_filename);
  if (m_pTextures[m_nSpriteLoadIndex] == 0){
    Corrupt = true;
    return false;
  }
  PhConsole::Console->Line(_T("Sprite Frame Added:%d"),C_NORMAL, m_nSpriteLoadIndex);
  m_pTextureEnd = &m_pTextures[m_nSpriteLoadIndex];
  m_nSpriteLoadIndex++;

  return true;
}

PhTexture* PhSprite::GetNextSprite()
{
  if (m_pTextures == NULL)
    return NULL;

  if (m_pTextures == m_pTextureEnd){
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
      if (_tcscmp(ffd.cFileName,_T(".")) != 0 && _tcscmp(ffd.cFileName,_T("..")) != 0){
        _tcscpy(szDir, _path);
        _tcscat(szDir, ffd.cFileName);
        AddSprite(szDir);
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

};
