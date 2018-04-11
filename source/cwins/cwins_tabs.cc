/**************************************************************************//**
 * @file	cwins_tabs.cc
 * @brief	視窗操作 : 控制項 TAB 類別，成員函式
 * @author	Swang
 * @date	2010-10-12
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_tabs.hh"

/**************************************************//**
 * @brief	插入一個標籤 (文字標籤)
 * @param	[in] index	標籤索引 (zero-base)
 * @param	[in] psz	文字緩衝區
 * @return  @c Bool
 *			- 運作成功傳回: TRUE
 *			- 運作失敗傳回: FALSE
 *****************************************************/
Bool WsTabs::InsertItem(int index, LPCTSTR psz)
{
	const Bool err = FALSE;

    TCITEM tci;
	TCHAR szText[MAX_PATH];
	
	if (psz == NULL) return err;
	::lstrcpy(szText, psz);
    tci.mask = TCIF_TEXT | TCIF_IMAGE; 
    tci.iImage = -1; 
	tci.pszText = szText;
    return this->InsertItem(index, &tci);
}

/**************************************************//**
 * @brief	快速建立 Tab 控制項
 * @param	[in] x			起始位置 X
 * @param	[in] y			起始位置 Y
 * @param	[in] wd			寬度
 * @param	[in] ht			高度
 * @param	[in] hParent	父視窗操作 handle
 * @param	[in] idItem		ID
 * @return	@c Bool
 *			- 執行成功傳回: TRUE
 *			- 執行失敗傳回: FALSE
 *****************************************************/
Bool WsTabs::CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem)
{
	const Bool err = FALSE;
	SaCTRLS ctrl;	// Structure for controller
	RECT rc;

	// 防呆驗證
	if (hParent == NULL || idItem == 0) return err;

	// 初始 DMCWNDCTRLS 內容
	::memset((void*)&ctrl, 0, sizeof(SaCTRLS));

	// 取得父視窗邊界資訊
	::GetClientRect(hParent, &rc);

	// 指定寬度為零 ==> 代表使用父視窗工作區寬度
	if (wd == 0) wd = (int)rc.right - rc.left;

	// 指定高度為零 ==> 代表使用父視窗工作區高度
	if (ht == 0) ht = (int)rc.bottom - rc.top;

	// 建立 DMCWNDCTRLS 內容
	ctrl.hParent = hParent;
	ctrl.emType = emCtrlSysTabControl32;
	ctrl.pszName = NULL;
	ctrl.dwStyle = 0;
	ctrl.dwExStyle = 0;
	ctrl.iPosx = x;
	ctrl.iPosy = y;
	ctrl.iWidth = wd;
	ctrl.iHeight = ht;
	ctrl.idItem = idItem; // conctrller item id
	ctrl.fnWndProcess = NULL;
	return this->CreateUseHotCodes(&ctrl);
}
