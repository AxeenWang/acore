/**************************************************************************//**
 * @file	wp8_race.cc
 * @brief	WP8cc 競走馬操作類別，成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_race.hh"

//#####################################################
//
// WP8RaceFrame 類別成員函式
//
//#####################################################

/**************************************************//**
 * @brief	WM_SIZE 訊息處理 : 視窗尺寸變更
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8RaceFrame::OnEventSize(WPARAM wParam, LPARAM lParam)
{
	WP8RaceList* cList = m_cList;
	int wd = (int)LOWORD(lParam);
	int ht = (int)HIWORD(lParam);

	if (cList != NULL) {
		cList->SetSize(wd, ht);
	}
}

/**************************************************//**
 * @brief	WM_CLOSE 訊息處理 : Dialog 關閉
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8RaceFrame::OnEventClose(WPARAM wParam, LPARAM lParam)
{
	this->Release();
	WP8Page::OnEventClose(wParam, lParam);
}

/**************************************************//**
 * @brief	WM_INITDIALOG 訊息處理 : Dialog 建立
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8RaceFrame::OnEventInitDialog(WPARAM wParam, LPARAM lParam)
{
	this->InitList();
}

/**************************************************//**
 * @brief	取得競走馬資料
 *****************************************************/
void WP8RaceFrame::LoadData()
{
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8RaceFrame::WP8RaceFrame()
	: WP8Page()
	, m_cList(NULL) {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8RaceFrame::~WP8RaceFrame() { }

/**************************************************//**
 * @brief	建立 List 物件
 *****************************************************/
void WP8RaceFrame::InitList()
{
	WP8RaceList* cList = new (std::nothrow) WP8RaceList();

	if (cList != NULL) {
		RECT rc;
		m_cList = cList;
		if (cList->Create(m_hWnd, IDC_RACE_LIST)) {
			this->GetClientRect(&rc);
			cList->SetPosition(0, 0);
			cList->SetSize(rc.right - rc.left, rc.bottom - rc.top);
			return;
		}
	}
	::PostMessage(m_hParent, WM_WP8ERROR, (WPARAM)emErrInitRaceList, 0);
}

/**************************************************//**
 * @brief	釋放已建立物件，釋放已配置記憶體
 *****************************************************/
void WP8RaceFrame::Release()
{
	SAFE_DELETE(m_cList);
}


//#####################################################
//
// WP8RaceList 類別成員函式
//
//#####################################################

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8RaceList::WP8RaceList() : WsListv() { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8RaceList::~WP8RaceList() { }

/**************************************************//**
 * @brief	建立 ListView 控制項
 * @param	[in] hParent	父視窗操作 handle
 * @param	[in] idItem		列表控制項 ID
 * @return	@c Bool
 *			- 函式運作成功傳回: TRUE
 *			- 函式運作失敗傳回: FALSE
 *****************************************************/
Bool WP8RaceList::Create(HWND hParent, int idItem)
{
	const Bool err = FALSE;
	const Bool eok = TRUE;

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

	if (hParent == NULL && idItem <= 0)
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
void WP8RaceList::InitColumn()
{
	const SaLVCOLUMN lvc[] = {
		240,	LVCOLUMN_ALIGN_LEFT,	TEXT("馬名"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("國"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("性"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("年"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("SP"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("ST"),
		80,		LVCOLUMN_ALIGN_CENTER,	TEXT("SP率"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("力"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("瞬"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("勝"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("柔"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("精"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("賢"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("健"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("總"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("氣"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("場"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("腳質"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("成型"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("成力"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("成度"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("壽命"),
		64,		LVCOLUMN_ALIGN_RIGHT,	TEXT("經驗值"),
		64,		LVCOLUMN_ALIGN_RIGHT,	TEXT("レース勘"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("調子"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("疲勞"),
		64,		LVCOLUMN_ALIGN_CENTER,	TEXT("馬體重"),
		96,		LVCOLUMN_ALIGN_CENTER,	TEXT("距離適應"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("仔出"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("毛色"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("高"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("長"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("跳"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("小"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("左"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("右"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("腳"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("喉"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("腰"),
		32,		LVCOLUMN_ALIGN_CENTER,	TEXT("遅"),
		240,	LVCOLUMN_ALIGN_LEFT,	TEXT("特性"),
		180,	LVCOLUMN_ALIGN_LEFT,	TEXT("父馬"),
		180,	LVCOLUMN_ALIGN_LEFT,	TEXT("父系"),
		180,	LVCOLUMN_ALIGN_LEFT,	TEXT("母馬"),
		180,	LVCOLUMN_ALIGN_LEFT,	TEXT("牝系"),
		48,		LVCOLUMN_ALIGN_RIGHT,	TEXT("出走"),
		120,	LVCOLUMN_ALIGN_LEFT,	TEXT("戰績"),
		120,	LVCOLUMN_ALIGN_LEFT,	TEXT("前走"),
		120,	LVCOLUMN_ALIGN_LEFT,	TEXT("次走"),
		80,		LVCOLUMN_ALIGN_LEFT,	TEXT("等級"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("賞金"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("本賞金"),
		80,		LVCOLUMN_ALIGN_LEFT,	TEXT("生產國"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("馬主"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("牧場"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("調教師"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("騎手"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("現役"),
		48,		LVCOLUMN_ALIGN_CENTER,	TEXT("史實"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("史實番號"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("能力番號"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("馬番號"),
		80,		LVCOLUMN_ALIGN_RIGHT,	TEXT("繼承特性")
	};
	const int cblvc = sizeof(lvc) / sizeof(SaLVCOLUMN);
	TCHAR sz[MAX_PATH];

	for (int i = 0; i < cblvc; i++) {
		::lstrcpy(sz, lvc[i].pszText);
		this->InsertColumn(i, lvc[i].iWidth, lvc[i].iAlign, sz);
	}
}
