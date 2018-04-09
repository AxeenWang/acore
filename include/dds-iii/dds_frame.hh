/**************************************************************************//**
 * @file	dds_frame.hh
 * @brief	DDS-III 主視窗操作類別
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-23
 * @note	none
 *****************************************************************************/
#ifndef __AXEEN_DDSIII_DDSFRAME_HH__
#define __AXEEN_DDSIII_DDSFRAME_HH__
#include "dds-iii-define.hh"
#include "dds_cheat.hh"

/**************************************************//**
 * @class	DDSFrame
 * @brief	DDS-III 主視窗操作類別
 * @author	Swang
 * @note	PS2 真女神轉生III-狂熱版，輔助工具主式窗類別
 *****************************************************/
class DDSFrame : public WsDialog
{
public:
	DDSFrame();
	virtual ~DDSFrame();

	virtual LRESULT MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam);
	void DoWmInitDialog(WPARAM wParam, LPARAM lParam);
	void DoWmClose(WPARAM wParam, LPARAM lParam);
	void DoWmCommand(WPARAM wParam, LPARAM lParam);
	void DoWmTimer(WPARAM wParam, LPARAM lParam);
	void DoWmActive(WPARAM wParam, LPARAM lParam);

	void DoCommandComboSelect(UINT id);
	void LoadMoonStatus();
	void LoadMemberData();
	void SaveMemberData();

	void CreateMonsterGroupFailed();
	void CreateMonsterGroup();
	void ComboMonsterCode();
	void ComboMonsterMemberNumber();
	void ComboMonsterLevel();
	void ComboMonsterPower();
	void ComboMonsterSkillAmount();
	void ComboMonsterSkill();
	void ComboMoon();
	void CreateCheatObject();
	
	void Release();

protected:
	DDSCheat*	m_xCheat;										//!< DDSCheat 目標程序操作物件

	WsCombo*	m_xComboMoon;									//!< DmcCombo 物件 (月亮狀態)
	WsCombo*	m_xComboMonsterCode;							//!< DmcCombo 物件 (惡魔編號)
	WsCombo*	m_xComboMonsterLevel;							//!< DmcCombo 物件 (仲魔等級)
	WsCombo*	m_xComboMonsterSkillAmount;						//!< DmcCombo 物件 (技能數量)
	WsCombo*	m_xComboMonsterMemberNumber;					//!< DmcCombo 物件 (仲魔編號)
	WsCombo*	m_xComboMonsterPower[DDSIII_POWER_TYPENUMS];	//!< DmcCombo 物件 (仲魔各項能力)
	WsCombo*	m_xComboMonsterSkill[DDSIII_SKILL_MAXREAL];		//!< DmcCombo 物件 (仲魔各項技能)
};

#endif	/* __AXEEN_DDSIII_DDSFRAME_HH__ */
