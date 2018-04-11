/**************************************************************************//**
 * @file	cwins_button.cc
 * @brief	視窗操作 : 控制項 Button 類別，成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_button.hh"

/**************************************************//**
 * @brief	範本, 建立 Button 控制項
 * @param	[in] pszName	按鈕名稱字串位址
 * @param	[in] x			按鈕起始位置 (對應父視窗左上座標 X)
 * @param	[in] y			按鈕起始位置 (對應父視窗左上座標 Y)
 * @param	[in] wd			按鈕寬度
 * @param	[in] ht			按鈕高度
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 * @note	使用 CreateWindowEx() 建立一個 Button
 *****************************************************/
Bool WsButton::CreateFromWindowEx(LPCTSTR pszName, int x, int y, int wd, int ht, HWND hParent, int idItem)
{
	const Bool	err = FALSE;
	HINSTANCE	hInst = ::GetModuleHandle(NULL);
	SaCTRLS		ctrl;

	if (hInst == NULL || hParent == NULL || idItem <= 0)
		return err;
	// 沒有設定控制項名稱
	if (pszName == NULL) pszName = TEXT("");

	memset((void*)&ctrl, 0, sizeof(SaCTRLS));
	ctrl.hParent = hParent;
	ctrl.emType = emCtrlButton;
	ctrl.pszName = pszName;
	ctrl.dwStyle = WS_TABSTOP | BS_PUSHBUTTON;
	ctrl.dwExStyle = 0;
	ctrl.iPosx = x;
	ctrl.iPosy = y;
	ctrl.iWidth = wd;
	ctrl.iHeight = ht;
	ctrl.idItem = idItem;
	ctrl.fnWndProcess = NULL;
	return this->CreateUseHotCodes(&ctrl);
}
