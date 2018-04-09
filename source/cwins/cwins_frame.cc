/**************************************************************************//**
 * @file	cwins_frame.cc
 * @brief	視窗操作 : 視窗操作類別，成員函式
 * @author	Swang
 * @date	2010-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#include "cwins\cwins_frame.hh"

/**************************************************//**
 * @brief	視窗訊息處理
 * @param	[in] hWnd		視窗 Handle
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT		視窗訊息處理後結果
 * @note	此項必須為靜態函數，為視窗 Callback function
 *****************************************************/
LRESULT CALLBACK WsFrame::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    WsFrame* fmObj = NULL;

	// is window create message?
	if (uMessage == WM_CREATE) {
		fmObj = (WsFrame*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if (fmObj != NULL) {
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)fmObj);
			fmObj->m_hWnd = hWnd;
		}
	}
    
	// get user saved data form "GWLP_USERDATA" mode
	if ((fmObj = (WsFrame*)::GetWindowLongPtr(hWnd, GWLP_USERDATA)) == NULL) {
		// transfer window message in system default callback function
		return ::DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	// transfer window message in user callback function
	return fmObj->MessageDispose(uMessage, wParam, lParam);
}

/**************************************************//**
 * @brief	視窗訊息處理
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		參數 1
 * @param	[in] lParam		參數 2
 * @return	@c LRESULT		視窗訊息處理後結果
 * @note	此為虛擬函數，提供 WndProc 調用由衍生類別進行內容變更
 * @warning	當使用 DestroyWindow 結束視窗或控制項之前，必須先調用 InDestroyWindow 成員函式。
 * @warning 否則必須手動釋放已建立之物件與記憶體配置，否則必造成 memory leak。
 *****************************************************/
