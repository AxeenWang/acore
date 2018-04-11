/**************************************************************************//**
 * @file	cwins_object.hh
 * @brief	cwins 視窗操作基底類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSOBJECT_HH__
#define __AXEEN_CWINS_CWINSOBJECT_HH__
#include "cwins_define.hh"

/**************************************************//**
 * @class	WsObject
 * @brief	視窗操作基底類別
 * @author	Swang
 * @note	視窗操作基礎命令，函式
 *****************************************************/
class WsObject
{
public:
	WsObject();
	WsObject(EmCTRLS type);
	virtual ~WsObject();

	// 訊息操作
	LRESULT SendMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);
	LRESULT SendChildMessage(int idItem, UINT uMessage, WPARAM wParam, LPARAM lParam);

	Bool	PostMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);
	Bool	PostChildMessage(int idItem, UINT uMessage, WPARAM wParam, LPARAM lParam);

	// 時間程序
	UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC fnTimerFunc);
	Bool KillTimer();

	// 字型操作
	Bool CreateFont(LPCTSTR fontFace, int size, Bool bBlod, int charset = DEFAULT_CHARSET);
	void DeleteFont();
	void SetFont(HFONT hFont);

	// 文字操作
	Bool SetText(LPCTSTR psz);
	int  GetText(LPTSTR psz, int cch);
	UINT GetChildText(int idItem, LPTSTR psz, int cch);
	Bool SetChildText(int idItem, LPCTSTR psz);

	// 視窗或控制項行動操作
	Bool Update();
	Bool Enable();
	Bool Disable();
	Bool EnableChild(int idItem);
	Bool DisableChild(int idItem);
	Bool Show();
	Bool Hide();
	Bool ShowChild(int idItem);
	Bool HideChild(int idItem);

	// 視窗或控制項 Style
	DWORD GetStyle();
	DWORD SetStyle(DWORD dwStyle);
	DWORD GetExStyle();
	DWORD SetExStyle(DWORD dwExStyle);

	// 視窗尺寸操作
	Bool GetFrameRect(LPRECT prc);
	Bool GetClientRect(LPRECT prc);
	Bool GetParentRect(LPRECT prc);
	Bool GetParentClientRect(LPRECT prc);
	Bool GetChildRect(int idItem, LPRECT prc);
	Bool GetChildClientRect(int idItem, LPRECT prc);
	int  GetBorderSize();

	// 視窗位置操作
	Bool SetPosition(int x, int y);
	Bool SetSize(int wd, int ht);
	Bool SetClientSize(int wd, int ht);
	void SetCenterPosition();

	// 視窗焦點
	HWND GetTopWindow();
	HWND GetFocus();
	HWND SetFocus();

	void SetIcon(HICON hIcon);

	HINSTANCE GetModule();
	HWND GetParent();
	HWND GetHandle();
	HWND GetChild(int idItem);
	int  GetID();
	Bool IsExist();

protected:
	void InDestroyWindow();
	void InitCommCtrl();

protected:
	HINSTANCE	m_hModule;		//!< 程序模組 HANDLE
	HWND		m_hParent;		//!< 父視窗操作 HANDLE
	HFONT		m_hFont;		//!< 保存建立字型 Handle
	HWND		m_hWnd;			//!< 視窗操作 HANDLE
	int			m_idItem;		//!< 視窗操作 ID
	UINT_PTR	m_idTimer;		//!< Timer ID (保存使用 SetTimer 成員傳回值)

	// WsCtrls 類別使用 
	EmCTRLS		m_emCtrlsType;	//!< 紀錄控制項視窗 Type (見 EmCTRLS)
	WNDPROC		m_fnWndProc;	//!< 控制項 Callback 位址指標，自行定義之 Callback
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsObject::WsObject()
	: m_hModule(NULL)
	, m_hParent(NULL)
	, m_hFont(NULL)
	, m_hWnd(NULL)
	, m_idItem(0)
	, m_idTimer(0)
	, m_emCtrlsType(emCtrlEmpty)
	, m_fnWndProc(NULL) {
	this->InitCommCtrl();
}

