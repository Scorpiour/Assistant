#ifndef __INCLUDE_DEALER_H__
#define __INCLUDE_DEALER_H__

#include "CommandQ.h"

class MyDealer:IDealer
{
protected:
	CommandQ* dealerQueue;
	HANDLE dealerProcHandler;
	(void*) (*pDealerProc)(void*);

	static void* __stdcall dealerProc(void*);

	MyDealer(const MyDealer&);
public:
	explicit MyDealer(void*(*pDealerProc)(void*));
	virtual ~MyDealer(void);
	virtual bool sendAsyncMessage(void);
	virtual bool acceptAsyncMessage(pIAsyncMessage);
};

#endif