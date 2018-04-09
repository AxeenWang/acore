/**************************************************************************//**
 * @file	acore_func.cc
 * @brief	acore 通用函式
 * @author	Swang
 * @date	2018-03-30
 * @date	2018-03-30
 * @note	none
 *****************************************************************************/
#include "acore\acore_func.hh"

int TestStruct(LPSaACOREEXAMPLE aPtr)
{
	const int err = -1;
	const int eok = 1;
	if (aPtr == NULL) return err;

	struct SaACOREEXAMPLE ast;
	::memset(&ast, 0, sizeof(ast));
	ast.uData1 = aPtr->uRes1;
	ast.uData2 = aPtr->uRes2;
	aPtr->uData1 = aPtr->uRes1;
	aPtr->uData2 = aPtr->uRes2;
	return eok;
}

void * amemset(void * destPtr, int fillValue, size_t fillCount)
{
	#if defined(__ACORE_64__)

	size_t	blockIndex;
	size_t	blocks = fillCount >> 3;
	size_t	bytesLeft = fillCount - (blocks << 3);
	UINT64	cData = (UINT64)((UINT8)fillValue);

	cData |= ((cData << 8)
		| (cData << 16)
		| (cData << 24)
		| (cData << 32)
		| (cData << 40)
		| (cData << 48)
		| (cData << 56));

	UINT64*	a64Ptr = (UINT64*)destPtr;
	for (blockIndex = 0; blockIndex < blocks; blockIndex++)
		a64Ptr[blockIndex] = cData;
	if (!bytesLeft) return destPtr;

	blocks = bytesLeft >> 2;
	bytesLeft = bytesLeft - (blocks << 2);

	UINT32* a32Ptr = (UINT32*)&a64Ptr[blockIndex];
	for (blockIndex = 0; blockIndex < blocks; blockIndex++)
		a32Ptr[blockIndex] = (UINT32)cData;
	if (!bytesLeft) return destPtr;

	#else

	size_t	blockIndex;
	size_t	blocks = fillCount >> 2;
	size_t	bytesLeft = fillCount - (blocks << 2);
	UINT32	cData = (UINT32)((UINT8)fillValue);

	cData |= ((cData << 8)
		| (cData << 16)
		| (cData << 24));

	UINT32* a32Ptr = (UINT32*)destPtr;
	for (blockIndex = 0; blockIndex < blocks; blockIndex++)
		a32Ptr[blockIndex] = cData;
	if (!bytesLeft) return destPtr;

	#endif

	blocks = bytesLeft >> 1;
	bytesLeft = bytesLeft - (blocks << 1);

	UINT16* a16Ptr = (UINT16*)&a32Ptr[blockIndex];

	for (blockIndex = 0; blockIndex < blocks; blockIndex++)
		a16Ptr[blockIndex] = (UINT16)cData;
	if (!bytesLeft) return destPtr;

	UINT8* a8Ptr = (UINT8*)&a16Ptr[blockIndex];
	for (blockIndex = 0; blockIndex < bytesLeft; blockIndex++)
		a8Ptr[blockIndex] = (UINT8)cData;
	return destPtr;
}
