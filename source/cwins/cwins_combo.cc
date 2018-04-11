/**************************************************************************//**
 * @file	cwins_combo.cc
 * @brief	cwins 視窗操作 : 控制項 ComboBox 類別，成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_combo.hh"

/**************************************************//**
 * @brief	建立 ComboBox 控制項
 * @param	[in] x			ComboBox 起始位置 (對應父視窗左上座標 X)
 * @param	[in] y			ComboBox 起始位置 (對應父視窗左上座標 Y)
 * @param	[in] wd			ComboBox 寬度
 * @param	[in] ht			ComboBox 高度
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @return	@c Bool
 *			- 函式運作成功傳回: TRUE
 *			- 函式運作失敗傳回: FALSE
 * @note	使用 Windows API CreateWindowEx() 建立 Combox 控制項
 *****************************************************/
Bool WsCombo::CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem)
{
	const Bool err = FALSE;
	HMODULE	hInst = ::GetModuleHandle(NULL);
	SaCTRLS	ctrl;

	// 防呆
	if (hInst == NULL || hParent == NULL || idItem <= ZERO)
		return err;

	::memset((void*)&ctrl, 0, sizeof(SaCTRLS));
	ctrl.hParent = hParent;
	ctrl.emType = emCtrlComboBox;
	ctrl.pszName = NULL;
	ctrl.dwStyle = WS_TABSTOP | CBS_DROPDOWN;
	ctrl.dwExStyle = 0;
	ctrl.iPosx = x;
	ctrl.iPosy = y;
	ctrl.iWidth = wd;
	ctrl.iHeight = ht;
	ctrl.idItem = idItem; // conctrller item id
	ctrl.fnWndProcess = NULL;
	return this->CreateUseHotCodes(&ctrl);
}
