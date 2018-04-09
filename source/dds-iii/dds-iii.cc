/**************************************************************************//**
 * @file	dds-iii.cc
 * @brief	DDS-III 程序運作起始處
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-24
 * @note	none
 *****************************************************************************/
#include "dds-iii\dds_frame.hh"

/**************************************************//**
 * @brief	Window 起始程序
 * @param	[in] hInstance		Handle of Instance (Module)
 * @param	[in] hPrevInstance	Handle of Instance (Win16 Old)
 * @param	[in] lpCmdLine		Command-line 字串指標
 * @param	[in] nShowCmd		顯示方式
 * @return	@c int				程序結束碼
 *****************************************************/
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	const TCHAR* szMutex = TEXT("{7730EF38-57A9-B0C3-D660-86CB5A4D17F6}");
	const TCHAR* szTitle = TEXT("DDS-III");
	const TCHAR* szExist = TEXT("DDS-III Trainer is running...");
	const TCHAR* szFails = TEXT("DDS-III Initialize failed");

	HANDLE		hMutex	= NULL;
	DDSFrame*	pmain	= NULL;

	// 檢查互拆識別，用於防止程式重載
	hMutex = ::CreateMutex(NULL, TRUE, szMutex);
	if (::GetLastError() == ERROR_ALREADY_EXISTS) {
		SAFE_CLOSE_HANDLE(hMutex);
		::MessageBox(NULL, szExist, szTitle, MB_OK | MB_ICONERROR);
		return APPLICATION_RETURN_OVERSETUP;
	}

	// 建立主要框架 (採用 Dialog 模式) 
	if ((pmain = new (std::nothrow) DDSFrame()) == NULL) {
		SAFE_CLOSE_HANDLE(hMutex);
		::MessageBox(NULL, szFails, szTitle, MB_OK | MB_ICONERROR);
		return APPLICATION_RETURN_CREATE_FRAME;
	}

	pmain->CreateFromResource(NULL, IDD_MAINFRAME, NULL, TRUE);
	SAFE_DELETE(pmain);
	SAFE_CLOSE_HANDLE(hMutex);

	return APPLICATION_RETURN_OK;
}
