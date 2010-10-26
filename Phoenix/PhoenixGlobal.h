#ifndef _PHOENIXGLOBAL_H_
#define _PHOENIXGLOBAL_H_

#pragma once

#include <iostream>
#include "PhoenixConsole.h"
#include <tchar.h>

namespace PhoenixCore{

//global varible for tracking memory allocations
static int Track = 0;
static int TickCount = 1;


};

#ifdef _DEBUG
using namespace PhoenixCore;

static PhConsole* DEBUGCONSOLE;

inline void * __cdecl operator new(size_t size)
{
  void *ptr = (void *)malloc(size);
  //AddTrack((DWORD)ptr, size, file, line);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log(_T("CREATED\n"),C_NORMAL);
  Track++;
  return(ptr);
};

inline void __cdecl operator delete(void *p)
{
  //RemoveTrack((DWORD)p);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log(_T("DELETED\n"),C_NORMAL);
  Track--;
  free(p);
};


inline void * __cdecl operator new[](size_t size)
{
  void *ptr = (void *)malloc(size);
  //AddTrack((DWORD)ptr, size, file, line);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log(_T("CREATED\n"),C_NORMAL);
  Track++;
  return(ptr);
};

inline void __cdecl operator delete[](void *p)
{
  //RemoveTrack((DWORD)p);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log(_T("DELETED\n"),C_NORMAL);
  Track--;
  free(p);
};
#endif

#endif //PHOENIXGLOBAL_H_
