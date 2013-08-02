#include "mainForm.h"
#include "CmdQueue.h"

using namespace System;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	HANDLE mainThreadSemaphore = CreateSemaphore(nullptr,(LONG)1,1,nullptr);
	CmdQueue mainCmdQueue;
	vector<HANDLE> subThreadHandler;

	if(!mainCmdQueue.Enqueue_Back(CREATE_MAIN_FORM))
	{
#ifdef GDEBUG
		MessageBox(nullptr,L"Fail to create main form!",APP_NAME,0);
#endif
	}

	while(true)
	{
		UINT data = mainCmdQueue.Dequeue_Front();
		switch(data)
		{
		case EMPTY_CMD_QUEUE:
			{
				//MessageBox(NULL,L"Empty Queue!",APP_NAME,0);
				Sleep(1);
				break;
			}
		case CREATE_MAIN_FORM:
			{
				MessageBox(NULL,L"Create Main Form!",APP_NAME,0);
					
				pFormInitializer initializer = new FormInitializer;

				initializer->hInstance = hInstance;
				initializer->hPrevInstance = hPrevInstance;
				initializer->lpCmdLine = lpCmdLine;
				initializer->nCmdShow = nCmdShow;
				initializer->mainThreadSemaphore = mainThreadSemaphore;
				initializer->pCmdQueue = &mainCmdQueue;

				HANDLE newFormHandler = CreateThread(nullptr,(DWORD)NULL,(LPTHREAD_START_ROUTINE)CreateNewFormThread,(void*)initializer,(DWORD)NULL,nullptr);
					
				if(NULL!=newFormHandler)
				{
					subThreadHandler.push_back(newFormHandler);
				}

				break;
			}
		case DESTROY_MAIN_FORM:
			{
				MessageBox(NULL,L"Main Form has been closed!",APP_NAME,0);
				return 0;
				break;
			}
		default:
			{
				break;
			}
		}
	}

	return 0;
}

