/**************************************************************************//**
 * @file	cwins_listv.hh
 * @brief	視窗操作 : 控制項 ListView 類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSLISTVIEW_HH__
#define __AXEEN_CWINS_CWINSLISTVIEW_HH__
#include "cwins_ctrls.hh"

/**************************************************//**
 * @class	WsListv
 * @brief	ListView 控制項操作類別
 * @author	Swang
 * @note	ListView 控制項與操作，繼承 WsCtrls
 *****************************************************/
class WsListv : public WsCtrls
{
public:
	WsListv();
	virtual ~WsListv();

    Bool InsertColumn(int index, int wd, int align, LPTSTR psz);
	Bool DeleteColumn(int index);
    void DeleteAllColumn();

    Bool GetColumn(int index, LPTSTR psz, int cch);
    Bool SetColumn(int index, LPTSTR psz);

	int  GetColumnWidth(int index);
	Bool SetColumnWidth(int index, int pixel);

	int  GetColumnCount();
	int  GetCountPerPage();
	int  GetTopIndex();

	Bool GetItemPosition(int index, LPPOINT aPtr);

    Bool InsertItem(int index, int isubs, LPTSTR psz);
	Bool DeleteItem(int index);
	Bool DeleteAllItem();

	Bool SetItemStatus(int index, LPLVITEM plvi);
	int  GetItemCount();
	int  GetSelectItemCount();
	int  GetSelectItem();
	Bool SetSelectItem(int index, Bool bSelect);
	int  GetSelectItemFirst();
	int  GetSelectItemNext();

    Bool SetItem(int index, int isubs, LPTSTR psz);
    Bool GetItem(int index, int isubs, LPTSTR psz, int cch);

	Bool SetBkColor(COLORREF dwColor);
	Bool SetTextColor(COLORREF dwColor);
	Bool SetTextBkColor(COLORREF dwColor);

	DWORD GetExStyle();
	void  SetExStyle(DWORD dwExStyle);
    void  DefaultStyle();

	Bool CreateFromResource(HWND hList, int idItem);
    Bool CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem);

protected:
	COLORREF ColorShade(COLORREF c, float fPercent);

private:
	void Example(WPARAM wParam, LPARAM lParam);

