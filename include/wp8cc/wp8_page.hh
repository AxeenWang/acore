/**************************************************************************//**
 * @file	wp8_page.hh
 * @brief	WP8cc 標籤頁操作類別
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8PAGE_HH__
#define __AXEEN_WP8_WP8PAGE_HH__
#include "wp8_define.hh"

/**************************************************//**
 * @class	WP8Page
 * @brief	WP8cc 標籤頁操作類別
 * @author	Swang
 * @note	繼承 WsDialog
 *****************************************************/
class WP8Page : public WsDialog
{
protected:
	virtual INT_PTR MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual void OnEventSize(WPARAM wParam, LPARAM lParam);
	virtual void OnEventClose(WPARAM wParam, LPARAM lParam);
	virtual void OnEventInitDialog(WPARAM wParam, LPARAM lParam);

public:
	virtual void LoadData();

public:
	WP8Page();
	virtual ~WP8Page();

protected:
	HBRUSH Brush(Bool bRelease = False);
};

#endif // !__AXEEN_WP8_WP8PAGE_HH__
