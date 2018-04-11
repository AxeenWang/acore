/**************************************************************************//**
 * @file	cwins_undef.hh
 * @brief	反定義作業系統 windows.h 一些巨集。
 * @author	Swang
 * @date	2018-03-25
 * @date	2018-03-25
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSUNDEF_HH__
#define __AXEEN_CWINS_CWINSUNDEF_HH__

#if defined(WINDOWS)
// ----------------- SendMessage ------------------
#ifdef SendMessage
#undef SendMessage
inline LRESULT WINAPI SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	#ifdef __ACORE_UNICODE__
	return ::SendMessageW(hWnd, Msg, wParam, lParam);
	#else
	return ::SendMessageA(hWnd, Msg, wParam, lParam);
	#endif
}
#endif	// !SendMessage

// ----------------- PostMessage ------------------
#ifdef PostMessage
#undef PostMessage
inline Bool WINAPI PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	#ifdef __ACORE_UNICODE__
	return ::PostMessageW(hWnd, Msg, wParam, lParam);
	#else
	return ::PostMessageA(hWnd, Msg, wParam, lParam);
	#endif
}
#endif	// !PostMessage

// ----------------- CreateFont ------------------
#ifdef CreateFont
#undef CreateFont
inline HFONT CreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCTSTR lpszFace)
{
	#ifdef __ACORE_UNICODE__
	return CreateFontW(nHeight, nWidth, nEscapement, nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet, fdwOutputPrecision, fdwClipPrecision, fdwQuality, fdwPitchAndFamily, lpszFace);
	#else
	return CreateFontA(nHeight, nWidth, nEscapement, nOrientation, fnWeight, fdwItalic, fdwUnderline, fdwStrikeOut, fdwCharSet, fdwOutputPrecision, fdwClipPrecision, fdwQuality, fdwPitchAndFamily, lpszFace);
	#endif
	}
#endif	// !CreateFont


// ----------------- PostMessage ------------------
#ifdef GetModuleHandle
#undef GetModuleHandle
inline HMODULE WINAPI GetModuleHandle(LPCTSTR lpModuleName)
{
#ifdef __ACORE_UNICODE__
	return ::GetModuleHandleW(lpModuleName);
#else
	return ::GetModuleHandleA(lpModuleName);
#endif
}
#endif	// !PostMessage

#endif	// !WINDOWS
#endif	// !__AXEEN_CWINS_CWINSUNDEF_HH__