/**************************************************//**
 * @brief	建構式
 * @param	[in] type 控制項種類代碼
 *****************************************************/
inline WsObject::WsObject(EmCTRLS type)
	: m_hModule(NULL)
	, m_hParent(NULL)
	, m_hFont(NULL)
	, m_hWnd(NULL)
	, m_idItem(0)
	, m_idTimer(0)
	, m_emCtrlsType(type)
	, m_fnWndProc(NULL) {
	this->InitCommCtrl();
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsObject::~WsObject() { }

/**************************************************//**
 * @brief	視窗訊息傳送 (等待訊息處理結果)
 * @param	[in] uMessage	訊息代碼
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT		訊息處理結果，依據指定的訊息結果而定
 * @see		MSDN SendMessage()
 *****************************************************/
inline LRESULT WsObject::SendMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) { return ::SendMessage(m_hWnd, uMessage, wParam, lParam); }

/**************************************************//**
 * @brief	子視窗(項目)訊息傳送 (等待訊息處理結果)
 * @param	[in] idItem		子控制項 id
 * @param	[in] uMessage	訊息代碼
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT		訊息處理結果，依據指定的訊息結果而定
 * @see		MSDN SendMessage()
 *****************************************************/
inline LRESULT WsObject::SendChildMessage(int idItem, UINT uMessage, WPARAM wParam, LPARAM lParam) { return ::SendMessage(this->GetChild(idItem), uMessage, wParam, lParam); }

/**************************************************//**
 * @brief	視窗訊息傳送 (不等待訊息處理結果)
 * @param	[in] uMessage	訊息代碼
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 * @see		MSDN PostMessage()
 *****************************************************/
inline Bool WsObject::PostMessage(UINT uMessage, WPARAM wParam, LPARAM lParam) { return ::PostMessage(m_hWnd, uMessage, wParam, lParam); }

/**************************************************//**
 * @brief	視窗訊息傳送 (不等待訊息處理結果)
 * @param	[in] idItem		子控制項 id
 * @param	[in] uMessage	訊息代碼
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 * @see		MSDN PostMessage()
 *****************************************************/
inline Bool WsObject::PostChildMessage(int idItem, UINT uMessage, WPARAM wParam, LPARAM lParam) { return ::PostMessage(this->GetChild(idItem), uMessage, wParam, lParam); }

/**************************************************//**
 * @brief	建立 Timer 事件
 * @param	[in] nIDEvent		計時器 ID
 * @param	[in] uElapse		延遲時間 (ms) 多少時間觸發一次
 * @param	[in] fnTimerFunc	指定 Timer callback function，若此值為 NULL 計時器會對對視窗發出 WM_TIMER 訊息
 * @return	@c UINT_PTR
 *			- 操作成功傳回: 計時器 ID
 *			- 操作失敗傳回: 0，調用 GetLastError 取得錯誤訊息。
 * @note	如果函式運作成功，將傳回新計時器的計時器識別項。這個值不一定等於透過 nIDEvent 參數傳入的值。\n
 *			應用程式必須將傳回值傳遞至 KillTimer 成員函式才能刪除計時器。
 * @note	此類別函式一個視窗或控制項僅保存一個 Timer \n
 *			若要多個 Timer 於同一個視窗或控制項，則必須再衍生類別自行處理。
 *****************************************************/
inline UINT_PTR WsObject::SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC fnTimerFunc)
{
	this->KillTimer();
	m_idTimer = ::SetTimer(m_hWnd, nIDEvent, uElapse, fnTimerFunc);
	return m_idTimer;
}

/**************************************************//**
 * @brief	刪除 Timer 事件
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::KillTimer()
{
	const Bool err = FALSE;
	UINT_PTR uTimer = m_idTimer;
	
	if (uTimer) { m_idTimer = 0; return ::KillTimer(m_hWnd, uTimer); }
	return err;
}

/**************************************************//**
 * @brief	刪除已建立字型
 * @note	刪除字型後，將會將 *hFontPtr 指向位置設為 NULL
 *****************************************************/
