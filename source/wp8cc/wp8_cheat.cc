/**************************************************************************//**
 * @file	wp8_cheat.cc
 * @brief	WP8cc 程序掛勾類別, 成員函式
 * @author	Swang
 * @date	2018-04-05
 * @date	2018-04-11
 * @note	none
 *****************************************************************************/
#include "wp8cc\wp8_cheat.hh"

/**************************************************//**
 * @brief	搜尋指定目標程序
 * @return	@c Bool
 *			- 若出現指定目標或目標已存在則傳回 TRUE
 *			- 若目標不存在或發生錯誤，則傳回 FALSE
 *****************************************************/
Bool WP8Cheat::WatchingYou()
{
	const	TCHAR* pexe = TEXT("WP8_2018.exe");
	const	Bool err = FALSE;
	const	Bool eok = TRUE;
	HANDLE	hProcess = m_hProcess;
	DWORD	idSave = m_idProcess;
	DWORD	pid = this->SearchProcess(pexe);

	// 已存在與目標程序掛勾
	if (hProcess != NULL) { if (pid == idSave) return eok; }

	// 尚未與目標掛勾
	this->ReleaseHook();
	// 搜尋指定目標程序，若目標程序已存在系統，則進行開啟目標程序進行掛勾
	if (pid != 0) {
		if ((hProcess = this->OpenProcess(pid)) != NULL) {
			m_hProcess = hProcess;
			m_idProcess = pid;
			return eok;
		}
	}
	return err;
}

/**************************************************//**
 * @brief	設定遊戲版本
 *****************************************************/
void WP8Cheat::SetVersion(Int32u ver)
{
	switch (ver) {
	case WP8VER_501:
		m_uVersion = WP8VER_501;
		break;
	case WP8VER_502:
		m_uVersion = WP8VER_502;
		break;
	default:
		m_uVersion = WP8VER_502;
	}
	this->InitDataAddress();
}

/**************************************************//**
 * @brief	取得騎師名字
 * @param	[in] index	索引
 * @return	@c LPCTSTR
 *			- 函式運作成功傳回: 騎師名字字串位址
 *			- 函式運作失敗傳回: NULL
 *****************************************************/
