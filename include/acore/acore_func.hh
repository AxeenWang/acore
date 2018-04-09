/**************************************************************************//**
 * @file	acore_func.hh
 * @brief	acore 通用函式 header 
 * @author	Swang
 * @date	2018-03-30
 * @date	2018-03-30
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_ACORE_ACOREFUNC_HH__
#define	__AXEEN_ACORE_ACOREFUNC_HH__
#include "acore_define.hh"

/**************************************************//**
 * @brief	結構測試範本
 * @param	[in,out] aPtr	ACOREEXAMPLE 指標
 * @return	@c int
 *	- 傳回1:		內容說明 1
 *	- 傳回2:		內容說明 2
 *	- 傳回3:		內容說明 3
 *	- 傳回-1:	內容說明 4
 * @note	這是用來練習 Doxygen 函式說明
 *****************************************************/
int TestStruct(LPSaACOREEXAMPLE aPtr);

/**************************************************//**
 * @brief	充填字元至指定區塊中
 * @param	[out]	destPtr		填充目標記憶體位址
 * @param	[in]	fillValue	欲充填的字元
 * @param	[in]	fillCount	欲充填的數量 (in byte)
 * @return	@c void*			傳回充填目標開頭位址
 *****************************************************/
void* amemset(void* destPtr, int fillValue, size_t fillCount);

/**************************************************//**
 * @brief	充填 0 到指定目標
 * @param	[out]	destPtr		填充目標記憶體位址
 * @param	[in]	count		欲充填的數量 (in byte)
 * @return	@c void*			傳回充填目標開頭位址
 *****************************************************/
inline void* zeromemory(void* destPtr, size_t count)
{
	return ::amemset(destPtr, 0, count);
}

#endif // !__AXEEN_ACORE_ACOREFUNC_HH__