inline void WsObject::DeleteFont()
{
	if (m_hFont != NULL) {
		::DeleteObject(m_hFont);
		m_hFont = NULL;
	}
}
/**************************************************//**
 * @brief	設定視窗字型 (使用已存在字型)
 * @param	[in] hFont 字型的 Handle
 * @note	設定顯示字型
 *****************************************************/
inline void WsObject::SetFont(HFONT hFont)
{
	if (hFont != NULL) {
		// 傳送 WM_SETFONT 訊息
		// wParam 為字型 Handle
		// lParam 低字元(low-word) 設定字型後是否立即重繪視窗內容 (TRUE / FALSE)
		::SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
	}
}

/**************************************************//**
 * @brief	設定(改變)視窗標題文字內容
 * @param	[in] psz 字串存放位址
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::SetText(LPCTSTR psz) { return ::SetWindowText(m_hWnd, psz); }

/**************************************************//**
 * @brief	取得(複製)視窗標題文字內容
 * @param	[out] psz	字串存放位址
 * @param	[in]  cch	要進行擷取字串長度 (單位 TCHAR)
 * @return	@c int
 *			- 操作成功傳回: 擷取的字串長度 (in TCHAR)
 *			- 操作失敗傳回: 0，調用 GetLastError 取得錯誤訊息
*****************************************************/
inline int WsObject::GetText(LPTSTR psz, int cch) { return ::GetWindowText(m_hWnd, psz, cch); }

/**************************************************//**
 * @brief	取得子控制項標題文字內容
 * @param	[in]  idItem	子控制項 id
 * @param	[out] psz		文字存放緩衝區指標
 * @param	[in]  cch		要取得(複製)文字長度 (單位 TCHAR) 
 * @return	@c UINT
 *			- 操作成功傳回: 實際取得字元數量 (in TCHAR)
 *			- 操作失敗傳回: 0
 * @see		MSDN GetDlgItemText()
 *****************************************************/
inline UINT WsObject::GetChildText(int idItem, LPTSTR psz, int cch) { return ::GetDlgItemText(m_hWnd, idItem, psz, cch); }

/**************************************************//**
 * @brief	設定子控制項標題文字內容
 * @param	[in] idItem	子控制項 id
 * @param	[in] psz	文字存放緩衝區指標
 * @return	@c Bool
 *			- 成功傳回: TRUE
 *			- 失敗傳回: FALSE
 * @see		MSDN SetDlgItemText()
 *****************************************************/
inline Bool WsObject::SetChildText(int idItem, LPCTSTR psz) { return ::SetDlgItemText(m_hWnd, idItem, psz); }

/**************************************************//**
 * @brief	更新視窗
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::Update() { return ::UpdateWindow(m_hWnd); }

/**************************************************//**
 * @brief	啟用視窗或控制項操作
 * @return	@c Bool
 *			- 若視窗先前被禁用傳回: TRUE
 *			- 若視窗先前非禁用傳回: FALSE
 *****************************************************/
inline Bool WsObject::Enable() { return ::EnableWindow(m_hWnd, TRUE); }

/**************************************************//**
 * @brief	停用視窗或控制項操作 (灰視窗不接收任何輸入動作)
 * @return	@c Bool
 *			- 若視窗先前被禁用傳回: TRUE
 *			- 若視窗先前非禁用傳回: FALSE
 *****************************************************/
inline Bool WsObject::Disable() { return ::EnableWindow(m_hWnd, FALSE); }

/**************************************************//**
 * @brief	啟用子視窗或控制項操作
 * @param	[in] idItem 子視窗或控制項 ID
 * @return	@c Bool
 *			- 若視窗先前被禁用傳回: TRUE
 *			- 若視窗先前非禁用傳回: FALSE
 *****************************************************/
inline Bool WsObject::EnableChild(int idItem) { return ::EnableWindow(this->GetChild(idItem), TRUE); }

/**************************************************//**
 * @brief	停用子視窗或控制項操作
 * @param	[in] idItem 子視窗或控制項 ID
 * @return	@c Bool
 *			- 若視窗先前被禁用傳回: TRUE
 *			- 若視窗先前非禁用傳回: FALSE
 *****************************************************/
