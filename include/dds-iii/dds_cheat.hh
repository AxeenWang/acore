/**************************************************************************//**
 * @file	dds_cheat.hh
 * @brief	DS-III 目標程序操作類別成員函式
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-26
 * @note	none
 *****************************************************************************/
#ifndef __DDSIII_DXCHEAT_HH__
#define __DDSIII_DXCHEAT_HH__
#include "dds-iii-define.hh"

// 物品資訊
#define DDS3_ITEM_BASE				0x21302A26		//!< 物品基底位址
#define DDS3_ITEM_NUMS				96				//!< 物品種類數
#define DDS3_ITEM_THRESHOLD			20				//!< 物品數量門檻值
#define DDS3_ITEM_MAX				50				//!< 物品數量門檻值

// 寶石資訊
#define DDS3_GEM_BASE				0x21302A84		//!< 寶石基底位址
#define DDS3_GEM_NUMS				16				//!< 寶石種類數
#define DDS3_GEM_THRESHOLD			25				//!< 寶石數量門檻值
#define DDS3_GEM_MAX				50				//!< 寶石數量門檻值

// 魔幣資訊
#define DDS3_GOLD_BASE				0x21301B44		//!< 魔幣基底位址
#define DDS3_GOLD_THRESHOLD			10000			//!< 魔幣門檻值

// 仲魔資訊
#define DDSIII_MEMBER_DATASIZE		0x66			//!< 仲魔資料擷取長度
#define DDSIII_MEMBER_MAX_NUMS		12				//!< 仲魔可招喚最大量
#define DDSIII_MEMBER_BASE			0x21301B54		//!< 仲魔資料基底位址
#define DDSIII_MEMBER_ONES			944				//!< 第一個仲魔偏位址
#define DDSIII_MEMBER_NEXT			236				//!< 下一個仲魔偏位址

#define DDSIII_POWER_TYPENUMS		5				//!< 仲魔能力種類數量
#define DDSIII_POWER_MAXVAL			40				//!< 惡魔能力值上限
#define DDSIII_SKILL_MAXFULL		24				//!< 惡魔最多技能數量
#define DDSIII_SKILL_MAXREAL		8				//!< 惡魔實際技能數量 (遊戲限制)

#define DDSIII_MOON_BASE			0x21301B3D		//!< 月亮變化位址

/******************************************************//**
 * @brief 建立 Listview 控制項， Column 資訊設定
 * @details 對齊方式參照 EmLVCALIGN
 *********************************************************/
typedef struct _DDSIII_MEMBERSTATUS {
	Int16u	minHP;		//!< 當前生命值
	Int16u	maxHP;		//!< 最大生命值
	Int16u	minMP;		//!< 當前魔法值
	Int16u	maxMP;		//!< 最大魔法值
	Int16u	status;		//!< 角色狀態
	Int32u	exp;		//!< 經驗值
} DDSIIIMEMBERSTATUS;

/**************************************************//**
 * @class	DDSCheat
 * @brief	DDS-III 作弊處理
 * @author	Swang
 * @note	繼承 DmcCheat 
 *****************************************************/
class DDSCheat : public WsCheat
{
public:
	DDSCheat();
	virtual ~DDSCheat();

	void CheckLife();
	void CheckItem();
	void CheckGem();
	void CheckGold();

	Bool LoadMemberData(int val);
	Bool SaveMemberData();

	/**************************************************//**
	 * @brief 取得惡魔編號
	 * @return int 傳回惡魔編號, 失敗傳回 -1
	 *****************************************************/
	int GetMonsterCode()
	{
		int val = 0;
		if (!this->GetDataEdit(&val, 0, 2))
			val = -1;
		return val;
	}

	/**************************************************//**
	 * @brief 取得仲魔等級
	 * @return int 等級
	 *****************************************************/
	int GetLevel()
	{
		int level = 0;
		if (!this->GetDataEdit(&level, 0x10, 2))
			level = -1;
		return level;
	}

