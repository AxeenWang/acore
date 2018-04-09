/**************************************************************************//**
 * @file	wp8_func.hh
 * @brief	WP8cc 功能頁面類別
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8FUNC_HH__
#define __AXEEN_WP8_WP8FUNC_HH__
#include "wp8_define.hh"

/**************************************************//**
 * @class	WP8Func
 * @brief	WP8cc 功能頁面類別
 * @author	Swang
 * @note	繼承 WsDialog
 *****************************************************/
class WP8Func : public WsDialog
{
protected:
	INT_PTR MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);
	void OnEventSize(WPARAM wParam, LPARAM lParam);
	void OnEventClose(WPARAM wParam, LPARAM lParam);
	void OnEventInitDialog(WPARAM wParam, LPARAM lParam);
	void OnEventCommand(WPARAM wParam, LPARAM lParam);

public:
	WP8Func();
	virtual ~WP8Func();
};



#endif // !__AXEEN_WP8_WP8FUNC_HH__
