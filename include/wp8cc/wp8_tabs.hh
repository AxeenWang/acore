/**************************************************************************//**
 * @file	wp8_tabs.hh
 * @brief	WP8cc 主視窗標籤操作類別
 * @author	Swang
 * @date	2018-04-04
 * @date	2018-04-04
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8TABS_HH__
#define __AXEEN_WP8_WP8TABS_HH__
#include "wp8_define.hh"

/**************************************************//**
 * @class	WP8Tabs
 * @brief	WP8cc 主視窗標籤控制項操作類別
 * @author	Swang
 * @note	繼承 WsTabs
 *****************************************************/
class WP8Tabs : public WsTabs
{
public:
	WP8Tabs();
	virtual ~WP8Tabs();
	Bool Create(HWND hParent, int idItem);

protected:
	void InitTab();
};

#endif // !__AXEEN_WP8_WP8TABS_HH__
