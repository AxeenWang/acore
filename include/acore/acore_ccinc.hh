/**************************************************************************//**
 * @file	acore_ccinc.hh
 * @brief	acore 作業系統，編譯工具 Header
 * @author	Swang
 * @date	2018-03-31
 * @date	2018-03-31
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_ACORE_ACORECCINC_HH__
#define	__AXEEN_ACORE_ACORECCINC_HH__

/********************************************//**
 * 使用 C Run Time (CRT) Header
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>

/********************************************//**
 * 使用 C++ Run Time (CRT) Header
 ***********************************************/
#include <iostream>
#include <vector>

/********************************************//**
 * 導入視窗控制 Windows API Header
 ***********************************************/
#if defined(WINDOWS)
#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#endif

/********************************************//**
 * 連結 acore library
 ***********************************************/
#if defined(WINDOWS) && !defined(_LIB) || defined(_CONSOLE)
	// 作業系統 library
	#pragma comment(lib, "winmm.lib")

	// acore library
	#if defined(__ACORE_64__)
	#if defined(_DEBUG)
	#pragma comment(lib, "acore64d.lib")
	#else
	#pragma comment(lib, "acore64.lib")
	#endif
	#else
	#if defined(_DEBUG)
	#pragma comment(lib, "acore32d.lib")
	#else
	#pragma comment(lib, "acore32.lib")
	#endif
	#endif
#endif

#endif // !__AXEEN_ACORE_ACORECCINC_HH__
