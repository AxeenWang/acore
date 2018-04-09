/**************************************************************************//**
 * @file	wp8_cheat.hh
 * @brief	WP8cc 程序掛勾類別
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8CHEAT_HH__
#define __AXEEN_WP8_WP8CHEAT_HH__
#include "cwins\cwins.hh"
#include "wp8_struct.hh"

// ====================================================
// WP8-2018 v1.0.2 Data Address
// ====================================================

// 比賽相關
#define WP8GAME_TOTAIL			18				//!< 比賽相關: 賽道、參賽馬數量
#define WP8GAME_SPEED_ADDR		0x00EBA484		//!< 比賽相關: 速度位址
#define WP8GAME_SPEED_SEEK		2				//!< 比賽相關: 速度下一筆資料位差
#define WP8GAME_TACTIC_ADDR		0x00EB9C58		//!< 比賽相關: 戰術位址
#define WP8GAME_TACTIC_SEEK		4				//!< 比賽相關: 戰術下一筆資料位差
#define WP8GAME_WEIGHT_ADDR		0x00EB9C58		//!< 比賽相關: 斤量位址
#define WP8GAME_WEIGHT_SEEK		1				//!< 比賽相關: 斤量下一筆資料位差
#define WP8GAME_JOCKEY_ADDR		0x00EB9CA4		//!< 比賽相關: 騎乘騎師位址
#define WP8GAME_JOCKEY_SEEK		2				//!< 比賽相關: 騎乘騎師下一筆資料位差

/******************************************************//**
 * @struct	SaWP8ADDRGAME
 * @brief	WP8-2018 比賽相關位址結構
 *********************************************************/
struct SaWP8ADDRGAME {
	int32u	uTotail;		//!< 賽道、參賽馬數量
	intxu	uSpeedAddr;		//!< 速度位址
	intxu	uSpeedSeek;		//!< 速度下一筆資料位差
	intxu	uTacticAddr;	//!< 戰術位址
	intxu	uTacticSeek;	//!< 戰術下一筆資料位差
	intxu	uWeightAddr;	//!< 斤量位址
	intxu	uWeightSeek;	//!< 斤量下一筆資料位差
	intxu	uJockeyAddr;	//!< 騎乘騎師位址
	intxu	uJockeySeek;	//!< 騎乘騎師下一筆資料位差
};
typedef SaWP8ADDRGAME*	LPSaWP8ADDRGAME;	//!< SaWP8ADDRGAME 長程指標

/******************************************************//**
 * @struct	SaWP8DATAGAME
 * @brief	WP8-2018 比賽資料結構
 *********************************************************/
struct SaWP8DATAGAME {
	int16u	speed[WP8GAME_TOTAIL];
	int32u	tactic[WP8GAME_TOTAIL];
	int8u	weigth[WP8GAME_TOTAIL];
	int16u	jockey[WP8GAME_TOTAIL];
};
typedef SaWP8DATAGAME*	LPSaWP8DATAGAME;	//!< SaWP8DATAGAME 長程指標

/******************************************************//**
 * @struct	SaWP8ADDRHORSE
 * @brief	WP8-2018 馬資料位址結構
 *********************************************************/
struct SaWP8ADDRHORSE {
	int32u	uTotail;		//!< 馬匹總數
	intxu	uAddr;			//!< 馬匹起始位置
	intxu	uSeek;			//!< 馬匹下一筆資料位差
};
typedef SaWP8ADDRHORSE*	LPSaWP8ADDRHORSE;	//!< SaWP8ADDRHORSE 長程指標

/******************************************************//**
 * @struct	SaWP8ADDRESS
 * @brief	WP8-2018 各項目資訊位址
 *********************************************************/
struct SaWP8ADDRESS {
	SaWP8ADDRGAME	sGame;
	SaWP8ADDRHORSE	sRace;	//!< Race horse address structure
	SaWP8ADDRHORSE	sPony;	//!< Pony address structure
	SaWP8ADDRHORSE	sMare;	//!< Mare address structure
	SaWP8ADDRHORSE	sStal;	//!< Stallion address structure
};
typedef SaWP8ADDRESS*	LPSaWP8ADDRESS;		//!< SaWP8ADDRESS 長程指標

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
	BOOL LoadData();
	BOOL SaveData();
	
	BOOL IsMatchMemory();
	BOOL IsMatchVersion();

protected:
	void CreateDataMemory();
	void DeleteDataMemory();
	void MatchAddress(int ver);

public:
	WP8Cheat();
	virtual ~WP8Cheat();

protected:
	int				m_iMatchMemory;		//!< 是否完成資料成員匹配 (個資料必須記憶體是否配置完成)
	int				m_iMatchVersion;	//!< 是否完成資料位址匹配
	LPSaWP8ADDRESS	m_aPtr;				//!< 各項數據位址結構
};

/**************************************************//**
 * @brief	配置記憶體
 * @return	@c BOOL
 *			- 資料配置已就緒傳回: TRUE
 *			- 資料配置未就緒傳回: FALSE
 *****************************************************/
inline BOOL WP8Cheat::IsMatchMemory() { return m_iMatchMemory > 0; }

/**************************************************//**
 * @brief	個資料位址是否完成初始化
 * @return	@c BOOL
 *			- 資料配置已就緒傳回: TRUE
 *			- 資料配置未就緒傳回: FALSE
 *****************************************************/
inline BOOL WP8Cheat::IsMatchVersion() { return m_iMatchVersion > 0; }

#endif // !__AXEEN_WP8_WP8CHEAT_HH__
