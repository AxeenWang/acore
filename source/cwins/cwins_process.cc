/**************************************************************************//**
 * @file	cwins_process.cc
 * @brief	程序操作基底類別，成員函式
 * @author	Swang
 * @date	2002-01-15
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_process.hh"

/**************************************************//**
 * @brief	搜尋指定目標程序
 * @param	[in] pszModule	指定程序名稱，如： foo.exe, foo.dll
 * @return	@c DWORD
 *			- 運作成功傳回: 目標模組的程序運作 ID
 *			- 運作失敗傳回: 0
 * @note	使用方式
 *			- 程序模組名稱即為可執行程式的檔案名稱，如 Foo.exe, Foo.dll
 *			- 程序模組名稱不必刻意注意大小寫，會自動進行辨認。
 *			- 若搜尋到指定程序於系統中運行，則傳回該程序運作之 ID
 *****************************************************/
DWORD WsProcess::SearchProcess(LPCTSTR pszModule)
{
	const DWORD errProcessID = 0;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// 採用快照方式，取得系統正在運作的全部程序。
	hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return errProcessID;

	// 在使用 結構前，必須先指定其長度 !!重要步驟
	::memset(&pe32, 0, sizeof(PROCESSENTRY32));
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// 取得第一個執行中程序，若失敗就退出
	if (!::Process32First(hProcessSnap, &pe32))
		return errProcessID;

	// 開始依序取得系統中所有執行的程式
	do {
		// 比對指定搜尋程式名稱
		if (this->StrCompare(pszModule, pe32.szExeFile, FALSE)) {
			// 找到目標程序, 回傳運行程序ID
			return pe32.th32ProcessID;
		}
	} while (::Process32Next(hProcessSnap, &pe32));

	return errProcessID;
}

/**************************************************//**
 * @brief	開啟目標程序
 * @param	[in] dwProcessID	運行中程序 ID
 * @return	@c HANDLE
 *			- 運作成功傳回: 模組程序運作 HANDLE
 *			- 運作失敗傳回: NULL
 * @note	使用系統運行ID 開啟指定之程序，即可針對開程序進行各項操作，如...
 *			- 對該程序記憶體讀寫 (遊戲作弊常用)
 *			- 對該程序模組進行操作，如取得運作式窗，並針對該視窗傳送命令
 *****************************************************/
HANDLE WsProcess::OpenProcess(DWORD dwProcessID)
{
	HANDLE hProcess = NULL;

	// 使用程序運作ID 進行取得程序運作 HANDLE
	if (dwProcessID != 0) {
		hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
		if (hProcess != NULL) {
			m_hProcess = hProcess;
			m_idProcess = dwProcessID;
		}
	}
	return hProcess;
}

/**************************************************//**
 * @brief	比對字串
 * @param	[in] pszDst	第一個字串位址
 * @param	[in] pszSrc	第二個字串位址
 * @param	[in] bCase	比對時是否區分字元大小寫 (TRUE = 區分大小寫)
 * @return	@c BOOL
 *			- 比對結果相符傳回: TRUE
 *			- 比對結果不符傳回: FALSE
 *****************************************************/
BOOL WsProcess::StrCompare(LPCTSTR pszDst, LPCTSTR pszSrc, BOOL bCase)
{
	TCHAR szDst[MAX_PATH];
	TCHAR szSrc[MAX_PATH];

	// 防呆，防例外處理
	if (pszDst == NULL || pszSrc == NULL)
		return FALSE;

	// 比對時區分大小寫
	if (bCase) return lstrcmp(pszDst, pszSrc) == 0;

	// 進行字串大小寫轉換後再比對
	lstrcpy(szDst, pszDst);
	lstrcpy(szSrc, pszSrc);
	StrUpper(szDst);
	StrUpper(szSrc);
	return lstrcmp(szDst, szSrc) == 0;
}

/**************************************************//**
 * @brief	轉換成大寫，將字串內容轉為大寫
 * @param	[in,out] psz 字串位址(指標)
 *****************************************************/
void WsProcess::StrUpper(LPTSTR psz)
{
	int i, len;

	if (psz == NULL) return;
	len = lstrlen(psz);
	for (i = 0; i < len; i++) {
		psz[i] = (TCHAR)_totupper(psz[i]);
	}
}

/**************************************************//**
 * @brief	轉換成小寫，將字串內容轉為小寫
 * @param	[in,out] psz 字串位址(指標)
 *****************************************************/
void WsProcess::StrLower(LPTSTR psz)
{
	int i, len;
	
	if (psz == NULL) return;
	len = lstrlen(psz);
	for (i = 0; i < len; i++) {
		psz[i] = (TCHAR)_totlower(psz[i]);
	}
}
