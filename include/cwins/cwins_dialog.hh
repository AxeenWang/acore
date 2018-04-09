/**************************************************************************//**
 * @file	cwins_dialog.hh
 * @brief	視窗操作 : 控制項 Dialog 類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSDIALOG_HH__
#define __AXEEN_CWINS_CWINSDIALOG_HH__
#include "cwins_ctrls.hh"

/******************************************************//**
 * @class	WsDialog
 * @brief	視窗操作 : 控制項 Dialog 類別
 * @author	Swang
 * @note	繼承 WsCtrls，Dialog 對話框操作類別
 *********************************************************/
class WsDialog : public WsCtrls
{
protected:
	static  INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual INT_PTR MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);

public:
	WsDialog();
	virtual ~WsDialog();
	BOOL CreateFromResource(HWND hParent, int idItem, void* pvUnknow, BOOL bModule=FALSE);
	BOOL CreateFromWindowEx(int x, int y, int wd, int ht, HWND hParent, int idItem, void* pvUnknow, BOOL bModule=FALSE);
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsDialog::WsDialog() : WsCtrls(emCtrlDialogBox) { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsDialog::~WsDialog() { }

#endif  // !__AXEEN_CWINS_CWINSDIALOG_HH__
