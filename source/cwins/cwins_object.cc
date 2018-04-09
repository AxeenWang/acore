/**************************************************************************//**
 * @file	cwins_object.cc
 * @brief	cwins 視窗操作基底類別 : 成員函式
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_object.hh"

/**************************************************//**
 * @brief	建立指定字型
 * @param	[in] fontFace	字型名稱
 * @param	[in] size		字型尺寸
 * @param	[in] bBlod		是否要粗體
 * @param	[in] charset	指定字符集
 * @return	@c BOOL
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE
 *****************************************************/
BOOL WsObject::CreateFont(LPCTSTR fontFace, int size, BOOL bBlod, int charset)
{
	HDC hDC = NULL;
	int iHeight, iBold;
	LOGFONT lf;

	this->DeleteFont();
	hDC = ::GetDC(m_hWnd);
	iHeight = -MulDiv(size, ::GetDeviceCaps(hDC, LOGPIXELSY), 72);
	::ReleaseDC(m_hWnd, hDC);
	iBold = bBlod ? FW_BOLD : FW_NORMAL;

	// 設定 LONGFONT 結構內容
	memset((void*)&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = iHeight;                      // 字體高度
	lf.lfWidth = 0;                             // 字體闊度
	lf.lfEscapement = 0;                        // 字體斜度
	lf.lfOrientation = 0;                       // 底線斜度
	lf.lfWeight = iBold;                        // 字體粗細
	lf.lfItalic = FALSE;                        // 設定字體為斜體
	lf.lfUnderline = FALSE;                     // 設定字體底線
	lf.lfStrikeOut = FALSE;                     // 設定刪線
	lf.lfCharSet = charset;                     // 設定字元集
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;     // 字體輸出解析度
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;   // 字型擷取解析度
	lf.lfQuality = DEFAULT_QUALITY;             // 字體輪廓質素
	lf.lfPitchAndFamily = 0;                    // 字體的外觀參考(沒有所需字體時用)
	::lstrcpy(lf.lfFaceName, fontFace);			// 字體名稱
	
	// 建立字型
	m_hFont = ::CreateFontIndirect(&lf);
	return m_hFont != NULL;
}

/**************************************************//**
 * @brief	取得視窗工作區邊框尺寸
 * @return	@c int 邊界尺寸 (in pixel)
 *****************************************************/
int WsObject::GetBorderSize()
{
	HWND hWnd = m_hWnd;
	RECT rcw, rcc;

	if (hWnd == NULL) return 0;
	::GetClientRect(hWnd, &rcc);
	::GetWindowRect(hWnd, &rcw);
	return ((rcw.right - rcw.left) - rcc.right) / 2;
}

/**************************************************//**
 * @brief	設定視窗-工作區矩形邊界尺寸
 * @param	[in] wd		視窗寬度
 * @param	[in] ht		視窗高度
 * @return	@c BOOL
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 * @see		MSDN SetWindowPos
 *****************************************************/
BOOL WsObject::SetClientSize(int wd, int ht)
{
	const UINT flag = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE;
	HWND hWnd = m_hWnd;
	RECT rc;

	::SetRect(&rc, 0, 0, wd, ht);
	::AdjustWindowRectEx(&rc, ::GetWindowLong(hWnd, GWL_STYLE), ::GetMenu(hWnd) != NULL, 0);
	wd = (int)(rc.right - rc.left);
	ht = (int)(rc.bottom - rc.top);
	return ::SetWindowPos(hWnd, NULL, 0, 0, wd, ht, flag);
}

/**************************************************//**
 * @brief	設定視窗、控制項居中顯示
 *****************************************************/
void WsObject::SetCenterPosition()
{
	HWND hWnd = m_hWnd;
	HWND hParent = m_hParent;

	int  x, y, w, h;
	RECT rc;

	if (hWnd != NULL) {
		if (hParent == NULL) {
			if ((hParent = ::GetParent(hWnd)) == NULL) {
				// 取得作業環境畫面邊界
				x = GetSystemMetrics(SM_CXSCREEN);
				y = GetSystemMetrics(SM_CYSCREEN);
			}
			else {
				// 取得父視窗工作區邊界
				::GetClientRect(hParent, &rc);
				x = (int)(rc.right - rc.left + 1);
				y = (int)(rc.bottom - rc.top + 1);
			}
		}
		else {
			// 取得父視窗工作區邊界
			::GetClientRect(hParent, &rc);
			x = (int)(rc.right - rc.left + 1);
			y = (int)(rc.bottom - rc.top + 1);
		}

		if (this->GetFrameRect(&rc)) {
			// 計算居中值
			w = (int)(rc.right - rc.left);
			h = (int)(rc.bottom - rc.top);
			x = (x - w) >> 1;
			y = (y - h) >> 1;
			this->SetPosition(x, y);
		}
	}
}

/**************************************************//**
 * @brief	視窗結束前清理動作，摧毀所有已建立物件或記憶體配置。
 * @note	再視窗或控制項，調用 DestroyWindow 或 EndDialog 之前， \n
 *			必須先調用此成員函式，確保所有釋放所有已建立物件或記憶體配置
 *****************************************************/
void WsObject::InDestroyWindow()
{
	HWND hCtrl = m_hWnd;
	WNDPROC	fnProc = m_fnWndProc;

	// 返回系統預設訊息處理函式位址
	if (fnProc != NULL) {
		::SetWindowLongPtr(hCtrl, GWLP_WNDPROC, (LONG_PTR)fnProc);
		m_fnWndProc = NULL;
	}
	m_emCtrlsType = emCtrlEmpty;

	this->KillTimer();
	this->DeleteFont();

	m_hModule = NULL;
	m_hParent = NULL;
	m_hWnd = NULL;
	m_idItem = NULL;
	m_hFont = NULL;
	m_idTimer = 0;
}

/**************************************************//**
 * @brief	指定使用擴展通用 Window 控制項
 * @note	指定使用 ComboBox, ListView Tab...等等之控制項 \n
 *			若視窗程式指定 XP-Style 則必須使用。
 *****************************************************/
void WsObject::InitCommCtrl()
{
	// 在此設定一個靜態識別旗標，令所有繼承者，不會重複指定通用控制項
	static BOOL bCommctrl = FALSE;
	INITCOMMONCONTROLSEX icce;

	if (!bCommctrl) {
		// 指定啟用全部控制項
		icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icce.dwICC = ICC_WIN95_CLASSES;
		if (::InitCommonControlsEx(&icce)) bCommctrl = TRUE;
	}
}