inline Bool WsObject::DisableChild(int idItem) { return ::EnableWindow(this->GetChild(idItem), FALSE); }

/**************************************************//**
 * @brief	顯示視窗或控制項
 * @return	@c Bool
 *			- 若視窗先前為顯示中傳回: TRUE
 *			- 若視窗先前為隱藏中傳回: FALSE
 * @note	顯示視窗參數
 *			- SW_HIDE               隱藏視窗
 *			- SW_SHOWNORMAL         顯示視窗，如果視窗被最小化或最大化，系統將其恢復到原來的尺寸和大小 (初始建立時的大小)
 *			- SW_SHOWMINIMIZED      顯示視窗並以最小化顯示
 *			- SW_SHOWMAXIMIZED      顯示視窗並以最大化顯示
 *			- SW_MAXIMIZE           最大化顯示視窗
 *			- SW_SHOWNOACTIVATE     以視窗最近一次的大小和狀態顯示，活耀狀態視窗仍維活耀狀態。
 *			- SW_SHOW               以原來大小及位置顯示視窗
 *			- SW_MINIMIZE           顯示視窗並最小化，交出活耀狀態給下一個 Z 順位
 *			- SW_SHOWMINNOACTIVE    視窗最小化，但仍保持活耀狀態
 *			- SW_SHOWNA             以原來的狀態顯示視窗，活耀狀態視窗仍維活耀狀態
 *			- SW_RESTORE            顯示視窗並呈現活耀狀態，如果視窗最小化或最大化，則係統將視窗恢復到原來的尺寸和位置，在恢復最小化視窗時，應該指定使用這個方式。
 *			- SW_SHOWDEFAULT        依據在 STARTUPINFO 結構中指定的 FLAG 標誌設定顯示狀態,STARTUPINFO 結構是由啟動應用程序的程序傳遞給 CreateProcess 函數。
 *			- SW_FORCEMINIMIZE      在 Windows NT5.0 中最小化視窗,即使擁有視窗的線程被激活也會最小化。在從其他線程最小化視窗時才使用這個參數。
 *****************************************************/
inline Bool WsObject::Show() { return ::ShowWindow(m_hWnd, SW_SHOW); }

/**************************************************//**
 * @brief	隱藏視窗或控制項
 * @return	@c Bool
 *			- 若視窗先前為顯示中傳回: TRUE
 *			- 若視窗先前為隱藏中傳回: FALSE
 *****************************************************/
inline Bool WsObject::Hide() { return ::ShowWindow(m_hWnd, SW_HIDE); }

/**************************************************//**
 * @brief	顯示子視窗或控制項
 * @param	[in] idItem 子視窗或控制項 ID
 * @return	@c Bool
 *			- 若視窗先前為顯示中傳回: TRUE
 *			- 若視窗先前為隱藏中傳回: FALSE
 *****************************************************/
inline Bool WsObject::ShowChild(int idItem) { return ::ShowWindow(this->GetChild(idItem), SW_SHOW); }

/**************************************************//**
 * @brief	隱藏子視窗或控制項
 * @param	[in] idItem 子視窗或控制項 ID
 * @return	@c Bool
 *			- 若視窗先前為顯示中傳回: TRUE
 *			- 若視窗先前為隱藏中傳回: FALSE
 *****************************************************/
inline Bool WsObject::HideChild(int idItem) { return ::ShowWindow(this->GetChild(idItem), SW_HIDE); }

/**************************************************//**
 * @brief	取得視窗、控制項樣式 (Style)
 * @return	@c DWORD
 *			- 操作成功傳回: Sytle 值
 *			- 操作失敗傳回: 0，調用 GetLastError 取得錯誤訊息
 * @see		MSDN GetWindowLong()
 *****************************************************/
inline DWORD WsObject::GetStyle() { return ::GetWindowLong(m_hWnd, GWL_STYLE); }

