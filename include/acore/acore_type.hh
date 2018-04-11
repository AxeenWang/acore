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

// acore 資料型別定義
#ifdef WINDOWS
typedef __int8				Int8;		//!< 有號式 8-bits 型別
typedef __int16				Int16;		//!< 有號式 16-bits 型別
typedef __int32				Int32;		//!< 有號式 32-bits 型別
typedef __int64				Int64;		//!< 有號式 64-bits 型別
typedef unsigned __int8		Int8u;		//!< 無號式 8-bits 型別
typedef unsigned __int16	Int16u;		//!< 無號式 16-bits 型別
typedef unsigned __int32	Int32u;		//!< 無號式 32-bits 型別
typedef unsigned __int64	Int64u;		//!< 無號式 64-bits 型別
#else
typedef char				Int8;		//!< 有號式 8-bits 型別
typedef short				Int16;		//!< 有號式 16-bits 型別
typedef int					Int32;		//!< 有號式 32-bits 型別
typedef int64_t				Int64;		//!< 有號式 64-bits 型別
typedef unsigned char		Int8u;		//!< 無號式 8-bits 型別
typedef unsigned short		Int16u;		//!< 無號式 16-bits 型別
typedef unsigned int		Int32u;		//!< 無號式 32-bits 型別
typedef unsigned int64_t	Int64u;		//!< 無號式 64-bits 型別
										// 定義 Visual studio C/C++ (Windows API) 常用 type
typedef Int8u				BYTE;		//!< 無號式 8-bits 型別
typedef Int16u				WORD;		//!< 無號式 16-bits 型別
typedef Int32u				DWORD;		//!< 無號式 32-bits 型別
typedef Int64u				DWORD64;	//!< 無號式 64-bits 型別
typedef Int32u				UINT;		//!< 無號式 32-bits 型別
typedef Int32				Bool;		//!< 布林式型別
typedef void*				HANDLE;		//!< HANDLE 型別

#if !defined(UNICODE)
typedef char				TCHAR;		//!< 字元 - 單位元組
#else
typedef wchar_t				TCHAR;		//!< 字元 - 雙位元組
#endif
#endif

typedef Int32	Bool;		//!< 布林式型別

#if defined(__ACORE_64__)
typedef Int64	IntQ;		//!< 有號數，對應CPU架構，最大型別 32-bit or 64bit
typedef Int64u	IntQu;		//!< 無號數，對應CPU架構，最大型別 32-bit or 64bit
#else
typedef Int32	IntQ;		//!< 有號數，對應CPU架構，最大型別 32-bit or 64bit
typedef Int32u	IntQu;		//!< 無號數，對應CPU架構，最大型別 32-bit or 64bit
#endif

#endif	// !__AXEEN_ACORE_ACORETYPE_HH__
