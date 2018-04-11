/**************************************************************************//**
 * @file	cwins_cheat.cc
 * @brief	程序操作 : 作弊用記憶體操作類別，成員函式
 * @author	Swang
 * @date	2002-01-15
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_cheat.hh"

/**************************************************//**
 * @brief	搜尋指定目標程序
 * @param	[in] pszModule	程序模組名稱
 *			- 程序模組名稱即為可執行程式的檔案名稱，如 Foo.exe, Foo.dll
 *			- 程序模組名稱不必刻意注意大小寫，會自動進行辨認。
 * @return	@c Bool
 *			- 若出現指定目標或目標已存在則傳回 TRUE
 *			- 若目標不存在或發生錯誤，則傳回 FALSE
 *****************************************************/
Bool WsCheat::SearchCheatProcess(LPCTSTR pszModule)
{
	const	Bool err = FALSE;
	const	Bool eok = TRUE;
	HANDLE	hProcess = m_hProcess;
	DWORD	idSave = m_idProcess;
	DWORD	pid = this->SearchProcess(pszModule);

	// 已存在與目標程序掛勾
	if (hProcess != NULL) {
		if (pid == idSave) return eok;
	}

	// 尚未與目標掛勾
	this->ReleaseHook();
	// 搜尋指定目標程序，若目標程序已存在系統，則進行開啟目標程序進行掛勾
	if (pid != 0) {
		if ((hProcess = this->OpenProcess(pid)) != NULL) {
			m_hProcess = hProcess;
			m_idProcess = pid;
			return eok;
		}
	}
	return err;
}

