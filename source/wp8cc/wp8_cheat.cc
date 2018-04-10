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
	this->InitDataAddress();
}

/**************************************************//**
 * @brief	取得遊戲時間
 * @see		SaWP8DATE
 *****************************************************/
void WP8Cheat::LoadGameDate()
{
	const int32u err = -1;
	const int32u month[] = { 4, 4, 5, 4, 5, 4, 4, 5, 4, 5, 4, 4 };
	const size_t month_length = sizeof(month) / sizeof(int32u);	
	int32u m, t, temp;

	// 時間資料讀取錯誤
	if ((t = this->LoadGameCurrentWeekNumber()) == err) {
		m_Date.WeekNumber = err;
		m_Date.Month = err;
		m_Date.Week = err;
		return;
	}

	// 取得遊戲中月份、週份
	temp = 0;
	for (m = 0; m < month_length; m++) {
		temp += month[m];
		if (temp >= t) { temp -= month[m]; break; }
	}

	m_Date.WeekNumber = t;
	m_Date.Week = t - temp + 1;	// zero-base so must plus 1
	m_Date.Month = m + 1;		// zero-base so must plus 1
}

/**************************************************//**
 * @brief	讀取遊戲當前週數
 * @return	@c int32u
 *			- 運作成功傳回: 當前週數
 *			- 運作失敗傳回: -1
 * @see		SaWP8DATE
 *****************************************************/
int32u WP8Cheat::LoadGameCurrentWeekNumber()
{
	const int32u err = -1;
	intxu	addr = m_Date.Addr;
	size_t	len = (size_t)m_Date.DataLength;
	int32u	date;

	// 數據不正確
	if (addr == 0 || len == 0)
		return err;

	// 讀取遊戲時間
	date = 0;
	if (this->ReadMemory((LPVOID)addr, &date, len) == len) {
		int32u w, m, t;
		w = (date >> 4) & 0x000F;	// HIBITS
		m = date & 0x000F;			// LOBITS
		t = m * 4 + w;

		// 比賽中?
		t = (w > 7) ? t - 4 : t;
		t = (w > 3) ? t - 4 : t;
		return t;
	}
	return err;
}

/**************************************************//**
 * @brief	初始化資料內容
 *****************************************************/
void WP8Cheat::InitData()
{
	const int32u err = -1;
	::memset((void*)&m_HorseAbility, 0, sizeof(SaWP8ABILITY));
	::memset((void*)&m_HorseRace, 0, sizeof(SaWP8RACE));
	::memset((void*)&m_HorsePony, 0, sizeof(SaWP8PONY));
	::memset((void*)&m_HorseMare, 0, sizeof(SaWP8MARE));
	::memset((void*)&m_HorseStallion, 0, sizeof(SaWP8STALLION));

	::memset((void*)&m_Date, 0, sizeof(SaWP8DATE));
	m_Date.WeekNumber = err;
	m_Date.Month = err;
	m_Date.Week = err;

	::memset((void*)&m_Racing, 0, sizeof(SaWP8RACING));
}

/**************************************************//**
 * @brief	對應各資料位址
 *****************************************************/
void WP8Cheat::InitDataAddress()
{
	// WP8-2018 address setting
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

	::memset((void*)&m_Date, 0, sizeof(SaWP8DATE));
	m_Date.Addr = WP8DATE_ADDR;
	m_Date.DataLength = WP8DATE_DATA_LENGTH;

	::memset((void*)&m_Racing, 0, sizeof(SaWP8RACING));
	m_Racing.Count = WP8GAME_COUNT;
	m_Racing.SpeedAddr = WP8GAME_SPEED_ADDR;
	m_Racing.SpeedSeek = WP8GAME_SPEED_SEEK;
	m_Racing.TacticAddr = WP8GAME_TACTIC_ADDR;
	m_Racing.TacticSeek = WP8GAME_TACTIC_SEEK;
	m_Racing.WeightAddr = WP8GAME_WEIGHT_ADDR;
	m_Racing.WeightSeek = WP8GAME_WEIGHT_SEEK;
	m_Racing.JockeyAddr = WP8GAME_JOCKEY_ADDR;
	m_Racing.JockeySeek = WP8GAME_JOCKEY_SEEK;

	// WP9-2018 v1.0.2.x offset
	if (m_uVersion == WP8VER_502) {
		m_HorseAbility.Addr += WP8VER_502_SEEK;
		m_HorseRace.Addr += WP8VER_502_SEEK;
		m_HorsePony.Addr += WP8VER_502_SEEK;
		m_HorseMare.Addr += WP8VER_502_SEEK;
		m_HorseStallion.Addr  += WP8VER_502_SEEK;

		m_Date.Addr += WP8VER_502_SEEK;
		m_Racing.SpeedAddr  += WP8VER_502_SEEK;
		m_Racing.TacticAddr += WP8VER_502_SEEK;
		m_Racing.WeightAddr += WP8VER_502_SEEK;
		m_Racing.JockeyAddr += WP8VER_502_SEEK;
	}
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Cheat::WP8Cheat()
	: WsCheat() {
	this->InitData();
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Cheat::~WP8Cheat()
{

}
