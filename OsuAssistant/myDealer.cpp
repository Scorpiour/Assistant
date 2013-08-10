#include "Dealer.h"

using namespace std;

MyDealer::MyDealer(void*(*ptr)(void*))
{
	dealerQueue = new CommandQ();
	if(nullptr!=ptr)
	{
		pDealerProc = ptr;
	}
	else
	{
		throw L"Null Sub Thread Entry! You must provide a sub thread entry function to dealer, which prototype is :\nvoid* __stdcall dealerProc(void*) ";
	}
	if(nullptr == (dealerProcHandler = CreateThread(NULL,(DWORD)NULL,(LPTHREAD_START_ROUTINE)pDealerProc,(void*)this,(DWORD)NULL,NULL)))
	{
		throw L"Fail to start sub thread proc routine!";
	}
	
}

MyDealer::MyDealer(const MyDealer& R)
{
}

MyDealer::~MyDealer(void)
{
	if(nullptr!=dealerQueue)
	{
		delete[] dealerQueue;
	}
	if(nullptr!=dealerProcHandler)
	{
		TerminateThread(dealerProcHandler,0);
		CloseHandle(dealerProcHandler);
	}
}

bool MyDealer::sendAsyncMessage(void)
{
}

bool MyDealer::acceptAsyncMessage(pIAsyncMessage)
{
}