/**************************************************//**
 * @brief	設定視窗、控制項樣式 (Style)
 * @param	[in] dwStyle 視窗樣式
 * @return	@c DWORD
 *			- 操作成功傳回: Sytle 值
 *			- 操作失敗傳回: 0，調用 GetLastError 取得錯誤訊息
 * @ see	MSDN SetWindowLing()
 *****************************************************/
inline DWORD WsObject::SetStyle(DWORD dwStyle) { return ::SetWindowLong(m_hWnd, GWL_STYLE, (LONG)dwStyle); }

/**************************************************//**
 * @brief	取得視窗、控制項擴展樣式 (ExStyle)
 * @return	@c DWORD
 *			- 操作成功傳回: ExSytle 值
 *			- 操作失敗傳回: 0，調用 GetLastError 取得錯誤訊息
 * @see		MSDN GetWindowLong()
 *****************************************************/
inline DWORD WsObject::GetExStyle() { return ::GetWindowLong(m_hWnd, GWL_EXSTYLE); }

/**************************************************//**
 * @brief	設定視窗、控制項擴展樣式 (ExStyle)
 * @param	[in] dwExStyle	視窗擴展樣式
 * @return	@c DWORD
 *			- 操作成功傳回: ExSytle 值
 *			- 操作失敗傳回: 0，調用 GetLastError 取得錯誤訊息
 * @see		MSDN GetWindowLong()
 *****************************************************/
inline DWORD WsObject::SetExStyle(DWORD dwExStyle) { return ::SetWindowLong(m_hWnd, GWL_EXSTYLE, (LONG)dwExStyle); }

/**************************************************//**
 * @brief	取得視窗、控制項矩形尺寸
 * @param	[out] prc	RECT 結構指標
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::GetFrameRect(LPRECT prc) { return::GetWindowRect(m_hWnd, prc); }

/**************************************************//**
 * @brief	取得視窗、控制項工作區，矩形邊界尺寸
 * @param	[out] prc	RECT 結構指標
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::GetClientRect(LPRECT prc) { return ::GetClientRect(m_hWnd, prc); }

/**************************************************//**
 * @brief	取得的父視窗(控制項)矩形尺寸
 * @param	[out] prc	RECT 結構指標
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::GetParentRect(LPRECT prc) { return ::GetWindowRect(m_hParent, prc); }

/**************************************************//**
 * @brief	取得父視窗(控制項)工作區，矩形尺寸
 * @param	[out] prc	RECT 結構指標
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::GetParentClientRect(LPRECT prc) { ::GetClientRect(m_hParent, prc); }

/**************************************************//**
 * @brief	取得子視窗、控制項尺寸
 * @param	[in]  idItem	子控制項 id
 * @param	[out] prc		RECT 結構指標
 * @return	@c Bool
 *	- 操作成功傳回: TRUE
 *	- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::GetChildRect(int idItem, LPRECT prc) { return ::GetWindowRect(::GetDlgItem(m_hWnd, idItem), prc); }

/**************************************************//**
 * @brief	取得子視窗、控制項工作區尺寸
 * @param	[in]  idItem	子控制項 id
 * @param	[out] prc		RECT 結構指標
 * @return	Bool
 *	- 操作成功傳回: TRUE
 *	- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline Bool WsObject::GetChildClientRect(int idItem, LPRECT prc) { return ::GetClientRect(::GetDlgItem(m_hWnd, idItem), prc); }

/**************************************************//**
 * @brief	設定視窗位置
 * @param	[in] x		視窗左上座標 X
 * @param	[in] y		視窗左上座標 Y
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 * @see		MSDN SetWindowPos
 *****************************************************/
inline Bool WsObject::SetPosition(int x, int y)
{
	const UINT flag = SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE;
	return ::SetWindowPos(m_hWnd, NULL, x, y, 0, 0, flag);
}

/**************************************************//**
 * @brief	設定視窗控制項矩形尺寸
 * @param	[in] wd		視窗寬度
 * @param	[in] ht		視窗高度
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 * @see		MSDN SetWindowPos
 *****************************************************/
