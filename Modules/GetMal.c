#include "Joystick.h"
#include "Modules.h"

typedef enum {
	OPEN_ATUMORI_UP,
	GETING_MAL,
	OPEN_ATUMORI_DOWN,
	DONE,
} State_t;

static State_t state = OPEN_ATUMORI_UP;
static uint16_t duration_count = 0;


static uint8_t openatumori_up(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {		
	case 0 ... 49:
		//SWITCHのホーム画面に行く(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;	
	case 50 ... 100:
		//設定まで移動下(50)
	 	ReportData->HAT = HAT_BOTTOM;
		break;
	case 101 ... 159:
		//設定まで移動右(48+10)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 160 ... 208:
		//Aボタン(49)
		if( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 209 ...414:
		//本体設定まで移動(125+80)
		ReportData->LY = STICK_MAX;
		break;
	case 415 ... 464:
		//Aボタン(49)
		ReportData->Button |= SWITCH_A;
		break;
	case 465 ... 534:
		//日付と時刻まで移動(70)
		ReportData->LY = STICK_MAX;
		break;
	case 535 ... 584:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 585 ... 630:
		//現在の日付と時刻(40+5)
		ReportData->LY = STICK_MAX;
		break;
	case 631 ... 680:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 681 ... 731:
		//時まで移動(49+1)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 732 ... 781:
		//時間を進める(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_TOP;
		break;
	case 782 ... 831:
		//決定まで移動(49)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 832 ... 881:
		//決定をAボタンでおす
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	//あつ森起動	
	case 0+882 ... 49+882:
		//SWITCHのホーム画面に行く(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 50+882 ... 99+882:
		//あつ森の起動場所までいく(49)
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 100+882 ... 149+882:
		//Aボタン(あつ森の画面へ)(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;	
	//セーブをする
	case 150+882 ... 209+882+49:
		//マイナスおす(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 210+882+50 ... 335+882+10000+200:
		//R+Aボタン(80+1S=8750+200)-を押した後、しずえさんの会話が終わるまで
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A | SWITCH_R;
		break;
	case 335+882+10001+200:
		return 1;		
	}
	return 0;
}


static uint8_t openatumori_down(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {		
	case 0 ... 49:
		//SWITCHのホーム画面に行く(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;	
	case 50 ... 100 :
		//設定まで移動下(50)
	 	ReportData->HAT = HAT_BOTTOM;
		break;
	case 101 ... 159:
		//設定まで移動右(48+10)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 160 ... 208:
		//Aボタン(49)
		if( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 209 ...414:
		//本体設定まで移動(125+80)
		ReportData->LY = STICK_MAX;
		break;
	case 415 ... 464:
		//Aボタン(49)
		ReportData->Button |= SWITCH_A;
		break;
	case 465 ... 534:
		//日付と時刻まで移動(70)
		ReportData->LY = STICK_MAX;
		break;
	case 535 ... 584:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 585 ... 630:
		//現在の日付と時刻(40+5)
		ReportData->LY = STICK_MAX;
		break;
	case 631 ... 680:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 681 ... 731:
		//時まで移動(49+1)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 732 ... 781:
		//時間を戻す(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 782 ... 831:
		//分まで移動(49)
		if( count % 50 < 25 )
			ReportData->HAT = HAT_RIGHT;
		break;
	case 832 ... 881+80:
		//時間を戻す(49+80)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 882+80 ... 931+80:
		//決定まで移動(49)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 932+80 ... 981+80:
		//決定をAボタンでおす(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 982+80 ... 1031+80:
		//HOMEにいく(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_HOME;
		break;
	case 1032+80 ... 3782+80:
		//Aボタン(125*22)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	//セーブをする
	case 3783+80 ... 3783+80+49:
		//マイナスおす(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 3783+80+50 ... 3783+80+7550:
		//Aボタン(60S=6875)ロード時間
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 3783+80+7551:
		return 1;
	}
	return 0;
}

static uint8_t getmal(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	
	switch (count) {
	
	//市役所まで移動
	case 0 ... 259:
		//左に移動(259)
		ReportData->LX = STICK_MIN;
		ReportData->Button |= SWITCH_B;
		break;
	case 260 ... 279:
		//上に移動+入る(19)
		ReportData->LY = STICK_MIN;
		break;
	case 280 ... 329:
		//Aをおす（49）
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 330 ... 1549-40:
		//ロード時間(1219)	
		break;
	case 1550-40 ... 1569-40:
		//少し上へ(19)
		ReportData->LY = STICK_MIN;
		ReportData->Button |= SWITCH_B;
		break;
	case 1570-40 ... 1695-40:
		//右へ(125)
		ReportData->LX = STICK_MAX;
		ReportData->Button |= SWITCH_B;
		break;	
	case 1696-40 ... 1745-40:
		//ATMに話しかける(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 1746-40 ... 3496-40:
		//Bをおす(125*13+49)
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_B;
		break;
	case 3597-40 ... 3646-40:
		//-をおしてセーブする(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 3647-40 ... 5272-40:
		//マイナスをおしてから文字が読み終わるまで(13s=1625)
		ReportData->Button |= SWITCH_R; 
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A | SWITCH_R;
		break;
	case 5273-40 ... 7273-40:
		//待ち時間(ホームへ行く)(16S=2000)
		break;
	case 7274:
		return 1;
	}
	return 0;
}

void GetMal_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {

	case OPEN_ATUMORI_UP:
		if (openatumori_up(ReportData, duration_count)) {
			state = GETING_MAL;
			duration_count = 0;
		}
		break;

	case GETING_MAL:
		if (getmal(ReportData, duration_count)) {
			state = OPEN_ATUMORI_DOWN;
			duration_count = 0;
		}
		break;

	case OPEN_ATUMORI_DOWN:
		if (openatumori_down(ReportData, duration_count)) {
			state = OPEN_ATUMORI_UP;
			duration_count = 0;
		}
		break;
	}
	duration_count++;
}
