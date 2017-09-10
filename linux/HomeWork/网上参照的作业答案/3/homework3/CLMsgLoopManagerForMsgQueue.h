#ifndef CLMsgLoopManagerForMsgQueue_H
#define CLMsgLoopManagerForMsgQueue_H

#include "CLMessageLoopManager.h"

class CLMessageQueue;

class CLMsgLoopManagerForMsgQueue : public CLMessageLoopManager
{
public:
	/*
	pMsgQueueӦ�Ӷ��з��䣬�Ҳ�����ʾ����delete
	*/
	CLMsgLoopManagerForMsgQueue(CLMessageQueue *pMsgQueue);
	virtual ~CLMsgLoopManagerForMsgQueue();

protected:
	virtual CLStatus Initialize();
	virtual CLStatus Uninitialize();
	
	virtual CLMessage* WaitForMessage();

private:
	CLMsgLoopManagerForMsgQueue(const CLMsgLoopManagerForMsgQueue&);
	CLMsgLoopManagerForMsgQueue& operator=(const CLMsgLoopManagerForMsgQueue&);

private:
	CLMessageQueue *m_pMsgQueue;
};

#endif