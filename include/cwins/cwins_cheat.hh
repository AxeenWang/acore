/**************************************************************************//**
 * @file	cwins_cheat.hh
 * @brief	程序操作 - 作弊用記憶體操作類別
 * @author	Swang
 * @date	2002-01-15
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSCHEAT_HH__
#define __AXEEN_CWINS_CWINSCHEAT_HH__
#include "cwins_process.hh"

/**************************************************//**
 * @class	WsCheat
 * @brief	程序操作 - 目標程序記憶體操作
 * @author	Swang
 * @note	繼承 WsProcess，進行系統中指定程序搜尋與記憶體操作。 \n
 *			所有遊戲修改器就是使用此等或更高級的作法。
 *****************************************************/
class WsCheat : public WsProcess
{
public:
	WsCheat();
	virtual ~WsCheat();

	Bool SearchCheatProcess(LPCTSTR pszModule);
	SIZE_T ReadMemory(LPCVOID aBasePtr, LPVOID aBuffPtr, SIZE_T uSize);
	SIZE_T WriteMemory(LPVOID aBasePtr, LPCVOID aBuffPtr, SIZE_T uSize);
	Bool IsHooking();

protected:
	void ReleaseHook();
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsCheat::WsCheat()
	: WsProcess() {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsCheat::~WsCheat() { }

/**************************************************//**
 * @brief	讀取指定記憶體區資料
 * @param	[in]  aBasePtr	欲讀取目標位址
 * @param	[out] aBuffPtr	欲讀取資料存放位址
 * @param	[in]  uSize		欲讀取資料長度 (單位 Byte)
 * @return	@c SIZE_T
 *			- 讀取成功傳回: 實際讀取資料長度 (單位 byte)
 *			- 讀取失敗傳回: 0
 *			- 實際資料讀取長度與指定長度不同，使用 GetLastError() 去了解狀況
 *****************************************************/
inline SIZE_T WsCheat::ReadMemory(LPCVOID aBasePtr, LPVOID aBuffPtr, SIZE_T uSize)
{
	HANDLE hProcess = m_hProcess;
	SIZE_T cbReads = 0;

	if (hProcess != NULL && aBasePtr != NULL && aBuffPtr != NULL) {
		::ReadProcessMemory(hProcess, aBasePtr, aBuffPtr, uSize, &cbReads);
	}
	return cbReads;
}

/******************************************************//**
 * @brief	寫入指定記憶體區資料
 * @param	[out] aBasePtr	欲寫入目標位址
 * @param	[in]  aBuffPtr	欲寫入資料存放位址
 * @param	[in]  uSize	欲寫入資料長度 (單位 byte)
 * @return	@c SIZE_T
 *			- 寫入成功傳回: 實際寫入資料長度 (單位 byte)
 *			- 寫入失敗傳回: 0
 *			- 實際資料寫入長度與指定長度不同，使用 GetLastError() 去了解狀況
 *********************************************************/
inline SIZE_T WsCheat::WriteMemory(LPVOID aBasePtr, LPCVOID aBuffPtr, SIZE_T uSize)
{
	HANDLE hProcess = m_hProcess;
	SIZE_T cbWrite = 0;

	if (hProcess != NULL && aBasePtr != NULL && aBuffPtr != NULL) {
		::WriteProcessMemory(hProcess, aBasePtr, aBuffPtr, uSize, &cbWrite);
	}
	return cbWrite;
}

/**************************************************//**
 * @brief	是否與目標掛勾完成
 * @return	@c Bool	若已有掛勾連結目標程序時傳回 TRUE，否則傳回 FALSE
 *****************************************************/
inline Bool WsCheat::IsHooking() { return m_hProcess != NULL; }

/**************************************************//**
 * @brief	釋放與目標程序掛勾
 *****************************************************/
inline void WsCheat::ReleaseHook()
{
	SAFE_CLOSE_HANDLE(m_hProcess);
	m_idProcess = 0;
}

#endif	// !__AXEEN_CWINS_CWINSCHEAT_HH__
