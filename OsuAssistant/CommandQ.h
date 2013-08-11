#ifndef __INCLUDE_COMMANDQ_H__
#define __INCLUDE_COMMANDQ_H__

#include "main.h"
#include <deque>

class CommandQ:ICommandQueue
{
protected:
	HANDLE queueSema;
	std::deque<pIAsyncMessage> innerQueue;
	CommandQ(const CommandQ&);
public:
	explicit CommandQ(void);

	virtual ~CommandQ(void);

	virtual bool Enqueue_Back(pIAsyncMessage);
	virtual bool Enqueue_Front(pIAsyncMessage);

	virtual pIAsyncMessage Dequeue_Back(void);
	virtual pIAsyncMessage Dequeue_Front(void);

	virtual pIAsyncMessage Peek_Back(void);
	virtual pIAsyncMessage Peek_Front(void);

	virtual bool Clear(void);
	virtual UINT Size(void)const;
	virtual bool isEmpty(void)const;
};

#endif