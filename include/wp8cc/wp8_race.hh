/**************************************************************************//**
 * @file	wp8_race.hh
 * @brief	WP8cc 競走馬操作類別
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8RACE_HH__
#define __AXEEN_WP8_WP8RACE_HH__
#include "wp8_page.hh"

/**************************************************//**
 * @class	WP8RaceList
 * @brief	WP8cc 競走馬列表操作類別
 * @author	Swang
 * @note	繼承 WsListv
 *****************************************************/
class WP8RaceList : public WsListv
{
public:
	WP8RaceList();
	virtual ~WP8RaceList();
	Bool Create(HWND hParent, int idItem);

protected:
	void InitColumn();
};


/**************************************************//**
 * @class	WP8RaceFrame
 * @brief	WP8cc 競走馬操作類別
 * @author	Swang
 * @note	繼承 WP8Page
 *****************************************************/
class WP8RaceFrame : public WP8Page
{
public:
	virtual void OnEventSize(WPARAM wParam, LPARAM lParam);
	virtual void OnEventClose(WPARAM wParam, LPARAM lParam);
	virtual void OnEventInitDialog(WPARAM wParam, LPARAM lParam);

public:
	virtual void LoadData();

public:
	WP8RaceFrame();
	virtual ~WP8RaceFrame();

protected:
	void InitList();
	void Release();

protected:
	WP8RaceList * m_cList;	//!< 競走馬列表物件
};

#endif // !__AXEEN_WP8_WP8RACE_HH__