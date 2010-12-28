#pragma once
#ifndef _PHOENIXWINDOWS_H_
#define _PHOENIXWINDOWS_H_

#define WIN //we are using windows if this define is true

#include <windows.h>

//windows callback function
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

#endif _PHOENIXWINDOWS_H_