LPCTSTR WP8Cheat::GetJockeyName(int index)
{
	static const TCHAR* text[] = {
		TEXT("森安重勝"),
		TEXT("津田昭"),
		TEXT("武邦彦"),
		TEXT("中西武信"),
		TEXT("加賀武見"),
		TEXT("徳吉一己"),
		TEXT("高橋隆"),
		TEXT("川端義雄"),
		TEXT("増沢末夫"),
		TEXT("中島啓之"),
		TEXT("佐山優"),
		TEXT("久保敏文"),
		TEXT("横山富雄"),
		TEXT("大崎昭一"),
		TEXT("鹿戸明"),
		TEXT("太宰義人"),
		TEXT("中野渡清一"),
		TEXT("白石一典"),
		TEXT("野村彰彦"),
		TEXT("武田悟"),
		TEXT("吉永正人"),
		TEXT("伊藤栄"),
		TEXT("飯田明弘"),
		TEXT("楠孝志"),
		TEXT("郷原洋行"),
		TEXT("高山裕"),
		TEXT("柴田政見"),
		TEXT("樋口弘"),
		TEXT("関口健太郎"),
		TEXT("安田富男"),
		TEXT("目野哲也"),
		TEXT("福島信晴"),
		TEXT("嶋田功"),
		TEXT("岡部幸雄"),
		TEXT("岩元市三"),
		TEXT("目黒正徳"),
		TEXT("菅原泰夫"),
		TEXT("菅野昭夫"),
		TEXT("田島良保"),
		TEXT("清水英次"),
		TEXT("田子冬樹"),
		TEXT("田村正光"),
		TEXT("小谷内秀夫"),
		TEXT("外枦保重秋"),
		TEXT("小島太"),
		TEXT("赤羽秀男"),
		TEXT("西橋豊治"),
		TEXT("吉永良人"),
		TEXT("嶋田潤"),
		TEXT("蓑田早人"),
		TEXT("山内研二"),
		TEXT("久保一秋"),
		TEXT("伊藤正徳"),
		TEXT("吉沢宗一"),
		TEXT("崎山博樹"),
		TEXT("松田幸春"),
		TEXT("柴田政人"),
		TEXT("坂井千明"),
		TEXT("西浦勝一"),
		TEXT("上野清章"),
		TEXT("柴崎勇"),
		TEXT("小迫次男"),
		TEXT("鍛冶谷誠"),
		TEXT("内田国男"),
		TEXT("高橋司"),
		TEXT("東信二"),
		TEXT("田所秀孝"),
		TEXT("鎌田光也"),
		TEXT("中島敏文"),
		TEXT("蛯沢誠治"),
		TEXT("小島貞博"),
		TEXT("秋山忠一"),
		TEXT("田中清隆"),
		TEXT("山田定男"),
		TEXT("柴田光陽"),
		TEXT("出口隆義"),
		TEXT("堀井雅広"),
		TEXT("佐藤等"),
		TEXT("安田隆行"),
		TEXT("原田雄二"),
		TEXT("蛯名信広"),
		TEXT("菅野澄男"),
		TEXT("池添兼雄"),
		TEXT("田島信行"),
		TEXT("中野栄治"),
		TEXT("花松進"),
		TEXT("南井克巳"),
		TEXT("鈴木三好"),
		TEXT("高市圭二"),
		TEXT("石神富士雄"),
		TEXT("久保田敏彦"),
		TEXT("北村卓士"),
		TEXT("根本康広"),
		TEXT("竹原啓二"),
		TEXT("加用正"),
		TEXT("猿橋重利"),
		TEXT("加藤和宏"),
		TEXT("大塚栄三郎"),
		TEXT("松永昌博"),
		TEXT("桜井誠二"),
		TEXT("的場均"),
		TEXT("赤城賢司"),
		TEXT("音無秀孝"),
		TEXT("東田幸男"),
		TEXT("杉浦宏昭"),
		TEXT("国兼正浩"),
		TEXT("河内洋"),
		TEXT("田原成貴"),
		TEXT("田中剛"),
		TEXT("今井規和"),
		TEXT("村本善之"),
		TEXT("丸山勝秀"),
		TEXT("大西直宏"),
		TEXT("柏崎正次"),
		TEXT("佐々木晶三"),
		TEXT("栗田伸一"),
		TEXT("田面木博公"),
		TEXT("菅原隆明"),
		TEXT("安藤賢一"),
		TEXT("小屋敷昭"),
		TEXT("鹿戸雄一"),
		TEXT("原昌久"),
		TEXT("本田勝"),
		TEXT("岡冨俊一"),
		TEXT("坂本勝美"),
		TEXT("細川英二"),
		TEXT("宮徹"),
		TEXT("菅谷正巳"),
		TEXT("木幡初広"),
		TEXT("三浦堅治"),
		TEXT("中竹和也"),
		TEXT("土肥幸広"),
		TEXT("中館英二"),
		TEXT("鈴木寿"),
		TEXT("松本達也"),
		TEXT("増井裕"),
		TEXT("横山賀一"),
		TEXT("古川寛和"),
		TEXT("須貝尚介"),
		TEXT("石橋守"),
		TEXT("武藤善則"),
		TEXT("谷中公一"),
		TEXT("山田和広"),
		TEXT("田島裕和"),
		TEXT("柴田善臣"),
		TEXT("岩戸孝樹"),
		TEXT("松永幹夫"),
		TEXT("塩村克己"),
		TEXT("横山典弘"),
		TEXT("瀬古正明"),
		TEXT("熊沢重文"),
		TEXT("武豊"),
		TEXT("蛯名正義"),
		TEXT("伊藤暢康"),
		TEXT("芹沢純一"),
		TEXT("千田輝彦"),
		TEXT("菊沢隆徳"),
		TEXT("藤原英幸"),
		TEXT("岸滋彦"),
		TEXT("岡潤一郎"),
		TEXT("横田雅博"),
		TEXT("高橋明"),
		TEXT("内田浩一"),
		TEXT("山田泰誠"),
		TEXT("田中勝春"),
		TEXT("五十嵐久"),
		TEXT("佐藤哲三"),
		TEXT("小池隆生"),
		TEXT("小野次郎"),
		TEXT("玉ノ井健志"),
		TEXT("角田晃一"),
		TEXT("小原義之"),
		TEXT("江田照男"),
		TEXT("沢昭典"),
		TEXT("四位洋文"),
		TEXT("牧田和弥"),
		TEXT("土谷智紀"),
		TEXT("浜野谷憲尚"),
		TEXT("安田康彦"),
		TEXT("村山明"),
		TEXT("橋本広喜"),
		TEXT("水野貴広"),
		TEXT("藤田伸二"),
		TEXT("河北通"),
		TEXT("郷原洋司"),
		TEXT("徳吉孝士"),
		TEXT("菊沢隆仁"),
		TEXT("上村洋行"),
		TEXT("後藤浩輝"),
		TEXT("横山義行"),
		TEXT("渡辺薫彦"),
		TEXT("橋本美純"),
		TEXT("吉永護"),
		TEXT("亀山泰延"),
		TEXT("幸英明"),
		TEXT("高橋康之"),
		TEXT("小林淳一"),
		TEXT("嶋田高宏"),
		TEXT("野元昭嘉"),
		TEXT("藤井正輝"),
		TEXT("伊藤直人"),
		TEXT("田口大二郎"),
		TEXT("高橋亮"),
		TEXT("小林徹弥"),
		TEXT("宗像徹"),
		TEXT("岩部純二"),
		TEXT("和田竜二"),
		TEXT("飯田祐史"),
		TEXT("吉田豊"),
		TEXT("小林久晃"),
		TEXT("福永祐一"),
		TEXT("川合達彦"),
		TEXT("高山太郎"),
		TEXT("矢原洋一"),
		TEXT("秋山真一郎"),
		TEXT("金折知則"),
		TEXT("青木芳之"),
		TEXT("山本康志"),
		TEXT("武幸四郎"),
		TEXT("常石勝義"),
		TEXT("柴田大知"),
		TEXT("田村真来"),
		TEXT("押田純子"),
		TEXT("細江純子"),
		TEXT("増沢由貴子"),
		TEXT("柴田未崎"),
		TEXT("池添謙一"),
		TEXT("松田大作"),
		TEXT("勝浦正樹"),
		TEXT("武士沢友治"),
		TEXT("西原玲奈"),
		TEXT("太宰啓介"),
		TEXT("村田一誠"),
		TEXT("中谷雄太"),
		TEXT("川島信二"),
		TEXT("酒井学"),
		TEXT("野崎孝仁"),
		TEXT("穂苅寿彦"),
		TEXT("柴原央明"),
		TEXT("竹之下智昭"),
		TEXT("北村宏司"),
		TEXT("梶晃啓"),
		TEXT("岩崎祐己"),
		TEXT("高田潤"),
		TEXT("二本柳壮"),
		TEXT("鈴来直人"),
		TEXT("南井大志"),
		TEXT("武英智"),
		TEXT("嘉藤貴行"),
		TEXT("田嶋翔"),
		TEXT("佐久間寛志"),
		TEXT("畑端省吾"),
		TEXT("石神深一"),
		TEXT("大庭和弥"),
		TEXT("高井彰大"),
		TEXT("小坂忠士"),
		TEXT("五十嵐雄祐"),
		TEXT("井西泰政"),
		TEXT("北村浩平"),
		TEXT("田中亮"),
		TEXT("田辺裕信"),
		TEXT("石橋脩"),
		TEXT("安藤勝巳"),
		TEXT("黒岩悠"),
		TEXT("加藤士津八"),
		TEXT("松岡正海"),
		TEXT("上野翔"),
		TEXT("難波剛健"),
		TEXT("吉田隼人"),
		TEXT("津村明秀"),
		TEXT("赤木高太郎"),
		TEXT("長谷川浩大"),
		TEXT("大野拓弥"),
		TEXT("小島太一"),
		TEXT("小牧太"),
		TEXT("藤岡祐介"),
		TEXT("柴山雄一"),
		TEXT("佐藤聖也（塚田祥雄）"),
		TEXT("鮫島良太"),
		TEXT("川田将雅"),
		TEXT("田中博康"),
		TEXT("的場勇人"),
		TEXT("北村友一"),
		TEXT("中村将之"),
		TEXT("宮崎北斗"),
		TEXT("安藤光彰"),
		TEXT("田村太雅"),
		TEXT("浜中俊"),
		TEXT("伊藤工真"),
		TEXT("内田博幸"),
		TEXT("岩田康誠"),
		TEXT("田中健"),
		TEXT("三浦皇成"),
		TEXT("国分優作"),
		TEXT("藤岡康太"),
		TEXT("大下智"),
		TEXT("丸山元気"),
		TEXT("小野寺祐太"),
		TEXT("荻野琢真"),
		TEXT("国分恭介"),
		TEXT("菅原隆一"),
		TEXT("西村太一"),
		TEXT("松山弘平"),
		TEXT("水口優也"),
		TEXT("平野優"),
		TEXT("杉原誠人"),
		TEXT("高倉稜"),
		TEXT("川須栄彦"),
		TEXT("横山和生"),
		TEXT("高嶋活士"),
		TEXT("藤懸貴志"),
		TEXT("森一馬"),
		TEXT("嶋田純次"),
		TEXT("長岡禎仁"),
		TEXT("花田大昂"),
		TEXT("菱田裕二"),
		TEXT("原田和真"),
		TEXT("山崎亮誠"),
		TEXT("中井裕二"),
		TEXT("原田敬伍"),
		TEXT("戸崎啓太"),
		TEXT("伴啓太"),
		TEXT("城戸義政"),
		TEXT("岩崎翼"),
		TEXT("木幡初也"),
		TEXT("石川裕紀人"),
		TEXT("小崎綾也"),
		TEXT("松若風馬"),
		TEXT("井上敏樹"),
		TEXT("野中悠太郎"),
		TEXT("ミルコデムーロ"),
		TEXT("クリストフルメール"),
		TEXT("藤田奈七子"),
		TEXT("木幡巧也"),
		TEXT("坂井瑠星"),
		TEXT("荻野極(森裕太朗)"),
		TEXT("嵐三太夫"),
		TEXT("細谷祐一郎"),
		TEXT("竹川雄一"),
		TEXT("森下昌恵"),
		TEXT("浅野大樹"),
		TEXT("宮本義和"),
		TEXT("久留米麗菜"),
		TEXT("伊波健"),
		TEXT("流蒼次郎"),
		TEXT("鶴野亮子"),
		TEXT("武田諭吉"),
		TEXT("遠藤俊幸"),
		TEXT("小野あかね"),
		TEXT("結城新吾"),
		TEXT("沢田栄輔"),
		TEXT("渡辺初"),
		TEXT("高野倉健哉"),
		TEXT("内山田安宏"),
		TEXT("星拓也"),
		TEXT("千葉大泉"),
		TEXT("大津鉄兵"),
		TEXT("楢崎安見"),
		TEXT("大橋広文"),
		TEXT("岬士郎"),
		TEXT("西村星香"),
		TEXT("阿部昇太郎"),
		TEXT("緒方冬弥"),
		TEXT("森下和"),
		TEXT("緑和馬"),
		TEXT("日向隼人"),
		TEXT("星川右京"),
		TEXT("海野響"),
		TEXT("木戸飛鳥"),
		TEXT("杉本楓"),
		TEXT("多崎烈"),
		TEXT("橘みゆき"),
		TEXT("三条レオ"),
		TEXT("獅子門輝貴"),
		TEXT("三条メグ"),
		TEXT("東山銀河"),
		TEXT("梅田卓哉"),
		TEXT("来原義彦"),
		TEXT("内川征輝"),
		TEXT("二宮佑馬"),
		TEXT("湯川雪夫"),
		TEXT("郷村慎太"),
		TEXT("大場智樹"),
		TEXT("作出精一"),
		TEXT("山下正広"),
		TEXT("木境甚吉"),
		TEXT("仲根功績"),
		TEXT("芝原陽光"),
		TEXT("熱川甚太"),
		TEXT("木口章二"),
		TEXT("清川彦昭"),
		TEXT("上納新吉"),
		TEXT("篠原準一"),
		TEXT("笹森将生"),
		TEXT("津理地影"),
		TEXT("三平建一"),
		TEXT("滝橋知久"),
		TEXT("平泉修平"),
		TEXT("菊地啓汰"),
		TEXT("柄山蒋良"),
		TEXT("高根一弥"),
		TEXT("丹下祐介"),
		TEXT("横出利充"),
		TEXT("宮出広"),
		TEXT("池下政幸"),
		TEXT("都曲広一"),
		TEXT("成畑浩"),
		TEXT("寺島哲平"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("--保留--"),
		TEXT("アルドロード"),
		TEXT("ウィルス"),
		TEXT("ヴェラスコス"),
		TEXT("エバーロ"),
		TEXT("カグラス"),
		TEXT("カストロ"),
		TEXT("サミー"),
		TEXT("サントン"),
		TEXT("スティーン"),
		TEXT("スミム"),
		TEXT("セラーゾ"),
		TEXT("ソノ"),
		TEXT("ソリシ"),
		TEXT("チャベサ"),
		TEXT("デウ"),
		TEXT("デザート"),
		TEXT("デラフーシ"),
		TEXT("ナカサニ"),
		TEXT("レスピノーゼ"),
		TEXT("パトゥン"),
		TEXT("ピネ"),
		TEXT("ピンケイ"),
		TEXT("プラダ"),
		TEXT("ブラット"),
		TEXT("ブリグハン"),
		TEXT("ベイルー"),
		TEXT("マーチス"),
		TEXT("マッキャノン"),
		TEXT("シューメイク"),
		TEXT("クローネ"),
		TEXT("フォルグル"),
		TEXT("ラペス"),
		TEXT("ブリッジ"),
		TEXT("ガイドリー"),
		TEXT("コステロ"),
		TEXT("エリオッタ"),
		TEXT("ダムサミー"),
		TEXT("ライド"),
		TEXT("バランスエル"),
		TEXT("フロアー"),
		TEXT("リンドラー"),
		TEXT("メイブル"),
		TEXT("ベーブ"),
		TEXT("アリメイダ"),
		TEXT("ロレンズ"),
		TEXT("クエン"),
		TEXT("エデラー"),
		TEXT("オランダ"),
		TEXT("スインボーン"),
		TEXT("カーサン"),
		TEXT("デットルー"),
		TEXT("ピボット"),
		TEXT("フォロン"),
		TEXT("コーサン"),
		TEXT("ロバート"),
		TEXT("ピュージズ"),
		TEXT("ベレス"),
		TEXT("スピーサー"),
		TEXT("ムンノ"),
		TEXT("ドーリー"),
		TEXT("オドーティー"),
		TEXT("ケネーン"),
		TEXT("クリーン"),
		TEXT("サムレン"),
		TEXT("シャンハン"),
		TEXT("ビーコン"),
		TEXT("マルタ"),
		TEXT("オファーマン"),
		TEXT("モニング"),
		TEXT("リーズ"),
		TEXT("メリー"),
		TEXT("オシェイ"),
		TEXT("マクドナル"),
		TEXT("ジャーク"),
		TEXT("ファリング"),
		TEXT("アスムッソン"),
		TEXT("バスキエ"),
		TEXT("サンモルト"),
		TEXT("ビレ"),
		TEXT("ルメージュ"),
		TEXT("ペリア"),
		TEXT("ムーラ"),
		TEXT("メンテサボル"),
		TEXT("ジャルヌ"),
		TEXT("テュルエ"),
		TEXT("スムヨン"),
		TEXT("ヘッダ"),
		TEXT("ゾフ"),
		TEXT("サボイ"),
		TEXT("ベリーニ"),
		TEXT("サイマー"),
		TEXT("ゼローディー"),
		TEXT("ウェルキル"),
		TEXT("スン"),
		TEXT("プレッシー"),
		TEXT("ウッドワンズ"),
		TEXT("イニス"),
		TEXT("ケイモティー"),
		TEXT("ラム"),
		TEXT("チャプス"),
		TEXT("オタリバン"),
		TEXT("オリバー"),
		TEXT("ハーノット"),
		TEXT("キャシド"),
		TEXT("チェ"),
		TEXT("パリス"),
		TEXT("ビートマン"),
		TEXT("ホーリュ"),
		TEXT("マーシャヌ"),
		TEXT("ヨーグ"),
		TEXT("ホワイ"),
		TEXT("デイ"),
		TEXT("マービン"),
		TEXT("コーディー"),
		TEXT("サンマルト"),
		TEXT("プラット"),
		TEXT("ハーディン"),
		TEXT("モーセ"),
		TEXT("ラグリ"),
		TEXT("ドーラーズ"),
		TEXT("五十畑春喜"),
		TEXT("斉高征之"),
		TEXT("井出利彦"),
		TEXT("門川秀雄"),
		TEXT("国枝充"),
		TEXT("左々岡一矢"),
		TEXT("増本孝弘"),
		TEXT("宮前光男"),
		TEXT("須ヶ原勇"),
		TEXT("小森敏人"),
		TEXT("村富勉"),
		TEXT("大嶋久司"),
		TEXT("大竹清三"),
		TEXT("鈴本久芳"),
		TEXT("内出隆夫"),
		TEXT("川口竜二"),
		TEXT("平田紀夫"),
		TEXT("水尾武志"),
		TEXT("丸川候弘"),
		TEXT("御田元良文"),
		TEXT("的矢節雄"),
		TEXT("宮村昌明"),
		TEXT("滝橋二朗"),
		TEXT("早手修太"),
		TEXT("荒木勝久"),
		TEXT("磯川恒夫"),
		TEXT("岡武盛靖"),
		TEXT("左々岡忠男"),
		TEXT("佐々岡洋輔"),
		TEXT("藤沢和輝"),
		TEXT("堀河千秋"),
		TEXT("右海清一"),
		TEXT("針田教"),
		TEXT("岩崎尚之"),
		TEXT("桑嶋晴天"),
		TEXT("秋山稔"),
		TEXT("佐堂健"),
		TEXT("本木健太"),
		TEXT("小山内仁"),
		TEXT("三澤省治"),
		TEXT("本田光昭"),
		TEXT("管野高哉"),
		TEXT("森上弘義"),
		TEXT("左々岡剛史"),
		TEXT("金城昌彦"),
		TEXT("野村武臣"),
		TEXT("谷崎誠三"),
		TEXT("谷崎尋士"),
		TEXT("川村章二"),
		TEXT("東山君吉"),
		TEXT("居上孝文"),
		TEXT("坂田重房"),
		TEXT("佐堂友宏"),
		TEXT("濱田茂彦"),
		TEXT("岡武雅"),
		TEXT("押畑実"),
		TEXT("阿武幸也"),
		TEXT("戸田尚弥"),
		TEXT("原田次郎"),
		TEXT("丸山高虎"),
		TEXT("蔵菅孝二朗"),
		TEXT("若江信"),
		TEXT("向谷滝"),
		TEXT("渡瀬翔"),
		TEXT("小枝幹生"),
		TEXT("津川房夫"),
		TEXT("渡良瀬庄司"),
		TEXT("仲田勉"),
		TEXT("播磨澄人"),
		TEXT("上原修"),
		TEXT("中声彰光"),
		TEXT("鷹狩浩史"),
		TEXT("南野真志"),
		TEXT("鮫洲夏也"),
		TEXT("川口勇"),
		TEXT("押畑順一"),
		TEXT("万能君"),
		TEXT("錯誤")
	};
	const int len = sizeof(text) / sizeof(TCHAR*);

	if (index >= 0 && index < len) {
		return text[index];
	}
	return NULL;
}

/**************************************************//**
 * @brief	取得遊戲時間
 * @see		SaWP8DATE
 *****************************************************/
void WP8Cheat::LoadGameDate()
{
	const Int32u err = -1;
	const Int32u month[] = { 4, 4, 5, 4, 5, 4, 4, 5, 4, 5, 4, 4 };
	const size_t month_length = sizeof(month) / sizeof(Int32u);	
	Int32u m, t, temp;

	// 時間資料讀取錯誤
	if ((t = this->LoadGameCurrentWeekNumber()) == err) {
		m_Date.WeekNumber = err;
		m_Date.Month = err;
		m_Date.Week = err;
		return;
	}

	// 取得遊戲中月份、週份
	temp = 0;
	for (m = 0; m < month_length; m++) {
		temp += month[m];
		if (temp >= t) { temp -= month[m]; break; }
	}

	m_Date.WeekNumber = t;
	m_Date.Week = t - temp + 1;	// zero-base so must plus 1
	m_Date.Month = m + 1;		// zero-base so must plus 1
}

/**************************************************//**
 * @brief	取得比賽資訊
 * @see		SaWP8DATE
 *****************************************************/
void WP8Cheat::LoadRacing()
{
	// 取得速度資料
	IntQu	addr = m_Racing.SpeedAddr;
	int		size = sizeof(m_Racing.SpeedData);
	void*	data = (void*)m_Racing.SpeedData;
	if (this->ReadMemory((LPVOID)addr, data, size) != size) {
		::memset(data, 0, size);
	}

	// 取得戰術
	addr = m_Racing.TacticAddr;
	size = sizeof(m_Racing.TacticData);
	data = (void*)m_Racing.TacticData;
	if (this->ReadMemory((LPVOID)addr, data, size) != size) {
		::memset(data, 0, size);
	}

	// 取得斤量
	addr = m_Racing.WeightAddr;
	size = sizeof(m_Racing.WeightData);
	data = (void*)m_Racing.WeightData;
	if (this->ReadMemory((LPVOID)addr, data, size) != size) {
		::memset(data, 0, size);
	}

	// 取得騎手
	addr = m_Racing.JockeyAddr;
	size = sizeof(m_Racing.JockeyData);
	data = (void*)m_Racing.JockeyData;
	if (this->ReadMemory((LPVOID)addr, data, size) != size) {
		::memset(data, 0, size);
	}
}

/**************************************************//**
 * @brief	取得賽道
 * @return	@c LPCTSTR	競賽速度字串
 *			- 若運作成功傳回: 當前賽道字串
 *			- 若運作失敗傳回: NULL
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
LPCTSTR WP8Cheat::GetRacingTrackText()
{
	static TCHAR text[STRING_TINY];
	const TCHAR* fmt = TEXT("%d");

	int result = (int)m_Racing.Count;
	if (result >= 0) {
		::wsprintf(text, fmt, result);
		return text;
	}
	return NULL;
}

/**************************************************//**
 * @brief	取得比賽速度
 * @param	[in] index	賽道索引
 * @return	@c LPCTSTR	競賽速度字串
 *			- 若運作成功傳回: 當前速度字串
 *			- 若運作失敗傳回: NULL
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
LPCTSTR WP8Cheat::GetRacingSpeedText(int index)
{
	static TCHAR text[STRING_TINY];
	const TCHAR* fmt = TEXT("%d");

	int result = (int)this->GetRacingSpeed(index);
	if (result >= 0) {
		::wsprintf(text, fmt, result);
		return text;
	}
	return NULL;
}

/**************************************************//**
 * @brief	取得比賽戰術
 * @param	[in] index	賽道索引
 * @return	@c Int32u	戰術
 *			- 若運作成功傳回: 當前戰術字串
 *			- 若運作失敗傳回: NULL
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
LPCTSTR WP8Cheat::GetRacingTacticText(int index)
{
	static const TCHAR* text[] = {
		TEXT("大逃"),
		TEXT("逃"),
		TEXT("先"),
		TEXT("差"),
		TEXT("追"),
		TEXT("自動"),
		TEXT("錯誤")
	};
	const int len = sizeof(text) / sizeof(TCHAR*);
	int result = (int)this->GetRacingTactic(index);

	if (result >= 0 && result < len) return text[result];
	return NULL;
}

/**************************************************//**
 * @brief	取得比賽騎手斤量
 * @param	[in] index	賽道索引
 * @return	@c Int32u	斤量字串
 *			- 若運作成功傳回: 當前騎手斤量
 *			- 若運作失敗傳回: NULL
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
LPCTSTR WP8Cheat::GetRacingWeightText(int index)
{
	static TCHAR text[STRING_TINY];
	const TCHAR* fmt = TEXT("%d");

	Int32u resual = this->GetRacingWeight(index);
	if (resual >= 0) {
		::wsprintf(text, fmt, resual);
		return text;
	}
	return NULL;
}

/**************************************************//**
 * @brief	取得比賽騎乘騎手
 * @param	[in] index	賽道索引
 * @return	@c Int32u	騎乘騎手名字
 *			- 若運作成功傳回: 當前騎乘騎手名字
 *			- 若運作失敗傳回: NULL
 * @note	必須先調用 LoadRacing 成員
 * @see		SaWP8RACING 結構說明
 *****************************************************/
LPCTSTR WP8Cheat::GetRacingJockeyText(int index)
{
	int result = (int)this->GetRacingJockey(index);
	return this->GetJockeyName(result);
}

/**************************************************//**
 * @brief	取得馬匹資料
 * @param	[in] addr	馬類型，基底位址
 * @param	[in] seek	馬類型，下一筆資料位移
 * @param	[in] count	馬類型，數量
 * @param	[in] data	馬類型，存放讀取資料起始位址
 * @param	[in] len	馬類型，每筆存放資料長度 (in byte)
 * @return	@c Bool
 *			- 運作成功傳回: TRUE
 *			- 運作失敗傳回: FALSE
 *****************************************************/
Bool WP8Cheat::LoadHorseData(IntQu addr, IntQu seek, int count, void* data, int len)
{
	Int8u* desc = (Int8u*)data;

	if (addr == 0 || data == NULL)
		return FALSE;

	// 讀取資料
	for (int i = 0; i < count; i++) {
		if (this->ReadMemory((LPCVOID)addr, (LPVOID)desc, len) != len) {
			::memset(data, 0, len);
			return FALSE;
		}
		addr += seek;
		desc += len;
	}
	return TRUE;
}

/**************************************************//**
 * @brief	讀取遊戲當前週數
 * @return	@c Int32u
 *			- 運作成功傳回: 當前週數
 *			- 運作失敗傳回: -1
 * @see		SaWP8DATE
 *****************************************************/
Int32u WP8Cheat::LoadGameCurrentWeekNumber()
{
	const Int32u err = -1;
	IntQu	addr = m_Date.Addr;
	size_t	len = (size_t)m_Date.DataLength;
	Int32u	date;

	// 數據不正確
	if (addr == 0 || len == 0)
		return err;

	// 讀取遊戲時間
	date = 0;
	if (this->ReadMemory((LPVOID)addr, &date, len) == len) {
		Int32u w, m, t;
		w = (date >> 4) & 0x000F;	// HIBITS
		m = date & 0x000F;			// LOBITS
		t = m * 4 + w;

		// 比賽中?
		t = (w > 7) ? t - 4 : t;
		t = (w > 3) ? t - 4 : t;
		return t;
	}
	return err;
}

/**************************************************//**
 * @brief	初始化資料內容
 *****************************************************/
void WP8Cheat::InitData()
{
	const Int32u err = -1;
	::memset((void*)&m_HorseAbility, 0, sizeof(SaWP8ABILITY));
	::memset((void*)&m_HorseRace, 0, sizeof(SaWP8RACE));
	::memset((void*)&m_HorsePony, 0, sizeof(SaWP8PONY));
	::memset((void*)&m_HorseMare, 0, sizeof(SaWP8MARE));
	::memset((void*)&m_HorseStallion, 0, sizeof(SaWP8STALLION));

	::memset((void*)&m_Date, 0, sizeof(SaWP8DATE));
	m_Date.WeekNumber = err;
	m_Date.Month = err;
	m_Date.Week = err;

	::memset((void*)&m_Racing, 0, sizeof(SaWP8RACING));
}

/**************************************************//**
 * @brief	對應各資料位址
 *****************************************************/
void WP8Cheat::InitDataAddress()
{
	// WP8-2018 address setting
	::memset((void*)&m_HorseAbility, 0, sizeof(SaWP8ABILITY));
	m_HorseAbility.Count = HORSE_ABILITY_COUNT;
	m_HorseAbility.Addr = HORSE_ABILITY_ADDR;
	m_HorseAbility.Seek = HORSE_ABILITY_SEEK;

	::memset((void*)&m_HorseRace, 0, sizeof(SaWP8RACE));
	m_HorseRace.Count = HORSE_RACE_COUNT;
	m_HorseRace.Addr = HORSE_RACE_ADDR;
	m_HorseRace.Seek = HORSE_RACE_SEEK;

	::memset((void*)&m_HorsePony, 0, sizeof(SaWP8PONY));
	m_HorsePony.Count = HORSE_PONY_COUNT;
	m_HorsePony.Addr = HORSE_PONY_ADDR;
	m_HorsePony.Seek = HORSE_PONY_SEEK;

	::memset((void*)&m_HorseMare, 0, sizeof(SaWP8MARE));
	m_HorseMare.Count = HORSE_MARE_COUNT;
	m_HorseMare.Addr = HORSE_MARE_ADDR;
	m_HorseMare.Seek = HORSE_MARE_SEEK;

	::memset((void*)&m_HorseStallion, 0, sizeof(SaWP8STALLION));
	m_HorseStallion.Count = HORSE_STALLION_COUNT;
	m_HorseStallion.Addr = HORSE_STALLION_ADDR;
	m_HorseStallion.Seek = HORSE_STALLION_SEEK;

	::memset((void*)&m_Date, 0, sizeof(SaWP8DATE));
	m_Date.Addr = WP8DATE_ADDR;
	m_Date.DataLength = WP8DATE_DATA_LENGTH;

	::memset((void*)&m_Racing, 0, sizeof(SaWP8RACING));
	m_Racing.Count = WP8GAME_COUNT;
	m_Racing.SpeedAddr = WP8GAME_SPEED_ADDR;
	m_Racing.SpeedSeek = WP8GAME_SPEED_SEEK;
	m_Racing.TacticAddr = WP8GAME_TACTIC_ADDR;
	m_Racing.TacticSeek = WP8GAME_TACTIC_SEEK;
	m_Racing.WeightAddr = WP8GAME_WEIGHT_ADDR;
	m_Racing.WeightSeek = WP8GAME_WEIGHT_SEEK;
	m_Racing.JockeyAddr = WP8GAME_JOCKEY_ADDR;
	m_Racing.JockeySeek = WP8GAME_JOCKEY_SEEK;

	// WP9-2018 v1.0.2.x offset
	if (m_uVersion == WP8VER_502) {
		m_HorseAbility.Addr += WP8VER_502_SEEK;
		m_HorseRace.Addr += WP8VER_502_SEEK;
		m_HorsePony.Addr += WP8VER_502_SEEK;
		m_HorseMare.Addr += WP8VER_502_SEEK;
		m_HorseStallion.Addr  += WP8VER_502_SEEK;

		m_Date.Addr += WP8VER_502_SEEK;
		m_Racing.SpeedAddr  += WP8VER_502_SEEK;
		m_Racing.TacticAddr += WP8VER_502_SEEK;
		m_Racing.WeightAddr += WP8VER_502_SEEK;
		m_Racing.JockeyAddr += WP8VER_502_SEEK;
	}
}

/**************************************************//**
 * @brief	建構式
 *****************************************************/
WP8Cheat::WP8Cheat()
	: WsCheat() {
	this->InitData();
}

/**************************************************//**
 * @brief	解構式
 *****************************************************/
WP8Cheat::~WP8Cheat()
{

}
