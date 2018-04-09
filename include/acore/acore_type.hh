/**************************************************************************//**
 * @file	acore_type.hh
 * @brief	資料型別定義
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-03-25
 * @note
 *	放置於先行編譯標頭檔之後
 *****************************************************************************/
#ifndef __AXEEN_ACORE_ACORETYPE_HH__
#define __AXEEN_ACORE_ACORETYPE_HH__

#ifdef WINDOWS
typedef __int8				int8;		//!< 有號式 8-bits 型別
typedef __int16				int16;		//!< 有號式 16-bits 型別
typedef __int32				int32;		//!< 有號式 32-bits 型別
typedef __int64				int64;		//!< 有號式 64-bits 型別
typedef unsigned __int8		int8u;		//!< 無號式 8-bits 型別
typedef unsigned __int16	int16u;		//!< 無號式 16-bits 型別
typedef unsigned __int32	int32u;		//!< 無號式 32-bits 型別
typedef unsigned __int64	int64u;		//!< 無號式 64-bits 型別

#else
typedef char				int8;		//!< 有號式 8-bits 型別
typedef short				int16;		//!< 有號式 16-bits 型別
typedef int					int32;		//!< 有號式 32-bits 型別
typedef int64_t				int64;		//!< 有號式 64-bits 型別
typedef unsigned char		int8u;		//!< 無號式 8-bits 型別
typedef unsigned short		int16u;		//!< 無號式 16-bits 型別
typedef unsigned int		int32u;		//!< 無號式 32-bits 型別
typedef unsigned int64_t	int64u;		//!< 無號式 64-bits 型別

										// 定義 Visual studio C/C++ (Windows API) 常用 type
typedef int8u				BYTE;		//!< 無號式 8-bits 型別
typedef int16u				WORD;		//!< 無號式 16-bits 型別
typedef int32u				DWORD;		//!< 無號式 32-bits 型別
typedef int64u				DWORD64;	//!< 無號式 64-bits 型別
typedef int32u				UINT;		//!< 無號式 32-bits 型別
typedef int32				BOOL;		//!< 布林式型別
typedef void*				HANDLE;		//!< HANDLE 型別

#if !defined(UNICODE)
typedef char				TCHAR;		//!< 字元 - 單位元組
#else
typedef wchar_t				TCHAR;		//!< 字元 - 雙位元組
#endif
#endif

#if defined(__ACORE_64__)
typedef int64	intx;		//!< 有號數，對應CPU架構，最大型別 32-bit or 64bit
typedef int64u	intxu;		//!< 無號數，對應CPU架構，最大型別 32-bit or 64bit
#else
typedef int64	intx;		//!< 有號數，對應CPU架構，最大型別 32-bit or 64bit
typedef int64u	intxu;		//!< 無號數，對應CPU架構，最大型別 32-bit or 64bit
#endif

#endif	// !__AXEEN_ACORE_ACORETYPE_HH__
