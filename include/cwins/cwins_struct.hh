/**************************************************************************//**
 * @file	cwins_struct.hh
 * @brief	cwins library 資料結構
 * @author	Swang
 * @date	2018-03-31
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSSTRUCT_HH__
#define __AXEEN_CWINS_CWINSSTRUCT_HH__

/******************************************************//**
 * @brief	列舉 Microsoft Window 控制項
 * @details	配合 WsCtrls 類別使用
 *			- Ws::GetControlClassName 取得控制項 Class 名稱
 *			- 依據指定列舉內容建立對應的 Window 控制項	
 *********************************************************/
enum EmCTRLS {
	emCtrlPassStart = 0,		//!< 起始識別符號
	emCtrlButton,				//!< Button
	emCtrlComboBox,				//!< Combo Box
	emCtrlEditBox,				//!< Edit control.
	emCtrlListBox,				//!< List box.
	emCtrlMDIClient,			//!< MDI client window.
	emCtrlScrollBar,			//!< Scroll bar.
	emCtrlStatic,				//!< Static control.

	emCtrlComboLBox,			//!< List box contained in a combo box.
	emCtrlDDEMLEvent,			//!< Dynamic Data Exchange Management Library (DDEML) events.
	emCtrlMessage,				//!< Message-only window.
	emCtrlDu32768,				//!< Menu.
	emCtrlDu32769,				//!< Desktop window.
	emCtrlDialogBox,			//!< Dialog box. (32770)
	emCtrlDu32771,				//!< Task switch window.
	emCtrlDu32772,				//!< Icon titles.

	emCtrlToolbarWindow32,		//!< Toolbar
	emCtrlTooltips_class32,		//!< Tooltip
	emCtrlMsctls_statusbar32,	//!< Status bar
	emCtrlSysTreeView32,		//!< Tree view
	emCtrlSysListView32,		//!< List view
	emCtrlSysAnimate32,			//!< Animation
	emCtrlSysHeader32,			//!< Header
	emCtrlMsctls_hotkey32,		//!< Hot-key
	emCtrlMsctls_progress32,	//!< Progress bar
	emCtrlRICHEDIT,				//!< Rich edit
	emCtrlMsctls_updown32,		//!< Up-down
	emCtrlSysTabControl32,		//!< Tab
	emCtrlPassEnd,				//!< 結束識別符號
	emCtrlEmpty = -1			//!< 錯誤識別符號
};

/******************************************************//**
 * @brief	ListView Column 內容顯示位置巨集
 *********************************************************/
#define LVCOLUMN_ALIGN_LEFT		0	//!< ListView Column 顯示位置靠左
#define LVCOLUMN_ALIGN_RIGHT	1	//!< ListView Column 顯示位置靠右
#define LVCOLUMN_ALIGN_CENTER	2	//!< ListView Column 顯示位置居中
#define LVCOLUMN_ALIGN_PASSEND	3	//!< ListView Column 結尾識別

/******************************************************//**
 * @struct	SaLVCOLUMN
 * @brief	建立 Listview 控制項， Column 資訊設定
 * @details	ListView REPORT style Column 文字顯示與對齊方式
 *********************************************************/
struct SaLVCOLUMN {
	int				iWidth;					//!< 寬度
	int				iAlign;					//!< 對齊方式 參照 LVCOLUMN_ALIGN_LEFT、LVCOLUMN_ALIGN_RIGHT、LVCOLUMN_ALIGN_CENTER
	const TCHAR*	pszText;				//!< 字串指標 for column
};
typedef SaLVCOLUMN*	PSaLVCOLUMN;	//!< SaLVCOLUMN 短程指標
typedef SaLVCOLUMN*	LPSaLVCOLUMN;	//!< SaLVCOLUMN 長程指標

/******************************************************//**
 * @struct	SaCTRLS
 * @brief	建立控制項之結構
 * @details	DmcCtrls 依據結構定義內容，建立相對應知控制項
 *********************************************************/
