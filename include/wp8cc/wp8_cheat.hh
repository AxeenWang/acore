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

protected:
	void MatchDataInfo();

public:
	WP8Cheat();
	virtual ~WP8Cheat();

protected:
	SaWP8ABILITY	m_HorseAbility;		//!< 馬能力結構
	SaWP8RACE		m_HorseRace;		//!< 競走馬結構
	SaWP8PONY		m_HorsePony;		//!< 幼駒結構
	SaWP8MARE		m_HorseMare;		//!< 繁殖牝馬結構
	SaWP8STALLION	m_HorseStallion;	//!< 種牡馬結構
	SaWP8GAME		m_GameInfo;			//!< 比賽相關結構

	int32u			m_uVersion;			//!< 遊戲版本
};

#endif // !__AXEEN_WP8_WP8CHEAT_HH__
