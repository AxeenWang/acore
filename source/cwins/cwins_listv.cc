/**************************************************************************//**
 * @file	cwins_listv.cc
 * @brief	視窗操作 : 控制項 ListView 類別，成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_listv.hh"

/**************************************************//**
 * @brief	插入一個欄位 (Column)
 * @param	[in] index	欄位項目索引 (zero-base)
 * @param	[in] wd		指定 Column 寬度
 * @param	[in] align	指定對齊方式
 * @param	[in] psz	指定 Column 顯示文字位址
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::InsertColumn(int index, int wd, int align, LPTSTR psz)
{
    const static int aiAssign[] = { LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_CENTER, LVCFMT_LEFT };
    LVCOLUMN lvc;

    // zero struct's Members
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
	if (align >= LVCOLUMN_ALIGN_PASSEND) align = LVCOLUMN_ALIGN_LEFT;

	// Setting properties Of members
	lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT; // LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.fmt = aiAssign[align];
	lvc.pszText = psz;
    lvc.cchTextMax = ::lstrlen(lvc.pszText);
    lvc.cx = wd;

    // LVM_INSERTCOLUMN 訊息處理，若執行成功將傳回一個索引直，若執行失敗將傳回 -1
    return this->SendMessage(LVM_INSERTCOLUMN, (WPARAM)index, (LPARAM)&lvc) != -1;
}

/**************************************************//**
 * @brief	刪除所有的欄位(Column)
 *****************************************************/
void WsListv::DeleteAllColumn()
{
	int count = this->GetColumnCount();
	if (count > 0) {
		for (int colIndex = 0; colIndex < count; ++colIndex) {
			this->DeleteColumn(0);
		}
	}
}

/**************************************************//**
 * @brief	取得指定欄位(Column)文字內容
 * @param	[in]  index	欄位項目索引 (zero-base)
 * @param	[out] psz	保存取得文字緩衝區
 * @param	[in]  cch	要取得字串長度 (in TCHAR)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::GetColumn(int index, LPTSTR psz, int cch)
{
    LVCOLUMN lvc;

    if (Null == psz) return False;
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT;
	lvc.pszText = psz;
    lvc.cchTextMax = cch;
    return (Bool)this->SendMessage(LVM_GETCOLUMN, (WPARAM)index, (LPARAM)&lvc);
}

/**************************************************//**
 * @brief	設定指定欄位(Column)文字內容
 * @param	[in] index	欄位項目索引 (zero-base)
 * @param	[in] psz	欲設定文字緩衝區
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::SetColumn(int index, LPTSTR psz)
{
    LVCOLUMN lvc;

	if (Null == psz) return False;
    ::memset((void*)&lvc, 0, sizeof(LVCOLUMN));
    lvc.mask = LVCF_TEXT;
	lvc.pszText = psz;
    return (Bool)this->SendMessage(LVM_SETCOLUMN, (WPARAM)index, (LPARAM)&lvc);
}

/**************************************************//**
 * @brief	插入一個項目(Item) - 文字模式
 * @param	[in] index	項目索引值   (zero-base)
 * @param	[in] isubs	項目子欄位索引(zero-base)
 * @param	[in] psz	字串緩衝區
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::InsertItem(int index, int isubs, LPTSTR psz)
{
    LVITEM lvi;

	if (Null == psz) return False;
    // Setting properties Of members
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;   // LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = index;      // choose item
    lvi.iSubItem = isubs;   // choose sub item
	lvi.pszText = psz;      // set text
    lvi.cchTextMax = ::lstrlen(lvi.pszText);

	// LVM_INSERTITEM
	// wParam 必須為零
	// lParam LVITEM 結構指標
	// 若運作失敗將傳回 -1
    return this->SendMessage(LVM_INSERTITEM, 0, (LPARAM)&lvi) != -1;
}

/**************************************************//**
 * @brief	設定指定項目(Item)被選中
 * @param	[in] index		項目索引值 (zero-base)
 * @param	[in] bSelect
 *			- True  設定被選擇
 *			- False 取消被選擇
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::SetSelectItem(int index, Bool bSelect)
{
    LVITEM lvi;
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    lvi.state = bSelect ? LVIS_SELECTED | LVIS_FOCUSED : 0;
    return this->SetItemStatus(index, &lvi);
}

/**************************************************//**
 * @brief	設定指定項目(Item)內容 - 文字模字
 * @param	[in] index	項目索引值   (zero-base)
 * @param	[in] isubs	項目子欄位索引(zero-base)
 * @param	[in] psz	字串緩衝區
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::SetItem(int index, int isubs, LPTSTR psz)
{
    LVITEM lvi;

    if (Null == psz) return False;
    // Setting properties Of members
    ::memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;   // LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = index;      // choose item
    lvi.iSubItem = isubs;   // choose sub item
    lvi.pszText = psz;      // push the string
    lvi.cchTextMax = ::lstrlen(lvi.pszText);
    return (Bool)this->SendMessage(LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&lvi);
}

/**************************************************//**
 * @brief	取得指定項目(Item)內容 - 文字模字
 * @param	[in]  index	項目索引值   (zero-base)
 * @param	[in]  isubs	項目子欄位索引(zero-base)
 * @param	[out] psz	字串緩衝區
 * @param	[in]  cch	要取得字串的長度 (in TCHAR)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsListv::GetItem(int index, int isubs, LPTSTR psz, int cch)
{
    LVITEM lvi;

    if (Null == psz) return False;
    // Setting properties Of members
    memset((void*)&lvi, 0, sizeof(LVITEM));
    lvi.mask = LVIF_TEXT;   // LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvi.iItem = index;      // choose item
    lvi.iSubItem = isubs;   // choose sub item
    lvi.pszText = psz;      // push string pointer
    lvi.cchTextMax = cch;   // the string length
    return this->SendMessage(LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&lvi) > 0;
}

/**************************************************//**
 * @brief	使用自訂 ListView 預設樣式
 *****************************************************/
