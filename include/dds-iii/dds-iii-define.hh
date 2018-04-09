/**************************************************************************//**
 * @file	dds-iii-define.hh
 * @brief	DDS-III 定義檔
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-26
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_DDSIII_DDSIIIDEFINE_HH__
#define __AXEEN_DDSIII_DDSIIIDEFINE_HH__
#include "cwins\cwins.hh"
// 使用 XP 視窗風格進行編譯
#include "cwins\cwins_xpstyle.hh"
#include "resource.h"

#define APPLICATION_RETURN_OVERSETUP	(-1)	//!< 應用程式重複開啟
#define APPLICATION_RETURN_CREATE_FRAME	(-2)	//!< 建立框架失敗
#define APPLICATION_RETURN_OK			(0)		//!< 正常結束

#define DDSIII_NAME			"DDS-III Nocturne Maniax Trainer"	//!< 主視窗標題名稱
#define DDSIII_CONNECT		"遊戲已開啟、連接作用中"					//!< 目前運作狀態訊息
#define DDSIII_DISCONNECT	"尚未偵測到遊戲"						//!< 目前運作狀態訊息

#define DDSIII_TIMER_AUTOLOCK_ID		1000	//!< 視窗 TimerID
#define DDSIII_TIMER_AUTOLOCK_TIMER		500		//!< Timer Event 觸發間格， 延遲單位(ms)

#endif  // !__AXEEN_DDSIII_DDSIIIDEFINE_HH__
