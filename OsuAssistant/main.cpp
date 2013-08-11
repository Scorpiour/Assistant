#include "CommandQ.h"
#include "Constance.h"
#include "Global.h"
#include "d3dProcBase.h"

#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3dx11.lib")
#pragma comment (lib,"d3dx10.lib")

LRESULT CALLBACK mainProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wcex;

	int width;
	int height;

	D3DBase myD3D;

	GetDesktopResolution(width,height);

	ZeroMemory(&wcex,sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW|CS_VREDRAW;
	wcex.lpfnWndProc = mainProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = _T("mainFormClassEx");

	RegisterClassEx(&wcex);

	hWnd = CreateWindowEx(NULL,
                        _T("mainFormClassEx"),    // name of the window class
                        _T("Test D3D Class"),   // title of the window
                        WS_EX_TOPMOST|WS_POPUP,    // window style
                        0,    // x-position of the window
                        0,    // y-position of the window
                        width,    // width of the window
                        height,    // height of the window
                        NULL,    // we have no parent window, NULL
                        NULL,    // we aren't using menus, NULL
                        hInstance,    // application handle
                        NULL);    // used with multiple windows, NULL

	ShowWindow(hWnd,nCmdShow);

	myD3D.initD3D(hWnd,width,height);

	MSG msg;

	while(true)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		switch(msg.message)
		{
		case WM_QUIT:
			{
				break;
			}
		}

		/*
		Run Game code here!
		*/
		myD3D.renderFrame();
	}

	myD3D.cleanD3D();

	return msg.wParam;
}

LRESULT CALLBACK mainProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}