/**************************************************************************//**
 * @file	wp8_racing.cc
 * @brief	WP8cc 比賽相關操作類別，成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_racing.hh"

//#####################################################
//
// WP8RacingFrame 類別成員函式
//
//#####################################################

/**************************************************//**
 * @brief	WM_SIZE 訊息處理 : 視窗尺寸變更
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8RacingFrame::OnEventSize(WPARAM wParam, LPARAM lParam)
{
	WP8RacingList* cList = m_cList;
	int wd = (int)LOWORD(lParam);
	int ht = (int)HIWORD(lParam);

	if (cList != Null) {
		cList->SetSize(wd, ht);
	}
}

/**************************************************//**
 * @brief	WM_CLOSE 訊息處理 : Dialog 關閉
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8RacingFrame::OnEventClose(WPARAM wParam, LPARAM lParam)
{
	this->Release();
	WP8Page::OnEventClose(wParam, lParam);
}

/**************************************************//**
 * @brief	WM_INITDIALOG 訊息處理 : Dialog 建立
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8RacingFrame::OnEventInitDialog(WPARAM wParam, LPARAM lParam)
{
	this->InitList();
}

/**************************************************//**
 * @brief	取得遊戲資料 : 比賽相關
 *****************************************************/
void WP8RacingFrame::LoadData()
{
	WP8Cheat* wp = ::GetCheat();
	WP8RacingList* lst = m_cList;

	if (wp == Null || lst == Null) return;	
	int track = wp->GetRacingTrack();
	TCHAR text[STRING_MAX];

	wp->LoadRacing();
	lst->DeleteAllItem();

	for (int i = 0; i < track; i++) {
		::wsprintf(text, TEXT("%d"), i+1);
		lst->InsertItem(i, 0, text);
		::lstrcpy(text, wp->GetRacingSpeedText(i));
		lst->SetItem(i, 2, text);
		::lstrcpy(text, wp->GetRacingTacticText(i));
		lst->SetItem(i, 3, text);
		::lstrcpy(text, wp->GetRacingWeightText(i));
		lst->SetItem(i, 4, text);
		::lstrcpy(text, wp->GetRacingJockeyText(i));
		lst->SetItem(i, 5, text);
	}
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8RacingFrame::WP8RacingFrame()
	: WP8Page()
	, m_cList(Null) {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8RacingFrame::~WP8RacingFrame() { this->Release(); }

/**************************************************//**
 * @brief	建立 List 物件
 *****************************************************/
void WP8RacingFrame::InitList()
{
	WP8RacingList* cList = new (std::nothrow) WP8RacingList();

	if (cList != Null) {
		RECT rc;
		m_cList = cList;
		if (cList->Create(m_hWnd, IDC_GAME_LIST)) {
			this->GetClientRect(&rc);
			cList->SetPosition(0, 0);
			cList->SetSize(rc.right - rc.left, rc.bottom - rc.top);
			return;
		}
	}
	::PostMessage(m_hParent, WM_WP8ERROR, (WPARAM)emErrInitGameList, 0);
}

/**************************************************//**
 * @brief	釋放已建立物件，釋放已配置記憶體
 *****************************************************/
void WP8RacingFrame::Release()
{
	SAFE_DELETE(m_cList);
}


//#####################################################
//
// WP8RacingList 類別成員函式
//
//#####################################################

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8RacingList::WP8RacingList()
	: WsListv() {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8RacingList::~WP8RacingList() { }

/**************************************************//**
 * @brief	建立 ListView 控制項
 * @param	[in] hParent	父視窗操作 handle
 * @param	[in] idItem		列表控制項 ID
 * @return	@c Bool
 *			- 函式運作成功傳回: True
 *			- 函式運作失敗傳回: False
 *****************************************************/
Bool WP8RacingList::Create(HWND hParent, int idItem)
{
	const Bool err = False;
	const Bool eok = True;

	// LVS_REPORT				: 設定成 Report 樣式
	// LVS_SHOWSELALWAYS		: 非當前使用視窗時，被選定 Item 仍以高亮反白顯示
	// LVS_EDITLABELS			: 子項目欄位可編輯
	DWORD	dwStyle = LVS_REPORT | LVS_SHOWSELALWAYS;
	// LVS_EX_FULLROWSELECT		: 選擇時，以全行高亮反白
	// LVS_EX_GRIDLINES			: 使用網格
	// LVS_EX_CHECKBOXES		: 帶有 Check Box
	// LVS_EX_HEADERDRAGDROP	: 讓 Listview Header(表頭) 顯示位置甩曳交換
	// LVS_EX_ONECLICKACTIVATE	: 單擊觸發
	// LVS_EX_TWOCLICKACTIVATE	: 雙擊觸發
	// LVS_EX_MULTIWORKAREAS	: 多工作區 (可複選項目)
	DWORD	dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;

	if (hParent == Null && idItem <= 0)
		return err;

	// 建立 List View
	if (this->CreateFromResource(::GetDlgItem(hParent, idItem), idItem)) {
		dwStyle |= this->GetStyle();
		dwExStyle |= this->GetExStyle();
		this->SetStyle(dwStyle);
		this->SetExStyle(dwExStyle);
		this->InitColumn();
		return eok;
	}
	return err;
}

/**************************************************//**
 * @brief	建立列表欄位
 *****************************************************/
void WP8RacingList::InitColumn()
{
	const SaLVCOLUMN lvc[] = {
		48,		LVCOLUMN_ALIGN_LEFT,	TEXT("賽道"),
		240,	LVCOLUMN_ALIGN_LEFT,	TEXT("馬名"),
		64,		LVCOLUMN_ALIGN_RIGHT,	TEXT("速度"),
		64,		LVCOLUMN_ALIGN_LEFT,	TEXT("戰略"),
		64,		LVCOLUMN_ALIGN_RIGHT,	TEXT("斤量"),
		120,	LVCOLUMN_ALIGN_LEFT,	TEXT("騎手"),
	};
	const int cblvc = sizeof(lvc) / sizeof(SaLVCOLUMN);
	TCHAR sz[MAX_PATH];

	for (int i = 0; i < cblvc; i++) {
		::lstrcpy(sz, lvc[i].pszText);
		this->InsertColumn(i, lvc[i].iWidth, lvc[i].iAlign, sz);
	}
}
