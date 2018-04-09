/**************************************************************************//**
 * @file	cwins_frame.hh
 * @brief	視窗操作 : 視窗操作類別
 * @author	Swang
 * @date	2010-10-10
 * @date	2018-04-02
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_CWINS_CWINSFRAME_HH__
#define __AXEEN_CWINS_CWINSFRAME_HH__
#include "cwins_object.hh"

/**************************************************//**
 * Macro 定義
 *****************************************************/
#define DEFAULT_WNDS_WIDTH      1280				//!< 預設視窗寬度
#define DEFAULT_WNDS_HEIGHT     720					//!< 預設視窗高度
#define DEFAULT_WNDS_STYLE      (WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)	//!< 預設視窗風格
#define DEFAULT_WNDS_CLASS      "DMC_SAMPLE_WINDOW"	//!< 預設視窗 Class 名稱 (for RegisterClass )
#define DEFAULT_WNDS_TITLE      "Dmc Sample Window"	//!< 預設視窗標題

/**************************************************//**
 * @class	WsFrame
 * @brief	視窗操作 : 視窗操作類別
 * @author	Swang
 * @note
 *	繼承 DmcBase
 *****************************************************/
class WsFrame : public WsObject
{
protected:
	static  LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	virtual LRESULT MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);

public:
	WsFrame();
	virtual ~WsFrame();

	int  Run();
	BOOL CreateFromWindowEx(HINSTANCE hInstance);

protected:
	BOOL InRegisterClass(LPSaFRAME fmsPtr);
	BOOL InCreateWindow(LPSaFRAME fmsPtr);
};

/**************************************************//**
 * @brief	建構式
 *****************************************************/
inline WsFrame::WsFrame() : WsObject() { }

/**************************************************//**
 * @brief	解構式
 *****************************************************/
inline WsFrame::~WsFrame() { }

#endif  /* __AXEEN_CWINS_CWINSFRAME_HH__ */