protected:
	int m_iSelectItemCount;		//!< 被選取項目總數
	int m_iSelectItemIndex;		//!< 當前選取的索引
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsListv::WsListv() : WsCtrls(emCtrlSysListView32), m_iSelectItemCount(0), m_iSelectItemIndex(0) { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsListv::~WsListv() { }


/**************************************************//**
 * @brief	刪除一個欄位(Column)
 * @param	[in] index	欄位項目索引 (zero-base)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::DeleteColumn(int index)
{
	// LVM_DELETECOLUMN
	// wParam 欄位索引
	// lParam 必須為零
	return (Bool)this->SendMessage(LVM_DELETECOLUMN, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	取得欄位(Column)寬度
 * @param	[in] index	欄位項目索引 (zero-base)
 * @return	@c int		傳回寬度數據，若失敗則傳回 0
 *****************************************************/
inline int WsListv::GetColumnWidth(int index)
{
	// LVM_GETCOLUMNWIDTH
	// wParam 欄位索引
	// lParam 必須為零
	return (int)this->SendMessage(LVM_GETCOLUMNWIDTH, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	設定欄位(Column)寬度
 * @param	[in] index	欄位項目索引 (zero-base)
 * @param	[in] pixel	欄位寬度 (in pixel) 像素
 * @return	@c int		傳回寬度數據，若失敗則傳回 0
 *****************************************************/
inline Bool WsListv::SetColumnWidth(int index, int pixel)
{
	// LVM_GETCOLUMNWIDTH
	// wParam 欄位索引 zero-base
	// lParam 欄位寬度 (像素)
	return (Bool)this->SendMessage(LVM_SETCOLUMNWIDTH, (WPARAM)index, (LPARAM)pixel);
}

/**************************************************//**
 * @brief	取得欄位(Column)數量
 * @return	@c int	Column 數量，若失敗傳回 -1
 * @note	Win32 API 並無提供刪除所有 Column 的功能， \n
 *			所以必須先取得 ListView 的 HDM 然後去取得 Header 數量
 *****************************************************/
inline int WsListv::GetColumnCount()
{
	// 取得 HDM Handle
	HWND hWnd = (HWND)::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0);
	if (hWnd != Null) {
		// HDM_GETITEMCOUNT
		// wParam 必須為零
		// lParam 必須為零
		return (int)this->SendMessage(HDM_GETITEMCOUNT, 0, 0);
	}
	return -1;
}

/**************************************************//**
 * @brief	取得目前可視範圍的項目數量
 * @return	@c int
 *			- 若運作成功，返回當前可是範圍的項目數量
 *			- 若為圖示或小圖示模式，將返回所有於 ListView 控制項的圖示數量
 *****************************************************/
inline int WsListv::GetCountPerPage()
{
	// LVM_GETCOUNTPERPAGE
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(LVM_GETCOUNTPERPAGE, 0, 0);
}

/**************************************************//**
 * @brief	取得指定項目位置
 * @param	[in]  index	項目索引
 * @param	[out] aPtr	POINT 結構指標
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::GetItemPosition(int index, LPPOINT aPtr)
{
	// LVM_GETITEMPOSITION
	// wParam 項目索引
	// lParam POINT 結構指標
	return (Bool)this->SendMessage(LVM_GETITEMPOSITION, (WPARAM)index, (LPARAM)aPtr);
}

/**************************************************//**
 * @brief	取得可是範圍內，於列表最上面項目的 index
 * @return	@c int	位於可是範圍內最上面項目的 index (zero-base)
 *****************************************************/
inline int WsListv::GetTopIndex()
{
	// LVM_GETTOPINDEX
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(LVM_GETTOPINDEX, 0, 0);
}

/**************************************************//**
 * @brief	刪除一個項目(Item)
 * @param	[in] index	項目索引值 (zero-base)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::DeleteItem(int index)
{
	// LVM_DELETEITEM
	// wParam 項目索引
	// lParam 必須為零
	return (Bool)this->SendMessage(LVM_DELETEITEM, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	刪除所有項目(Item)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::DeleteAllItem()
{
	// LVM_DELETEALLITEMS
	// wParam 必須為零
	// lParam 必須為零
	return (Bool)this->SendMessage(LVM_DELETEALLITEMS, 0, 0);
}

/**************************************************//**
 * @brief	取得項目(Item)數量
 * @return	@c int	全部項目(Item)的數量
 *****************************************************/
inline int WsListv::GetItemCount()
{
	// LVM_GETITEMCOUNT
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(LVM_GETITEMCOUNT, 0, 0);
}

/**************************************************//**
 * @brief	設定項目(Item)狀態
 * @param	[in] index	項目索引值   (zero-base)
 * @param	[in] plvi	LVITEM 結構指標
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::SetItemStatus(int index, LPLVITEM plvi)
{
	// LVM_SETITEMSTATE
	// wParam 項目索引
	// lParam LVITEM 結構指標
	return (Bool)this->SendMessage(LVM_SETITEMSTATE, (WPARAM)index, (LPARAM)plvi);
}
    
/**************************************************//**
 * @brief	取得被選中項目(Item)數量 (光標 or 反白)
 * @return	@c int	被選中項目(Item)的數量
 * @note	取得目前列表上被選取的數量
 *****************************************************/
inline int WsListv::GetSelectItemCount()
{
	// LVM_GETSELECTEDCOUNT
	// wParam 必須為零
	// lParam 必須為零
	return (int)this->SendMessage(LVM_GETSELECTEDCOUNT, 0, 0);
}

/**************************************************//**
 * @brief	取得被選取的項目 (光標 or 反白)
 * @return	@c int	項目的索引 (zero-base)
 *			- 運作成功傳回: 項目索引
 *			- 運作失敗傳回: -1
 *****************************************************/
inline int WsListv::GetSelectItem()
{
	// LVM_GETNEXTITEM
	// wParam 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam 指定項目搜尋方式
	return (int)this->SendMessage(LVM_GETNEXTITEM, -1, LVNI_SELECTED);
}

/**************************************************//**
 * @brief	取得被選取的第一個項目 (光標 or 反白)
 * @return	@c int	項目索引 (zero-base)
 *			- 運作成功傳回: 項目索引
 *			- 運作失敗傳回: -1
 *****************************************************/
inline int WsListv::GetSelectItemFirst()
{
	// LVM_GETNEXTITEM
	// wParam 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam 指定項目搜尋方式
	m_iSelectItemCount = this->GetSelectItemCount();
	m_iSelectItemIndex = (int)this->SendMessage(LVM_GETNEXTITEM, -1, LVNI_ALL);
	return m_iSelectItemIndex;
}

/**************************************************//**
 * @brief	取得被選取的下一個項目 (光標 or 反白)
 * @return	@c int	項目(Item)的索引 (zero-base)
 *			- 運作成功傳回: 項目索引
 *			- 運作失敗傳回: -1
 *****************************************************/
inline int WsListv::GetSelectItemNext()
{
	// LVM_GETNEXTITEM
	// wParam 用於開始搜索項目的索引，-1 以查找與指定標誌匹配的第一個項目，指定的項目本身將被排除在搜索之外。
	// lParam 指定項目搜尋方式
	return (int)this->SendMessage(LVM_GETNEXTITEM, m_iSelectItemIndex, LVNI_ALL);
}

/**************************************************//**
 * @brief	設定背景顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::SetBkColor(COLORREF dwColor)
{
	// LVM_SETBKCOLOR
	// wParam 必須為零
	// lParam COLORREF 型別, 背景顏色 RGB (若使用 CLR_NONE 定義值，則為無被景色)
	return (Bool)this->SendMessage(LVM_SETBKCOLOR, 0, (LPARAM)dwColor);
}

/**************************************************//**
 * @brief	設定文字顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::SetTextColor(COLORREF dwColor)
{
	// LVM_SETTEXTCOLOR
	// wParam 必須為零
	// lParam COLORREF 型別, 顏色定義。
	return (Bool)this->SendMessage(LVM_SETTEXTCOLOR, 0, (LPARAM)dwColor);
}

/**************************************************//**
 * @brief	設定文字背景顏色
 * @param	[in] dwColor 顏色(RGB)
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
inline Bool WsListv::SetTextBkColor(COLORREF dwColor)
{
	// LVM_SETTEXTBKCOLOR
	// wParam 必須為零
	// lParam COLORREF 型別, 背景顏色 RGB (若使用 CLR_NONE 定義值，則為無被景色)
	return (Bool)this->SendMessage(LVM_SETTEXTBKCOLOR, 0, (LPARAM)dwColor);
}

/**************************************************//**
 * @brief   取得 ListView 擴展樣式
 * @details 詳細說明
 *			- Gets the extended styles
 *			- that are currently in use for a given list-view control.
 * @return	@c DWORD
 *			- that represents the styles currently in use for a given list-view control.
 *****************************************************/
inline DWORD WsListv::GetExStyle()
{
	// LVM_GETEXTENDEDLISTVIEWSTYLE
	// wParam 必須為零
	// lParam 必須為零
	return (DWORD)this->SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);
}

/**************************************************//**
 * @brief   設定 ListView 擴展樣式
 * @details 詳細說明
 *			- Sets the extended styles,
 *			- that are currently in use for a given list-view control.
 * @param	[in] dwExStyle 擴展樣式
 *			- dwExStyle a specifies the extended list-view control style.
 *****************************************************/
inline void WsListv::SetExStyle(DWORD dwExStyle)
{
	// LVM_SETEXTENDEDLISTVIEWSTYLE
	// wParam 必須為零
	// lParam Extended List-View Styles. (延伸風格資料)
	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwExStyle);
}

/**************************************************//**
 * @brief	建立顏色陰影
 * @param	[in] c			COLORREF 格式，顏色值
 * @param	[in] fPercent	陰影階層
 *****************************************************/
inline COLORREF WsListv::ColorShade(COLORREF c, float fPercent)
{
	//	create a lighter shade (by fPercent %) of a given colour
	return RGB((BYTE)((float)GetRValue(c) * fPercent / 100.0),
		(BYTE)((float)GetGValue(c) * fPercent / 100.0),
		(BYTE)((float)GetBValue(c) * fPercent / 100.0));
}

/**************************************************//**
 * @brief	結合資源檔或其他已存在的 ListView 控制項
 * @param	[in] hList	子項目視窗
 * @param	[in] idItem	控制項 ID
 * @return	@c Bool
 *			- 操作成功傳回: True
 *			- 操作失敗傳回: False，調用 GetLastError 取得錯誤訊息
 ******************************************************/
inline Bool WsListv::CreateFromResource(HWND hList, int idItem) { return this->CombineResource(hList, idItem); }

#endif	/* __AXEEN_CWINS_CWINSLISTVIEW_HH__ */