struct SaCTRLS {
	EmCTRLS			emType;			//!< conctrller type, see "EmCTRLS" enumlator
	const TCHAR*	pszName;		//!< conctrller item window text
	DWORD			dwStyle;		//!< conctrller item style
	DWORD			dwExStyle;		//!< conctrller item extern style
	int				iPosx;			//!< start draw position (x-coordination)
	int				iPosy;			//!< start draw position (y-coordination)
	int				iWidth;			//!< the window width
	int				iHeight;		//!< the window height
	int				idItem;			//!< conctrller item id
	HWND			hParent;		//!< handle of parent window
	WNDPROC			fnWndProcess;	//!< pointer of callback function
	void*			pvUnknow;		//!< pointer of user data
};
typedef SaCTRLS*	PSaCTRLS;		//!< SaCTRLS 短程指標
typedef SaCTRLS*	LPSaCTRLS;		//!< SaCTRLS 長程指標

/******************************************************//**
 * @struct	SaCTRLSPARAM
 * @brief	建立控制項額外資料
 * @note	使用 SetWindowLongPtr (GWLP_WNDPROC) 建立新訊息處理函式時 \n
			可先利用 SetWindowLongPtr (GWLP_USERDATA) 設定為此額外資料
 *********************************************************/
struct SaCTRLSPARAM {
	void*	pvObj;		//!< 控制項類別物件指標
	void*	pvParam;	//!< 額外資料指標
	void*	Reserved1;	//!< 保留未來擴充，亦可任意使用資料。
	void*	Reserved2;	//!< 保留未來擴充，亦可任意使用資料。
};
typedef SaCTRLSPARAM*	PSaCTRLSPARAM;	//!< SaCTRLSPARAM 短程指標
typedef SaCTRLSPARAM*	LPSaCTRLSPARAM;	//!< SaCTRLSPARAM 長程指標

/******************************************************//**
 * @struct	SaDIALOGPARAM
 * @brief	建立 Dialog 額外參數結構
 * @details	Dialog 被建立時會發出 WM_INITDIALOG 訊息
 *
 *	WM_INITDIALOG
 *	- wParam =	控制項接收默認鍵盤焦點的 HWND
 *	- lParam =	附加初始化數據。\n
 *				使用 CreateDialogIndirectParam、CreateDialogParam、DialogBoxIndirectParam、DialogBoxParam 功能建立 Dialog\n
 *				該數據將作為 lParam 參數傳遞給系統 。\n
 *				對於屬性表，該參數是指向用於創建頁面的 PROPSHEETPAGE 結構的指標。\n
 *				如果使用其他對話框功能建立，則此參數為零。
 *********************************************************/
struct SaDIALOGPARAM {
	void* pvDialog;				//!< 存放物件指標 (this)
	void* pvParam;				//!< 存放其他資訊
};
typedef SaDIALOGPARAM*	PSaDIALOGPARAM;		//!< SaDIALOGPARAM 短程指標
typedef SaDIALOGPARAM*	LPSaDIALOGPARAM;	//!< SaDIALOGPARAM 長程指標

/**************************************************//**
 * @struct	SaFRAME
 * @brief	建立標準視窗框架結構
 * @details 依據結構內容，使用 DmcFrame 建立對應視窗框架
 *****************************************************/
struct SaFRAME {
	HINSTANCE	hInstance;		//!< set handle of instance (handle of process module)
	HWND		hWndParent;		//!< set handle of parent window
	WNDPROC		fnWndProc;		//!< set a window call-back function pointer
	LPCTSTR		pszClassName;	//!< pointer of class name
	LPCTSTR		pszTitleName;	//!< pointer of window's name
	int			iPosx;			//!< set display window x-coordinate
	int			iPosy;			//!< set display window y-coordinate
	int			iWidth;			//!< set window client-area width
	int			iHeight;		//!< set window client-area height
	UINT		uClassStyle;	//!< set register window class style
	HBRUSH		hBackground;	//!< set wndow background color
	HICON		hIcon;			//!< set handle of icon
	HICON		hIconSm;		//!< set handle of small icon
	HCURSOR		hCursor;		//!< set handle of cursor
	DWORD		dwStyle;		//!< set window style
	DWORD		dwExStyle;		//!< set window extend style
	int			idItem;			//!< set item ID
};
typedef SaFRAME*	PSaFRAME;	//!< SaFRAME 短程指標
typedef SaFRAME*	LPSaFRAME;	//!< SaFRAME 長程指標

#endif // !__AXEEN_CWINS_CWINSSTRUCT_HH__
