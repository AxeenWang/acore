/**************************************************************************//**
 * @file	cwins_edit.cc
 * @brief	視窗操作 : 控制項 EditBox 類別，成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_edit.hh"

/**************************************************//**
 * @brief	建立 EditBox 控制項
 * @param	[in] pszName  EditBox 名稱
 * @param	[in] x        EditBox 起始位置 (對應父視窗左上座標 X)
 * @param	[in] y        EditBox 起始位置 (對應父視窗左上座標 Y)
 * @param	[in] wd       EditBox 寬度
 * @param	[in] ht       EditBox 高度
 * @param	[in] hParent  父視窗 Handle
 * @param	[in] idItem   控制項 ID
 * @return	@c BOOL
 *			- 函式運作成功傳回: TRUE
 *			- 函式運作失敗傳回: FALSE
******************************************************/
BOOL WsEdit::CreateFromWindowEx(LPCTSTR pszName, int x, int y, int wd, int ht, HWND hParent, int idItem)
{
	const BOOL err = FALSE;
	HMODULE hInst = ::GetModuleHandle(NULL);
	SaCTRLS ctrl;

	if ((NULL == hInst) || (NULL == hParent) || (idItem <= 0))
		return err;
	
	if (NULL == pszName) pszName = TEXT("");

	::memset((void*)&ctrl, 0, sizeof(SaCTRLS));
	ctrl.hParent = hParent;
	ctrl.emType = emCtrlEditBox;
	ctrl.pszName = pszName;
	ctrl.dwStyle = WS_TABSTOP;
	ctrl.dwExStyle = 0;
	ctrl.iPosx = x;
	ctrl.iPosy = y;
	ctrl.iWidth = wd;
	ctrl.iHeight = ht;
	ctrl.idItem = idItem;
	ctrl.fnWndProcess = NULL;
	return this->CreateUseHotCodes(&ctrl);
}
