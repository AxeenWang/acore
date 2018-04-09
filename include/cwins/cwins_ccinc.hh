/**************************************************************************//**
 * @file	cwins_ccinc.hh
 * @brief	作業系統、編譯環境 Header
 * @author	Swang
 * @date	2018-03-31
 * @date	2018-03-31
 * @note	note
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSCCINC_HH__
#define __AXEEN_CWINS_CWINSCCINC_HH__
#include <TlHelp32.h>

/********************************************//**
 * 導入 Windows Library
 ***********************************************/
#if defined(WINDOWS) && !defined(_LIB) || defined(_CONSOLE)
	// 作業系統 library
	#pragma comment(lib, "comctl32.lib")
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "shlwapi.lib")

	// cwins library
	#if defined(__ACORE_64__)
	#if defined(_DEBUG)
	#pragma comment(lib, "cwins64d.lib")
	#else
	#pragma comment(lib, "cwins64.lib")
	#endif
	#else
	#if defined(_DEBUG)
	#pragma comment(lib, "cwins32d.lib")
	#else
	#pragma comment(lib, "cwins32.lib")
	#endif
	#endif
#endif

#endif // !__AXEEN_CWINS_CWINSCCINC_HH__