void WsListv::DefaultStyle()
{
    // LVS_REPORT           : 設定成 Report 樣式
    // LVS_SHOWSELALWAYS    : 非當前使用視窗時，被選定 Item 仍以高亮反白顯示
    // LVS_EDITLABELS       : 子項目欄位可編輯
    DWORD dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS;

    // LVS_EX_FULLROWSELECT     : 選擇時，以全行高亮反白
    // LVS_EX_GRIDLINES         : 使用網格
    // LVS_EX_CHECKBOXES        : 帶有 Check Box
    // LVS_EX_HEADERDRAGDROP    : 讓 Listview Header(表頭) 顯示位置甩曳交換
    // LVS_EX_ONECLICKACTIVATE  : 單擊觸發
    // LVS_EX_TWOCLICKACTIVATE  : 雙擊觸發
    // LVS_EX_MULTIWORKAREAS    : 多工作區 (可複選項目)
    DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;

    dwStyle   |= this->GetStyle();
    dwExStyle |= this->GetExStyle();
    this->SetStyle(dwStyle);
    this->SetExStyle(dwExStyle);
}

/**************************************************//**
 * @brief	建立 ListView 控制項
 * @param	[in] x			ListView 起始位置 (對應父視窗左上座標 X)
 * @param	[in] y			ListView 起始位置 (對應父視窗左上座標 Y)
 * @param	[in] wd			ListView 寬度
 * @param	[in] ht			ListView 高度
 * @param	[in] hParent	父視窗 Handle
 * @param	[in] idItem		控制項 ID
 * @return	@c Bool
 *			- 運作成功傳回 True
 *			- 運作失敗傳回 False
 * @note	使用 CreateWindowEx 建立 ListView 控制項
 *****************************************************/
Bool WsListv::CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem)
{
	const Bool err = False;
    SaCTRLS ctrl; // Structure for controller

	if (hParent == Null)	// hParent (父視窗) 不得為 Null
		return err;
	if (idItem <= 0)		// 子項目 ItemID 不得為 零 或 負數
		return err;

	// 將傳入參數填入 DMCWNDCTRLS 結構
    ::memset((void*)&ctrl, 0, sizeof(SaCTRLS));
    ctrl.hParent = hParent;
    ctrl.emType = emCtrlSysListView32;
    ctrl.pszName = Null;
    ctrl.dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS; // LVS_EDITLABELS;
    ctrl.dwExStyle = 0;
    ctrl.iPosx = x;
    ctrl.iPosy = y;
    ctrl.iWidth = wd;
    ctrl.iHeight = ht;
    ctrl.idItem = idItem; // conctrller item id
    ctrl.fnWndProcess = Null;
	return this->CreateUseHotCodes(&ctrl);
}

/**************************************************//**
 * @brief	範例程式 - 如何取得 ListView 行與列的訊息
 * @param	[in] wParam	參數 1 (仿視窗訊息處理函式)
 * @param	[in] lParam 參數 2 (仿視窗訊息處理函式)
 * @note	如何獲取 ListView 控制項行與列被滑鼠點擊出發事件 \n
 *			假設父視窗 A 中有一個 ListView 控制項 B，B 的 style 為 report \n
 *			使用者點擊了 B 的內部，我們如何知道用戶點擊了哪一個單元格呢？ \n
 *			使用者點擊 B 的內部時，B 會向父視窗 A 發送 WM_NOTIFY 訊息。 \n
 *			假設使用者單擊了 B 的內部，B 的 ID 為 ID_LV，那麼我們在父視窗 A 訊息處理程式中，可以追加程式碼。
 *
 * @code
 *	case WM_NOTIFY:
 *	{
 *		switch (LOWORD(wParam))
 *		{
 *		case ID_LV:
 *			if (((LPNMHDR)lParam)->code == NM_CLICK) {
 *				int iItem = ((LPNMITEMACTIVATE)lParam)->iItem;
 *				int iSubItem = ((LPNMITEMACTIVATE)lParam)->iSubItem;
 *				if (iItem >= 0 && iSubItem > 1) {
 *					// 這樣就成功獲取了行和列的資訊
 *					return 0;
 *				}
 *			}
 *			break;
 *		}
 *		break;
 *	}
 * @endcode
 *****************************************************/
