#include "CmdQueue.h"

CmdQueue::CmdQueue(void)
{
	if(cmd.size()!=0)
	{
		cmd.clear();
	}

	queueSema = CreateSemaphore(nullptr,(LONG)1,1,nullptr);
}

void CmdQueue::Lock(void)
{
	WaitForSingleObject(queueSema,DWORD(0xfffffffff));
}

void CmdQueue::Unlock(void)
{
	ReleaseSemaphore(queueSema,1,NULL);
}

CmdQueue::CmdQueue(CmdQueue& R)
{
	WaitForSingleObject(queueSema,DWORD(0xfffffffff));
	
	cmd.clear();
	R.Lock();
	cmd = R.cmd;
	R.Unlock();

	ReleaseSemaphore(queueSema,1,NULL);
}

CmdQueue::~CmdQueue(void)
{
	WaitForSingleObject(queueSema,DWORD(0xfffffffff));

	cmd.clear();

	ReleaseSemaphore(queueSema,1,NULL);
}

UINT CmdQueue::Dequeue_Front(void)
{
	try
	{
		WaitForSingleObject(queueSema,DWORD(0xfffffffff));
		UINT ret;
		if(!isEmpty())
		{
			ret = cmd.front();
			cmd.pop_front();
		}
		else
		{
			ret = EMPTY_CMD_QUEUE;
		}
		ReleaseSemaphore(queueSema,1,NULL);
		return ret;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,1,NULL);
		return READ_CMDQUEUE_ERROR;
	}
}
UINT CmdQueue::Dequeue_Back(void)
{
	try
	{
		WaitForSingleObject(queueSema,DWORD(0xfffffffff));
		UINT ret;
		if(!isEmpty())
		{
			ret = cmd.back();
			cmd.pop_back();
		}
		else
		{
			ret = EMPTY_CMD_QUEUE;
		}
		ReleaseSemaphore(queueSema,1,NULL);
		return ret;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,1,NULL);
		return READ_CMDQUEUE_ERROR;
	}
}

bool CmdQueue::Enqueue_Front(UINT value)
{
	try
	{
		WaitForSingleObject(queueSema,DWORD(0xfffffffff));
	
		cmd.push_front(value);

		ReleaseSemaphore(queueSema,1,NULL);

		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,1,NULL);
		return false;
	}
}
bool CmdQueue::Enqueue_Back(UINT value)
{
	try
	{
		WaitForSingleObject(queueSema,DWORD(0xfffffffff));

		cmd.push_back(value);

		ReleaseSemaphore(queueSema,1,NULL);

		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,1,NULL);
		return false;
	}
}

UINT CmdQueue::Length(void)const
{
	return cmd.size();
}

bool CmdQueue::isEmpty(void)const
{
	return cmd.size()==0;
}
	
void CmdQueue::Clear(void)
{
	WaitForSingleObject(queueSema,DWORD(0xfffffffff));

	cmd.clear();

	ReleaseSemaphore(queueSema,1,NULL);
}