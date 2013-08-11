#include "CommandQ.h"

using namespace std;

CommandQ::CommandQ(void)
{
	queueSema = CreateSemaphore(NULL,(LONG)1,(LONG)1,NULL);
}

CommandQ::CommandQ(const CommandQ& R)
{
}

CommandQ::~CommandQ(void)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.clear();

		ReleaseSemaphore(queueSema,(LONG)1,0);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}
}

bool CommandQ::Enqueue_Back(pIAsyncMessage msgPtr)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.push_back(msgPtr);

		ReleaseSemaphore(queueSema,(LONG)1,0);
		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
		return false;
	}
}

bool CommandQ::Enqueue_Front(pIAsyncMessage msgPtr)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.push_front(msgPtr);

		ReleaseSemaphore(queueSema,(LONG)1,0);
		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
		return false;
	}
}

pIAsyncMessage CommandQ::Dequeue_Back(void)
{
	pIAsyncMessage msgPtr = nullptr;
	
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		if(innerQueue.empty())
		{
			msgPtr = nullptr;
		}
		else
		{
			msgPtr = innerQueue.back();
			innerQueue.pop_back();
		}
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}

	return msgPtr;
}

pIAsyncMessage CommandQ::Dequeue_Front(void)
{
	pIAsyncMessage msgPtr = nullptr;
	
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		if(innerQueue.empty())
		{
			msgPtr = nullptr;
		}
		else
		{
			msgPtr = innerQueue.front();
			innerQueue.pop_front();
		}
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}

	return msgPtr;
}

pIAsyncMessage CommandQ::Peek_Back(void)
{
	pIAsyncMessage msgPtr = nullptr;
	
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		if(innerQueue.empty())
		{
			msgPtr = nullptr;
		}
		else
		{
			msgPtr = innerQueue.back();
		}
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}

	return msgPtr;
}

pIAsyncMessage CommandQ::Peek_Front(void)
{
	pIAsyncMessage msgPtr = nullptr;
	
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		if(innerQueue.empty())
		{
			msgPtr = nullptr;
		}
		else
		{
			msgPtr = innerQueue.front();
		}
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
	}

	return msgPtr;
}

bool CommandQ::Clear(void)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.clear();

		ReleaseSemaphore(queueSema,(LONG)1,0);
		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1,0);
		return false;
	}
}

UINT CommandQ::Size(void)const
{
	return innerQueue.size();
}

bool CommandQ::isEmpty(void)const
{
	return (innerQueue.size()==0);
}