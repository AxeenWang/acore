/**************************************************************************//**
 * @file	wp8_frame.hh
 * @brief	WP8cc 主視窗類別 : 成員函示
 * @author	Swang
 * @date	2018-04-03
 * @date	2018-04-03
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8FRAME_HH__
#define __AXEEN_WP8_WP8FRAME_HH__
#include "wp8_tabs.hh"
#include "wp8_func.hh"
#include "wp8_race.hh"
#include "wp8_game.hh"

/******************************************************//**
 * @class	WP8Frame
 * @brief	WP8cc	主視窗類別
 * @author	Swang
 * @note	繼承 WsFrame
 *********************************************************/
class WP8Frame : public WsFrame
{
protected:
	LRESULT MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);
	void OnEventCreate(WPARAM wParam, LPARAM lParam);
	void OnEventSize(WPARAM wParam, LPARAM lParam);
	void OnEventClose(WPARAM wParam, LPARAM lParam);
	void OnEventNotify(WPARAM wParam, LPARAM lParam);

	// User Event
	void OnEventWP8Func(WPARAM wParam, LPARAM lParam);
	void OnEventWP8Error(WPARAM wParam, LPARAM lParam);

	void TabSelectChange(int index);
public:
	WP8Frame();
	virtual ~WP8Frame();
	BOOL Create(HINSTANCE hInstance);

protected:
	void LoadGameData();

	void InitFrame();
	void InitTabs();
	void InitPage();
	void InitPosition();
	void Release();

protected:
	WP8Tabs *	m_cTabsObj;					//!< 主視窗 WP8Tabs 物件
	WP8Func *	m_cFuncObj;					//!< 主視窗功能選項 WsDialog 物件
	int			m_iPage;					//!< 當前顯示標籤頁面索引
	std::vector <WP8Page*> m_vPage;			//!< WP8Page 物件 - 各功能標籤 Dialog 頁面
};

#endif // !__AXEEN_WP8_WP8FRAME_HH__
