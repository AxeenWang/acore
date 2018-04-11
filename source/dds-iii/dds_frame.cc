/**************************************************************************//**
 * @file	dds_frame.cc
 * @brief	DDS-III 主視窗操作類別成員函式
 * @author	Swang
 * @date	2018-03-20
 * @date	2018-03-26
 * @note	none
 *****************************************************************************/
#include "dds-iii\dds_frame.hh"

/**************************************************//**
 * @brief 建構式
 *****************************************************/
DDSFrame::DDSFrame() 
	: WsDialog()
	, m_xCheat(Null)
	, m_xComboMoon(Null)
	, m_xComboMonsterCode(Null)
	, m_xComboMonsterLevel(Null)
	, m_xComboMonsterSkillAmount(Null)
	, m_xComboMonsterMemberNumber(Null)
{
	int size = sizeof(m_xComboMonsterSkill) / sizeof(WsCombo*);
	for (int i = 0; i < size; i++) {
		m_xComboMonsterSkill[i] = Null;
	}

	size = sizeof(m_xComboMonsterPower) / sizeof(WsCombo*);
	for (int i = 0; i < size; i++) {
		m_xComboMonsterPower[i] = Null;
	}
}

/**************************************************//**
 * @brief 解構式
 *****************************************************/
DDSFrame::~DDSFrame() { this->Release(); }

/**************************************************//**
 * @brief 視窗訊息處理
 * @param [in] uMessage 視窗訊息
 * @param [in] wParam 參數
 * @param [in] lParam 參數
 * @return LRESULT 視窗訊息處理後結果
 * @note 此為虛擬函數，提供 WndProc 調用
 *****************************************************/
LRESULT DDSFrame::MessageDispose(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_ACTIVATE:
		this->DoWmActive(wParam, lParam);
		break;
	case WM_INITDIALOG:
		this->DoWmInitDialog(wParam, lParam);
		break;
	case WM_DESTROY:
		break;
	case WM_CLOSE:
		this->DoWmClose(wParam, lParam);
		break;
	case WM_COMMAND:
		this->DoWmCommand(wParam, lParam);
		break;
	case WM_TIMER:
		this->DoWmTimer(wParam, lParam);
		break;
	default:
		return False;
	}
	return True;
}

/**************************************************//**
 * @brief WM_INITDIALOG 訊息處理
 * @param [in] wParam 參數
 * @param [in] lParam 參數
 *****************************************************/
void DDSFrame::DoWmInitDialog(WPARAM wParam, LPARAM lParam)
{
	const UINT_PTR eventID = DDSIII_TIMER_AUTOLOCK_ID;
	const UINT timer = DDSIII_TIMER_AUTOLOCK_TIMER;
	const int msgid = IDC_EDIT_MESSAGE;
	const TCHAR* sznm = TEXT(DDSIII_NAME);
	const TCHAR* szff = TEXT(DDSIII_DISCONNECT);

	HWND hEdit = this->GetChild(msgid);

	this->SetIcon(::LoadIcon(::GetModuleHandle(Null), MAKEINTRESOURCE(IDI_ICON)));
	this->SetText(sznm);
	this->SetChildText(msgid, szff);
	this->EnableChild(msgid);

	this->CreateCheatObject();
	this->CreateMonsterGroup();
	this->SetCenterPosition();
	this->SetTimer(eventID, timer, Null);
}

/**************************************************//**
 * @brief WM_CLOSE 訊息處理
 * @param [in] wParam 參數
 * @param [in] lParam 參數
 *****************************************************/
void DDSFrame::DoWmClose(WPARAM wParam, LPARAM lParam)
{
	this->Release();
	this->InDestroyWindow();
	::PostQuitMessage(0);
}

/**************************************************//**
 * @brief WM_COMMAND 訊息處理
 * @param [in] wParam 參數
 * @param [in] lParam 參數
 *****************************************************/
void DDSFrame::DoWmCommand(WPARAM wParam, LPARAM lParam)
{
	UINT idItem = (UINT)LOWORD(wParam);
	UINT uEvent = (UINT)HIWORD(wParam);

	// Combo Box 事件處理
	if (uEvent == CBN_SELCHANGE)
		this->DoCommandComboSelect(idItem);
	else if (idItem == IDC_MONSTER_BTN_SAVE)
		this->SaveMemberData();
}

/**************************************************//**
 * @brief WM_TIMER 訊息處理
 * @param [in] wParam 參數
 * @param [in] lParam 參數
 *****************************************************/
