/**************************************************************************//**
 * @file	wp8_cheat_struct.hh
 * @brief	WP8cc 程序掛勾類別，參數、結構、列舉定義
 * @author	Swang
 * @date	2018-04-10
 * @date	2018-04-10
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8CHEATSTRUCT_HH__
#define __AXEEN_WP8_WP8CHEATSTRUCT_HH__
#include "cwins\cwins.hh"

// Patch version
#define WP8VER_501					0x20180101	//!< WP8 遊戲版本號 WP8-2018 v1.0.1
#define WP8VER_502					0x20180102	//!< WP8 遊戲版本號 WP8-2018 v1.0.2
#define WP8VER_502_SEEK				0x00000100	//!< WP8-2018 v1.0.2 位移

// 時間、日期
#define WP8DATE_ADDR				0x00E29FDC	//!< WP8 當前時間位址
#define WP8DATE_DATA_LENGTH			1			//!< WP8 當前時間資料長度
#define WP8DATE_WEEK_LENGTH			52			//!< 一年週數

// 比賽相關
#define WP8GAME_COUNT				18			//!< 比賽相關: 賽道、參賽馬數量
#define WP8GAME_SPEED_ADDR			0xEBA384	//!< 比賽相關: 速度位址
#define WP8GAME_SPEED_SEEK			2			//!< 比賽相關: 速度下一筆資料位差
#define WP8GAME_TACTIC_ADDR			0xEB9B58	//!< 比賽相關: 戰術位址
#define WP8GAME_TACTIC_SEEK			4			//!< 比賽相關: 戰術下一筆資料位差
#define WP8GAME_WEIGHT_ADDR			0xEBA3A8	//!< 比賽相關: 斤量位址
#define WP8GAME_WEIGHT_SEEK			1			//!< 比賽相關: 斤量下一筆資料位差
#define WP8GAME_JOCKEY_ADDR			0xEB9BA4	//!< 比賽相關: 騎乘騎師位址
#define WP8GAME_JOCKEY_SEEK			2			//!< 比賽相關: 騎乘騎師下一筆資料位差

 // 馬能力
#define HORSE_ABILITY_ADDR			0x00E22A54	//!< 馬能力基底位址
#define HORSE_ABILITY_SEEK			0x0000001C	//!< 馬能力下一筆資料位移
#define	HORSE_ABILITY_COUNT			0x00006A15	//!< 馬能力筆數 (27157)
#define HORSE_ABILITY_EMPTY_NUMBER	27157		//!< 馬能力空番號
#define HORSE_ABILITY_DATA_LENGTH	7			//!< 馬能力資料長度 (in int32u)

 // 競走馬
#define HORSE_RACE_ADDR				0x00E23568	//!< 競走馬基底位址
#define HORSE_RACE_SEEK				0x00000084	//!< 競走馬下一筆資料位移
#define HORSE_RACE_COUNT			0x000017C0	//!< 競走馬筆數 (6080)
#define HORSE_RACE_EMPTY_NUMBER		-1			//!< 競走馬空番號
#define HORSE_RACE_DATA_LENGTH		33			//!< 競走馬資料長度 (in int32u)

 // 幼駒
#define HORSE_PONY_ADDR				0x00E240E4	//!< 幼駒基底位址
#define HORSE_PONY_SEEK				0x00000018	//!< 幼駒下一筆資料位移
#define HORSE_PONY_COUNT			0x00000C58	//!< 幼駒筆數	 (3160)
#define HORSE_PONY_EMPTY_NUMBER		-1			//!< 幼駒空番號
#define HORSE_PONY_DATA_LENGTH		6			//!< 幼駒資料長度 (in int32u)

 // 繁殖牝馬
#define HORSE_MARE_ADDR				0x00E23FA8	//!< 繁殖牝馬基底位址
#define HORSE_MARE_SEEK				0x00000030	//!< 繁殖牝馬下一筆資料位移
#define HORSE_MARE_COUNT			0x00002710	//!< 繁殖牝馬筆數 (2710)
#define HORSE_MARE_EMPTY_NUMBER		-1			//!< 繁殖牝馬空番號
#define HORSE_MARE_DATA_LENGTH		19			//!< 繁殖牝馬資料長度 (in int32u)

 // 種牡馬
#define HORSE_STALLION_ADDR			0x00E29E78	//!< 種牡馬基底位址
#define HORSE_STALLION_SEEK			0x0000004C	//!< 種牡馬下一筆資料位址
#define HORSE_STALLION_COUNT		0x000007D0	//!< 種牡馬筆數 (2000)
#define HORSE_STALLION_EMPTY_NUMBER	2000		//!< 種牡馬空番號
#define HORSE_STALLION_DATA_LENGTH	12			//!< 種牡馬資料長度 (in int32u)

/******************************************************//**
 * @struct	SaWP8DATE
 * @brief	時間結構
 * @details	月份週數分配方式
 *			- 例: int bufWeek [] = { 4, 4, 5, 4, 5, 4, 4, 5, 4, 5, 4, 4 };
 *			- 一年週數總和為 52 週
 * @note	WP8 時間存放方式 
 *			- 存放時間使用 1 byte 資料長度
 *			- 當前週數 = 高 4 bits (HIBITS)
 *			- 當前月數 = 低 4 bits (LOBITS) zero-base
 *			- 如 4 月 1 週 資料為 0x13
 *			- 如 6 月 2 週 資料為 0x25
			- 取得當前週數算法
 *				-# dat = 取得當前時間資料
 *				-# m = (LOBITS)dat
 *				-# w = (HIBITS)dat
 *				-# t = m * 4 + w (當前週數)
 *			- 比賽中 w 數據會有所變化，該數據還包含比賽場次資訊
 *				-# t = (w > 7) ? t - 4 : t;
 *				-# t = (w > 3) ? t - 4 : t;
 *********************************************************/
