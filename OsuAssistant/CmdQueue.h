#ifndef __INCLUDE_CMDQUEUE_H__
#define __INCLUDE_CMDQUEUE_H__

#include "mainForm.h"

const UINT EMPTY_CMD_QUEUE = 0x0;
const UINT CREATE_MAIN_FORM = 0x1;
const UINT DESTROY_MAIN_FORM = 0x2;
const UINT WRITE_CMDQUEUE_ERROR = 0x3;
const UINT READ_CMDQUEUE_ERROR = 0x4;

class CmdQueue
{
protected:
	deque<UINT> cmd;
	HANDLE queueSema;

	void Lock(void);
	void Unlock(void);
public:
	explicit CmdQueue(void);
	explicit CmdQueue(CmdQueue&);

	virtual ~CmdQueue(void);

	UINT Dequeue_Front(void);
	UINT Dequeue_Back(void);

	bool Enqueue_Front(UINT);
	bool Enqueue_Back(UINT);

	UINT Length(void)const;
	bool isEmpty(void)const;
	
	void Clear(void);

};

#endif