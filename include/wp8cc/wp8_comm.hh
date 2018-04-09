/**************************************************************************//**
 * @file	wp8_comm.hh
 * @brief	WP8cc 通用函式 Header
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-05
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_WP8_WP8COMM_HH__
#define __AXEEN_WP8_WP8COMM_HH__
#include "wp8_cheat.hh"

WP8Cheat*	StartCheat();
void		EndCheat();
WP8Cheat*	GetCheat();

void		SysError(EmWP8ERROR err, HWND hWnd = NULL);
LPCTSTR		GetNamePark(EmNAMEPARK index);
LPCTSTR		SearchNamePark(EmNAMEPARK index);
LPCTSTR		GetJockeyName(int index);

#endif // !__AXEEN_WP8_WP8COMM_HH__
