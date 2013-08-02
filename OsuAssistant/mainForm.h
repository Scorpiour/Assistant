#ifndef __INCLUDE_MAINFORM_H__
#define __INCLUDE_MAINFORM_H__

#ifndef GDEBUG
#define GDEBUG
#endif

#include <Windows.h>
#include <cstdlib>
#include <string>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

using namespace std;

class CmdQueue;

typedef struct newFormStruct
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPSTR lpCmdLine;
	int nCmdShow;
	HANDLE mainThreadSemaphore;
	CmdQueue* pCmdQueue;
}FormInitializer,*pFormInitializer;

void* __stdcall CreateNewFormThread(void*);
int CALLBACK createNewForm(HINSTANCE,HINSTANCE,LPSTR,int);
LRESULT CALLBACK mainWndProc(HWND, UINT, WPARAM, LPARAM);

const TCHAR APP_NAME[] = _T("osuAssistant");
const TCHAR AppTitle[] = _T("osu! Assistant");

#endif