void DDSFrame::DoWmTimer(WPARAM wParam, LPARAM lParam)
{
	const TCHAR* szModule = TEXT("pcsx2.exe");
	const TCHAR* szon = TEXT(DDSIII_CONNECT);
	const TCHAR* szff = TEXT(DDSIII_DISCONNECT);
	const int msgid = IDC_EDIT_MESSAGE;
	DDSCheat* pcheat = m_xCheat;

	if (pcheat == Null)
		return;
	
	// 尚未連接目標程序
	if (!pcheat->IsHooking()) {
		if (pcheat->SearchCheatProcess(szModule)) {
			this->SetChildText(msgid, szon);
			this->LoadMoonStatus();
			this->LoadMemberData();
		}
		return;
	}

	// 已連接目標程序
	if (!pcheat->SearchCheatProcess(szModule)) {
		this->SetChildText(msgid, szff);
		return;
	}

	HWND hWnd = m_hWnd;

	// 更新月亮狀態
	//if (m_bBackGroundPlay) {
	//	int val = pcheat->GetMoon();
	//	m_xComboMoon->SetCursel(val);
	//}

	// 仲魔狀態
	if (::SendDlgItemMessage(hWnd, IDC_CHK_AUTOLOCK_HPMP, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		pcheat->CheckLife();
	}

	// 物品數量
	if (::SendDlgItemMessage(hWnd, IDC_CHK_AUTOLOCK_ITEM, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		pcheat->CheckItem();
	}

	// 寶石數量
	if (::SendDlgItemMessage(hWnd, IDC_CHK_AUTOLOCK_GEMS, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		pcheat->CheckGem();
	}

	// 魔幣數量
	if (::SendDlgItemMessage(hWnd, IDC_CHK_AUTOLOCK_GOLD, BM_GETCHECK, 0, 0) == BST_CHECKED) {
		pcheat->CheckGold();
	}
}

/**************************************************//**
 * @brief WM_ACTIVE 訊息處理
 * @param [in] wParam 參數
 * @param [in] lParam 參數
 *****************************************************/
void DDSFrame::DoWmActive(WPARAM wParam, LPARAM lParam)
{
	UINT uCode = LOWORD(wParam);
	
	// 當視窗被激活時
	if (uCode == WA_ACTIVE || uCode == WA_CLICKACTIVE) {
		this->LoadMoonStatus();
		this->LoadMemberData();
	}

	//if (m_bBackGroundPlay) {
	//	int val = pcheat->GetMoon();
	//	m_xComboMoon->SetCursel(val);
	//}

	//if (uCode == WA_INACTIVE)
	//	m_bBackGroundPlay = True;
	//else {
	//	m_bBackGroundPlay = False;
	//	this->LoadMemberData();
	//}
}

/**************************************************//**
 * @brief 執行 WM_COMMAND 指定事件
 * @param id	子控制項 ID
 *****************************************************/
void DDSFrame::DoCommandComboSelect(UINT id)
{
	const int ability = IDC_MEMBER_COMBO_POWER;
	const int skills = IDC_MEMBER_COMBO_SKILL;

	DDSCheat* pcx = m_xCheat;
	WsCombo* pcombo;
	int len, val;

	if (pcx == Null) return;

	// 仲魔編號
	if (id == IDC_MONSTER_COMBO_MEMBERNUMBER)
		this->LoadMemberData();

	// 月亮狀態
	else if (id == IDC_COMBO_MOON) {
		pcombo = m_xComboMoon;
		val = pcombo->GetCursel();
		pcx->SetMoon(val);
	}

	// 仲魔等級
	else if (id == IDC_MONSTER_COMBO_LEVEL) {
		pcombo = m_xComboMonsterLevel;
		val = pcombo->GetCursel();
		pcx->SetLevel(val);
	}

	// 技能數量
	else if (id == IDC_MEMBER_COMBO_SKILLAMOUNT) {
		pcombo = m_xComboMonsterSkillAmount;
		val = pcombo->GetCursel();
		pcx->SetSkillAmount(val);
	}

	else {
		// 惡魔能力
		len = sizeof(m_xComboMonsterPower) / sizeof(WsCombo*);
		for (int i = 0; i < len; i++) {
			if (id == (i + ability)) {
				pcombo = m_xComboMonsterPower[i];
				val = pcombo->GetCursel();
				pcx->SetAbility(i, val);
				return;
			}
		}

		// 惡魔技能
		len = sizeof(m_xComboMonsterSkill) / sizeof(WsCombo*);
		for (int i = 0; i < len; i++) {
			if (id == (i + skills)) {
				pcombo = m_xComboMonsterSkill[i];
				val = pcombo->GetCursel();
				pcx->SetSkill(i, val);
				return;
			}
		}
	}
}

/**************************************************//**
 * @brief 讀取月亮狀態
 *****************************************************/
void DDSFrame::LoadMoonStatus()
{
	DDSCheat* pcx = m_xCheat;
	WsCombo* pcombo = m_xComboMoon;
	int val;

	if (pcx == Null || pcombo == Null) return;
	val = pcx->GetMoon();
	pcombo->SetCursel(val);
}

/**************************************************//**
 * @brief 讀取指定仲魔資料
 *****************************************************/
void DDSFrame::LoadMemberData()
{
	DDSCheat* pcx = m_xCheat;
	WsCombo* pcombo = m_xComboMonsterMemberNumber;
	int member = 0;
	int val, len;

	if (pcx == Null)
		return;

	member = pcombo->GetCursel();
	if (!pcx->LoadMemberData(member))
		return;

	// 惡魔編號
	pcombo = m_xComboMonsterCode;
	val = pcx->GetMonsterCode();
	pcombo->SetCursel(val);

	// 惡魔等級
	pcombo = m_xComboMonsterLevel;
	val = pcx->GetLevel();
	pcombo->SetCursel(val);

	// 技能數量
	pcombo = m_xComboMonsterSkillAmount;
	val = pcx->GetSkillAmount();
	pcombo->SetCursel(val);

	// 惡魔技能
	len = sizeof(m_xComboMonsterSkill) / sizeof(WsCombo*);
	for (int i = 0; i < len; i++) {
		pcombo = m_xComboMonsterSkill[i];
		val = pcx->GetSkill(i);
		pcombo->SetCursel(val);
	}

	// 惡魔能力
	len = sizeof(m_xComboMonsterPower) / sizeof(WsCombo*);
	for (int i = 0; i < len; i++) {
		pcombo = m_xComboMonsterPower[i];
		val = pcx->GetAbility(i);
		pcombo->SetCursel(val);
	}

	// 惡魔經驗
	TCHAR szbuf[MAX_PATH];
	val = pcx->GetExp();
	::wsprintf(szbuf, TEXT("%d"), val);
	this->SetChildText(IDC_MONSTER_EDIT_REALEXP, szbuf);

	// 生命值
	int minVal, maxVal;
	minVal = pcx->GetMinHP();
	maxVal = pcx->GetMaxHP();
	::wsprintf(szbuf, TEXT("HP %3d / %3d"), minVal, maxVal);
	this->SetChildText(IDC_MONSTER_EDIT_HP, szbuf);

	// 魔法值
	minVal = pcx->GetMinMP();
	maxVal = pcx->GetMaxMP();
	::wsprintf(szbuf, TEXT("MP %3d / %3d"), minVal, maxVal);
	this->SetChildText(IDC_MONSTER_EDIT_MP, szbuf);
}

/**************************************************//**
 * @brief 保存仲魔資料
 *****************************************************/
void DDSFrame::SaveMemberData()
{
	DDSCheat* pcx = m_xCheat;
	HWND hEdit1 = this->GetChild(IDC_MONSTER_EDIT_REALEXP);
	HWND hEdit2 = this->GetChild(IDC_MONSTER_EXIT_NEXTEXP);
	int val;
	TCHAR szbuf[MAX_PATH];

	if (pcx == Null) return;

	// 惡魔經驗
	::GetWindowText(hEdit1, szbuf, sizeof(szbuf));
	val = ::_ttoi(szbuf);
	::GetWindowText(hEdit2, szbuf, sizeof(szbuf));
	val += ::_ttoi(szbuf);
	pcx->SetExp(val);
	
	if (pcx->SaveMemberData()) {
		val = pcx->GetExp();
		::wsprintf(szbuf, TEXT("%d"), val);
		::SetWindowText(hEdit1, szbuf);
		::SetWindowText(hEdit2, TEXT(""));
	}
}

/**************************************************//**
 * @brief 建立仲魔控制項群組 - 錯誤處理
 *****************************************************/
void DDSFrame::CreateMonsterGroupFailed()
{
	const TCHAR* szTil = TEXT("DDS-III");
	const TCHAR* szMsg = TEXT("DDS-III Initial failed...");
	HWND hWnd = m_hWnd;
	
	::MessageBox(hWnd, szMsg, szTil, MB_OK | MB_ICONERROR);
	::PostMessage(hWnd, WM_CLOSE, 0, 0);
}

/**************************************************//**
 * @brief 建立仲魔控制項群組
 *****************************************************/
void DDSFrame::CreateMonsterGroup()
{
	this->ComboMoon();
	this->ComboMonsterCode();
	this->ComboMonsterMemberNumber();
	this->ComboMonsterLevel();
	this->ComboMonsterPower();
	this->ComboMonsterSkillAmount();
	this->ComboMonsterSkill();
}

/**************************************************//**
 * @brief 建立仲魔控制項 - 惡魔編號
 *****************************************************/
void DDSFrame::ComboMonsterCode()
{
	const int ctrsid = IDC_MONSTER_COMBO_CODE;

	HWND hWnd = m_hWnd;
	WsCombo* pcombo = new (std::nothrow) WsCombo();
	TCHAR szbuf[MAX_PATH];

	// Combo Box 物件建立失敗
	if (pcombo == Null) {
		this->CreateMonsterGroupFailed();
		return;
	}
	m_xComboMonsterCode = pcombo;
	pcombo->CreateFromResource(::GetDlgItem(hWnd, ctrsid), ctrsid);
	pcombo->RemoveAllItem();

	// 建立下拉式清單內容
	for (int i = 0; i < 200; i++) {
		wsprintf(szbuf, TEXT("惡魔編號 %d"), i);
		pcombo->InsertItem(i, szbuf);
	}
	pcombo->SetCursel(0);
	pcombo->Disable();
}

/**************************************************//**
 * @brief 建立仲魔控制項 - 仲魔欄位編號
 *****************************************************/
void DDSFrame::ComboMonsterMemberNumber()
{
	const int ctrsid = IDC_MONSTER_COMBO_MEMBERNUMBER;
	const int maxmembers = DDSIII_MEMBER_MAX_NUMS;

	HWND hWnd = m_hWnd;
	WsCombo* pcombo = new (std::nothrow) WsCombo();
	TCHAR szbuf[MAX_PATH];

	// Combo Box 物件建立失敗
	if (pcombo == Null) {
		this->CreateMonsterGroupFailed();
		return;
	}
	m_xComboMonsterMemberNumber = pcombo;
	pcombo->CreateFromResource(::GetDlgItem(hWnd, ctrsid), ctrsid);
	pcombo->RemoveAllItem();

	// 建立下拉式清單
	pcombo->InsertItem(0, TEXT("主人公"));
	for (int i = 0; i < maxmembers; i++) {
		wsprintf(szbuf, TEXT("仲魔 %d"), i + 1);
		pcombo->InsertItem(-1, szbuf);
	}
	pcombo->SetCursel(0);
}

/**************************************************//**
 * @brief 建立仲魔控制項 - 仲魔等級表
 *****************************************************/
void DDSFrame::ComboMonsterLevel()
{
	const int ctrsid = IDC_MONSTER_COMBO_LEVEL;
	const int maxval = DDSIII_POWER_MAXVAL + 1;
	const TCHAR* szformat = TEXT("LV %d");
	HWND hWnd = m_hWnd;
	WsCombo* pcombo = new (std::nothrow) WsCombo();
	TCHAR szbuf[MAX_PATH];

	// Combo Box 物件建立失敗
	if (pcombo == Null) {
		this->CreateMonsterGroupFailed();
		return;
	}
	m_xComboMonsterLevel = pcombo;
	pcombo->CreateFromResource(::GetDlgItem(hWnd, ctrsid), ctrsid);
	pcombo->RemoveAllItem();

	for (int i = 0; i < maxval; i++) {
		::wsprintf(szbuf, szformat, i);
		pcombo->InsertItem(i, szbuf);
	}
	pcombo->SetCursel(0);
}

/**************************************************//**
 * @brief 建立仲魔控制項 - 仲魔能力表
 *****************************************************/
void DDSFrame::ComboMonsterPower()
{
	const TCHAR* szpow[] = {
		TEXT("力 = %d"),
		TEXT("魔 = %d"),
		TEXT("體 = %d"),
		TEXT("速 = %d"),
		TEXT("運 = %d")
	};

	const int skills = sizeof(m_xComboMonsterPower) / sizeof(WsCombo*);
	const int maxval = DDSIII_POWER_MAXVAL + 1;
	const int ctrsid = IDC_MEMBER_COMBO_POWER;

	WsCombo* pcombo[skills];
	HWND hWnd = m_hWnd;
	TCHAR szbuf[MAX_PATH];

	// 建立仲魔能力 Combo box
	for (int i = 0; i < skills; i++) {
		pcombo[i] = new (std::nothrow) WsCombo();
		if (pcombo[i] == Null) {
			this->CreateMonsterGroupFailed();
			return;
		}
		m_xComboMonsterPower[i] = pcombo[i];
		pcombo[i]->CreateFromResource(::GetDlgItem(hWnd, i + ctrsid), i + ctrsid);
		pcombo[i]->RemoveAllItem();
	}

	// 建立下拉式清單內容
	for (int i = 0; i < skills; i++) {
		for (int k = 0; k < maxval; k++) {
			::wsprintf(szbuf, szpow[i], k);
			pcombo[i]->InsertItem(k, szbuf);
		}
		pcombo[i]->SetCursel(0);
	}
}

/**************************************************//**
 * @brief 建立仲魔控制項 - 仲魔技能數量
 *****************************************************/
void DDSFrame::ComboMonsterSkillAmount()
{
	const int ctrsid = IDC_MEMBER_COMBO_SKILLAMOUNT;
	const int maxval = DDSIII_SKILL_MAXREAL + 1;
	const TCHAR* szformat = TEXT("技能數量 = %d");
	HWND hWnd = m_hWnd;
	WsCombo* pcombo = new (std::nothrow) WsCombo();
	TCHAR szbuf[MAX_PATH];

	// Combo Box 物件建立失敗
	if (pcombo == Null) {
		this->CreateMonsterGroupFailed();
		return;
	}
	m_xComboMonsterSkillAmount = pcombo;
	pcombo->CreateFromResource(::GetDlgItem(hWnd, ctrsid), ctrsid);
	pcombo->RemoveAllItem();

	for (int i = 0; i < maxval; i++) {
		::wsprintf(szbuf, szformat, i);
		pcombo->InsertItem(i, szbuf);
	}
	pcombo->SetCursel(0);
}

/**************************************************//**
 * @brief 建立仲魔控制項 - 仲魔技能表
 *****************************************************/
void DDSFrame::ComboMonsterSkill()
{
	const TCHAR* szName[] = {
		TEXT("空白"),
		TEXT("火起"),
		TEXT("火焰爆擊"),
		TEXT("烈焰咆嘯"),
		TEXT("真.火起"),
		TEXT("真.火焰爆擊"),
		TEXT("真.烈焰咆嘯"),
		TEXT("冰凍"),
		TEXT("冰雪凍氣"),
		TEXT("冰冷極寒"),
		TEXT("真.冰凍"),
		TEXT("真.冰雪凍氣"),
		TEXT("真.冰冷極寒"),
		TEXT("落雷"),
		TEXT("雷電鏈閃"),
		TEXT("狂雷之怒濤"),
		TEXT("真.落雷"),
		TEXT("真.雷電鏈閃"),
		TEXT("真.狂雷之怒濤"),
		TEXT("風來"),
		TEXT("疾風襲"),
		TEXT("風暴之狂嘯"),
		TEXT("真.風來"),
		TEXT("真.疾風襲"),
		TEXT("真.風暴之狂嘯"),
		TEXT("末日光"),
		TEXT("末日衝擊"),
		TEXT("末日終極爆裂"),
		TEXT("破魔"),
		TEXT("強力破魔"),
		TEXT("破魔陣"),
		TEXT("強力破魔陣"),
		TEXT("咒殺"),
		TEXT("強力咒殺"),
		TEXT("咒殺陣"),
		TEXT("強力咒殺陣"),
		TEXT("癒之歌"),
		TEXT("癒之詠唱"),
		TEXT("癒之極樂調"),
		TEXT("全癒之歌"),
		TEXT("全癒之詠唱"),
		TEXT("全癒之極樂調"),
		TEXT("魔力轉移"),
		TEXT("醒腦術"),
		TEXT("大醒腦術"),
		TEXT("魔封解除"),
		TEXT("毒解除"),
		TEXT("麻痺解除"),
		TEXT("石化解除"),
		TEXT("魂歸術"),
		TEXT("痊癒魂歸術"),
		TEXT("棄命魂歸術"),
		TEXT("攻擊下降"),
		TEXT("速度下降"),
		TEXT("防禦下降"),
		TEXT("魔力封印"),
		TEXT("封魔陣"),
		TEXT("上升打消"),
		TEXT("無"),
		TEXT("束縛術"),
		TEXT("催眠術"),
		TEXT("混亂術"),
		TEXT("魅惑術"),
		TEXT("惡魔密語"),
		TEXT("物攻提升"),
		TEXT("速度提升"),
		TEXT("防禦提升"),
		TEXT("魔功提升"),
		TEXT("即死防禦"),
		TEXT("魔法護盾"),
		TEXT("力量護盾"),
		TEXT("分析敵情"),
		TEXT("脫身術"),
		TEXT("驅魔術"),
		TEXT("集魔術"),
		TEXT("淨身術"),
		TEXT("照明術"),
		TEXT("下降打消"),
		TEXT("無"),
		TEXT("瘟疫收割"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("突撃"),
		TEXT("地獄突"),
		TEXT("蠻力暴亂"),
		TEXT("烈風破"),
		TEXT("冥界破"),
		TEXT("焦熱斬"),
		TEXT("劇毒刀"),
		TEXT("絕妙劍"),
		TEXT("八相發破"),
		TEXT("暗夜剣"),
		TEXT("不動剣"),
		TEXT("山嵐"),
		TEXT("死亡震盪"),
		TEXT("斷頭台"),
		TEXT("亂入劍"),
		TEXT("九十九針"),
		TEXT("麻痺針"),
		TEXT("毒針"),
		TEXT("石化針"),
		TEXT("玉碎破"),
		TEXT("特攻"),
		TEXT("啃咬"),
		TEXT("劇毒啃咬"),
		TEXT("魅惑啃咬"),
		TEXT("石化啃咬"),
		TEXT("麻痺啃咬"),
		TEXT("地獄之牙"),
		TEXT("爪擊"),
		TEXT("劇毒爪擊"),
		TEXT("麻痺爪擊"),
		TEXT("鋼鐵之爪"),
		TEXT("神光破"),
		TEXT("無"),
		TEXT("無"),
		TEXT("無"),
		TEXT("死亡遊戲"),
		TEXT("なし"),
		TEXT("ゼロス・ビート"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("破邪的光彈"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("槍林彈雨"),
		TEXT("鬼神樂"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("至高的魔彈"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("自爆"),
		TEXT("邪靈蜂起"),
		TEXT("なし"),
		TEXT("大地震"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("神恩のラッパ"),
		TEXT("魔緑のラッパ"),
		TEXT("螺旋の蛇"),
		TEXT("マグマ・アクシス"),
		TEXT("なし"),
		TEXT("地母の晩餐"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("追い討ち"),
		TEXT("死魔の触手"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("火炎吐息"),
		TEXT("地獄的業火"),
		TEXT("日珥"),
		TEXT("諸神的黃昏"),
		TEXT("冷凍吐息"),
		TEXT("絕對零度"),
		TEXT("放電"),
		TEXT("電擊波動"),
		TEXT("羽振翅"),
		TEXT("龍捲"),
		TEXT("真空刃"),
		TEXT("湿った風"),
		TEXT("裁きの雷火"),
		TEXT("天罰"),
		TEXT("デスタッチ"),
		TEXT("吸魔"),
		TEXT("吸血"),
		TEXT("破魔的雷光"),
		TEXT("明星光"),
		TEXT("無穢之威光"),
		TEXT("ヘルズアイ"),
		TEXT("石化之眼"),
		TEXT("封印之眼"),
		TEXT("邪惡之眼"),
		TEXT("なし"),
		TEXT("バエルの呪い"),
		TEXT("毒瓦斯吐息"),
		TEXT("雄叫"),
		TEXT("霧之吐息"),
		TEXT("挑釁"),
		TEXT("ランダマイザ"),
		TEXT("魔界のしらべ"),
		TEXT("ソルニゲル"),
		TEXT("パララアイ"),
		TEXT("搖籃曲"),
		TEXT("バインドボイス"),
		TEXT("永遠の誘い"),
		TEXT("快音波"),
		TEXT("セクシーアイ"),
		TEXT("肉体の解放"),
		TEXT("パニックボイス"),
		TEXT("大いなる酪酊"),
		TEXT("常世の祈り"),
		TEXT("獣の眼光"),
		TEXT("龍の眼光"),
		TEXT("無尽無辺光"),
		TEXT("召喚"),
		TEXT("代為招喚"),
		TEXT("蓄力"),
		TEXT("逃亡"),
		TEXT("群れ集い"),
		TEXT("闇の遠吠え"),
		TEXT("なし"),
		TEXT("高笑い"),
		TEXT("魔王的號令"),
		TEXT("なし"),
		TEXT("邪霊烏合"),
		TEXT("分身"),
		TEXT("夜のオーロラ"),
		TEXT("シナイの神火"),
		TEXT("霊魂流出"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("無尽光"),
		TEXT("神の悪意"),
		TEXT("地獄への導き"),
		TEXT("死門の流冰"),
		TEXT("蜃気楼"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("原色之舞"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("シナイの神火"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("死縄の葬列"),
		TEXT("ソウルバランス"),
		TEXT("E&I"),
		TEXT("リペリオン"),
		TEXT("トゥーサムタイム"),
		TEXT("挑発（ダンテ）"),
		TEXT("スティンガー"),
		TEXT("ラウンドトリップ"),
		TEXT("ワールウインド"),
		TEXT("ショウタイム"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("ホーリースター"),
		TEXT("血之劇場"),
		TEXT("鮮紅的鬥牛布"),
		TEXT("なし"),
		TEXT("煩悩即菩提"),
		TEXT("瞑想"),
		TEXT("テラーソード"),
		TEXT("ヘルスピン"),
		TEXT("ヘルエギゾースト"),
		TEXT("ヘルパーナー"),
		TEXT("なし"),
		TEXT("女帝のリビドー"),
		TEXT("邪神の蛮声"),
		TEXT("ゴッドアロー"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("一分の活泉"),
		TEXT("ニ分の活泉"),
		TEXT("三分の活泉"),
		TEXT("一分の魔脈"),
		TEXT("ニ分の魔脈"),
		TEXT("三分の魔脈"),
		TEXT("逃走加速"),
		TEXT("なし"),
		TEXT("心眼"),
		TEXT("會心"),
		TEXT("煌天的會心"),
		TEXT("靜天的會心"),
		TEXT("吸収攻撃"),
		TEXT("なし"),
		TEXT("全体攻撃"),
		TEXT("反撃"),
		TEXT("猛反撃"),
		TEXT("デスカウンター"),
		TEXT("なし"),
		TEXT("火炎高揚"),
		TEXT("冰結高揚"),
		TEXT("電撃高揚"),
		TEXT("衝撃高揚"),
		TEXT("耐物理"),
		TEXT("耐火焔"),
		TEXT("耐冰結"),
		TEXT("耐電撃"),
		TEXT("耐衝撃"),
		TEXT("耐破魔"),
		TEXT("耐呪殺"),
		TEXT("耐魔力"),
		TEXT("耐神經"),
		TEXT("耐精神"),
		TEXT("物理無效"),
		TEXT("火炎無效"),
		TEXT("冰結無效"),
		TEXT("電撃無效"),
		TEXT("衝撃無效"),
		TEXT("破魔無效"),
		TEXT("呪殺無效"),
		TEXT("魔力無效"),
		TEXT("神經無效"),
		TEXT("精神無效"),
		TEXT("物理吸収"),
		TEXT("火炎吸収"),
		TEXT("冰結吸収"),
		TEXT("電撃吸収"),
		TEXT("衝撃吸収"),
		TEXT("物理反射"),
		TEXT("火炎反射"),
		TEXT("冰結反射"),
		TEXT("電撃反射"),
		TEXT("衝撃反射"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("食いしばり"),
		TEXT("勝利的息吹"),
		TEXT("勝利のチャクラ"),
		TEXT("勝利の雄叫び"),
		TEXT("息吹の具足"),
		TEXT("チャクラの具足"),
		TEXT("盗人の知恵"),
		TEXT("なし"),
		TEXT("尋寶"),
		TEXT("見習的成長"),
		TEXT("カリスマ"),
		TEXT("なし"),
		TEXT("貫通"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("永不放棄"),
		TEXT("以父之名起誓"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("上前搭話"),
		TEXT("スカウト"),
		TEXT("誘拐"),
		TEXT("誘惑"),
		TEXT("洗腦"),
		TEXT("なし"),
		TEXT("靜天之契"),
		TEXT("口説き落とし"),
		TEXT("ヘッドハント"),
		TEXT("英雄狩"),
		TEXT("悪戯"),
		TEXT("死の契約"),
		TEXT("撒嬌耍賴"),
		TEXT("物乞い"),
		TEXT("恐喝"),
		TEXT("ストーンハント"),
		TEXT("物々交換"),
		TEXT("借金"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("砍價"),
		TEXT("執り成し"),
		TEXT("挽留"),
		TEXT("同族之誼"),
		TEXT("說服"),
		TEXT("脅し"),
		TEXT("わがまま"),
		TEXT("なし"),
		TEXT("なし"),
		TEXT("乙女的仲裁"),
		TEXT("酒の宴"),
		TEXT("ゴマすり"),
		TEXT("ジャイヴトーク"),
	};

	const TCHAR* szformat = TEXT("%04X - %s");
	const int skills = sizeof(m_xComboMonsterSkill) / sizeof(WsCombo*);
	const int maxval = sizeof(szName) / sizeof(TCHAR*);
	const int ctrsid = IDC_MEMBER_COMBO_SKILL;

	WsCombo* pcombo[skills];
	HWND hWnd = m_hWnd;
	TCHAR szbuf[MAX_PATH];

	// 建立技能 Combo box
	for (int i = 0; i < skills; i++) {
		pcombo[i] = new (std::nothrow) WsCombo();
		if (pcombo[i] == Null) {
			this->CreateMonsterGroupFailed();
			return;
		}
		m_xComboMonsterSkill[i] = pcombo[i];
		pcombo[i]->CreateFromResource(::GetDlgItem(hWnd, i + ctrsid), i + ctrsid);
		pcombo[i]->RemoveAllItem();
	}

	for (int i = 0; i < skills; i++) {
		for (int k = 0; k < maxval; k++) {
			::wsprintf(szbuf, szformat, k, szName[k]);
			pcombo[i]->InsertItem(k, szbuf);
		}
		pcombo[i]->SetCursel(0);
	}
}

/**************************************************//**
 * @brief 建立月亮狀態 Combo box
 *****************************************************/
void DDSFrame::ComboMoon()
{
	const int ctrsid = IDC_COMBO_MOON;
	const int maxval = 16;
	const int half = 8;
	const TCHAR* szformat = TEXT("%2d : %s");
	const TCHAR* szmoonNew = TEXT("新月");
	const TCHAR* szmoonHaf = TEXT("上弦月");
	const TCHAR* szmoonFul = TEXT("滿月");
	const TCHAR* szmoonDaf = TEXT("下弦月");

	HWND hWnd = m_hWnd;
	WsCombo* pcombo = new (std::nothrow) WsCombo();
	TCHAR szbuf[MAX_PATH];

	// Combo Box 物件建立失敗
	if (pcombo == Null) {
		this->CreateMonsterGroupFailed();
		return;
	}
	m_xComboMoon = pcombo;
	pcombo->CreateFromResource(::GetDlgItem(hWnd, ctrsid), ctrsid);
	pcombo->RemoveAllItem();

	for (int i = 0; i < maxval; i++) {
		if (i == 0)
			::wsprintf(szbuf, szformat, i, szmoonNew);
		else if (i > 0 && i < 8)
			::wsprintf(szbuf, szformat, i, szmoonHaf);
		else if (i == 8)
			::wsprintf(szbuf, szformat, i, szmoonFul);
		else
			::wsprintf(szbuf, szformat, i, szmoonDaf);
		pcombo->InsertItem(i, szbuf);
	}
	pcombo->SetCursel(0);
}

/**************************************************//**
 * @brief 建立 Cheat Object
 *****************************************************/
void DDSFrame::CreateCheatObject()
{
	DDSCheat* pcheat = new (std::nothrow) DDSCheat();
	
	SAFE_DELETE(m_xCheat);
	if (pcheat == Null) {
		this->CreateMonsterGroupFailed();
		return;
	}
	m_xCheat = pcheat;
}

/**************************************************//**
 * @brief 釋放、摧毀所有子控制項
 *****************************************************/
void DDSFrame::Release()
{
	int size = sizeof(m_xComboMonsterSkill) / sizeof(WsCombo*);
	this->KillTimer();

	for (int i = 0; i < size; i++) {
		SAFE_DELETE(m_xComboMonsterSkill[i]);
	}

	size = sizeof(m_xComboMonsterPower) / sizeof(WsCombo*);
	for (int i = 0; i < size; i++) {
		SAFE_DELETE(m_xComboMonsterPower[i]);
	}

	SAFE_DELETE(m_xComboMoon);
	SAFE_DELETE(m_xComboMonsterCode);
	SAFE_DELETE(m_xComboMonsterLevel);
	SAFE_DELETE(m_xComboMonsterSkillAmount);
	SAFE_DELETE(m_xComboMonsterMemberNumber);
	SAFE_DELETE(m_xCheat);
}
