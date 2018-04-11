/**************************************************************************//**
 * @file	dds_cheat.cc
 * @brief	DS-III 目標程序操作類別成員函式
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-26
 * @note	none
 *****************************************************************************/
#include "dds-iii\dds_cheat.hh"

/**************************************************//**
 * @brief DDSCheat 建構式
 *****************************************************/
DDSCheat::DDSCheat() : WsCheat(), m_xBasePoint(0), m_iBaseID(0)
{
	const int len = DDSIII_MEMBER_DATASIZE;
	::memset((void*)m_cBaseData, 0, len);
	::memset((void*)m_cBaseEdit, 0, len);
	::memset((void*)m_cBaseSave, 0, len);
}

/**************************************************//**
 * @brief DDSCheat 解構式
 *****************************************************/
DDSCheat::~DDSCheat() { this->Destroy(); }

/**************************************************//**
 * @brief	檢查仲魔生命狀態
 *****************************************************/
void DDSCheat::CheckLife()
{
	const IntQu abase = DDSIII_MEMBER_BASE;
	const IntQu aones = DDSIII_MEMBER_ONES;
	const IntQu anext = DDSIII_MEMBER_NEXT;
	const int maxmember = DDSIII_MEMBER_MAX_NUMS;
	IntQu addr = abase + 2;

	if (m_hProcess == NULL) return;
	
	// 主人公 HP, MP 狀態處理
	this->GodBlessYou(addr);

	// 仲魔 HP, MP 狀態處理
	addr += aones;
	for (int i = 0; i < maxmember; i++) {
		this->GodBlessYou(addr);
		addr += anext;
	}
}

/**************************************************//**
 * @brief	檢查已擁有物品數量
 * @note	若已擁有的物品數量低於門檻值，則將該物品數量設為門檻值
 *****************************************************/
void DDSCheat::CheckItem()
{
	HANDLE hProc = m_hProcess;
	IntQu abase = DDS3_ITEM_BASE;
	UINT num;

	if (hProc == NULL) return;
	for (int i = 0; i < DDS3_ITEM_NUMS; i++) {
		num = 0;
		this->ReadMemory((LPCVOID)abase, (LPVOID)&num, 1);
		if (num !=0) {
			if (num < DDS3_ITEM_THRESHOLD) {
				num = DDS3_ITEM_THRESHOLD;
				this->WriteMemory((LPVOID)abase, (LPCVOID)&num, 1);
			}
			else {
				if (num > DDS3_ITEM_MAX) {
					num = DDS3_ITEM_MAX;
					this->WriteMemory((LPVOID)abase, (LPCVOID)&num, 1);
				}
			}
		}
		abase++;
	}
}

/**************************************************//**
 * @brief	檢查已擁有寶石數量
 * @note
 *	若已擁有寶石數量低於門檻值，將寶石數量設為門檻值
 *****************************************************/
void DDSCheat::CheckGem()
{
	HANDLE hProc = m_hProcess;
	IntQu abase = DDS3_GEM_BASE;
	UINT num;

	if (hProc == NULL) return;
	for (int i = 0; i < DDS3_GEM_NUMS; i++) {
		num = 0;
		this->ReadMemory((LPCVOID)abase, (LPVOID)&num, 1);
		if (num !=0) {
			if (num < DDS3_GEM_THRESHOLD) {
				num = DDS3_GEM_THRESHOLD;
				this->WriteMemory((LPVOID)abase, (LPCVOID)&num, 1);
			}
			else {
				if (num > DDS3_GEM_MAX) {
					num = DDS3_GEM_MAX;
					this->WriteMemory((LPVOID)abase, (LPCVOID)&num, 1);
				}
			}
		}
		abase++;
	}
}

/**************************************************//**
 * @brief	檢查魔幣數量
 * @note
 *	若魔幣數量少於門檻值，將以門檻值作為最低值
 *****************************************************/
void DDSCheat::CheckGold()
{
	HANDLE hProc = m_hProcess;
	IntQu abase = DDS3_GOLD_BASE;
	UINT num;

	if (hProc == NULL) return;
	this->ReadMemory((LPCVOID)abase, (LPVOID)&num, 4);
	if (num < DDS3_GOLD_THRESHOLD) {
		num = DDS3_GOLD_THRESHOLD;
		this->WriteMemory((LPVOID)abase, (LPCVOID)&num, 4);
	}
}

/**************************************************//**
 * @brief	讀取仲魔資料
 * @param	[in] val	招收仲魔存放欄位之編號
 * @return	Bool 型別
 *	- 讀取成功傳回: TRUE
 *	- 讀取失敗傳回: FALSE
 *****************************************************/
Bool DDSCheat::LoadMemberData(int val)
{
	const int maxsize = DDSIII_MEMBER_DATASIZE;
	const int maxmembers = DDSIII_MEMBER_MAX_NUMS;
	const int abase = DDSIII_MEMBER_BASE;
	const int aones = DDSIII_MEMBER_ONES;
	const int anext = DDSIII_MEMBER_NEXT;
	const Bool err = FALSE;
	IntQu	xAddress;

	// 檢查編號是否正確
	if (val < 0 || val > maxmembers)
		return err;

	// 計算仲魔資料位址
	if (val == 0) 
		xAddress = abase;
	else 
		xAddress = abase + aones + ((val - 1) * anext);

	// 讀取資料
	if (this->ReadMemory((LPCVOID)xAddress, m_cBaseData, maxsize) != maxsize) {
		this->ClearLoadData();
		return err;
	}

	// 完成操作
	m_xBasePoint = xAddress;
	m_iBaseID = val;
	::memcpy(m_cBaseEdit, m_cBaseData, maxsize);
	return TRUE;
}

