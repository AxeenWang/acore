﻿/**************************************************************************//**
 * @file	acore_macro.hh
 * @brief	巨集定義
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-03-25
 * @note
 *	放置於先行編譯標頭檔之後
 *****************************************************************************/
#ifndef __AXEEN_ACORE_ACOREMACRO_HH__
#define __AXEEN_ACORE_ACOREMACRO_HH__

/********************************************//**
 * 常數巨集
 ***********************************************/
#ifndef Null
#ifdef __cplusplus
#define Null  0				//!< 空值，無值 null
#else
#define Null  ((void*)0)	//!< 空值，無值 null
#endif
#endif

#ifndef True
#define True	1			//!< 布林式判別 for Bool
#endif

#ifndef False
#define False	0			//!< 布林式判別 for Bool
#endif

/********************************************//**
 * 字串宣告巨集 - Windows 風格字串定義
 ***********************************************/
#ifndef WINDOWS
#if defined(UNICODE) || (_UNICODE)
#ifndef __TEXT
#define __TEXT(quote) L ## quote		//!< 字串定義巨集
#endif
#else
#ifndef __TEXT
#define __TEXT(quote) quote				//!< 字串定義巨集
#endif
#endif
  
#ifndef TEXT
#define TEXT(quote) __TEXT(quote)		//!< 字串定義巨集
#endif
#endif

/********************************************//**
 * 定義型巨集
 ***********************************************/
#define STRING_MAX		260		//!< 最大字串容量
#define STRING_HUGE		196		//!< 超大字串容量
#define STRING_LARGE	132		//!< 大型字串容量
#define STRING_MIDDLE	64		//!< 中型字串容量
#define STRING_SMALL	32		//!< 小型字串容量
#define STRING_TINY		24		//!< 最小字串容量

/********************************************//**
 * 常用動作巨集
 ***********************************************/
#define SAFE_FREE(p)            { if (Null!=(p))  { ::free((void*)(p); (p)=Null; } }	//!< 釋放記憶體
#define SAFE_DELETE(p)          { if (Null!=(p))  { delete (p); (p)=Null; } }			//!< 釋放記憶體配置 (物件型)
#define SAFE_DELETE_ARRAY(p)    { if (Null!=(p))  { delete [] (p); (p)=Null; } }		//!< 釋放記憶體配置 (陣列型)
#define SAFE_CLOSE_FILE(p)      { if (Null!=(p))  { ::fclose(p); (p)=Null; } }			//!< 關閉檔案
#define SAFE_CLOSE_HANDLE(p)    { if (Null!=(p) && INVALID_HANDLE_VALUE!=(p))  { ::CloseHandle(p); (p)=Null; } }	//!< 關閉 Window Handle

#endif	__AXEEN_ACORE_ACOREMACRO_HH__
