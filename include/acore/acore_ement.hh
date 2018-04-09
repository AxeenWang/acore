/**************************************************************************//**
 * @file	acore_ement.hh
 * @brief	編譯環境定義
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-03-25
 * @note	編譯環境的前置處理定義
 *****************************************************************************/
#ifndef __AXEEN_ACORE_ACOREEMENT_HH__
#define __AXEEN_ACORE_ACOREEMENT_HH__

/********************************************//**
 * 定義 WINDOWS 識別符號
 ***********************************************/
#if defined(_WIN32) || (_WIN64) || (_WIN32_WCE)
#ifndef WINDOWS
#define WINDOWS
#endif
#endif

/********************************************//**
 * 定義編譯作業環境 (32bits? 64bits?) 識別符號
 ***********************************************/
#if defined(_WIN64) || (__x86_64__) || (__ppc64__) || (_M_X64) || (_M_AMD64)
#define __ACORE_64__
#elif defined(_WIN32) || (_X86_) || (__PPC__) || (_M_IX86)
#define __ACORE_32__
#endif

/********************************************//**
 * 定義編譯作業環境，採用 UNICODE
 ***********************************************/
#if defined(_UNICODE) || (UNICODE)
#define __ACORE_UNICODE__
#endif

/********************************************//**
 * 定義 WINDOWS 作業版本識別符號 _WIN32_WINNT, WINVER
 *  - Set using Windows Platform SDK
 *  - 設定平台編譯環境 Windows SDK
 ***********************************************/
#if defined(WINDOWS)
	// _WIN32_WINNT version constants (see windows sdk sdkddkver.h)
	#define _WIN_SYMBOL_WINNT4      0x0400  // Windows NT 4.0
	#define _WIN_SYMBOL_WIN2K       0x0500  // Windows 2000
	#define _WIN_SYMBOL_WINXP       0x0501  // Windows XP
	#define _WIN_SYMBOL_WIN2K3      0x0502  // Windows Server 2003
	#define _WIN_SYMBOL_WINVISTA    0x0600  // Windows Vista
	#define _WIN_SYMBOL_WIN2K8      0x0600  // Windows Server 2008
	#define _WIN_SYMBOL_WIN7        0x0601  // Windows 7
	#define _WIN_SYMBOL_WIN8        0x0602  // Windows 8
	#define _WIN_SYMBOL_WIN8BLUE    0x0603  // Windows 8.1
	#define _WIN_SYMBOL_WIN10       0x0A00  // Windows 10

	// Set default _WIN32_WINNT version
	#ifndef _WIN32_WINNT
	#define _WIN32_WINNT _WIN_SYMBOL_WIN7
	#else
	#if (_WIN32_WINNT < _WIN_SYMBOL_WIN7)
	#undef  _WIN32_WINNT
	#define _WIN32_WINNT _WIN_SYMBOL_WIN7
	#endif
	#endif

	// Set WINVER based on _WIN32_WINNT
	// 設定最低要求作業環境版本
	#ifndef WINVER
	#define WINVER _WIN32_WINNT
	#else
	#undef  WINVER
	#define WINVER _WIN32_WINNT
	#endif

	// Set WINVER based on _WIN32_WINNT
	// 設定最低要求作業環境版本
	#ifndef _WIN32_IE
	#define _WIN32_IE _WIN32_WINNT
	#else
	#undef  _WIN32_IE
	#define _WIN32_IE _WIN32_WINNT
	#endif

	// To do speed up compilations, before include windows.h
	// 濾除多餘與重複載入之 Header
	#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
	#endif

	// Enable features that require more care in declaring and using types.
	// 嚴格進行型別檢查
	#ifndef STRICT
	#define STRICT
	#endif

	#ifndef _CRT_SECURE_NO_WARNINGS
	#define	_CRT_SECURE_NO_WARNINGS
	#endif
#endif

#endif	// !__AXEEN_ACORE_ACOREEMENT_HH__
