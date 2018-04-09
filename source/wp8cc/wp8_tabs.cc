/**************************************************************************//**
 * @file	wp8_tabs.cc
 * @brief	WP8cc 主視窗標籤操作類別，成員函式
 * @author	Swang
 * @date	2018-04-04
 * @date	2018-04-04
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_tabs.hh"

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Tabs::WP8Tabs()
	: WsTabs() {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Tabs::~WP8Tabs() { }

/**************************************************//**
 * @brief	建立控制項
 * @param	[in] hParent	父視窗操作 handle
 * @param	[in] idItem		控制項 ID	
 *****************************************************/
BOOL WP8Tabs::Create(HWND hParent, int idItem)
{
	const BOOL err = FALSE;
	const BOOL eok = TRUE;
	const DWORD dwStyle = WS_CLIPSIBLINGS | TCS_FIXEDWIDTH;	// | WS_BORDER;

	SaCTRLS ctrls;

	if (hParent == NULL || idItem <= 0)
		return err;

	// 建立 DMCWNDCTRLS 內容
	::memset(&ctrls, 0, sizeof(SaCTRLS));
	ctrls.hParent = hParent;
	ctrls.emType = emCtrlSysTabControl32;
	ctrls.pszName = NULL;
	ctrls.dwStyle = dwStyle;
	ctrls.dwExStyle = 0;
	ctrls.iPosx = 0;
	ctrls.iPosy = 0;
	ctrls.iWidth = 0;
	ctrls.iHeight = 0;
	ctrls.idItem = idItem; // conctrller item id
	ctrls.fnWndProcess = NULL;
	
	if (this->CreateUseHotCodes(&ctrls)) {
		this->InitTab();
		return eok;
	}
	return err;
}

/**************************************************//**
 * @brief	建立標籤
 *****************************************************/
void WP8Tabs::InitTab()
{
	const TCHAR* szItem[] = {
		TEXT("競走馬"),
		TEXT("幼駒"),
		TEXT("繁殖牝馬"),
		TEXT("種牡馬"),
		TEXT("調教師"),
		TEXT("騎手"),
		TEXT("馬主"),
		TEXT("比賽相關")
	};
	const int len = sizeof(szItem) / sizeof(TCHAR*);

	// 建立標籤
	for (int i = 0; i < len; i++) {
		if (!this->InsertItem(i, szItem[i])) {
			this->DeleteAllItem();
			::PostMessage(m_hParent, WM_WP8ERROR, (WPARAM)emErrInitTabItem, 0);
		}
	}
}
