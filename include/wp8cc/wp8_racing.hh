/**************************************************************************//**
 * @file	wp8_racing.hh
 * @brief	WP8cc 比賽相關操作類別
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8RACING_HH__
#define __AXEEN_WP8_WP8RACING_HH__
#include "wp8_page.hh"

/**************************************************//**
 * @class	WP8RacingList
 * @brief	WP8cc 比賽相關 : 列表操作類別
 * @author	Swang
 * @note	繼承 WsListv
 *****************************************************/
class WP8RacingList : public WsListv
{
public:
	WP8RacingList();
	virtual ~WP8RacingList();
	BOOL Create(HWND hParent, int idItem);

protected:
	void InitColumn();
};

/**************************************************//**
 * @class	WP8RacingFrame
 * @brief	WP8cc 比賽相關 : 頁面操作類別
 * @author	Swang
 * @note	繼承 WP8Page
 *****************************************************/
class WP8RacingFrame : public WP8Page
{
protected:
	virtual void OnEventSize(WPARAM wParam, LPARAM lParam);
	virtual void OnEventClose(WPARAM wParam, LPARAM lParam);
	virtual void OnEventInitDialog(WPARAM wParam, LPARAM lParam);

public:
	virtual void LoadData();

public:
	WP8RacingFrame();
	virtual ~WP8RacingFrame();

protected:
	void InitList();
	void Release();

protected:
	WP8RacingList * m_cList;	//!< 競走馬列表物件
};

#endif // !__AXEEN_WP8_WP8RACING_HH__
