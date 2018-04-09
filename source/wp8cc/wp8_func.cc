/**************************************************************************//**
 * @file	wp8_func.cc
 * @brief	WP8cc 功能頁面類別，成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_func.hh"

/**************************************************//**
 * @brief	Dialog 訊息處理 Callback fuction
 * @details 虛擬函數，訊息處理函數
 * @param	[in] uMessage	視窗訊息
 * @param	[in] wParam		訊息參數
 * @param	[in] lParam		訊息參數
 * @return	@c INT_PTR		訊息處理結果
 * @note	MessageDisopse 為虛擬函示，由衍生者重載重新定義動作內容
 *****************************************************/
INT_PTR WP8Func::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
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
	case WM_COMMAND:
		this->OnEventCommand(wParam, lParam);
		break;
	//case WM_CTLCOLORDLG:
		// 依據指定筆刷重新繪製 Dialog
	//	if (this->Brush() != NULL) return (INT_PTR)(this->Brush());
	//	break;
	default:
		return FALSE;
	}
	return TRUE;
}

/**************************************************//**
 * @brief	WM_SIZE 訊息處理 : 視窗尺寸變更
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Func::OnEventSize(WPARAM wParam, LPARAM lParam)
{
}

/**************************************************//**
 * @brief	WM_CLOSE 訊息處理 : 視窗關閉
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Func::OnEventClose(WPARAM wParam, LPARAM lParam)
{
	this->InDestroyWindow();
	::EndDialog(m_hWnd, 0);
}

/**************************************************//**
 * @brief	WM_INITDIALOG 訊息處理 : Dialog 建立
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Func::OnEventInitDialog(WPARAM wParam, LPARAM lParam)
{

}

/**************************************************//**
 * @brief	WM_COMMAND 訊息處理 : 命令觸發
 * @param	[in] wParam	參數 1
 * @param	[in] lParam 參數 2
 *****************************************************/
void WP8Func::OnEventCommand(WPARAM wParam, LPARAM lParam)
{
	// 子控制項觸發，取得控制項 ID
	UINT uCode = (UINT)LOWORD(wParam);

	if (uCode == IDC_WP8FUNC_BTN_LOAD) {
		::PostMessage(m_hParent, WM_WP8FUNC, (WPARAM)emWP8FuncLoad, 0);
	}
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Func::WP8Func()
	: WsDialog() {
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Func::~WP8Func() { }
