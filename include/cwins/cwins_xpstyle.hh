/**************************************************************************//**
 * @file	cwins_xpstyle.hh
 * @brief	Window XP Style 定義 header
 * @author	Swang
 * @date	2018-04-02
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSXPSTYLE_HH__
#define	__AXEEN_CWINS_CWINSXPSTYLE_HH__

/********************************************//**
 * 是否使用 XP-Style？
 ***********************************************/
#if defined(WINDOWS) && !defined(_LIB) || defined(_CONSOLE)
#   if defined _M_IX86
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   elif defined _M_IA64
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   elif defined _M_X64
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   else
#       pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#   endif
#endif

#endif // !__AXEEN_CWINS_CWINSXPSTYLE_HH__
