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

		ReleaseSemaphore(queueSema,(LONG)1);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1);
	}
}

bool CommandQ::Enqueue_Back(pIAsyncMessage msgPtr)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.push_back(msgPtr);

		ReleaseSemaphore(queueSema,(LONG)1);
		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1);
		return false;
	}
}

bool CommandQ::Enqueue_Front(pIAsyncMessage msgPtr)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.push_front(msgPtr);

		ReleaseSemaphore(queueSema,(LONG)1);
		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1);
		return false;
	}
}

pIAsyncMessage CommandQ::Dequeue_Back(void)
{
	pIAsyncMessage msgPtr = nullptr;
	
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		msgPtr = innerQueue.back();
		innerQueue.pop_back();

		ReleaseSemaphore(queueSema,(LONG)1);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1);
	}

	return msgPtr;
}

pIAsyncMessage CommandQ::Dequeue_Front(void)
{
	pIAsyncMessage msgPtr = nullptr;
	
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		msgPtr = innerQueue.back();
		innerQueue.pop_back();

		ReleaseSemaphore(queueSema,(LONG)1);
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1);
	}

	return msgPtr;
}

bool CommandQ::Clear(void)
{
	try
	{
		WaitForSingleObject(queueSema,INFINITE);

		innerQueue.clear();

		ReleaseSemaphore(queueSema,(LONG)1);
		return true;
	}
	catch(...)
	{
		ReleaseSemaphore(queueSema,(LONG)1);
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