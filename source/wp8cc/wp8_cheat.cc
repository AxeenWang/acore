/**************************************************************************//**
 * @file	wp8_cheat.cc
 * @brief	WP8cc 程序掛勾類別, 成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_cheat.hh"

/**************************************************//**
 * @brief	搜尋指定目標程序
 * @return	@c BOOL
 *			- 若出現指定目標或目標已存在則傳回 TRUE
 *			- 若目標不存在或發生錯誤，則傳回 FALSE
 *****************************************************/
BOOL WP8Cheat::WatchingYou()
{
	const	TCHAR* pexe = TEXT("WP8_2018.exe");
	const	BOOL err = FALSE;
	const	BOOL eok = TRUE;
	HANDLE	hProcess = m_hProcess;
	DWORD	idSave = m_idProcess;
	DWORD	pid = this->SearchProcess(pexe);

	// 已存在與目標程序掛勾
	if (hProcess != NULL) { if (pid == idSave) return eok; }

	// 尚未與目標掛勾
	this->ReleaseHook();
	// 搜尋指定目標程序，若目標程序已存在系統，則進行開啟目標程序進行掛勾
	if (pid != 0) {
		if ((hProcess = this->OpenProcess(pid)) != NULL) {
			m_hProcess = hProcess;
			m_idProcess = pid;
			return eok;
		}
	}
	return err;
}

/**************************************************//**
 * @brief	設定遊戲版本
 *****************************************************/
void WP8Cheat::SetVersion(int32u ver)
{
	switch (ver) {
	case WP8VER_501:
		m_uVersion = WP8VER_501;
		break;
	case WP8VER_502:
		m_uVersion = WP8VER_502;
		break;
	default:
		m_uVersion = WP8VER_502;
	}
	this->MatchDataInfo();
}

/**************************************************//**
 * @brief	對應各資料位址
 *****************************************************/
void WP8Cheat::MatchDataInfo()
{
	::memset((void*)&m_HorseAbility, 0, sizeof(SaWP8ABILITY));
	m_HorseAbility.Count = HORSE_ABILITY_COUNT;
	m_HorseAbility.Addr = HORSE_ABILITY_ADDR;
	m_HorseAbility.Seek = HORSE_ABILITY_SEEK;

	::memset((void*)&m_HorseRace, 0, sizeof(SaWP8RACE));
	m_HorseRace.Count = HORSE_RACE_COUNT;
	m_HorseRace.Addr = HORSE_RACE_ADDR;
	m_HorseRace.Seek = HORSE_RACE_SEEK;

	::memset((void*)&m_HorsePony, 0, sizeof(SaWP8PONY));
	m_HorsePony.Count = HORSE_PONY_COUNT;
	m_HorsePony.Addr = HORSE_PONY_ADDR;
	m_HorsePony.Seek = HORSE_PONY_SEEK;

	::memset((void*)&m_HorseMare, 0, sizeof(SaWP8MARE));
	m_HorseMare.Count = HORSE_MARE_COUNT;
	m_HorseMare.Addr = HORSE_MARE_ADDR;
	m_HorseMare.Seek = HORSE_MARE_SEEK;

	::memset((void*)&m_HorseStallion, 0, sizeof(SaWP8STALLION));
	m_HorseStallion.Count = HORSE_STALLION_COUNT;
	m_HorseStallion.Addr = HORSE_STALLION_ADDR;
	m_HorseStallion.Seek = HORSE_STALLION_SEEK;

	::memset((void*)&m_GameInfo, 0, sizeof(SaWP8GAME));
	m_GameInfo.Count = WP8GAME_COUNT;
	m_GameInfo.SpeedAddr = WP8GAME_SPEED_ADDR;
	m_GameInfo.SpeedSeek = WP8GAME_SPEED_SEEK;
	m_GameInfo.TacticAddr = WP8GAME_TACTIC_ADDR;
	m_GameInfo.TacticSeek = WP8GAME_TACTIC_SEEK;
	m_GameInfo.WeightAddr = WP8GAME_WEIGHT_ADDR;
	m_GameInfo.WeightSeek = WP8GAME_WEIGHT_SEEK;
	m_GameInfo.JockeyAddr = WP8GAME_JOCKEY_ADDR;
	m_GameInfo.JockeySeek = WP8GAME_JOCKEY_SEEK;

	if (m_uVersion == WP8VER_502) {
		m_HorseAbility.Addr += WP8VER_502_SEEK;
		m_HorseRace.Addr += WP8VER_502_SEEK;
		m_HorsePony.Addr += WP8VER_502_SEEK;
		m_HorseMare.Addr += WP8VER_502_SEEK;
		m_HorseStallion.Addr  += WP8VER_502_SEEK;

		m_GameInfo.SpeedAddr  += WP8VER_502_SEEK;
		m_GameInfo.TacticAddr += WP8VER_502_SEEK;
		m_GameInfo.WeightAddr += WP8VER_502_SEEK;
		m_GameInfo.JockeyAddr += WP8VER_502_SEEK;
	}

}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Cheat::WP8Cheat()
	: WsCheat() {
	::memset((void*)&m_HorseAbility, 0, sizeof(SaWP8ABILITY));
	::memset((void*)&m_HorseRace, 0, sizeof(SaWP8RACE));
	::memset((void*)&m_HorsePony, 0, sizeof(SaWP8PONY));
	::memset((void*)&m_HorseMare, 0, sizeof(SaWP8MARE));
	::memset((void*)&m_HorseStallion, 0, sizeof(SaWP8STALLION));
	::memset((void*)&m_GameInfo, 0, sizeof(SaWP8GAME));
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Cheat::~WP8Cheat()
{

}
