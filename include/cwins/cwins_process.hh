/**************************************************************************//**
 * @file	cwins_process.hh
 * @brief	程序操作基底類別
 * @author	Swang
 * @date	2002-01-15
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSPROCESS_HH__
#define __AXEEN_CWINS_WINSPROCESS_HH__
#include "cwins_define.hh"

/**************************************************//**
 * @class	WsProcess
 * @brief	程序操作基底類別
 * @author	Swang
 * @note	取得於系統運行中之程序模組
 *****************************************************/
class WsProcess
{
public:
	WsProcess();
	virtual ~WsProcess();
	DWORD	SearchProcess(LPCTSTR pszModule);
	HANDLE  OpenProcess(DWORD dwProcessID);
	HANDLE	GetProcessHandle();
	DWORD	GetProcessID();

private:
	/******************************************************//**
	 * @brief	比對字串
	 * @param	[in] pszDst	第一個字串位址
	 * @param	[in] pszSrc	第二個字串位址
	 * @param	[in] bCase	比對時是否區分字元大小寫 (True = 區分大小寫)
	 * @return	@c Bool
	 *			- 比對結果相符傳回: True
	 *			- 比對結果不符傳回: False
	 *********************************************************/
	Bool StrCompare(LPCTSTR pszDst, LPCTSTR pszSrc, Bool bCase);

	/******************************************************//**
	 * @brief	轉換成大寫，將字串內容轉為大寫
	 * @param	[in,out] psz 字串位址(指標)
	 *********************************************************/
	void StrUpper(LPTSTR psz);

	/******************************************************//**
	 * @brief	轉換成小寫，將字串內容轉為小寫
	 * @param	[in,out] psz 字串位址(指標)
	 *********************************************************/
	void StrLower(LPTSTR psz);

protected:
    HANDLE  m_hProcess;		//!< Handle of Process
    DWORD   m_idProcess;	//!< ProcessID
};

/******************************************************//**
 * @brief	建構式
 *********************************************************/
inline WsProcess::WsProcess()
	: m_hProcess(Null),
	m_idProcess(0) {
}

/******************************************************//**
 * @brief	解構式
 *********************************************************/
inline WsProcess::~WsProcess()
{
	SAFE_CLOSE_HANDLE(m_hProcess);
	m_idProcess = 0;
}

/**************************************************//**
 * @brief	取得已連接的 Process Handle
 * @return	@c HANDLE	傳回目標模組的程序運作 handle
 *****************************************************/
inline HANDLE WsProcess::GetProcessHandle() { return m_hProcess; }

/**************************************************//**
 * @brief	取得已連接的 Process ID
 * @return	@c DWORD	傳回目標模組的程序運作 ID
 *****************************************************/
inline DWORD WsProcess::GetProcessID() { return m_idProcess; }


#endif  // !__AXEEN_CWINS_CWINSPROCESS_HH__
