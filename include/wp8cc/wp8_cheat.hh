/**************************************************************************//**
 * @file	wp8_cheat.hh
 * @brief	WP8cc 程序掛勾類別
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8CHEAT_HH__
#define __AXEEN_WP8_WP8CHEAT_HH__
#include "wp8_cheat_struct.hh"

/**************************************************//**
 * @class	WP8Cheat
 * @brief	WP8cc 程序掛勾類別
 * @author	Swang
 * @note	繼承 WP8Page
 *****************************************************/
class WP8Cheat : public WsCheat
{
public:
	BOOL WatchingYou();
	void SetVersion(int32u ver);

	void	LoadGameDate();
	int32u	GetCurrentWeekNumber(BOOL bOnly = TRUE);
	int32u	GetCurrentWeek();
	int32u	GetCurrentMonth();
	
protected:
	int32u	LoadGameCurrentWeekNumber();
	void	InitData();
	void	InitDataAddress();

public:
	WP8Cheat();
	virtual ~WP8Cheat();

protected:
	SaWP8ABILITY	m_HorseAbility;		//!< 馬能力結構
	SaWP8RACE		m_HorseRace;		//!< 競走馬結構
	SaWP8PONY		m_HorsePony;		//!< 幼駒結構
	SaWP8MARE		m_HorseMare;		//!< 繁殖牝馬結構
	SaWP8STALLION	m_HorseStallion;	//!< 種牡馬結構

	SaWP8DATE		m_Date;				//!< WP8 時間
	SaWP8RACING		m_Racing;			//!< 比賽相關結構
	int32u			m_uVersion;			//!< 遊戲版本
};

/**************************************************//**
 * @brief	取得遊戲目前週數
 * @param	[in] bOnly	是否僅僅取得週數識別
 *			- TRUE	= 僅取得週數，不做月週資料演算
 *			- FALSE	= 取得完整遊戲時間資訊。
 * @return	@c int32u	遊戲週數
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline int32u WP8Cheat::GetCurrentWeekNumber(BOOL bOnly)
{
	if (bOnly)
		return this->LoadGameCurrentWeekNumber();
	this->LoadGameDate();
	return m_Date.WeekNumber;
}

/**************************************************//**
 * @brief	取得遊戲目前週份
 * @return	@c int32u	遊戲目前週份
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline int32u WP8Cheat::GetCurrentWeek() { return m_Date.Week; }

/**************************************************//**
 * @brief	取得遊戲目前月份
 * @return	@c int32u	遊戲目前月份
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline int32u WP8Cheat::GetCurrentMonth() { return m_Date.Month; }


#endif // !__AXEEN_WP8_WP8CHEAT_HH__