struct SaWP8DATE {
	intxu	Addr;			//!< 當前時間位址
	int32u	DataLength;		//!< 當前時間資料長度 (in byte)
	int32u	WeekNumber;		//!< 週數
	int32u	Month;			//!< 當前月
	int32u	Week;			//!< 當前週
};

/******************************************************//**
 * @struct	SaWP8RACING
 * @brief	比賽相關結構
 *********************************************************/
struct SaWP8RACING {
	int32u	Count;						//!< 賽道數量
	intxu	SpeedAddr;					//!< 速度位址
	intxu	SpeedSeek;					//!< 速度下一筆資料位移 (in byte)
	int16u	SpeedData[WP8GAME_COUNT];	//!< 速度資料
	intxu	TacticAddr;					//!< 戰術位址
	intxu	TacticSeek;					//!< 戰術下一筆資料位移 (in byte)
	int32u	TacticData[WP8GAME_COUNT];	//!< 戰術資料
	intxu	WeightAddr;					//!< 斤量位址
	intxu	WeightSeek;					//!< 斤量下一筆資料位移 (in byte)
	int8u	WeightData[WP8GAME_COUNT];	//!< 斤量資料
	intxu	JockeyAddr;					//!< 騎乘騎師位址
	intxu	JockeySeek;					//!< 騎乘騎師下一筆資料位移 (in byte)
	intxu	JockeyData[WP8GAME_COUNT];	//!< 騎乘騎師資料
};
typedef SaWP8RACING*	LPSaWP8RACING;	//!< SaWP8RACING 指標型態

/******************************************************//**
 * @struct	SaWP8ABILITY
 * @brief	馬能力結構
 *********************************************************/
struct SaWP8ABILITY {
	int32u	Count;								//!< 數量
	intxu	Addr;								//!< 位址
	intxu	Seek;								//!< 下一筆資料位移
	int32u	Data[HORSE_ABILITY_COUNT][HORSE_ABILITY_DATA_LENGTH];	//!< 資料
};
typedef SaWP8ABILITY*	LPSaWP8ABILITY;			//!< SaWP8ABILITY 指標型態

/******************************************************//**
 * @struct	SaWP8RACE
 * @brief	競走馬結構
 *********************************************************/
struct SaWP8RACE {
	int32u	Count;								//!< 數量
	intxu	Addr;								//!< 位址
	intxu	Seek;								//!< 下一筆資料位移
	int32u	Data[HORSE_RACE_COUNT][HORSE_RACE_DATA_LENGTH];			//!< 資料
};
typedef SaWP8RACE*	LPSaWP8RACE;				//!< SaWP8RACE 指標型態

/******************************************************//**
 * @struct	SaWP8PONY
 * @brief	幼駒結構
 *********************************************************/
struct SaWP8PONY {
	int32u	Count;								//!< 數量
	intxu	Addr;								//!< 位址
	intxu	Seek;								//!< 下一筆資料位移
	int32u	Data[HORSE_PONY_COUNT][HORSE_PONY_DATA_LENGTH];		//!< 資料
};
typedef SaWP8PONY*	LPSaWP8PONY;				//!< SaWP8PONY 指標型態

/******************************************************//**
 * @struct	SaWP8MARE
 * @brief	繁殖牝馬結構
 *********************************************************/
struct SaWP8MARE {
	int32u	Count;								//!< 數量
	intxu	Addr;								//!< 位址
	intxu	Seek;								//!< 下一筆資料位移
	int32u	Data[HORSE_MARE_COUNT][HORSE_MARE_DATA_LENGTH];		//!< 資料
};
typedef SaWP8MARE*	LPSaWP8MARE;				//!< SaWP8MARE 指標型態

/******************************************************//**
 * @struct	SaWP8STALLION
 * @brief	繁殖牝馬結構
 *********************************************************/
struct SaWP8STALLION {
	int32u	Count;								//!< 數量
	intxu	Addr;								//!< 位址
	intxu	Seek;								//!< 下一筆資料位移
	int32u	Data[HORSE_STALLION_COUNT][HORSE_STALLION_DATA_LENGTH];		//!< 資料
};
typedef SaWP8STALLION*	LPSaWP8STALLION;		//!< SaWP8STALLION 指標型態

#endif // !__AXEEN_WP8_WP8CHEATSTRUCT_HH__