	/**************************************************//**
	 * @brief 取得仲魔經驗值
	 * @return int 經驗值
	 *****************************************************/
	int GetExp()
	{
		int exp = 0;
		if (!this->GetDataEdit(&exp, 0x0C, 4))
			exp = -1;
		return exp;
	}

	/**************************************************//**
	 * @brief	取得仲魔當前生命值
	 * @return	int	當前生命值
	 *****************************************************/
	int GetMinHP()
	{
		int hp = 0;
		if (!this->GetDataEdit(&hp, 0x02, 2))
			hp = -1;
		return hp;
	}

	/**************************************************//**
	 * @brief	取得仲魔最大生命值
	 * @return	int	最大生命值
	 *****************************************************/
	int GetMaxHP()
	{
		int hp = 0;
		if (!this->GetDataEdit(&hp, 0x04, 2))
			hp = -1;
		return hp;
	}

	/**************************************************//**
	 * @brief	取得仲魔當前魔法值
	 * @return	int	當前魔法值
	 *****************************************************/
	int GetMinMP()
	{
		int mp = 0;
		if (!this->GetDataEdit(&mp, 0x06, 2))
			mp = -1;
		return mp;
	}

	/**************************************************//**
	 * @brief	取得最大魔法值
	 * @return	int 最大魔法值
	 *****************************************************/
	int GetMaxMP()
	{
		int mp = 0;
		if (!this->GetDataEdit(&mp, 0x08, 2))
			mp = -1;
		return mp;
	}

	/**************************************************//**
	 * @brief	取得目前狀態
	 * @return	int	目前狀態
	 *****************************************************/
	int GetStatus()
	{
		int status = 0;
		if (!this->GetDataEdit(&status, 0x0A, 2))
			status = -1;
		return status;
	}

	/**************************************************//**
	 * @brief	取得仲魔能力值
	 * @param	[in] inx	能力索引
	 *	- 力 = 0
	 *	- 魔 = 1
	 *	- 體 = 2
	 *	- 速 = 3
	 *	- 運 = 4
	 * @return	int	能力值
	 *****************************************************/
	int GetAbility(int inx)
	{
		const int offset = 0x12;
		int ability = 0;
		int newset;

		if (inx == 0) newset = offset;
		else newset = (inx - 1) + offset + 2;

		if (!this->GetDataEdit(&ability, newset, 1))
			ability = -1;
		return ability;
	}

	/**************************************************//**
	 * @brief	取得技能數量
	 * @return	int	技能數量
	 *****************************************************/
	int GetSkillAmount()
	{
		int skill = 0;
		if (!this->GetDataEdit(&skill, 0x34, 2))
			skill = -1;
		return skill;
	}

	/**************************************************//**
	 * @brief	取得技能
	 * @param	inx	技能欄位
	 * @return	val 技能編號
	 *****************************************************/
	int GetSkill(int inx)
	{
		int skill = 0;
		int offset = (inx * 2) + 0x36;

		if (!this->GetDataEdit(&skill, offset, 2))
			skill = -1;
		return skill;
	}


	/**************************************************//**
	 * @brief	設定惡魔編號
	 * @param	[in] val	惡魔的編號
	 *****************************************************/
	void SetMonsterCode(int val)
	{
		int monster = val;
		this->SetDataEdit(&monster, 0x00, 2);
	}

	/**************************************************//**
	 * @brief 設定仲魔等級
	 * @param val 等級
	 *****************************************************/
	void SetLevel(int val)
	{
		int level = val;
		this->SetDataEdit(&level, 0x10, 2);
	}

	/**************************************************//**
	 * @brief	設定仲魔經驗值
	 * @param	val	經驗值
	 *****************************************************/
	void SetExp(int val)
	{
		const int maxval = 9999999;
		int exp = val > maxval ? maxval : val;
		this->SetDataEdit(&exp, 0x0C, 4);
	}

