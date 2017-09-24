#ifndef CLIOVectors_H
#define CLIOVectors_H

#include <list>
#include <sys/uio.h>
#include <vector>
#include "CLStatus.h"

#define IOVECTOR_DELETE 0
#define IOVECTOR_STAIN 1
#define IOVECTOR_NON_DELETE 2

class CLIteratorForIOVectors;

struct SLIOVectorItem
{
	struct iovec IOVector;
	bool bDelete;
};

class CLIOVectors
{
	friend class CLIteratorForIOVectors;

public:
	CLIOVectors();
	virtual ~CLIOVectors();

	CLStatus PushBack(char *pBuffer, size_t nBufferLength, bool bDeleted = false);
	CLStatus PushFront(char *pBuffer, size_t nBufferLength, bool bDeleted = false);

	CLStatus PopBack(char **ppBuffer, size_t *pnBufferLength);
	CLStatus PopFront(char **ppBuffer, size_t *pnBufferLength);

	void GetIterator(unsigned int Index, CLIteratorForIOVectors& Iter);
	CLStatus WriteBlock(CLIteratorForIOVectors& Iter, char *pBuf, unsigned Length);
	CLStatus ReadBlock(CLIteratorForIOVectors& Iter, char *pBuf, unsigned Length);

	CLStatus WriteBlock(unsigned int Index, char *pBuf, unsigned int Length);
	CLStatus ReadBlock(unsigned int Index, char *pBuf, unsigned int Length);

	CLStatus PushBackRangeToAIOVector(CLIOVectors& IOVectors, unsigned int Index, unsigned int Length, int DeleteAction = IOVECTOR_NON_DELETE);
	CLStatus PushBackRangeToAIOVector(CLIOVectors& IOVectors, CLIteratorForIOVectors& Iter, unsigned int Length, int DeleteAction = IOVECTOR_NON_DELETE);

	CLStatus FindIOVectors(CLIOVectors& IOVectors, bool bDelete);

	CLStatus PushBackIOVector(CLIOVectors& IOVectors, int DeleteAction = IOVECTOR_STAIN);

	void DifferenceBetweenIOVectors(CLIOVectors& Operand, CLIOVectors& Difference);

	bool IsRangeOverlap(iovec& Range);

	size_t Size();
	int GetNumberOfIOVec();
	iovec *GetIOVecArray();

	void Clear();
	CLStatus GetIndex(CLIteratorForIOVectors& Iter, unsigned int& Index);

private:
	bool IsRangeInAIOVector(char *pAddr, unsigned int Length, std::list<SLIOVectorItem>::iterator& CurrentIter);

	void GetIndexPosition(unsigned int Index, char **ppAddrForIndex, std::list<SLIOVectorItem>::iterator *pIter);

	CLStatus TransferBlock(bool bWriteIntoIOVectors, char *pAddrInIOVector, std::list<SLIOVectorItem>::iterator& CurrentIter, char *pBuf, unsigned int Length, char **ppEndAddrInIOVector = 0);
	CLStatus TransferBlockByIndex(bool bWriteIntoIOVectors, unsigned int Index, char *pBuf, unsigned int Length);
	CLStatus TransferBlockByIterator(bool bWriteIntoIOVectors, CLIteratorForIOVectors& Iter, char *pBuf, unsigned Length);

	void DifferenceBetweenRanges(iovec& Range1, iovec& Range2, std::vector<iovec>& vResults);
	void DifferenceBetweenRangeAndIOVector(iovec& Range, CLIOVectors& IOVector, std::vector<iovec>& vResult);

	CLStatus PushBufferAtFrontOrBack(char *pBuffer, size_t nBufferLength, bool bDeleted, bool bAtFront);
	CLStatus PopBufferAtFrontOrBack(char **ppBuffer, size_t *pnBufferLength, bool bAtFront);

private:
	CLIOVectors(const CLIOVectors&);
	CLIOVectors& operator=(const CLIOVectors&);

private:
	std::list<SLIOVectorItem> m_IOVectors;
	size_t m_nDataLength;
};

#endif