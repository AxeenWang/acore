/**************************************************************************//**
 * @file	wp8_cheat.cc
 * @brief	WP8cc 程序掛勾類別, 成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
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
 * @brief	讀取 WP8 資料
 * @return	@c BOOL
 *			- 資料讀取成功傳回: TRUE
 *			- 資料讀取失敗傳回: FALSE
 *****************************************************/
BOOL WP8Cheat::LoadData()
{
	//TODO
	return 0;
}

/**************************************************//**
 * @brief	保存 WP8 資料
 * @return	@c BOOL
 *			- 資料保存成功傳回: TRUE
 *			- 資料保存失敗傳回: FALSE
 *****************************************************/
BOOL WP8Cheat::SaveData()
{
	//TODO
	return 0;
}

/**************************************************//**
 * @brief	配置記憶體
 *****************************************************/
void WP8Cheat::CreateDataMemory()
{
	int iMatch = m_iMatchMemory;

	for (;;) {
		if (iMatch > 0) break;
		iMatch = 0;
		LPSaWP8ADDRESS aPtr = new (std::nothrow) SaWP8ADDRESS();
		if (aPtr == NULL) break;
		iMatch++;

		m_iMatchMemory = iMatch;
		return;
	}
	m_iMatchMemory = -1;
}

/**************************************************//**
 * @brief	配置記憶體
 *****************************************************/
void WP8Cheat::DeleteDataMemory()
{
	SAFE_DELETE(m_aPtr);
	m_iMatchMemory = -1;
	m_iMatchVersion = -1;
}

/**************************************************//**
 * @brief	匹配對應版本數據位址
 * @param	[in] ver 版本號
 *****************************************************/
void WP8Cheat::MatchAddress(int ver)
{
	for (;;) {
		if (m_aPtr == NULL) break;
		::memset((void*)m_aPtr, 0, sizeof(SaWP8ADDRESS));
		m_aPtr->sGame.uTotail = WP8GAME_TOTAIL;
		m_aPtr->sGame.uSpeedAddr = WP8GAME_SPEED_ADDR;
		m_aPtr->sGame.uSpeedSeek = WP8GAME_SPEED_SEEK;
		m_aPtr->sGame.uTacticAddr = WP8GAME_TACTIC_ADDR;
		m_aPtr->sGame.uTacticSeek = WP8GAME_TACTIC_SEEK;
		m_aPtr->sGame.uWeightAddr = WP8GAME_WEIGHT_ADDR;
		m_aPtr->sGame.uWeightSeek = WP8GAME_WEIGHT_SEEK;
		m_aPtr->sGame.uJockeyAddr = WP8GAME_JOCKEY_ADDR;
		m_aPtr->sGame.uJockeySeek = WP8GAME_JOCKEY_SEEK;

		m_iMatchVersion = ver;
		return;
	}
	m_iMatchVersion = -1;
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Cheat::WP8Cheat()
	: WsCheat()
	, m_iMatchMemory(-1)
	, m_iMatchVersion(-1)
	, m_aPtr(NULL) {
	this->CreateDataMemory();
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Cheat::~WP8Cheat()
{
	// 刪除所有物件成員
	this->DeleteDataMemory();
}