inline Bool WsObject::SetSize(int wd, int ht)
{
	const UINT flag = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE;
	return ::SetWindowPos(m_hWnd, NULL, 0, 0, wd, ht, flag);
}

/**************************************************//**
 * @brief	取得目前位於最上層的子控制項 Handle
 * @return	@c HWND
 *			- 操作成功傳回: 子控制項 HWND
 *			- 操作失敗傳回: NULL，調用 GetLastError 取得錯誤訊息
 * @note	識別在子視窗連結清單的最上層子視窗，如果子視窗不存在，這個值是 NULL。\n
 *			傳回的指標可能是暫時的，而且不應儲存供之後使用。
 *****************************************************/
inline HWND WsObject::GetTopWindow() { return ::GetTopWindow(m_hWnd); }

/**************************************************//**
 * @brief	取得當前輸入焦點視窗
 * @return	@c HWND
 *			- 傳回不為零，目前焦點的視窗 HANDLE
 *			- 傳回 NULL，如果沒有焦點的視窗。
 *****************************************************/
inline HWND WsObject::GetFocus() { return ::GetFocus(); }

/**************************************************//**
 * @brief	設定視窗為輸入焦點
 * @return	@c HWND
 *			- 先前擁有輸入焦點的視窗物件的指標，如果沒有此視窗，則傳回 NULL 。
 *			- 傳回的指標是暫時的，而且不應儲存與保存給其他函式使用。
 *****************************************************/
inline HWND WsObject::SetFocus() { return ::SetFocus(m_hWnd); }

/******************************************************//**
 * @brief	設定視窗 ICON
 * @param	[in] hIcon	Handle of Icon
 *********************************************************/
inline void WsObject::SetIcon(HICON hIcon)
{
	HWND hWnd = m_hWnd;
	if (hWnd != NULL && hIcon != NULL) {
		::SendMessage(hWnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
	}
}

/**************************************************//**
 * @brief	取得程序模組 Handle
 * @return	@c HINSTANCE	程序模組 HANDLE
 * @note	取得物件內程序模組 hanlde，若視窗尚未建立將傳回 NULL
 *****************************************************/
inline HINSTANCE WsObject::GetModule() { return m_hModule; }

/**************************************************//**
 * @brief	取得父視窗操作 Handle
 * @return	@c HWND	程序模組 hanlde
 * @note	取得物件父視窗操作 handle，若非子項目將傳回 NULL
 *****************************************************/
inline HWND WsObject::GetParent()
{
	HWND hWnd = ::GetParent(m_hWnd);
	if (m_hParent == NULL || m_hParent != hWnd)
		m_hParent = hWnd;
}

/**************************************************//**
 * @brief	取得視窗或控制項操作 Handle
 * @return	@c HWND	程序模組 HANDLE
 * @note	取得窗操作 HANDLE，若視窗尚未建立將傳回 NULL
 *****************************************************/
inline HWND WsObject::GetHandle() { return m_hWnd; }

/**************************************************//**
 * @brief	取得子控制項 Handle
 * @param	[in] idItem	子項目 ID
 * @return	@c HWND
 *			- 操作成功傳回: 子控制項 HWND
 *			- 操作失敗傳回: NULL，調用 GetLastError 取得錯誤訊息
 *****************************************************/
inline HWND WsObject::GetChild(int idItem) { return ::GetDlgItem(m_hWnd, idItem); }

/**************************************************//**
 * @brief	取得視窗或控制項操作 ID
 * @return	@c inc	視窗或控制項 ID
 * @note	取得窗操作 HANDLE，若視窗尚未建立將傳回 NULL
 *****************************************************/
inline int  WsObject::GetID() { return m_idItem; }

/**************************************************//**
 * @brief	視窗或控制項已建立
 * @return	@c Bool
 *			- 視窗或控制項已建立傳回: TRUE
 *			- 視窗或控制項未建立傳回: FALSE
 * @note	取得窗操作 HANDLE，若視窗尚未建立將傳回 NULL
 *****************************************************/
inline Bool WsObject::IsExist() { return m_hWnd != NULL; }

#endif // !__AXEEN_CWINS_CWINSOBJECT_HH__
