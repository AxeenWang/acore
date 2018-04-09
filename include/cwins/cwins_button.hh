/**************************************************************************//**
 * @file	cwins_button.hh
 * @brief	視窗操作 : 控制項 Button 類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSBUTTON_HH__
#define __AXEEN_CWINS_CWINSBUTTON_HH__
#include "cwins_ctrls.hh"

/**************************************************//**
 * @class	WsButton
 * @brief	視窗操作 : 控制項 Button 類別
 * @author	Swang
 * @note	按鈕控制項操作類別，繼承 WsCtrls
 *****************************************************/
class WsButton : public WsCtrls
{
public:
	WsButton();
	virtual ~WsButton();

	// 按鈕核對勾選狀態
	LRESULT GetCheck();
	LRESULT	SetCheck(int iCheck);

	// 單遠或複選狀態
	LRESULT GetState();
	LRESULT SetState(BOOL bState);

	// 建立按鈕
	BOOL CreateFromResource(HWND hButton, int idItem);
	BOOL CreateFromWindowEx(LPCTSTR pszName, int x, int y, int wd, int ht, HWND hParent, int idItem);
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsButton::WsButton() : WsCtrls(emCtrlButton) { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsButton::~WsButton() { }

/**************************************************//**
 * @brief	獲取單選按鈕或複選框(CheckBox)的檢查狀態
 * @return	@c LRESULT
 *			- BST_CHECKED		按鈕被選中
 *			- BST_INDETERMINATE	按鈕呈灰色，表示不確定狀態（僅在按鈕具有BS_3STATE或BS_AUTO3STATE樣式時適用）
 *			- BST_UNCHECKED		按鈕選中狀態被清除
*****************************************************/
inline LRESULT WsButton::GetCheck()
{
	// 傳送　BM_GETCHECK 訊息
	// wParam 未使用，必須為 0
	// lParam 未使用，必須為 0
	return ::SendMessage(m_hWnd, BM_GETCHECK, 0, 0);
}

/**************************************************//**
 * @brief	設置單選按鈕或複選框的檢查狀態
 * @param	[in] iCheck	設定按鈕 Cechk 狀態值
 *			- BST_CHECKED		將按鈕狀態設置為選中(選取中)
 *			- BST_INDETERMINATE	將按鈕狀態設置為灰色，表示不確定狀態。僅當按鈕具有BS_3STATE或BS_AUTO3STATE樣式時才使用此值。
 *			- BST_UNCHECKED		將按鈕狀態設置為清除(未選取)
 * @return	@c LRESULT	傳回值始終為零
 *****************************************************/
inline LRESULT WsButton::SetCheck(int iCheck)
{
	// 傳送 BM_SETCHECK 訊息
	// wParam = iCheck
	// lParam = 未使用
	return ::SendMessage(m_hWnd, BM_SETCHECK, (WPARAM)iCheck, 0);
}

/**************************************************//**
 * @brief	取得單選按鈕或複選框狀態
 * @return	@c LRESULT
 *			- BST_CHECKED			該按鈕被選中
 *			- BST_DROPDOWNPUSHED	Windows Vista。該按鈕處於下拉狀態。僅當按鈕具有TBSTYLE_DROPDOWN樣式時才適用
 *			- BST_FOCUS				該按鈕具有鍵盤焦點
 *			- BST_HOT				火熱狀態，也就是說，滑鼠游標停在它上面
 *			- BST_INDETERMINATE		按鈕的狀態是不確定的，僅當按鈕具有BS_3STATE或BS_AUTO3STATE樣式時才適用
 *			- BST_PUSHED			按鈕顯示處於按下狀態
 *			- BST_UNCHECKED			為被選中，沒有特殊的狀態，相當於零
 *****************************************************/
inline LRESULT WsButton::GetState()
{
	// 傳送 BM_GETSTATE 訊息
	// wParam 未使用，必須為 0
	// lParam 未使用，必須為 0
	return ::SendMessage(m_hWnd, BM_GETSTATE, 0, 0);
}

/**************************************************//**
 * @brief	設定單選按鈕或複選框狀態
 * @param	[in] bState	設定按鈕 State 狀態值
 *			- TRUE	設定按鈕為觸發狀態(按下、被選中、發光)
 *			- FALSE	清除按鈕所有被設定狀態
 * @return	@c LRESULT	傳回值始終為零
 *****************************************************/
inline LRESULT WsButton::SetState(BOOL bState)
{
	// 傳送 BM_SETSTATE 訊息
	// wParam 指定按鈕是否被選中
	// lParam
	return ::SendMessage(m_hWnd, BM_SETSTATE, (WPARAM)bState, 0);
}

/**************************************************//**
 * @brief	結合資源檔或其他已存在的 Button
 * @param	[in] hButton	子項目視窗
 * @param	[in] idItem		控制項 ID
 * @return	@c BOOL
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 ******************************************************/
inline BOOL WsButton::CreateFromResource(HWND hButton, int idItem) { return this->CombineResource(hButton, idItem); }

#endif	/* __AXEEN_CWINS_CWINSBUTTON_HH__ */
