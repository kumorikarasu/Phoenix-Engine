#ifndef _PHOENIXGLOBAL_H_
#define _PHOENIXGLOBAL_H_

#pragma once

#include <iostream>
#include "PhoenixConsole.h"

namespace PhoenixCore{

//global varible for tracking memory allocations
static int Track = 0;


};

#ifdef _DEBUG
using namespace PhoenixCore;

static PhConsole* DEBUGCONSOLE;

inline void * __cdecl operator new(size_t size)
{
  void *ptr = (void *)malloc(size);
  //AddTrack((DWORD)ptr, size, file, line);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log("CREATED\n",C_NORMAL);
  Track++;
  return(ptr);
};

inline void __cdecl operator delete(void *p)
{
  //RemoveTrack((DWORD)p);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log("DELETED\n",C_NORMAL);
  Track--;
  free(p);
};


inline void * __cdecl operator new[](size_t size)
{
  void *ptr = (void *)malloc(size);
  //AddTrack((DWORD)ptr, size, file, line);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log("CREATED\n",C_NORMAL);
  Track++;
  return(ptr);
};

inline void __cdecl operator delete[](void *p)
{
  //RemoveTrack((DWORD)p);
  if (DEBUGCONSOLE)
    DEBUGCONSOLE->Log("DELETED\n",C_NORMAL);
  Track--;
  free(p);
};
#endif

#endif //PHOENIXGLOBAL_H_
