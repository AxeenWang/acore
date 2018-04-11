/**************************************************************************//**
 * @file	cwins_ctrls.cc
 * @brief	視窗操作 : 控制項操作項基底類別，成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_ctrls.hh"

/******************************************************//**
 * @brief	建立控制項，使用 HotCode 方式建立
 * @param	[in] ccPtr SaCTRLS 結構指標
 * @return	@c Bool
 *			- 建立成功傳回: TRUE
 *			- 建立失敗傳回: FALSE
 * @see		SaCTRLS 結構, EmCTRLS 列舉
 * @note	依據 SaCTRLS 結構定義內容建立對應控制項，控制項可見 EmCTRLS 所定義的內容
 *********************************************************/
Bool WsCtrls::CreateUseHotCodes(LPSaCTRLS ccPtr)
{
	const Bool err = FALSE;
	HMODULE	hInst = ::GetModuleHandle(NULL);
	HWND	hCtrl = NULL;
	HMENU	hMenu = NULL;
	DWORD	dwStyle = 0;
	DWORD	dwExStyle = 0;
	LPCTSTR	pszClass;
	IntQu	idItem;

	if (hInst == NULL							// 無效的模組 handle
		|| ccPtr == NULL						// 無效的 SaCTRLS 指標
		|| this->IsExist()						// 此類別物件已經存在視窗定義
		|| ccPtr->hParent == NULL				// 無效的父視窗操作 handle
		|| ccPtr->idItem < 0					// 無效的子控制項 id
		|| ccPtr->emType <= emCtrlPassStart		// 子控制項型態指定錯誤
		|| ccPtr->emType >= emCtrlPassEnd)		// 子控制項型態指定錯誤
		return err;

	// 取得 Controller 對應 class 名稱
	pszClass = this->GetControlClassName(ccPtr->emType);
	if (pszClass == NULL) return err;

	// 設定視窗 style
	if (ccPtr->emType == emCtrlDialogBox)
		dwStyle = ccPtr->dwStyle | WS_CLIPSIBLINGS | WS_VISIBLE;
	else
		dwStyle = ccPtr->dwStyle | WS_CLIPSIBLINGS | WS_VISIBLE | WS_CHILD;

	dwExStyle = ccPtr->dwExStyle;
	idItem = (IntQu)ccPtr->idItem;
	hMenu = (HMENU)idItem;

	// 建立控制項
	hCtrl = CreateWindowEx(
		dwExStyle,
		pszClass,
		ccPtr->pszName,
		dwStyle,
		ccPtr->iPosx,
		ccPtr->iPosy,
		ccPtr->iWidth,
		ccPtr->iHeight,
		ccPtr->hParent,
		hMenu, hInst,
		(LPVOID)ccPtr->pvUnknow);
	if (hCtrl == NULL) return err;

	// 保存各項數據
	m_hModule = hInst;
	m_hParent = ccPtr->hParent;
	m_hWnd = hCtrl;
	m_idItem = ccPtr->idItem;
	m_emCtrlsType = ccPtr->emType;

	// 使用自定義 Callback function ?
	if (ccPtr->fnWndProcess != NULL) {
		// 指定訊息處理函數
		m_fnWndProc = (WNDPROC)::GetWindowLongPtr(hCtrl, GWLP_WNDPROC);
		::SetWindowLongPtr(hCtrl, GWLP_WNDPROC, (LONG_PTR)ccPtr->fnWndProcess);
	}
	return hCtrl != NULL;
}

/******************************************************//**
 * @brief	建立控制項，Resource 模式
 * @param	[in] hParent		父視窗 HANDLE
 * @param	[in] idItem			控制項 ID
 * @param	[in] fnWndProcess	控制項 callback function address
 * @return	@c Bool
 *			- 建立成功傳回: TRUE
 *			- 建立失敗傳回: FALSE
 *********************************************************/
