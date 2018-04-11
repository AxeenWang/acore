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
    WsFrame* fmObj = Null;

	// is window create message?
	if (uMessage == WM_CREATE) {
		fmObj = (WsFrame*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if (fmObj != Null) {
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)fmObj);
			fmObj->m_hWnd = hWnd;
		}
	}
    
	// get user saved data form "GWLP_USERDATA" mode
	if ((fmObj = (WsFrame*)::GetWindowLongPtr(hWnd, GWLP_USERDATA)) == Null) {
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
    while (::GetMessage(&message, Null, 0, 0))
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
 * @return	@c Bool
 *			- 運作成功傳回: True
 *			- 運作失敗傳回: False
 *****************************************************/
Bool WsFrame::CreateFromWindowEx(HINSTANCE hInstance)
{
	const Bool err = False;
	const Bool eok = True;
	SaFRAME frm;

	if (hInstance == Null) 	return err;

	::memset((void*)&frm, 0, sizeof(SaFRAME));
	frm.hInstance = hInstance;
	frm.hWndParent = Null;
	frm.fnWndProc = Null;
	frm.pszClassName = TEXT(DEFAULT_WNDS_CLASS);
	frm.pszTitleName = TEXT(DEFAULT_WNDS_TITLE);
	frm.iPosx = 0;
	frm.iPosy = 0;
	frm.iWidth = DEFAULT_WNDS_WIDTH;
	frm.iHeight = DEFAULT_WNDS_HEIGHT;
	frm.uClassStyle = 0;
	frm.hBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	frm.hIcon = Null;
	frm.hIconSm = Null;
	frm.hCursor = Null;
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
 * @return	@c Bool
 *			- 運作成功回傳: True
 *			- 運作失敗回傳: False
 * @see SaFRAME struct
 * @see MSDN WNDCLASSEX struct
 *****************************************************/
Bool WsFrame::InRegisterClass(LPSaFRAME fmsPtr)
{
	const Bool err = False;

	UINT        uStyle = (CS_HREDRAW | CS_VREDRAW);    // | CS_DBLCLKS;
	HINSTANCE   hInst = Null;
	HCURSOR     hCusr = Null;
	HICON       hIcon = Null;
	HBRUSH      hBrsh = Null;
	WNDPROC     fnWndProc = Null;
	WNDCLASSEX  wcex;

	if (fmsPtr == Null) return err;

	// 填入註冊數據
	uStyle |= fmsPtr->uClassStyle;
	hInst = fmsPtr->hInstance;
	hCusr = fmsPtr->hCursor;
	hIcon = fmsPtr->hIcon;
	hBrsh = fmsPtr->hBackground;
	fnWndProc = fmsPtr->fnWndProc;

	// Check and set cursor
	if (hCusr == Null)
		hCusr = ::LoadCursor(Null, IDC_ARROW);

	// Check and set icon (use default application icon)
	if (hIcon == Null)
		hIcon = ::LoadIcon(Null, IDI_APPLICATION);

	// Check and set back ground color
	if (hBrsh == Null)
		hBrsh = (HBRUSH)(COLOR_WINDOW + 1);

	// Check and set the callback function
	if (Null == fnWndProc)
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
	wcex.lpszMenuName = Null;			// pointer of menu name (string)
	wcex.lpszClassName = fmsPtr->pszClassName;	// pointer of class name (string)
	wcex.hIconSm = hIcon;				// pointer of icon for small icon using

	m_hModule = hInst;
	return ::RegisterClassEx(&wcex) != 0;
}

/**************************************************//**
 * @brief	建立視窗
 * @param	[in] fmsPtr	SaFRAME 結構指標
 * @return	Bool 型別
 *	成功回傳 True
 *	失敗回傳 False
 *****************************************************/
Bool WsFrame::InCreateWindow(LPSaFRAME fmsPtr)
{
	const	Bool err = false;
	HWND	hWnd = Null;
	HMENU	hMenu = Null;
	DWORD	dwStyle = 0;    // WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	DWORD	dwExStyle = 0;
	IntQu	idItem = 0;
	int		x, y, wd, ht;

	if (fmsPtr == Null) return err;

	// save window sample info
	idItem = (IntQu)fmsPtr->idItem;
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
	return hWnd != Null;
}
