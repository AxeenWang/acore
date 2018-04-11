/**************************************************************************//**
 * @file	wp8_page.cc
 * @brief	WP8 標籤頁操作類別，成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_page.hh"

/**************************************************//**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details 虛擬函數，訊息處理函數
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c INT_PTR		訊息處理結果
 * @note	MessageDisopse 為虛擬函示，由衍生者重載重新定義動作內容
 *****************************************************/
INT_PTR WP8Page::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_SIZE:
		this->OnEventSize(wParam, lParam);
		break;
	case WM_CLOSE:
		this->OnEventClose(wParam, lParam);
		break;
	case WM_INITDIALOG:
		this->OnEventInitDialog(wParam, lParam);
		break;
	case WM_CTLCOLORDLG:
		// 依據指定筆刷重新繪製 Dialog
		if (this->Brush() != Null) return (INT_PTR)(this->Brush());
		break;
	default:
		return False;
	}
	return True;
}

/**************************************************//**
 * @brief	WM_SIZE 訊息處理 : 視窗尺寸變更
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Page::OnEventSize(WPARAM wParam, LPARAM lParam)
{
}

/**************************************************//**
 * @brief	WM_CLOSE 訊息處理 : 視窗關閉
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Page::OnEventClose(WPARAM wParam, LPARAM lParam)
{
	this->Brush(True);	// param : bRelease = True
	this->InDestroyWindow();
	::EndDialog(m_hWnd, 0);
}

/**************************************************//**
 * @brief	WM_INITDIALOG 訊息處理 : Dialog 建立
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Page::OnEventInitDialog(WPARAM wParam, LPARAM lParam)
{
}

/**************************************************//**
 * @brief	取得遊戲資料
 *****************************************************/
void WP8Page::LoadData()
{

}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Page::WP8Page()
	: WsDialog() {
	this->Brush();
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Page::~WP8Page() { }

/**************************************************//**
 * @brief	建立筆刷
 * @param	[in] bRelease 是否釋放筆刷
 * @return	@c HBRUSH 筆刷操作 handle
 *****************************************************/
HBRUSH WP8Page::Brush(Bool bRelease)
{
	static HBRUSH hBrush = Null;

	if (bRelease) {
		if (hBrush != Null) {
			// 刪除筆刷
			::DeleteObject(hBrush);
			hBrush = Null;
		}
	}
	else {
		if (hBrush == Null) {
			// 建立筆刷顏色
			hBrush = ::CreateSolidBrush(RGB(255, 255, 255));
		}
	}
	return hBrush;
}
