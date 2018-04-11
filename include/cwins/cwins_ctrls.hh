/**************************************************************************//**
 * @file	cwins_ctrls.hh
 * @brief	視窗操作 : 控制項操作項基底類別
 * @author	Swang
 * @date	2000-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSCTRLS_HH__
#define __AXEEN_CWINS_CWINSCTRLS_HH__
#include "cwins_object.hh"

/**************************************************//**
 * @class	WsCtrls
 * @brief	視窗操作 : 控制項操作項基底類別
 * @author	Swang
 * @note	控制項操作基底類別，繼承 DmcBase
 *****************************************************/
class WsCtrls : public WsObject
{
public:
	WsCtrls();
	WsCtrls(EmCTRLS type);
	virtual ~WsCtrls();
	Bool CreateUseHotCodes(LPSaCTRLS ccPtr);
	Bool CreateUseResource(HWND hParent, int idItem, WNDPROC fnWndProcess);
	Bool CombineResource(HWND hCtrl, int idItem);
	LPCTSTR GetControlClassName(EmCTRLS index);
};

/**************************************************//**
 * @brief 建構式
 *****************************************************/
inline WsCtrls::WsCtrls() : WsObject() { }

/**************************************************//**
 * @brief	建構式
 * @param	type	控制項種類
 * @see		EmCTRLS
 *****************************************************/
inline WsCtrls::WsCtrls(EmCTRLS type) : WsObject(type) { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsCtrls::~WsCtrls() { }

#endif  // !__AXEEN_CWINS_CWINSCTRLS_HH__