Bool WsCtrls::CreateUseResource(HWND hParent, int idItem, WNDPROC fnWndProcess)
{
	const Bool err = FALSE;
	HMODULE	hInst;
	HWND	hCtrl;

	if (this->IsExist() || hParent == NULL || idItem < 0)
		return err;

	hInst = ::GetModuleHandle(NULL);
	hCtrl = ::GetDlgItem(hParent, idItem);
	if (hInst == NULL || hCtrl == NULL)
		return err;

	m_hModule = hInst;
	m_hParent = hParent;
	m_hWnd = hCtrl;
	m_idItem = idItem;

	if (fnWndProcess != NULL) {
		// 保存當前預設訊息處理函式位址
		m_fnWndProc = (WNDPROC)::GetWindowLongPtr(hCtrl, GWLP_WNDPROC);

		// 設定新的訊息處理函式位址
		::SetLastError(0);
		if (::SetWindowLongPtr(hCtrl, GWLP_WNDPROC, (LONG_PTR)fnWndProcess) == 0) {
			return err;
		}
	}
	return hCtrl != NULL;
}

/**************************************************//**
 * @brief	結合資源檔或其他已存在的控制項
 * @param	[in] hCtrl	子項目視窗 handle
 * @param	[in] idItem	控制項 ID
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 ******************************************************/
Bool WsCtrls::CombineResource(HWND hCtrl, int idItem)
{
	HMODULE	hInst = ::GetModuleHandle(NULL);
	// 驗證控制項 Handle
	if (hCtrl != NULL && hInst != NULL) {
		this->m_hWnd = hCtrl;
		this->m_hParent = ::GetParent(hCtrl);
		this->m_hModule = hInst;
	}
	return hCtrl != NULL;
}

/******************************************************//**
 * @brief	取得控制項名稱
 * @param	[in] index	取得控制項 calss name 索引，參照 EmCTRLS
 * @return	@c LPCTSTR
 *			- 執行成功 傳回字串位址
 *			- 執行失敗 傳回 NULL
 *********************************************************/
LPCTSTR WsCtrls::GetControlClassName(EmCTRLS index)
{
	static const TCHAR* szClass[] = {
		TEXT("Pass Start"),			//!< 起始識別符
		TEXT("Button"),				//!< Button
		TEXT("ComboBox"),			//!< Combo Box
		TEXT("Edit"),				//!< Edit control.
		TEXT("ListBox"),			//!< List box.
		TEXT("MDIClient"),			//!< MDI client window.
		TEXT("ScrollBar"),			//!< Scroll bar.
		TEXT("Static"),				//!< Static control.

		TEXT("ComboLBox"),			//!< List box contained in a combo box.
		TEXT("DDEMLEvent"),			//!< Dynamic Data Exchange Management Library (DDEML) events.
		TEXT("Message"),			//!< Message-only window.
		TEXT("#32768"),				//!< Menu.
		TEXT("#32769"),				//!< Desktop window.
		TEXT("#32770"),				//!< Dialog box. (32770)
		TEXT("#32771"),				//!< Task switch window.
		TEXT("#32772"),				//!< Icon titles.

		TEXT("ToolbarWindow32"),	//!< Toolbar
		TEXT("tooltips_class32"),	//!< Tooltip
		TEXT("msctls_statusbar32"), //!< Status bar
		TEXT("SysTreeView32"),		//!< Tree view
		TEXT("SysListView32"),		//!< List view
		TEXT("SysAnimate32"),		//!< Animation
		TEXT("SysHeader32"),		//!< Header
		TEXT("msctls_hotkey32"),	//!< Hot-key
		TEXT("msctls_progress32"),	//!< Progress bar
		TEXT("RICHEDIT"),			//!< Rich edit
		TEXT("msctls_updown32"),	//!< Up-down
		TEXT("SysTabControl32"),	//!< Tab
		TEXT("Pass Error")			//!< 錯誤識別符
	};
	const int len = sizeof(szClass) / sizeof(szClass[0]);
	int idx = (int)index;

	if (idx >= len)
		return NULL;
	return (LPCTSTR)szClass[idx];
}
