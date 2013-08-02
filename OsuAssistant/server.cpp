#include "Communicate.h"
//#include <winsock.h>

#pragma comment(lib,"Ws2_32.lib")

void* __stdcall InitializeServerThread(void* initializer)
{
	pCmdLineInitializer ptr = (pCmdLineInitializer)initializer;

	while(true)
	{
		try
		{
			IPv6Server mainServer(ptr->pCmdQueue,"assistant server");
		}
		catch(tstring message)
		{		
			message.append(_T("\n\n Restart Server?"));

			if(IDOK==MessageBox(nullptr,message.c_str(),APP_NAME,MB_OKCANCEL))
			{
				continue;
			}
			else
			{
				break;
			}
		}
		catch(...)
		{
			break;
		}
		//Sleep(10000);
	}
	delete[] ptr;
	ExitThread((DWORD)NULL);
}

IPv6Server::IPv6Server(CmdQueue* queuePtr,const char* _hostName)
{
	pCmdQueue = queuePtr;

	if(!isCmdQueueReady())
	{
		throw _T("Fail to initialize main command queue");
	}
	
	char buffer[BUFF_SIZE];
	char* hostName;
	int family = AF_UNSPEC;
	int sockType = SOCK_STREAM;
	char* defaultPort = (char*)DEFAULT_PORT;  //(char*)(to_string(DEFAULT_PORT).c_str());
	char* address = nullptr;
	DWORD dwRetValue = 0;
	int iResult = 0;
	int fromLength = 0;
	int amountRead = 0;

	SOCKADDR_STORAGE from;
	WSADATA wsaData;
	
	ADDRINFO* pAddrInfo = nullptr;
	ADDRINFO* pAI = nullptr;

	if(nullptr!=_hostName || NULL!=_hostName)
	{
		hostName = (char*)_hostName;
	}
	else
	{
		hostName = nullptr;
	}

	iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iResult)
	{
		tstring errMessage = _T("WSA Startup Error - code: ");
		errMessage.append(to_wstring(WSAGetLastError()));
		WSACleanup();
		throw errMessage;
	}
	from.ss_family = (ADDRESS_FAMILY) family;

	while(true)
	{
		Sleep(999999);
	}
}

IPv6Server::~IPv6Server(void)
{
}

IPv6Server::IPv6Server(IPv6Server& RS)
{
	//Do nothing in copy constructor, also not allow to call
}

bool IPv6Server::isCmdQueueReady(void)const
{
	return (pCmdQueue!=nullptr&&pCmdQueue!=NULL);
}