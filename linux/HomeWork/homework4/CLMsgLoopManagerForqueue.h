#ifndef CLMsgLoopManagerForqueue_H
#define CLMsgLoopManagerForqueue_H

#include <string>
#include "CLMessageLoopManager.h"

class CLQueue;

class CLMsgLoopManagerForqueue : public CLMessageLoopManager
{
public:
	/*
	pMsgQueue��pMsgObserver��Ӧ�Ӷ��з��䣬�Ҳ�����ʾ����delete
	*/
	CLMsgLoopManagerForqueue(CLMessageObserver *pMsgObserver, const char* pstrThreadName);
	virtual ~CLMsgLoopManagerForqueue();

protected:
	virtual CLStatus Initialize();
	virtual CLStatus Uninitialize();
	
	virtual CLMessage* WaitForMessage();

private:
	CLMsgLoopManagerForqueue(const CLMsgLoopManagerForqueue&);
	CLMsgLoopManagerForqueue& operator=(const CLMsgLoopManagerForqueue&);

private:
	CLQueue* m_pMsgQueue;
	std::string m_strThreadName;
};

#endif