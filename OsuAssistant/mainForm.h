#ifndef __INCLUDE_MAINFORM_H__
#define __INCLUDE_MAINFORM_H__

#ifndef GDEBUG
#define GDEBUG
#endif

#include <WinSock2.h>
#include <WS2tcpip.h>
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
class IPv6Server;

typedef struct newFormStruct
{
	CmdQueue* pCmdQueue;
}CmdLineInitializer,*pCmdLineInitializer;

typedef basic_string<TCHAR> tstring;

void* __stdcall CreateCMDProc(void*);
void* __stdcall InitializeServerThread(void*);

LRESULT CALLBACK mainWndProc(HWND, UINT, WPARAM, LPARAM);

const TCHAR APP_NAME[] = _T("osuAssistant");
const TCHAR AppTitle[] = _T("osu! Assistant");
const TCHAR MAINFORM_NAME[] = _T("AssistantMainForm");

const int UPDATE_CMD_QUEUE = 0x4001;


#endif