/**************************************************//**
 * @brief	保存仲魔資料
 * @return	Bool 型別
 *	- 保存成功傳回: TRUE
 *	- 保存失敗傳回: FALSE
 *****************************************************/
Bool DDSCheat::SaveMemberData()
{
	const int maxsize = DDSIII_MEMBER_DATASIZE;
	const Bool err = FALSE;
	IntQu	xAddress = m_xBasePoint;

	if (xAddress == 0)
		return err;

	// 讀取當前指定欲存放仲魔資料
	if (this->ReadMemory((LPCVOID)xAddress, m_cBaseSave, maxsize) != maxsize)
		return err;

	// 比對資料是否變動
	for (int i = 0; i < maxsize; i++) {
		if (m_cBaseData[i] != m_cBaseSave[i]) return err;
	}

	// 保存資料
	if (this->WriteMemory((LPVOID)xAddress, m_cBaseEdit, maxsize) == maxsize) {
		// 資料保存成功，更新原讀取資料
		::memcpy(m_cBaseData, m_cBaseEdit, maxsize);
	}
	return TRUE;
}

/**************************************************//**
 * @brief	神的祝福
 * @param	[in] addr	仲魔生命資料基礎位址
 * @note
 *	神的祝福，對於指定仲魔生命與魔法的祝福
 *	- 當前生命值若小於最大生命值的 1/2 則等於最大生命值的 1/2
 *	- 當前魔法值若小於最大魔法值的 1/2 則等於最大魔法值的 1/2
 *	- 移除所有負面狀態
 *****************************************************/
void DDSCheat::GodBlessYou(IntQu addr)
{
	DDSIIIMEMBERSTATUS ms;

	::memset(&ms, 0, sizeof(ms));
	this->ReadMemory((LPCVOID)addr, &ms, 10);
	if (ms.minHP > ms.maxHP)
		ms.minHP = ms.maxHP;
	ms.maxHP >>= 1;
	if (ms.minMP > ms.maxMP)
		ms.minMP = ms.maxMP;
	ms.maxMP >>= 1;
	ms.status = 0;
	if (ms.minHP < ms.maxHP)
		ms.minHP = ms.maxHP;
	if (ms.minMP < ms.maxMP)
		ms.minMP = ms.maxMP;
	this->WriteMemory((LPVOID)addr, &ms.minHP, 2);
	this->WriteMemory((LPVOID)(addr+4), &ms.minMP, 2);
	this->WriteMemory((LPVOID)(addr+8), &ms.status, 2);
}


/**************************************************//**
 * @brief	取得指定位置資料
 * @param	[in] dst	存放資料位址
 * @param	[in] inx	要擷取目標索引 (偏位址 in byte)
 * @param	[in] len	要擷取資料長度
 * @return Bool
 *	- 成功傳回: TRUE
 *	- 失敗傳回: FALSE
 *****************************************************/
Bool DDSCheat::GetDataEdit(void* dst, int inx, size_t len)
{
	const int maxsize = DDSIII_MEMBER_DATASIZE;
	if (dst == NULL)
		return FALSE;
	if ((len + inx) > maxsize)
		return FALSE;
	::memcpy(dst, &m_cBaseEdit[inx], len);
	return TRUE;
}

/**************************************************//**
 * @brief	設定指定位置資料
 * @param	[in] src	資料位址
 * @param	[in] inx	要存放目標位置 (偏位址 in byte)
 * @param	[in] len	要存放資料長度
 * @return	Bool
 *	- 成功傳回: TRUE
 *	- 失敗傳回: FALSE
 *****************************************************/
void DDSCheat::SetDataEdit(void * src, int inx, size_t len)
{
	const int maxsize = DDSIII_MEMBER_DATASIZE;
	if (src == NULL)
		return;
	if ((len + inx) > maxsize)
		return;
	::memcpy(&m_cBaseEdit[inx], src, len);
}

/**************************************************//**
 * @brief 清空暫存資料
 *****************************************************/
void DDSCheat::ClearLoadData()
{
	const int len = DDSIII_MEMBER_DATASIZE;
	m_xBasePoint = 0;
	m_iBaseID = 0;
	::memset((void*)m_cBaseData, 0, len);
	::memset((void*)m_cBaseEdit, 0, len);
	::memset((void*)m_cBaseSave, 0, len);
}

/**************************************************//**
 * @brief	釋放所有建立物件
 * @note	釋放程序中建立之記憶體或其他物件
 *****************************************************/
void DDSCheat::Destroy()
{
	const int len = DDSIII_MEMBER_DATASIZE;
	m_xBasePoint = 0;
	m_iBaseID = 0;
	::memset((void*)m_cBaseData, 0, len);
	::memset((void*)m_cBaseEdit, 0, len);
	::memset((void*)m_cBaseSave, 0, len);
}