	/**************************************************//**
	 * @brief	設定當前生命值
	 * @param	val	當前生命值
	 *****************************************************/
	void SetMinHP(int val)
	{
		int hp = val;
		this->SetDataEdit(&hp, 0x02, 2);
	}

	/**************************************************//**
	 * @brief	設定最大生命值
	 * @param	val	最大生命值
	 *****************************************************/
	void SetMaxHP(int val)
	{
		int hp = val;
		this->SetDataEdit(&hp, 0x04, 2);
	}

	/**************************************************//**
	 * @brief	設定當前魔法值
	 * @param	val	當前魔法值
	 *****************************************************/
	void SetMinMP(int val)
	{
		int mp = val;
		this->SetDataEdit(&mp, 0x06, 2);
	}

	/**************************************************//**
	 * @brief	設定最大魔法值
	 * @param	val	最大魔法值
	 *****************************************************/
	void SetMaxMP(int val)
	{
		int mp = val;
		this->SetDataEdit(&mp, 0x08, 2);
	}

	/**************************************************//**
	 * @brief	設定目前狀態
	 * @return	val	狀態值
	 *****************************************************/
	void SetStatus(int val)
	{
		int status = val;
		this->SetDataEdit(&status, 0x0A, 2);
	}

	/**************************************************//**
	 * @brief	設定仲魔能力值
	 * @param	[in] inx	能力索引
	 *	- 力 = 0
	 *	- 魔 = 1
	 *	- 體 = 2
	 *	- 速 = 3
	 *	- 運 = 4
	 * @param	[in] val	能力值
	 *****************************************************/
	void SetAbility(int inx, int val)
	{
		const int offset = 0x12;
		int ability = val;
		int newset;

		if (inx == 0) newset = offset;
		else newset = (inx - 1) + offset + 2;
		this->SetDataEdit(&ability, newset, 1);
	}

	/**************************************************//**
	 * @brief	設定技能數量
	 * @param	val	技能數量
	 *****************************************************/
	void SetSkillAmount(int val)
	{
		int skill;
		if (val == 0)
			skill = 1;
		else
			skill = val;
		this->SetDataEdit(&skill, 0x34, 2);
	}

	/**************************************************//**
	 * @brief	設定技能
	 * @param	inx	技能欄位
	 * @param	val 技能編號
	 *****************************************************/
	void SetSkill(int inx, int val)
	{
		int skill = val;
		int offset = (inx * 2) + 0x36;
		this->SetDataEdit(&skill, offset, 2);
	}


	/**************************************************//**
	 * @brief	取得月亮變化值
	 * @return	int 型別, 返回月亮狀態值
	 *****************************************************/
	int GetMoon()
	{
		IntQu addr = DDSIII_MOON_BASE;
		int moon = 0;
		if (this->ReadMemory((LPCTSTR)addr, &moon, 1) != 1)
			moon = -1;
		return moon;
	}

	/**************************************************//**
	 * @brief	設定月亮變化值
	 * @return	int 型別, 返回月亮狀態值
	 *****************************************************/
	void SetMoon(int val)
	{
		IntQu addr = DDSIII_MOON_BASE;
		int moon = val;
		this->WriteMemory((LPVOID)addr, &moon, 1);
	}

protected:
	void GodBlessYou(IntQu addr);
	Bool GetDataEdit(void* dst, int inx, size_t len);
	void SetDataEdit(void* src, int inx, size_t len);
	void ClearLoadData();
	void Destroy();

protected:
	IntQu	m_xBasePoint;							//!< 載入的仲魔資料基底位址
	int		m_iBaseID;								//!< 載入的招募仲魔欄位編號
	BYTE	m_cBaseData[DDSIII_MEMBER_DATASIZE];	//!< 載入的原始資料
	BYTE	m_cBaseEdit[DDSIII_MEMBER_DATASIZE];	//!< 修改中資料
	BYTE	m_cBaseSave[DDSIII_MEMBER_DATASIZE];	//!< 存檔比對資料
};

#endif	/* __DDSIII_DXCHEAT_HH__ */