LRESULT WsFrame::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_CLOSE:
		::DestroyWindow(m_hWnd);
		break;
	default:
		return ::DefWindowProc(m_hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

/**************************************************//**
 * @brief	視窗訊息處理迴圈
 * @return	@c int	視窗結束狀態碼
 * @note	一個視窗模組程式必須建立一個訊息迴圈，已取得系統提供之訊息
 *****************************************************/
int WsFrame::Run()
{
    MSG message = { 0 };
    while (::GetMessage(&message, NULL, 0, 0))
    {
        // If wanna WS_TABSTOP work, must join this check
        if (!::IsDialogMessage(m_hWnd, &message))
        {
            ::TranslateMessage(&message);
            ::DispatchMessage(&message);
        }
    }
    return (int)message.wParam;
}

/**************************************************//**
 * @brief	建立一個範本視窗
 * @param	[in] hInstance	程序運行模組 Hanlde of Module
 * @return	@c BOOL
 *			- 運作成功傳回: TRUE
 *			- 運作失敗傳回: FALSE
 *****************************************************/
BOOL WsFrame::CreateFromWindowEx(HINSTANCE hInstance)
{
	const BOOL err = FALSE;
	const BOOL eok = TRUE;
	SaFRAME frm;

	if (hInstance == NULL) 	return err;

	::memset((void*)&frm, 0, sizeof(SaFRAME));
	frm.hInstance = hInstance;
	frm.hWndParent = NULL;
	frm.fnWndProc = NULL;
	frm.pszClassName = TEXT(DEFAULT_WNDS_CLASS);
	frm.pszTitleName = TEXT(DEFAULT_WNDS_TITLE);
	frm.iPosx = 0;
	frm.iPosy = 0;
	frm.iWidth = DEFAULT_WNDS_WIDTH;
	frm.iHeight = DEFAULT_WNDS_HEIGHT;
	frm.uClassStyle = 0;
	frm.hBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	frm.hIcon = NULL;
	frm.hIconSm = NULL;
	frm.hCursor = NULL;
	frm.dwStyle = DEFAULT_WNDS_STYLE;
	frm.dwExStyle = 0;
	frm.idItem = 0;

	if (!this->InRegisterClass(&frm))
		return err;
	if (!this->InCreateWindow(&frm))
		return err;

	this->SetClientSize(DEFAULT_WNDS_WIDTH, DEFAULT_WNDS_HEIGHT);
	this->SetCenterPosition();
	this->Show();
	this->Update();
	return eok;
}

/**************************************************//**
 * @brief	向系統註冊一個視窗類別
 * @param	[in] fmsPtr	SaFRAME 結構指標
 * @return	@c BOOL
 *			- 運作成功回傳: TRUE
 *			- 運作失敗回傳: FALSE
 * @see SaFRAME struct
 * @see MSDN WNDCLASSEX struct
 *****************************************************/
BOOL WsFrame::InRegisterClass(LPSaFRAME fmsPtr)
{
	const BOOL err = FALSE;

	UINT        uStyle = (CS_HREDRAW | CS_VREDRAW);    // | CS_DBLCLKS;
	HINSTANCE   hInst = NULL;
	HCURSOR     hCusr = NULL;
	HICON       hIcon = NULL;
	HBRUSH      hBrsh = NULL;
	WNDPROC     fnWndProc = NULL;
	WNDCLASSEX  wcex;

	if (fmsPtr == NULL) return err;

	// 填入註冊數據
	uStyle |= fmsPtr->uClassStyle;
	hInst = fmsPtr->hInstance;
	hCusr = fmsPtr->hCursor;
	hIcon = fmsPtr->hIcon;
	hBrsh = fmsPtr->hBackground;
	fnWndProc = fmsPtr->fnWndProc;

	// Check and set cursor
	if (hCusr == NULL)
		hCusr = ::LoadCursor(NULL, IDC_ARROW);

	// Check and set icon (use default application icon)
	if (hIcon == NULL)
		hIcon = ::LoadIcon(NULL, IDI_APPLICATION);

	// Check and set back ground color
	if (hBrsh == NULL)
		hBrsh = (HBRUSH)(COLOR_WINDOW + 1);

	// Check and set the callback function
	if (NULL == fnWndProc)
		fnWndProc = (WNDPROC)WsFrame::WndProc;

	// regist the window class
	memset((void*)&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);	// size of the WNDCLASSEX structure
	wcex.style = uStyle;				// the window style
	wcex.lpfnWndProc = fnWndProc;		// the callback function
	wcex.cbClsExtra = 0;				// nothing to do, always 0
	wcex.cbWndExtra = 0;				// nothing to do, always 0
	wcex.hInstance = hInst;				// handle of module
	wcex.hIcon = hIcon;					// handle of icon
	wcex.hCursor = hCusr;				// handle of cursor
	wcex.hbrBackground = hBrsh;			// handle of background
	wcex.lpszMenuName = NULL;			// pointer of menu name (string)
	wcex.lpszClassName = fmsPtr->pszClassName;	// pointer of class name (string)
	wcex.hIconSm = hIcon;				// pointer of icon for small icon using

	m_hModule = hInst;
	return ::RegisterClassEx(&wcex) != 0;
}

/**************************************************//**
 * @brief	建立視窗
 * @param	[in] fmsPtr	SaFRAME 結構指標
 * @return	BOOL 型別
 *	成功回傳 TRUE
 *	失敗回傳 FALSE
 *****************************************************/
BOOL WsFrame::InCreateWindow(LPSaFRAME fmsPtr)
{
	const	BOOL err = false;
	HWND	hWnd = NULL;
	HMENU	hMenu = NULL;
	DWORD	dwStyle = 0;    // WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	DWORD	dwExStyle = 0;
	intxu	idItem = 0;
	int		x, y, wd, ht;

	if (fmsPtr == NULL) return err;

	// save window sample info
	idItem = (intxu)fmsPtr->idItem;
	dwStyle |= fmsPtr->dwStyle;
	dwExStyle |= fmsPtr->dwExStyle;
	hMenu = (HMENU)idItem;
	x = fmsPtr->iPosx;
	y = fmsPtr->iPosy;
	wd = fmsPtr->iWidth;
	ht = fmsPtr->iHeight;

	// Is using default window style?
	if (dwStyle == 0) dwStyle = DEFAULT_WNDS_STYLE;

	// Create window
	hWnd = ::CreateWindowEx(
		dwExStyle,				// window extern style
		fmsPtr->pszClassName,	// window class name
		fmsPtr->pszTitleName,	// window name
		dwStyle,				// window style, "WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX"
		x,						// window position
		y,						// window position
		wd,						// window width
		ht,						// window height
		fmsPtr->hWndParent,		// handle of parent window
		hMenu,					// handle of menu or Item ID
		m_hModule,				// handle of instance
		(LPVOID)this);			// pointer of parameter
	return hWnd != NULL;
}
