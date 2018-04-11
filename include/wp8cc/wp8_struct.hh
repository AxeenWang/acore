/**************************************************************************//**
 * @file	wp8_struct.hh
 * @brief	結構、列舉宣告 Header
 * @author	Swang
 * @date	2018-04-03
 * @date	2018-04-03
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8STRUCT_HH__
#define	__AXEEN_WP8_WP8STRUCT_HH__

#define	WP8_DEFAULT_WIDTH	800			//!< WP8cc 主視窗框架預設寬度
#define WP8_DEFAULT_HEIGHT	360			//!< WP8cc 主視窗框架預設高度

#define WP8_TABS_X			4			//!< 主視窗標籤控制項起始位置 x
#define	WP8_TABS_Y			4			//!< 主視窗標籤控制項起始位置 y
#define WP8_FUNC_X			2			//!< 功能頁起始位置修正 X
#define WP8_FUNC_Y			4			//!< 功能頁起始位置修正 Y
#define WP8_TAB_PAGE_X		2			//!< 標籤頁面起始位置修正 X
#define WP8_TAB_PAGE_Y		4			//!< 標籤頁面起始位置修正 Y

#define WM_WP8FUNC			WM_USER+101	//!< WP8Func 回報訊息 : 讀取鍵觸發
#define WM_WP8ERROR			WM_USER+500	//!< 自訂訊息 : 發生錯誤

/******************************************************//**
 * @brief	列舉視窗名稱
 * @details	配合 GetNamePark、SearchNamePark  函式使用。
 *********************************************************/
enum EmNAMEPARK {
	emNameDefault = 0,	//!< WP8cc 主視窗預設名稱
	emNameClassName,	//!< WP8cc 註冊視窗 Class name
	emNameTitleName,	//!< WP8cc 主視窗名稱
	emNameError,		//!< WP8cc 錯誤對話框標題名稱
	emNamePassEnd		//!< EmNAMEPARK 結尾識別
};

/******************************************************//**
 * @brief	錯誤訊息
 * @details	配合 SysError 函式使用。
 *********************************************************/
enum EmWP8ERROR {
	emErrOK	= 0,
	emErrMutex,
	emErrWP8Frame,
	emErrCreateWP8Frame,
	emErrWP8Cheat,
	emErrGameNotFound,
	emErrInitTabs,
	emErrInitPage,
	emErrInitTabItem,
	emErrInitRaceList,
	emErrInitGameList,
	emErrUnknow
};

/******************************************************//**
 * @brief	WP8Func 類別回傳訊息
 * @details	配合 WP8Func 回傳訊息給父視窗 WP8Frame 類別。
 *********************************************************/
enum EmWP8FUNCPARAM {
	emWP8FuncNone = 0,
	emWP8FuncLoad
};

/******************************************************//**
 * @struct	SaCONSTTEXT
 * @brief	WP8cc 名稱定義結構
 *********************************************************/
struct SaCONSTTEXT {
	int				index;	//!< 名稱索引
	const TCHAR*	name;	//!< 字串位址
};


#endif // !__AXEEN_WP8_WP8STRUCT_HH__
