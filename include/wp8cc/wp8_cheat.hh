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
	Bool WatchingYou();
	void SetVersion(Int32u ver);
	LPCTSTR	GetJockeyName(int index);

	// 時間
	void	LoadGameDate();
	Int32u	GetCurrentWeekNumber(Bool bOnly = True);
	Int32u	GetCurrentWeek();
	Int32u	GetCurrentMonth();

	// 比賽相關
	void	LoadRacing();
	int		GetRacingTrack();
	LPCTSTR	GetRacingTrackText();
	Int32u	GetRacingSpeed(int index);
	LPCTSTR	GetRacingSpeedText(int index);
	Int32u	GetRacingTactic(int index);
	LPCTSTR	GetRacingTacticText(int index);
	Int32u	GetRacingWeight(int index);
	LPCTSTR GetRacingWeightText(int index);
	Int32u	GetRacingJockey(int index);
	LPCTSTR GetRacingJockeyText(int index);

	// 馬資料
	Bool	LoadHorseAbility();
	Bool	LoadHorseRace();
	Bool	LoadHorsePony();
	Bool	LoadHorseMare();
	Bool	LoadHorseStallion();
	Bool	LoadHorseData();
	
protected:
	Int32u	LoadGameCurrentWeekNumber();
	Bool	LoadHorseData(IntQu addr, IntQu seek, int count, void* data, int len);

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
	Int32u			m_uVersion;			//!< 遊戲版本
};

/**************************************************//**
 * @brief	取得遊戲目前週數
 * @param	[in] bOnly	是否僅僅取得週數識別
 *			- True	= 僅取得週數，不做月週資料演算
 *			- False	= 取得完整遊戲時間資訊。
 * @return	@c Int32u	遊戲週數
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetCurrentWeekNumber(Bool bOnly)
{
	if (bOnly)
		return this->LoadGameCurrentWeekNumber();
	this->LoadGameDate();
	return m_Date.WeekNumber;
}

/**************************************************//**
 * @brief	取得遊戲目前週份
 * @return	@c Int32u	遊戲目前週份
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetCurrentWeek() { return m_Date.Week; }

/**************************************************//**
 * @brief	取得遊戲目前月份
 * @return	@c Int32u	遊戲目前月份
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetCurrentMonth() { return m_Date.Month; }

/**************************************************//**
 * @brief	取得遊戲比賽跑道數量
 * @return	@c int	遊戲目前月份
 * @note	必須先調用 LoadGameDate 成員
 * @see		SaWP8DATE 結構說明
 *****************************************************/
inline int WP8Cheat::GetRacingTrack() { return (int)m_Racing.Count; }

/**************************************************//**
 * @brief	取得比賽速度
 * @param	[in] index	賽道索引
 * @return	@c Int32u	競賽速度
 *			- 若運作成功傳回: 當前速度
 *			- 若運作失敗傳回: -1
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetRacingSpeed(int index)
{
	if (index >= 0 && index < (int)m_Racing.Count) {
		return (Int32u)m_Racing.SpeedData[index];
	}
	return -1;
}

/**************************************************//**
 * @brief	取得比賽戰術
 * @param	[in] index	賽道索引
 * @return	@c Int32u	戰術
 *			- 若運作成功傳回: 當前戰術
 *			- 若運作失敗傳回: -1
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetRacingTactic(int index)
{
	if (index >= 0 && index < (int)m_Racing.Count) {
		return m_Racing.TacticData[index];
	}
	return -1;
}

/**************************************************//**
 * @brief	取得比賽騎手斤量
 * @param	[in] index	賽道索引
 * @return	@c Int32u	斤量
 *			- 若運作成功傳回: 當前騎手斤量
 *			- 若運作失敗傳回: -1
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetRacingWeight(int index)
{
	if (index >= 0 && index < (int)m_Racing.Count) {
		return (Int32u)m_Racing.WeightData[index];
	}
	return -1;
}

/**************************************************//**
 * @brief	取得比賽騎乘騎手
 * @param	[in] index	賽道索引
 * @return	@c Int32u	騎乘騎手
 *			- 若運作成功傳回: 當前騎乘騎手
 *			- 若運作失敗傳回: -1
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
inline Int32u WP8Cheat::GetRacingJockey(int index)
{
	if (index >= 0 && index < (int)m_Racing.Count) {
		return (Int32u)m_Racing.JockeyData[index];
	}
	return -1;
}

/**************************************************//**
 * @brief	取得馬能力
 * @return	@c Bool	運作成功與否
 * @see		LoadHorseData
 *****************************************************/
inline Bool WP8Cheat::LoadHorseAbility()
{
	return this->LoadHorseData(
		m_HorseAbility.Addr,
		m_HorseAbility.Seek,
		(int)m_HorseAbility.Count,
		(void*)&m_HorseAbility.Data[0],
		sizeof(m_HorseAbility.Data[0])
	);
}

/**************************************************//**
 * @brief	取得競走馬
 * @return	@c Bool	運作成功與否
 * @see		LoadHorseData
 *****************************************************/
inline Bool WP8Cheat::LoadHorseRace()
{
	return this->LoadHorseData(
		m_HorseRace.Addr,
		m_HorseRace.Seek,
		(int)m_HorseRace.Count,
		(void*)&m_HorseRace.Data[0],
		sizeof(m_HorseRace.Data[0])
	);
}

/**************************************************//**
 * @brief	取得幼駒
 * @return	@c Bool	運作成功與否
 * @see		LoadHorseData
 *****************************************************/
inline Bool WP8Cheat::LoadHorsePony()
{
	return this->LoadHorseData(
		m_HorsePony.Addr,
		m_HorsePony.Seek,
		(int)m_HorsePony.Count,
		(void*)&m_HorsePony.Data[0],
		sizeof(m_HorsePony.Data[0])
	);
}

/**************************************************//**
 * @brief	取得繁殖牝馬
 * @return	@c Bool	運作成功與否
 * @see		LoadHorseData
 *****************************************************/
inline Bool WP8Cheat::LoadHorseMare()
{
	return this->LoadHorseData(
		m_HorseMare.Addr,
		m_HorseMare.Seek,
		(int)m_HorseMare.Count,
		(void*)&m_HorseMare.Data[0],
		sizeof(m_HorseMare.Data[0])
	);
}

/**************************************************//**
 * @brief	取得種牡馬
 * @return	@c Bool	運作成功與否
 * @see		LoadHorseData
 *****************************************************/
inline Bool WP8Cheat::LoadHorseStallion()
{
	return this->LoadHorseData(
		m_HorseStallion.Addr,
		m_HorseStallion.Seek,
		(int)m_HorseStallion.Count,
		(void*)&m_HorseStallion.Data[0],
		sizeof(m_HorseStallion.Data[0])
	);
}

/**************************************************//**
 * @brief	取得全部馬資訊
 * @return	@c Bool	運作成功與否
 * @see		LoadHorseData
 *****************************************************/
inline Bool WP8Cheat::LoadHorseData()
{
	for (;;) {
		if (!this->LoadHorseAbility())
			break;
		if (!this->LoadHorseRace())
			break;
		if (!this->LoadHorsePony())
			break;
		if (!this->LoadHorseMare())
			break;
		if (!this->LoadHorseStallion())
			break;
		return True;
	}
	return False;
}

#endif // !__AXEEN_WP8_WP8CHEAT_HH__
