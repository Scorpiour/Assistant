#include "mainForm.h"
#include "CmdQueue.h"
#include "Communicate.h"

using namespace System;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	HANDLE mainThreadSemaphore = CreateSemaphore(nullptr,(LONG)1,1,nullptr);
	CmdQueue mainCmdQueue;
	//vector<HANDLE> subThreadHandler;

	//Initialize main command queue controler
	pCmdLineInitializer CmdInitializer = new CmdLineInitializer;
	CmdInitializer->pCmdQueue = &mainCmdQueue;
	HANDLE cmdQueueHandler = CreateThread(NULL,(DWORD)NULL,(LPTHREAD_START_ROUTINE)CreateCMDProc,(void*)CmdInitializer,(DWORD)NULL,NULL);

	//Initialize main communicate model
	CmdInitializer = new CmdLineInitializer;
	CmdInitializer->pCmdQueue = &mainCmdQueue;
	HANDLE mainServerHandler = CreateThread(NULL,(DWORD)NULL,(LPTHREAD_START_ROUTINE)InitializeServerThread,(void*)CmdInitializer,(DWORD)NULL,NULL);


	if(!mainCmdQueue.Enqueue_Back(CREATE_MAIN_FORM))
	{
#ifdef GDEBUG
		MessageBox(nullptr,L"Fail to create main form!",APP_NAME,0);
#endif
	}

	WNDCLASSEX mainWndEx;

	mainWndEx.cbSize = sizeof(WNDCLASSEX);
	mainWndEx.style = CS_HREDRAW| CS_VREDRAW;
	mainWndEx.lpfnWndProc = mainWndProc;
	mainWndEx.cbClsExtra = 0;
	mainWndEx.cbWndExtra = 0;
	mainWndEx.hInstance = hInstance;
	mainWndEx.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	mainWndEx.hCursor = LoadCursor(NULL,IDC_ARROW);
	mainWndEx.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	mainWndEx.lpszMenuName = nullptr;
	mainWndEx.lpszClassName = MAINFORM_NAME;
	mainWndEx.hIconSm = LoadIcon(mainWndEx.hInstance,MAKEINTRESOURCE(IDI_APPLICATION));

	if(!RegisterClassEx(&mainWndEx))
	{
		MessageBox(nullptr,_T("Fail to register winform"),APP_NAME,0);
		return 1;
	}

	HWND hWnd = CreateWindow(	mainWndEx.lpszClassName,
								AppTitle,
								WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								800,
								600,
								nullptr,
								nullptr,
								hInstance,
								nullptr);
	if(!hWnd)
	{
		MessageBox(nullptr,_T("Fail to create window"),APP_NAME,0);
		return 1;
	}

	ShowWindow(hWnd,nCmdShow);

	UpdateWindow(hWnd);

	SendMessage(hWnd,UPDATE_CMD_QUEUE,NULL,(LPARAM)(void*)(&mainCmdQueue));

	MSG mainFormMsg;

	while(GetMessage(&mainFormMsg,nullptr,0,0))
	{
		TranslateMessage(&mainFormMsg);
		DispatchMessage(&mainFormMsg);
	}

	return (int)mainFormMsg.wParam;
}

LRESULT CALLBACK mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR welcome[] = _T("Hello world!");

	static CmdQueue* pCmdQueue = nullptr;

	switch(message)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC hdc = BeginPaint(hWnd,&paint);

			TextOut(hdc,10,10,welcome,_tcslen(welcome));
			
			EndPaint(hWnd,&paint);
			break;
		}
	case WM_DESTROY:
		{
			if(nullptr!=pCmdQueue)
			{
				pCmdQueue->Enqueue_Back(DESTROY_CMD_QUEUE);
			}
			PostQuitMessage(0);
			break;
		}
	case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			//OnSize(hwnd,(UINT)wParam,width,height);
			break;
		}
	case UPDATE_CMD_QUEUE:
		{
			if(nullptr==pCmdQueue)
			{
				pCmdQueue = (CmdQueue*)(void*)lParam;
			}
			break;
		}
	default:
		{
			return DefWindowProc(hWnd,message,wParam,lParam);
			break;
		}
	}

	return 0;
}
