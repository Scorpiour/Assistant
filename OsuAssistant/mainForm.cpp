#include "mainForm.h"
#include "CmdQueue.h"


void* __stdcall CreateCMDProc(void* initValuePtr)
{
	pCmdLineInitializer ptr = (pCmdLineInitializer)initValuePtr;

	while(true)
	{
		UINT data = ptr->pCmdQueue->Dequeue_Front();
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
				
				break;
			}
		case DESTROY_CMD_QUEUE:
			{
				MessageBox(NULL,L"Command Queue has been released!",APP_NAME,0);
				delete[] ptr;
				ExitThread((DWORD)NULL);
			}
		default:
			{
				break;
			}
		}
	}

	delete[] ptr;
	ExitThread((DWORD)NULL);
}
