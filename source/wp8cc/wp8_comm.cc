/**************************************************************************//**
 * @file	wp8_comm.cc
 * @brief	WP8cc 通用函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_comm.hh"

static WP8Cheat* static_cheat_object = NULL;

/******************************************************//**
 * @brief	WP8cc 名稱定義
 *********************************************************/
static SaCONSTTEXT static_name_park[] = {
	emNameDefault,			TEXT("WP8cc"),
	emNameClassName,		TEXT("AXEEN_WP8CC_CLASS"),
	emNameTitleName,		TEXT("WP8cc - Winning Post 8 2018 Viewer"),
	emNameError,			TEXT("WP8cc Error!"),
	emNamePassEnd,			TEXT("WP8cc Pass End")
};

/******************************************************//**
 * @brief	WP8cc 錯誤碼文字定義
 * @note	配合 SysError() 使用顯示錯誤資訊
 *********************************************************/
static SaCONSTTEXT static_error_message[] = {
	emErrOK,				TEXT("正確運作"),
	emErrMutex,				TEXT("正在執行中，不支援重複開啟。"),
	emErrWP8Frame,			TEXT("建立視窗操作物件失敗！"),
	emErrCreateWP8Frame,	TEXT("建立主視窗框架失敗！"),
	emErrWP8Cheat,			TEXT("建立程序操作連結物件失敗！"),
	emErrGameNotFound,		TEXT("Winning Post 8 2018 不存在！"),
	emErrInitTabs,			TEXT("初始化主視窗標籤失敗！"),
	emErrInitPage,			TEXT("初始化標籤頁面失敗！"),
	emErrInitTabItem,		TEXT("初始化"),
	emErrInitRaceList,		TEXT("初始化競走馬列表失敗！"),
	emErrInitGameList,		TEXT("初始化比賽相關列表失敗！"),
	emErrUnknow,			TEXT("未知錯誤")
};

/**************************************************//**
 * @brief	啟動 WPCheat 物件
 * @return	@c WP8Cheat*
 *			- 運作成功傳回: 非零值 WP8Cheat 物件指標
 *			- 運作失敗傳回: NULL
 *****************************************************/
WP8Cheat * StartCheat()
{
	WP8Cheat* wp = static_cheat_object;

	if (wp != NULL) { SAFE_DELETE(wp); }

	if (wp == NULL) {
		wp = new (std::nothrow) WP8Cheat();
		if (wp != NULL) {
			static_cheat_object = wp;
			wp->SetVersion(WP8VER_502);
			return wp;
		}
	}
	return NULL;
}

/**************************************************//**
 * @brief	關閉 WPCheat 物件
 *****************************************************/
void EndCheat()
{
	WP8Cheat* wp = static_cheat_object;
	if (wp != NULL) {
		SAFE_DELETE(wp);
		static_cheat_object = wp;
	}
}

/**************************************************//**
 * @brief	取得 WPCheat 物件
 * @return	@c WP8Cheat* 物件指標
 *			- 物件已建立傳回: 非零值 WP8Cheat 物件指標
 *			- 物件未建立傳回: NULL
 *****************************************************/
WP8Cheat * GetCheat() { return static_cheat_object; }

/**************************************************//**
 * @brief	顯示錯誤訊息
 * @param	[in] err	錯誤碼
 * @param	[in] hWnd	視窗操作 handle
 *****************************************************/
void SysError(EmWP8ERROR err, HWND hWnd)
{
	const int len = sizeof(static_error_message) / sizeof(SaCONSTTEXT);
	TCHAR szTitle[MAX_PATH];

	if (::GetNamePark(emNameError) != NULL)
		::lstrcpy(szTitle, ::GetNamePark(emNameError));
	else
		::lstrcpy(szTitle, TEXT("WP8cc Error"));

	for (int i = 0; i < len; i++) {
		if (static_error_message[i].index == err)
		{
			::MessageBox(hWnd, static_error_message[err].name, szTitle, MB_OK | MB_ICONERROR);
			return;
		}
	}
	::MessageBox(hWnd, static_error_message[len-1].name, szTitle, MB_OK | MB_ICONERROR);
}

/**************************************************//**
 * @brief	取得 WP8cc 名稱定義
 * @param	[in] index	EmNAMEPARK 型別索引
 * @return	@c LPCTSTR
 *			- 字串取得成功傳回: 非零值字串指標
 *			- 字串取得失敗傳回: NULL
 *****************************************************/
LPCTSTR GetNamePark(EmNAMEPARK index)
{
	const int iPark = sizeof(static_name_park) / sizeof(SaCONSTTEXT);

	if (index >= emNamePassEnd || index < emNameDefault)
		return NULL;
	return static_name_park[index].name;
}

/**************************************************//**
 * @brief	搜尋 WP8cc 名稱定義
 * @param	[in] index	EmNAMEPARK 搜尋索引
 * @return	@c LPCTSTR
 *			- 字串取得成功傳回: 非零值字串指標
 *			- 字串取得失敗傳回: NULL
 *****************************************************/
LPCTSTR SearchNamePark(EmNAMEPARK index)
{
	const int len = sizeof(static_name_park) / sizeof(SaCONSTTEXT);
	for (int i = 0; i < len; i++) {
		if (static_name_park[i].index == index) {
			return static_name_park[i].name;
		}
	}
	return NULL;
}

