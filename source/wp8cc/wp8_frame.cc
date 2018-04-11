/**************************************************************************//**
 * @file	wp8_frame.cc
 * @brief	WP8CC 主視窗類別
 * @author	Swang
 * @date	2018-04-03
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_frame.hh"

/**************************************************//**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details 虛擬函數，訊息處理函數
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c LRESULT		訊息處理結果
 * @note	MessageDisopse 為虛擬函示，由衍生者重載重新定義動作內容
 *****************************************************/
LRESULT WP8Frame::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_CREATE:
		this->OnEventCreate(wParam, lParam);
		break;
	//case WM_DESTROY:
	//	::PostQuitMessage(0);
		break;
	case WM_SIZE:
		this->OnEventSize(wParam, lParam);
		break;
	case WM_CLOSE:
		this->OnEventClose(wParam, lParam);
		break;
	case WM_NOTIFY:
		this->OnEventNotify(wParam, lParam);
		break;
	case WM_WP8FUNC:
		this->OnEventWP8Func(wParam, lParam);
		break;
	case WM_WP8ERROR:
		this->OnEventWP8Error(wParam, lParam);
		break;
	default:
		return ::DefWindowProc(m_hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

/**************************************************//**
 * @brief	WM_CREATE 訊息處理 : 視窗建立
 * @param	[in] wParam	訊息參數
 * @param	[in] lParam	訊息參數
 *****************************************************/
void WP8Frame::OnEventCreate(WPARAM wParam, LPARAM lParam)
{
	this->InitFrame();
	this->InitTabs();
	this->InitPage();
	this->InitPosition();
}

/**************************************************//**
 * @brief	WM_SIZE 訊息處理 : 視窗尺寸變更
 * @param	[in] wParam	訊息參數
 * @param	[in] lParam	訊息參數
 *****************************************************/
void WP8Frame::OnEventSize(WPARAM wParam, LPARAM lParam)
{
	WP8Tabs*	cTabs = m_cTabsObj;
	WP8Func*	cFunc = m_cFuncObj;
	WP8Page*	cPage;
	int x, y, wd, ht;
	RECT rc1, rc2, rc3;

	// 設定 Tab 顯示位置
	if (cTabs == NULL) return;
	x = y = 0;
	wd = (int)LOWORD(lParam);
	ht = (int)HIWORD(lParam);
	//cTabs->SetPosition(x, y);
	cTabs->SetSize(wd, ht);

	// 設定功能頁顯示位置
	if (cFunc == NULL) return;
	cTabs->GetClientRect(&rc1);
	cTabs->GetItemRect(0, &rc2);
	cFunc->GetFrameRect(&rc3);
	x = WP8_FUNC_X;
	y = rc2.bottom - rc2.top + WP8_FUNC_Y;
	wd = (rc1.right - rc1.left) - (x << 1);
	ht = rc3.bottom - rc3.top;
	//cFunc->SetPosition(x, y);
	cFunc->SetSize(wd, ht);

	// 設定標籤頁面位置
	x = WP8_TAB_PAGE_X;
	y = rc3.bottom - rc3.top + y + WP8_TAB_PAGE_Y;
	ht = rc1.bottom - rc1.top - y - (WP8_TAB_PAGE_Y >> 1);

	size_t len = m_vPage.size();
	for (size_t i = 0; i < len; i++) {
		cPage = m_vPage[i];
		if (cPage == NULL) return;
		//cPage->SetPosition(x, y);
		cPage->SetSize(wd, ht);
	}
}

/**************************************************//**
 * @brief	WM_CLOSE 訊息處理 : 視窗關閉
 * @param	[in] wParam	訊息參數
 * @param	[in] lParam	訊息參數
 *****************************************************/
void WP8Frame::OnEventClose(WPARAM wParam, LPARAM lParam)
{
	WP8Page* cPage;
	size_t len = m_vPage.size();
	for (size_t i = 0; i < len; i++) {
		if ((cPage = m_vPage[i]) != NULL) {
			::SendMessage(cPage->GetHandle(), WM_CLOSE, 0, 0);
		}
	}
	this->Release();
	this->InDestroyWindow();
	::PostQuitMessage(0);
}

/**************************************************//**
 * @brief	WM_NOTIFY 訊息處理 : 額外訊息通知
 * @param	[in] wParam	訊息參數
 * @param	[in] lParam	訊息參數
 *****************************************************/
void WP8Frame::OnEventNotify(WPARAM wParam, LPARAM lParam)
{
	LPNMHDR p = (LPNMHDR)lParam;

	// 被選擇的標籤有變化，進行 Dialog 頁面切換
	if (p->code == TCN_SELCHANGE) {
		WP8Tabs* cTabs = m_cTabsObj;
		if (cTabs != NULL) {
			int index = cTabs->GetCursel();
			this->TabSelectChange(index);
		}
	}
}

/**************************************************//**
 * @brief	WM_WP8FUNC	子視窗 WP8Func 訊息通知
 * @param	[in] wParam	WP8Func 指定功能
 *			- 0	要求讀取遊戲資料
 *			- 1 保留
 * @param	[in] lParam	未使用
 *****************************************************/
void WP8Frame::OnEventWP8Func(WPARAM wParam, LPARAM lParam)
{
	EmWP8FUNCPARAM code = (EmWP8FUNCPARAM)wParam;
	switch (code) {
	case emWP8FuncLoad:
		this->LoadGameData();
		break;
	default: ;
	}
}

/**************************************************//**
 * @brief	WM_WP8ERROR 錯誤發生訊息通知
 * @param	[in] wParam	錯誤代碼
 * @param	[in] lParam	訊息參數
 *****************************************************/
void WP8Frame::OnEventWP8Error(WPARAM wParam, LPARAM lParam)
{
	::SysError((EmWP8ERROR)wParam, m_hWnd);
	this->PostMessage(WM_CLOSE, 0, 0);
}

/**************************************************//**
 * @brief	標籤改變
 * @param	[in] index	新觸發標籤索引，若傳入值小於零，則全部頁面隱藏
 *****************************************************/
void WP8Frame::TabSelectChange(int index)
{
	WP8Page* cPage;
	size_t len = m_vPage.size();
	int pev = m_iPage;

	// 隱藏所有頁面?
	if (index < 0) {
		for (size_t i = 0; i < len; i++) {
			if ((cPage = m_vPage[i]) != NULL) {
				cPage->Hide();
			}
		}
		return;
	}

	// 改變頁面顯示
	if (index < len) {
		if ((cPage = m_vPage[pev]) != NULL)
			cPage->Hide();
		if ((cPage = m_vPage[index]) != NULL) {
			cPage->Show();
			m_iPage = index;
		}
	}
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Frame::WP8Frame()
	: WsFrame()
	, m_cTabsObj(NULL)
	, m_cFuncObj(NULL)
	, m_iPage(0) {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Frame::~WP8Frame() { }

/**************************************************//**
 * @brief	建立 WP8cc 主視窗框架 (Dialog)
 * @param	[in] hInstance 程序模組 handle
 *****************************************************/
Bool WP8Frame::Create(HINSTANCE hInstance)
{
	const Bool err = FALSE;
	const DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	const int wd = WP8_DEFAULT_WIDTH;
	const int ht = WP8_DEFAULT_HEIGHT;
	SaFRAME ws;

	if (hInstance == NULL) return err;

	::memset((void*)&ws, 0, sizeof(ws));
	ws.hInstance = hInstance;
	ws.hWndParent = NULL;
	ws.fnWndProc = NULL;
	ws.pszClassName = ::GetNamePark(emNameClassName);
	ws.pszTitleName = ::GetNamePark(emNameTitleName);
	ws.iPosx = 0;
	ws.iPosy = 0;
	ws.iWidth = wd;
	ws.iHeight = ht;
	ws.uClassStyle = 0;
	ws.hBackground = (HBRUSH)(COLOR_WINDOW + 1);
	ws.hIcon = NULL;
	ws.hIconSm = NULL;
	ws.hCursor = NULL;
	ws.dwStyle = dwStyle;
	ws.dwExStyle = 0;
	ws.idItem = 0;

	if (!this->InRegisterClass(&ws))
		return err;
	return this->InCreateWindow(&ws);
}

/**************************************************//**
 * @brief	讀取遊戲資料
 *****************************************************/
void WP8Frame::LoadGameData()
{
	HWND hWnd = m_hWnd;
	WP8Cheat* wp = ::GetCheat();
	WP8Tabs* cTabs = m_cTabsObj;
	WP8Page* cPage;

	// 物件尚未建立
	if (wp == NULL) {
		wp = ::StartCheat();
		if (wp == NULL) {
			::SysError(emErrWP8Cheat, hWnd);
			return;
		}
	}

	// 遊戲尚未建立掛勾
	if (!wp->IsHooking()) {
		if (!wp->WatchingYou()) {
			::SysError(emErrGameNotFound, hWnd);
			return;
		}
	}

	// 讀取遊戲時間
	int t = (int)wp->GetCurrentWeekNumber(FALSE);
	int m = (int)wp->GetCurrentMonth();
	int w = (int)wp->GetCurrentWeek();
	this->ModifyTitle(t, m, w);

	wp->LoadHorseAbility();

	// 通知旗下各子控制項、視窗進行讀取與版面佈局
	int cursel = cTabs->GetCursel();
	if (cursel != -1) {
		cPage = m_vPage[cursel];
		if (cPage != NULL) {
			cPage->LoadData();
		}
	}
}

/**************************************************//**
 * @brief	修改視窗標題內容
 * @param	[in] t 週數
 * @param	[in] m 月份
 * @param	[in] w 週份
 *****************************************************/
void WP8Frame::ModifyTitle(int t, int m, int w)
{
	const TCHAR* fmt = TEXT("%s - %d 月 %d 週 (第 %d 週)");
	TCHAR szText[MAX_PATH];

	::wsprintf(szText, fmt, ::GetNamePark(emNameTitleName), m, w, t);
	this->SetText(szText);
}

/**************************************************//**
 * @brief	初始化視窗框架內容
 *****************************************************/
void WP8Frame::InitFrame()
{
	const TCHAR* szfont = TEXT("Microsoft JhengHei");	//TEXT("Meiryo UI");	//TEXT("微軟正黑體");
	const int ifont = 11;

	this->SetIcon(::LoadIcon(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
	this->CreateFont(szfont, ifont, FALSE);

	this->SetCenterPosition();
	this->Update();
	this->Show();
}

/**************************************************//**
 * @brief	建立標籤控制項
 *****************************************************/
void WP8Frame::InitTabs()
{
	HWND hWnd = m_hWnd;
	HFONT hFont = m_hFont;
	WP8Tabs* cTab = new (std::nothrow) WP8Tabs();

	for (;;) {
		if (cTab == NULL) break;
		if (!cTab->Create(hWnd, IDC_WP8TABS)) break;
		m_cTabsObj = cTab;
		if (hFont != NULL) { cTab->SetFont(m_hFont); }
		return;
	}
	this->PostMessage(WM_WP8ERROR, (WPARAM)emErrInitTabs, 0);
}

/**************************************************//**
 * @brief	建立標籤頁面 (Dialog)
 *****************************************************/
void WP8Frame::InitPage()
{
	HWND hWnd = m_hWnd;
	WP8Tabs* cTab = m_cTabsObj;
	WP8Func* cFunc;
	WP8Page* cPage;
	int len;

	for (;;) {
		if (m_cTabsObj == NULL) break;

		// 建立功能頁面
		cFunc = new (std::nothrow) WP8Func();
		if (cFunc == NULL) break;

		m_cFuncObj = cFunc;
		if (!cFunc->CreateFromResource(hWnd, IDD_WP8FUNC, NULL)) break;
		cFunc->Show();

		len = cTab->GetItemCount();
		for (int i = 0; i < len; i++) {
			switch (i) {
			case 0:
				cPage = (WP8Page*)new (std::nothrow) WP8RaceFrame();
				break;
			case 7:
				cPage = (WP8Page*)new (std::nothrow) WP8RacingFrame();
				break;
			default:
				cPage = new (std::nothrow) WP8Page();
			}

			if (cPage == NULL) break;
			m_vPage.push_back(cPage);
			cPage->CreateFromResource(hWnd, i + IDD_TAB_PAGE_01, NULL);
			cPage->Hide();
		}
		if (m_vPage.size() < len) break;
		m_vPage[0]->Show();
		return;
	}
	this->PostMessage(WM_WP8ERROR, (WPARAM)emErrInitPage, 0);
}

/**************************************************//**
 * @brief	初始化各子項目顯示位置
 *****************************************************/
void WP8Frame::InitPosition()
{
	WP8Tabs*	cTabs = m_cTabsObj;
	WP8Func*	cFunc = m_cFuncObj;
	WP8Page*	cPage;
	int x, y, wd, ht;
	RECT rc1, rc2, rc3;

	// 設定 Tab 顯示位置
	this->GetClientRect(&rc1);
	x = y = 0;
	wd = rc1.right - rc1.left;
	ht = rc1.bottom - rc1.top;
	cTabs->SetPosition(x, y);
	cTabs->SetSize(wd, ht);

	// 設定功能頁顯示位置
	cTabs->GetClientRect(&rc1);
	cTabs->GetItemRect(0, &rc2);
	cFunc->GetFrameRect(&rc3);
	x = WP8_FUNC_X;
	y = rc2.bottom - rc2.top + WP8_FUNC_Y;
	wd = (rc1.right - rc1.left) - (x << 1);
	ht = rc3.bottom - rc3.top;
	cFunc->SetPosition(x, y);
	cFunc->SetSize(wd, ht);

	// 設定標籤頁面位置
	x = WP8_TAB_PAGE_X;
	y = rc3.bottom - rc3.top + y + WP8_TAB_PAGE_Y;
	ht = rc1.bottom - rc1.top - y - (WP8_TAB_PAGE_Y >> 1);

	size_t len = m_vPage.size();
	for (size_t i = 0; i < len; i++) {
		cPage = m_vPage[i];
		cPage->SetPosition(x, y);
		cPage->SetSize(wd, ht);
	}
}

/**************************************************//**
 * @brief	釋放已建立物件，釋放已配置記憶體
 *****************************************************/
void WP8Frame::Release()
{
	WP8Page* cPage;
	size_t len = (int)m_vPage.size();

	// 釋放 Dialog 物件
	for (size_t i = 0; i < len; i++) {
		cPage = m_vPage[i];
		SAFE_DELETE(cPage);
	}
	m_vPage.clear();
	m_vPage.shrink_to_fit();
	SAFE_DELETE(m_cFuncObj);
	SAFE_DELETE(m_cTabsObj);
}
