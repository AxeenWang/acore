/**************************************************************************//**
 * @file	cwins_tabs.hh
 * @brief	視窗操作 : 控制項 TAB 類別
 * @author	Swang
 * @date	2010-10-12
 * @date	2018-03-24
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSTAB_HH__
#define __AXEEN_CWINS_CWINSTAB_HH__
#include "cwins_ctrls.hh"

/**************************************************//**
 * @class	WsTabs
 * @brief	標籤、標籤頁控制項操作類別
 * @author	Swang
 * @note	繼承 WsCtrls
 *****************************************************/
class WsTabs : public WsCtrls
{
public:
	WsTabs();
	virtual ~WsTabs();

	Bool DeleteAllItem();
	Bool DeleteItem(int index);
	void DeSelectAll(Bool bDeSel);

	// 標籤位置相關
	int  GetCurselFocus();
	void SetCurselFocus(int index);
	int  GetCursel();
	int  SetCursel(int index);

	// 標籤操作
	Bool InsertItem(int index, LPTCITEM pttci);
	Bool InsertItem(int index, LPCTSTR psz);
	Bool GetItem(int index, TCITEM* pttci);
	Bool SetItem(int index, LPTCITEM pttci);
	int  GetItemCount();

	// 位置操作
	void AdjustRect(Bool bMode, RECT* prc);
	Bool GetItemRect(int index, RECT* prc);
	LRESULT SetItemSize(int wd, int ht);
	INT SetMinWidth(int wd);

