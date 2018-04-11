/**************************************************************************//**
 * @file	acore_struct.hh
 * @brief	acore 結構宣告
 * @author	Swang
 * @date	2018-03-31
 * @date	2018-03-31
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_ACORE_ACORESTRUCT_HH__
#define __AXEEN_ACORE_ACORESTRUCT_HH__

/******************************************************//**
 * @brief	EmSAMPLE
 * @note	僅僅是一個範本，用來試驗與練習 Doxygen 註解方式
 *********************************************************/
enum EmSAMPLE {
	emItem1 = 0,		//!< 列舉項目 1
	emItem2,			//!< 列舉項目 2
	emItem3,			//!< 列舉項目 3
	emItem4				//!< 列舉項目 4
};

/******************************************************//**
 * @struct	SaACOREEXAMPLE
 * @brief	結構範本
 * @note	僅僅是一個範本，用來試驗與練習 Doxygen 註解方式
 *********************************************************/
struct SaACOREEXAMPLE {
	Int32u	uRes1;		//!< 結構資料 1
	Int32u	uRes2;		//!< 結構資料 2
	Int64u	uData1;		//!< 結構資料 3
	Int64u	uData2;		//!< 結構資料 4
};
typedef SaACOREEXAMPLE*	PSaACOREEXAMPLE;	//!< 結構 ACOREEXAMPLE_ 短程指標
typedef SaACOREEXAMPLE*	LPSaACOREEXAMPLE;	//!< 結構 ACOREEXAMPLE_ 長程指標

#endif // !__AXEEN_ACORE_ACORESTRUCT_HH__
