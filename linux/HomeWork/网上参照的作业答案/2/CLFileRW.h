#ifndef CLFileRW_H
#define CLFileRW_H

#include <pthread.h>
#include "CLStatus.h"


class CLFileRW
{
public:
	static CLFileRW * GetInstance();//��ȡ�ļ���������
	static CLStatus FileWrite(const char *wMsg);//�ļ���д����
	static CLStatus FileRead(char *rMsg, int rLength);//�ļ��Ķ�����
	
	CLStatus FWrite(const char *wMsg);
	CLStatus FRead(char *rMsg, int rLength);
	CLStatus Flush();//ˢ�»���

private:
	static void OnProcessExit();//�����˳�ʱִ�иó���
	CLStatus WriteMsgToFile(const char *wMsg);
	static pthread_mutex_t *InitializeMutex();//��ʼ��������

private:
	CLFileRW(const CLFileRW&);
	CLFileRW& operator=(const CLFileRW&);

	CLFileRW();
	~CLFileRW();

private:
	int m_Fd;//�ļ���ʶ��
	pthread_mutex_t *m_pMutexForUseFile;//�ļ�ʹ�û�����
	
	static CLFileRW *m_pFile;//�ļ����������ָ��
	static pthread_mutex_t *m_pMutexForCreatingFile;//�����ļ�������

private:
	char *m_pBuffer;//ָ�򻺴�
	unsigned int m_nUsedBytesForBuffer;//��ʹ�õĻ���ĳ���

private:
	bool m_bFlagForProcessExit;//�����˳���־
	bool m_bFlagForLastReaded;//�ϴβ����Ƿ��Ƕ�
};

#endif
