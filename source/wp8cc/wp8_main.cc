/**************************************************************************//**
 * @file	wp8_main.cc
 * @brief	WP8cc 程序起始函示
 * @author	Swang
 * @date	2018-04-03
 * @date	2018-04-03
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_frame.hh"

/**************************************************//**
 * @brief	wWinMain WP8cc 程序入口
 * @param	[in] hInstance		Handle of Instance (Module)
 * @param	[in] hPrevInstance	Handle of Instance (Win16 Old)
 * @param	[in] lpCmdLine		Command-line 字串指標
 * @param	[in] nShowCmd		顯示方式
 * @return	@c int 程序結束碼
 *****************************************************/
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	const TCHAR* szMutex = TEXT("{8880EF18-59A9-B055-D668-86CB5A6D16F6}");
	int err = 0;
	HANDLE hMutex = Null;
	WP8Cheat* chtObj = Null;
	WP8Frame* frmObj = Null;


	for (;;) {
		// 檢查互拆識別，用於防止程式重載
		hMutex = ::CreateMutex(Null, True, szMutex);
		if (::GetLastError() == ERROR_ALREADY_EXISTS) {
			::SysError(emErrMutex); break;
		}

		// 建立程序操作物件 WP8Cheat
		if ((chtObj = ::StartCheat()) == Null) {
			::SysError(emErrWP8Cheat); break;
		}

		// 建立主要框架物件 WP8Frame
		if ((frmObj = new (std::nothrow) WP8Frame()) == Null) {
			::SysError(emErrWP8Frame); break;
		}

		// 建立視窗框架
		if (!frmObj->Create(hInstance)) {
			::SysError(emErrCreateWP8Frame); break;
		}
		err = frmObj->Run();
		err = 0 - err;
		break;
	}
	::EndCheat();
	SAFE_DELETE(frmObj);
	SAFE_CLOSE_HANDLE(hMutex);
	return 0 - err;
}
