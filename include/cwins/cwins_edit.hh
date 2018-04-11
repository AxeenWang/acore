/**************************************************************************//**
 * @file	cwins_edit.hh
 * @brief	視窗操作 : 控制項 EditBox 類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-03-26
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSEDIT_HH__
#define __AXEEN_CWINS_CWINSEDIT_HH__
#include "cwins_ctrls.hh"

/**************************************************//**
 * @class	WsEdit
 * @brief	視窗控制 - 控制項基底類別
 * @author	Swang
 * @note
 * 控制項與操作基底類別
 *	- 繼承 DmcCtrls
 *****************************************************/
class WsEdit : public WsCtrls
{
public:
	WsEdit();
	virtual ~WsEdit();
	Bool CreateFromResource(HWND hEdit, int idItem);
	Bool CreateFromWindowEx(LPCTSTR pszName, int x, int y, int wd, int ht, HWND hParent, int idItem);
};

/******************************************************//**
 * @brief 建構式
 *********************************************************/
inline WsEdit::WsEdit() : WsCtrls(emCtrlEditBox) { }

/******************************************************//**
 * @brief 建構式
 *********************************************************/
inline WsEdit::~WsEdit() { }

/**************************************************//**
 * @brief	結合資源檔或其他已存在的 EditBox 控制項
 * @param	[in] hEdit	子項目視窗 handle
 * @param	[in] idItem	控制項 ID
 * @return	@c Bool
 *			- 操作成功傳回: TRUE
 *			- 操作失敗傳回: FALSE，調用 GetLastError 取得錯誤訊息
 ******************************************************/
inline Bool WsEdit::CreateFromResource(HWND hEdit, int idItem) { return this->CombineResource(hEdit, idItem); }

#endif // !__AXEEN_CWINS_CWINSEDIT_HH__
