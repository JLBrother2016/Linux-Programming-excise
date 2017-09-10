#ifndef CLMessageQueue_H
#define CLMessageQueue_H

#include "CLStatus.h"
#include "CLMutex.h"
#include "CLEvent.h"

#define LENGTH 10
class CLMessage;

/*
�������̰߳�ȫ��
��Ҫ��CLMsgLoopManagerForMsgQueue ���ʹ�ã�����������Ҫ�Ӷ��з��䣬�Ҳ��õ���delete
*/
class CLMessageQueue
{
public:
	/*
	���캯����������������ʱ�����׳��ַ������͵��쳣
	*/
	CLMessageQueue();
	virtual ~CLMessageQueue();

public:
	CLStatus PushMessage(CLMessage * pMessage);
	CLMessage* GetMessage();

private:
	CLStatus Push(CLMessage * pMessage);
	CLMessage* Pop();

private:
	CLMessageQueue(const CLMessageQueue&);
	CLMessageQueue& operator=(const CLMessageQueue&);

public:
	CLMessage *my_Queue[LENGTH];
	int start,tail,count;
	CLMutex m_Mutex;
	CLEvent m_Event;
};

#endif