void WsListv::Example(WPARAM wParam, LPARAM lParam)
{

}

#if 0
//static LRESULT CALLBACK ListViewWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
//void PaintAlternatingRows();
//void EraseAlternatingRowBkgnds(HDC hDC);

LRESULT WsListv::ListViewWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SaCTRLSPARAM* cvPtr = (SaCTRLSPARAM*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	if (cvPtr == 0) return 0;

	switch (iMessage) {
	case WM_PAINT:
		// intercept the WM_PAINT message which is called each time an area
		// of the control's client area requires re-drawing
		((WsListv*)cvPtr->pvObj)->PaintAlternatingRows();
		return 0;
	case WM_ERASEBKGND:
		// intercept the WM_ERASEBKGRN message which is called each time an area
		// of the control's lient area background requires re-drawing
		((WsListv*)cvPtr->pvObj)->EraseAlternatingRowBkgnds((HDC)wParam);
		return 0;
	}
	// continue with default message processing
	return CallWindowProc((WNDPROC)cvPtr->pvParam, hWnd, iMessage, wParam, lParam);
}

void WsListv::PaintAlternatingRows()
{
	HWND	hWnd = m_hWnd;
	WNDPROC	fnProc = m_fnWndProc;

	if (fnProc == Null) return;

	RECT	rectUpd;	//	rectangle to update
	RECT	rectDestin;	//	temporary storage
	RECT	rect;		//	row rectangle
	POINT	pt;
	int		iItems, iTop;
	COLORREF c;			//	temporary storage

	// get the rectangle to be updated
	::GetUpdateRect(hWnd, &rectUpd, False);
	// allow default processing first
	::CallWindowProc(fnProc, hWnd, WM_PAINT, 0, 0);
	// set the row horizontal dimensions
	::SetRect(&rect, rectUpd.left, 0, rectUpd.right, 0);
	// number of displayed rows
	iItems = this->GetCountPerPage();
	// first visible row
	iTop = this->GetTopIndex();
	this->GetItemPosition(iTop, &pt);

	for (int i = iTop; i <= iTop + iItems; i++) {
		// set row vertical dimensions
		rect.top = pt.y;
		this->GetItemPosition(i + 1, &pt);
		rect.bottom = pt.y;
		// if row rectangle intersects update rectangle then it requires re-drawing
		if (::IntersectRect(&rectDestin, &rectUpd, &rect)) {
			// change text background colour accordingly
			c = (i % 2) ? this->ColorShade(GetSysColor(COLOR_WINDOW), 95.0) : ::GetSysColor(COLOR_WINDOW);
			this->SetBkColor(c);
			// invalidate the row rectangle then...
			::InvalidateRect(hWnd, &rect, False);
			// ...force default processing
			CallWindowProc(fnProc, m_hWnd, WM_PAINT, 0, 0);
		}
	}
}

void WsListv::EraseAlternatingRowBkgnds(HDC hDC)
{
	HWND	hWnd = m_hWnd;
	RECT	rect;			//	row rectangle
	POINT	pt;
	int		iItems, iTop;
	HBRUSH	brushCol1;		//	1st colour
	HBRUSH	brushCol2;		//	2nd colour

	// create coloured brushes
	brushCol1 = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	brushCol2 = CreateSolidBrush(this->ColorShade(::GetSysColor(COLOR_WINDOW), 95.0));
	// get horizontal dimensions of row
	::GetClientRect(hWnd, &rect);
	// number of displayed rows
	iItems = this->GetCountPerPage();
	// first visible row
	iTop = this->GetTopIndex();
	this->GetItemPosition(iTop, &pt);

	for (int i = iTop; i <= iTop + iItems; i++) {
		// set row vertical dimensions
		rect.top = pt.y;
		this->GetItemPosition(i + 1, &pt);
		rect.bottom = pt.y;
		// fill row with appropriate colour
		::FillRect(hDC, &rect, (i % 2) ? brushCol2 : brushCol1);
	}

	//	cleanup
	::DeleteObject(brushCol1);
	::DeleteObject(brushCol2);
}
#endif