	// 建立 Tab
	Bool CreateFromResource(HWND hTab, int idItem);
	Bool CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem);
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsTabs::WsTabs()
	: WsCtrls(emCtrlSysTabControl32) {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsTabs::~WsTabs() { }

/**************************************************//**
 * @brief	刪除所有標籤
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
*****************************************************/
inline Bool WsTabs::DeleteAllItem()
{
	// 傳送 TCM_DELETEALLITEMS 訊息
	// wParam 必須為零
	// lParam 必須為零
	return (Bool)this->SendMessage(TCM_DELETEALLITEMS, 0, 0);
}

/**************************************************//**
 * @brief	刪除一個標籤
 * @param	[in] index 項目索引值 (zero-base)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
*****************************************************/
inline Bool WsTabs::DeleteItem(int index)
{
	// 傳送 TCM_DELETEITEM 訊息
	// wParam 標籤的索引值 (zero-base)
	// lParam 必須為零
	return (Bool)this->SendMessage(TCM_DELETEITEM, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	重置標籤(書籤)狀態
 * @details MSDN 說明
 *			- Resets items in a tab control.
 *			- Clearing any that were set to the TCIS_BUTTONPRESSED state
 * @param	[in] bDeSel	指定重置標籤範圍
 *			- False, 所有的標籤將被清除狀態
 *			- True,  當前被選定的標籤將被清除狀態
*****************************************************/
inline void WsTabs::DeSelectAll(Bool bDeSel)
{
	// 傳送 TCM_DESELECTALL 訊息, TCIS_BUTTONPRESSED
	// wParam 標示要清除的範圍
	// lParam 必須為零
	this->SendMessage(TCM_DESELECTALL, (WPARAM)bDeSel, 0);
}

/**************************************************//**
 * @brief	取得目前被選定標籤 (焦點)
 * @return	@c int
 *			- 運作成功傳回：標籤索引 (zero-base)
 *			- 運作失敗傳回：-1 (錯誤)
 *****************************************************/
inline int WsTabs::GetCurselFocus()
{
	// 傳送 TCM_GETCURFOCUS 訊息
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(TCM_GETCURFOCUS, 0, 0);
}

/**************************************************//**
 * @brief	設定被選定標籤 (焦點)
 * @param	[in] index	標籤索引 (zero-base)
 *****************************************************/
inline void WsTabs::SetCurselFocus(int index)
{
	// 傳送 TCM_SETCURFOCUS 訊息
	// wParam 選定的標籤索引值 (zero-base)
	// lParam 必須為零
	this->SendMessage(TCM_SETCURFOCUS, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	取得被選定標籤
 * @return	@c int
 *			- 運作成功傳回：標籤索引 (zero-base)
 *			- 運作失敗傳回：-1 (錯誤)
 *****************************************************/
inline int WsTabs::GetCursel()
{
	// 傳送 TCM_GETCURSEL 訊息
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(TCM_GETCURSEL, 0, 0);
}

/**************************************************//**
 * @brief	設定指定標籤被選定
 * @param	[in] index	書籤索引值 (zero-base)
 * @return	@c int
 *			- 運作成功傳回：標籤索引 (zero-base)
 *			- 運作失敗傳回：-1 (錯誤)
 *****************************************************/
inline int WsTabs::SetCursel(int index)
{
	// 傳送 TCM_SETCURSEL 訊息
	// wParam 要被設定的標籤索引
	// lParam 必須為零
	return (int)this->SendMessage(TCM_SETCURSEL, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	插入一個標籤
 * @param	[in] index	要插入標籤的索引 (zero-base)
 * @param	[in] pttci	TCITEM 結構指標
 * @return  @c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsTabs::InsertItem(int index, LPTCITEM pttci)
{
	// 傳送 TCM_INSERTITEM 訊息
	// wParam 要插入的標籤索引
	// lParam TCITEM 結構指標
	return this->SendMessage(TCM_INSERTITEM, (WPARAM)index, (LPARAM)pttci) >= 0;
}

/**************************************************//**
 * @brief	取得指定標籤訊息
 * @param	[in]  index	標籤索引 (zero-base)
 * @param	[out] pttci TCITEM 結構指標
 * @return  @c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsTabs::GetItem(int index, TCITEM* pttci)
{
	// 傳送 TCM_GETITEM 訊息
	// wParam 欲取得資訊的標籤索引
	// lParam TCITEM 結構指標
	return (Bool)this->SendMessage(TCM_GETITEM, (WPARAM)index, (LPARAM)pttci);
}

/**************************************************//**
 * @brief	設定指定標籤訊息
 * @param	[in]  index	標籤索引 (zero-base)
 * @param	[out] pttci TCITEM 結構指標
 * @return  @c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsTabs::SetItem(int index, LPTCITEM pttci)
{
	// 傳送 TCM_SETITEM 訊息
	// wParam 欲設定資訊的標籤索引
	// lParam TCITEM 結構指標
	return (Bool)this->SendMessage(TCM_SETITEM, (WPARAM)index, (LPARAM)pttci);
}

/**************************************************//**
 * @brief	取得標籤數量
 * @return	@c int
 *			- 執行成功傳回: 標籤數量
 *			- 執行失敗傳回: 0
 *****************************************************/
inline int WsTabs::GetItemCount()
{
	// 傳送 TCM_GETITEMCOUNT 訊息
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(TCM_GETITEMCOUNT, 0, 0);
}

/**************************************************//**
 * @brief	調整標籤頁面工作區塊尺寸
 * @param	[in]	 bMode	採用模式
 * @param	[in,out] prc	RECT 結構位址指標 
 * @note	bMode 會設定為 False，採用使窗對應舉行區域。
 *			- True : Specifies a display rectangle and receives the corresponding window rectangle
 *			- False: specifies a window rectangle and receives the corresponding display area.
 *****************************************************/
inline void WsTabs::AdjustRect(Bool bMode, RECT* prc)
{
	// 傳送 TCM_ADJUSTRECT 訊息
	// wParam 使用模式
	//	- True => lParam specifies a display rectangle and receives the corresponding window rectangle
	//	- False=> lParam specifies a window rectangle and receives the corresponding display area.
	// lParam RECT 結構指標
	this->SendMessage(TCM_ADJUSTRECT, (WPARAM)bMode, (LPARAM)prc);
}

/**************************************************//**
 * @brief	取得標籤邊界尺寸
 * @param	[in]  index	書籤索引 (zero-base)
 * @param	[out] prc	RECT 結構指標
 * @return	@c int
 *			- 執行成功傳回: True
 *			- 執行失敗傳回: False
 *****************************************************/
inline Bool WsTabs::GetItemRect(int index, RECT* prc)
{
	// 傳送 TCM_GETITEMRECT 訊息
	// wParam 標籤索引
	// lParam RECT 結構指標
	return (Bool)this->SendMessage(TCM_GETITEMRECT, (WPARAM)index, (LPARAM)prc);
}

/**************************************************//**
 * @brief	設定標籤尺寸
 * @details	Setsthe width and height of tabs in a fixed-width or owner-drawn tab control.
 * @param	[in] wd	寬度
 * @param	[in] ht	高度
 * @return	@c LRESULT	舊的標籤尺寸資訊 HIWORD 為高度、LOWORD 為寬度
 *****************************************************/
inline LRESULT WsTabs::SetItemSize(int wd, int ht)
{
	LPARAM lParam = ht;
	lParam = (lParam << 16) | wd;
	// 傳送 TCM_SETITEMSIZE 訊息
	// wParam	必須為零
	// lParam	頁簽尺寸 (HIWORD = 高) (LOWORD = 寬)
	return (int)this->SendMessage(TCM_SETITEMSIZE, 0, lParam);
}

/**************************************************//**
 * @brief	設定標籤最小寬度
 * @param	[in] wd	標籤寬度 (in pixel)
 * @return	@c INT
 *			- An INT value that represents the previous minimum tab width.
 * @note	MSDN 說明
 *			- Minimum width to be set for a tab control item.
 *			- If this parameter is set to -1, the control will use the default tab width.
 *****************************************************/
inline INT WsTabs::SetMinWidth(int wd)
{
	// 傳送 TCM_SETMINTABWIDTH 訊息
	// wParam 必須為零
	// lParam 頁簽項目最小寬度，如果此參數為-1，則使用預設寬度。
	return (INT)this->SendMessage(TCM_SETMINTABWIDTH, 0, (LPARAM)wd);
}

/**************************************************//**
 * @brief	結合資源檔或其他已存在的 Tab 控制項
 * @param	[in] hTab	子項目視窗 handle
 * @param	[in] idItem	控制項 ID
 * @return	@c Bool
 *			- 操作成功傳回: True
 *			- 操作失敗傳回: False，調用 GetLastError 取得錯誤訊息
 ******************************************************/
inline Bool WsTabs::CreateFromResource(HWND hTab, int idItem) { return this->CombineResource(hTab, idItem); }

#endif // !__AXEEN_CWINS_CWINSTAB_HH__
