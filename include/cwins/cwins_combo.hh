/**************************************************************************//**
 * @file	cwins_combo.hh
 * @brief	cwins 視窗操作 : 控制項 ComboBox 類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSCOMMBO_H__
#define __AXEEN_CWINS_CWINSCOMMBO_H__
#include "cwins_ctrls.hh"

/**************************************************//**
 * @class	WsCombo
 * @brief	視窗操作 : 控制項 ComboBox 類別
 * @author	Swang
 * @note	ComboBox 控制項操作，繼承 WsCtrls
 *****************************************************/
class WsCombo : public WsCtrls
{
public:
	WsCombo();
	virtual ~WsCombo();
	
	void RemoveAllItem();

	int	DeleteItem(int index);
	int InsertItem(int index, LPCTSTR pszText);
	int AddItem(LPCTSTR pszText);
	
	int GetCount();
	int GetCursel();
	int SetCursel(int index);

	int GetItemTextLength(int index);
	int GetItemText(int index, LPTSTR pszText);

	BOOL CreateFromResource(HWND hCombo, int idItem);
	BOOL CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem);
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsCombo::WsCombo() : WsCtrls(emCtrlComboBox) { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsCombo::~WsCombo() { }

/**************************************************//**
 * @brief	清除所有 ComboBox 列表內容內容
 *****************************************************/
inline void WsCombo::RemoveAllItem()
{
	// CB_RESETCONTENT
	// wParam 必須為零
	// lParam 必須為零
	this->SendMessage(CB_RESETCONTENT, 0, 0);
}

/**************************************************//**
 * @brief	新增或插入一個字串型別 (string item)
 * @param	[in] index		要新增或插入的索引碼 (zero-base)
 * @param	[in] pszText	插入字串緩衝區(指標)
 * @return	@c int
 *			- 執行成功，傳回登錄索引值
 *			- 執行失敗，傳回 CB_ERR
 * @note	使用 InsertItem 新增一個項目，新增項為會依據指定位置插入，安插後原有項目 index 將往後遞增
 *****************************************************/
inline int WsCombo::InsertItem(int index, LPCTSTR pszText)
{
	// CB_INSERTSTRING
	// wParam 指定項目索引
	// lParam 字串指標
	return (int)this->SendMessage(CB_INSERTSTRING, (WPARAM)index, (LPARAM)pszText);
}

/**************************************************//**
 * @brief	新增一個字串型別 (string item)
 * @param	[in] pszText	新增字串緩衝區(指標)
 * @return	@c int
 *			- 執行成功，傳回登錄索引值
 *			- 執行失敗，傳回 CB_ERR
 * @note	使用 AddItem 新增一個項目，所新增項目會被自動排序
 *****************************************************/
inline int WsCombo::AddItem(LPCTSTR pszText)
{
	// CB_ADDSTRING
	// wParam 未使用，建議設為 0
	// lParam 字串指標
	return (int)this->SendMessage(CB_ADDSTRING, 0, (LPARAM)pszText);
}

/**************************************************//**
 * @brief	取得 Combo Box 成員列表數量
 * @return	@c int
 *			- 執行成功傳回: 目前 Item 數量
 *			- 執行失敗傳回: CB_ERR
 *****************************************************/
inline int WsCombo::GetCount()
{
	// CB_GETCOUNT
	// wParam 未使用，必須為零
	// lParam 未使用，必須為零
	return (int)this->SendMessage(CB_GETCOUNT, 0, 0);
}

/**************************************************//**
 * @brief	取得目前清單上 Cursel (光標? 反白?) 位置
 * @return	@c int
 *			- 執行成功傳回: cursel(光標?) 位置 (zero-base)
 *			- 執行失敗傳回: CB_ERR
 *****************************************************/
inline int WsCombo::GetCursel()
{
	// CB_GETCURSEL
	// wParam 未使用，必須為零
	// lParam 未使用，必須為零
	return (int)this->SendMessage(CB_GETCURSEL, 0, 0);
}

/**************************************************//**
 * @brief	設定目前清單上 Cursel (光標? 反白?) 位置
 * @param	[in] index	欲設定 cursel 位置索引碼 (zero-base)
 * @return	@c int
 *			- 執行成功傳回: 當前 cursel 位置 (zero-base)
 *			- 執行失敗傳回: CB_ERR
 *****************************************************/
inline int WsCombo::SetCursel(int index)
{
	// CB_SETCURSEL
	// wParam 項目索引
	// lParam 未使用，必須為零
	return (int)this->SendMessage(CB_SETCURSEL, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	刪除一個 Item
 * @param	[in] index	欲刪除的索引碼 (zero-base)
 * @return	@c int
 *			- 執行成功傳回: 目前 Item 數量
 *			- 執行失敗傳回: CB_ERR
 *****************************************************/
inline int WsCombo::DeleteItem(int index)
{
	// CB_DELETESTRING
	// wParam 項目索引
	// lParam 未使用
	return (int)this->SendMessage(CB_DELETESTRING, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	取得 Item 字串長度
 * @param	[in] index	要取得字串長度的索引碼 (zero-base)
 * @return	@c int
 *			- 執行成功，傳回所指 Item 字串長度，單位 TCHAR (不含 NULL 結尾)
 *			- 執行失敗，傳回 CB_ERR
 *****************************************************/
inline int WsCombo::GetItemTextLength(int index)
{
	// CB_GETLBTEXTLEN
	// wParam 項目索引
	// lParam 未使用，必須為零
	return (int)this->SendMessage(CB_GETLBTEXTLEN, (WPARAM)index, 0);
}

/**************************************************//**
 * @brief	取得 Item 字串
 * @param	[in]  index		要取得字串的索引碼 (zero-base)
 * @param	[out] pszText	要存放字串緩衝區
 * @return	@c int
 *			- 執行成功傳回: 指定 Item 的字串長度，單位 TCHAR (不含 NULL 結尾)
 *			- 執行失敗傳回: CB_ERR
 *****************************************************/
inline int WsCombo::GetItemText(int index, LPTSTR pszText)
{
	// CB_GETLBTEXT
	// wParam 項目索引
	// lParam 存放取得字串緩衝區指標
	return (int)this->SendMessage(CB_GETLBTEXT, (WPARAM)index, (LPARAM)pszText);
}

/**************************************************//**
 * @brief	結合資源檔或其他已建立的 ComboBox 控制項
 * @param	[in] hCombo	子項目視窗
 * @param	[in] idItem	控制項 ID
 * @return	@c BOOL
 *			- 函式運作成功傳回: TRUE
 *			- 函式運作失敗傳回: FALSE
 *****************************************************/
inline BOOL WsCombo::CreateFromResource(HWND hCombo, int idItem) { return this->CombineResource(hCombo, idItem); }

#endif	/* __AXEEN_CWINS_CWINSCOMMBO_H__ */
