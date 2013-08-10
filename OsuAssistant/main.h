#ifndef __INCLUDE_MAIN_H__
#define __INCLUDE_MAIN_H__

#include <WinSock2.h>
#include <windowsx.h>
#include <amp.h>
#include <cstdlib>

typedef class AsyncMessageBase
{
public:

}IAsyncMessage,*pIAsyncMessage;

typedef class DealerBase
{
public:
	virtual bool sendAsyncMessage(void) = 0;
	virtual bool acceptAsyncMessage(pIAsyncMessage) = 0;
}IDealer,*pIDealer;

typedef class RequesterBase
{
public:
	virtual pIAsyncMessage receiveAsyncMessage(void) = 0;
}IRequester,*pIRequester;

typedef class CommandQueueBase
{
public:
	virtual bool Enqueue_Back(pIAsyncMessage) = 0;
	virtual bool Enqueue_Front(pIAsyncMessage) = 0;

	virtual pIAsyncMessage Dequeue_Back(void) = 0;
	virtual pIAsyncMessage Dequeue_Front(void) = 0;

	virtual bool Clear(void) = 0;
	virtual UINT Size(void)const = 0;
	virtual bool isEmpty(void)const = 0;
}ICommandQueue,*pICommandQueue;

#endif