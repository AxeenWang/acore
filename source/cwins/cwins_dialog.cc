/**************************************************************************//**
 * @file	cwins_dialog.cc
 * @brief	視窗操作 : 控制項 Dialog 類別，成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_dialog.hh"

/**************************************************//**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details	靜態函數，控制項訊息處理
 * @param	[in] hWnd		視窗 Handle
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c INT_PTR		運作結果返回資訊
 * @note	DialogProc 函示為靜態函示，作為建立 Dialog callback function
 *****************************************************/
INT_PTR WsDialog::DialogProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	SaDIALOGPARAM*	ddPtr = NULL;	// user parameter
	WsDialog*		ddObj = NULL;	// dialog object

	// is dialog initialized message?
	if (uMessage == WM_INITDIALOG) {
		// save user data using "GWLP_USERDATA" mode
		ddPtr = (SaDIALOGPARAM*)lParam;
		ddObj = (WsDialog*)ddPtr->pvDialog;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ddObj);
		ddObj->m_hWnd = hWnd;
		lParam = (LPARAM)ddPtr->pvParam;
	}

	// get user saved data form "GWLP_USERDATA" mode
	if ((ddObj = (WsDialog*)::GetWindowLongPtr(hWnd, GWLP_USERDATA)) == NULL)
		return 0;
	// transfer window message
	return ddObj->MessageDispose(uMessage, wParam, lParam);
}

/**************************************************//**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details 虛擬函數，訊息處理函數
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c INT_PTR		訊息處理結果
 * @note	MessageDisopse 為虛擬函示，由衍生者重載重新定義動作內容
 * @warning	當使用 EndDialog 結束 Dialog 之前，必須先調用 InDestroyWindow 成員函式。
 * @warning 否則必須手動釋放已建立之物件與記憶體配置，否則必造成 memory leak。
 *****************************************************/
INT_PTR WsDialog::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_INITDIALOG:
		break;
	case WM_CLOSE:
		::EndDialog(m_hWnd, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

/**************************************************//**
 * @brief	建立 Dialog 控制項
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @param	[in] pvUnknow	額外參數指標 (使用者可利用)
 * @param	[in] bModule	是否建立 Module Dialog
 *			- 預設為 FALSE 建立 Child Dialog
 *			- 設定為 TRUE 建立 Module Dialog
 * @return	@c BOOL
 *			- 函式運作成功傳回: TRUE
 *			- 函式運作失敗傳回: FALSE
 * @details 使用資源檔(Resource)定義的 Dialog 資源建立
 *****************************************************/
BOOL WsDialog::CreateFromResource(HWND hParent, int idItem, void * pvUnknow, BOOL bModule)
{
	const BOOL err = FALSE;
	HINSTANCE hInst = ::GetModuleHandle(NULL);	// 取得程序模組 Handle
	HWND hWnd = m_hWnd;
	LPTSTR pszTemplate;
	SaDIALOGPARAM ddPtr;

	// 若 hWnd != NULL 表示物件內容已存在
	if (hInst == NULL || hWnd != NULL)
		return err;

	// 控制項 ID 不能小於或等於 0
	if (idItem <= 0) return err;

	// 使用 MAKEINTRESOURCE 巨集轉換控制項 ID
	// 造出 DialogBoxParam、CreateDialogParam 函數所需資源ID 字串
	pszTemplate = MAKEINTRESOURCE(idItem);

	// 保存相關資料
	m_hModule = hInst;
	m_hParent = hParent;
	ddPtr.pvDialog = (void*)this;
	ddPtr.pvParam = pvUnknow;

	if (bModule) {
		// DialogBoxParam 若運作失敗將傳回 -1
		return ::DialogBoxParam(hInst, pszTemplate, hParent, (DLGPROC)WsDialog::DialogProc, (LPARAM)&ddPtr) != -1;
	}
	else {
		// 若運作失敗將傳回 NULL，若運作成功傳回 Dialog Handle
		return ::CreateDialogParam(hInst, pszTemplate, hParent, (DLGPROC)WsDialog::DialogProc, (LPARAM)&ddPtr) != NULL;
	}
}

/**************************************************//**
 * @brief	建立 Dialog 控制項
 * @param	[in] x			起始座標 X
 * @param	[in] y			起始座標 Y
 * @param	[in] wd			寬度
 * @param	[in] ht			高度
 * @param	[in] hParent	父視窗操作 handle
 * @param	[in] idItem		視窗或控制項 ID
 * @param	[in] pvUnknow	自定義資料
 * @param	[in] bModule	是否建立 Module Dialog
 *			- 預設為 FALSE 建立 Child Dialog
 *			- 設定為 TRUE 建立 Module Dialog
 * @return	@c BOOL
 *			- 函式運作成功傳回: TRUE
 *			- 函式運作失敗傳回: FALSE
 * @details 使用 CreateWindowEx() 建立 Dialog
 *****************************************************/
BOOL WsDialog::CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem, void* pvUnknow, BOOL bModule)
{
	const int err = FALSE;
	const TCHAR* pszName = TEXT("DialogEx");
	HINSTANCE hInst = ::GetModuleHandle(NULL);
	SaCTRLS ctrl;
	SaDIALOGPARAM ddPtr;

	memset((void*)&ctrl, 0, sizeof(SaCTRLS));
	ctrl.hParent = hParent;
	ctrl.emType = emCtrlDialogBox;
	ctrl.pszName = pszName;
	
	if (bModule) ctrl.dwStyle = DS_MODALFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CAPTION | WS_SYSMENU;
	else ctrl.dwStyle = WS_CHILD;

	ctrl.dwExStyle = 0;
	ctrl.iPosx = x;
	ctrl.iPosy = y;
	ctrl.iWidth = wd;
	ctrl.iHeight = ht;
	ctrl.idItem = idItem;
	ctrl.fnWndProcess = (WNDPROC)WsDialog::DialogProc;
	
	ddPtr.pvDialog = (void*)this;
	ddPtr.pvParam = pvUnknow;
	ctrl.pvUnknow = (void*)&ddPtr;
	return this->CreateUseHotCodes(&ctrl);
}
