#include "CommandQ.h"
#include "Constance.h"

#pragma comment (lib,"d3d9.lib")
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

void initD3D(HWND hWnd);
void render_frame(void);
void cleanD3D(void);


LRESULT CALLBACK mainProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wcex;

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
                        WS_OVERLAPPEDWINDOW,    // window style
                        300,    // x-position of the window
                        300,    // y-position of the window
                        800,    // width of the window
                        600,    // height of the window
                        NULL,    // we have no parent window, NULL
                        NULL,    // we aren't using menus, NULL
                        hInstance,    // application handle
                        NULL);    // used with multiple windows, NULL

	ShowWindow(hWnd,nCmdShow);

	initD3D(hWnd);

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

		render_frame();
		/*
		Run Game code here!
		*/
	}

	cleanD3D();

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

void initD3D(HWND hWnd)
{
	//Crate D3D interface
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp,sizeof(d3dpp));

	//True = windowed, False = Full-screen
	d3dpp.Windowed = TRUE;

	//Discard swapping for best speed
	//Flip to ensure the back buffers are protected already
	//Copy to not only swap ptr but whole buffer, not recommend
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//Set to the handler of window where d3d used
	d3dpp.hDeviceWindow = hWnd;

	/*
	HRESULT CreateDevice(
    UINT Adapter,
    D3DDEVTYPE DeviceType,
    HWND hFocusWindow,
    DWORD BehaviorFlags,
    D3DPRESENT_PARAMETERS *pPresentationParameters,
    IDirect3DDevice9 **ppReturnedDeviceInterface);
	*/
	d3d->CreateDevice(
			D3DADAPTER_DEFAULT,					//use default adapter
			D3DDEVTYPE_HAL,						//HAL:Hardware Abstraction Layer
			hWnd,								//window hWnd
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,//i may choose D3DCREATE_HARDWARE_VERTEXPROCESSING
			&d3dpp,
			&d3ddev);
}

void render_frame(void)
{
	static unsigned short r;
	static unsigned short g;
	static unsigned short b;

	r++;
	g+=2;
	b+=4;
	if(r > 255)
	{
		r = 0;
	}
	if(g > 255)
	{
		g = 0;
	}
	if(b > 255)
	{
		b = 0;
	}
	//Clear the back buffer to a blue screen
	d3ddev->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(r,g,b),1.0f,0);

	d3ddev->BeginScene();

	d3ddev->EndScene();

	d3ddev->Present(NULL,NULL,NULL,NULL);
}

void cleanD3D(void)
{
	d3ddev->Release();
	d3d->Release();
}