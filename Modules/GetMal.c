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
	case 50 ... 99 :
		//設定まで移動下(49)
	 	ReportData->HAT = HAT_BOTTOM;
		break;
	case 100 ... 158:
		//設定まで移動右(48+10)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 159 ... 207:
		//Aボタン(49)
		if( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 208 ...413:
		//本体設定まで移動(125+80)
		ReportData->LY = STICK_MAX;
		break;
	case 414 ... 463:
		//Aボタン(49)
		ReportData->Button |= SWITCH_A;
		break;
	case 464 ... 533:
		//日付と時刻まで移動(70)
		ReportData->LY = STICK_MAX;
		break;
	case 534 ... 583:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 584 ... 629:
		//現在の日付と時刻(40+5)
		ReportData->LY = STICK_MAX;
		break;
	case 630 ... 679:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 680 ... 730:
		//時まで移動(49+1)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 731 ... 780:
		//時間を進める(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_TOP;
		break;
	case 781 ... 830:
		//決定まで移動(49)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 831 ... 880:
		//決定をAボタンでおす
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	//あつ森起動	
	case 0+881 ... 49+881:
		//SWITCHのホーム画面に行く(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 50+881 ... 99+881:
		//あつ森の起動場所までいく(49)
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 100+881 ... 149+881:
		//Aボタン(あつ森の画面へ)(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;	
	//セーブをする
	case 150+881 ... 209+881+49:
		//マイナスおす(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 210+881+50 ... 335+881+10000:
		//R+Aボタン(80S=8750)-を押した後、しずえさんの会話が終わるまで
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A | SWITCH_R;
		break;
	case 335+881+10001:
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
	case 50 ... 99 :
		//設定まで移動下(49)
	 	ReportData->HAT = HAT_BOTTOM;
		break;
	case 100 ... 158:
		//設定まで移動右(48+10)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 159 ... 207:
		//Aボタン(49)
		if( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 208 ...413:
		//本体設定まで移動(125+80)
		ReportData->LY = STICK_MAX;
		break;
	case 414 ... 463:
		//Aボタン(49)
		ReportData->Button |= SWITCH_A;
		break;
	case 464 ... 533:
		//日付と時刻まで移動(70)
		ReportData->LY = STICK_MAX;
		break;
	case 534 ... 583:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 584 ... 629:
		//現在の日付と時刻(40+5)
		ReportData->LY = STICK_MAX;
		break;
	case 630 ... 679:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 680 ... 730:
		//時まで移動(49+1)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 731 ... 780:
		//時間を戻す(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 781 ... 830:
		//分まで移動(49)
		if( count % 50 < 25 )
			ReportData->HAT = HAT_RIGHT;
		break;
	case 831 ... 880+3:
		//時間を戻す(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 881+3 ... 930+3:
		//決定まで移動(49)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 931+3 ... 980+3:
		//決定をAボタンでおす(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 981+3 ... 1030+3:
		//HOMEにいく(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_HOME;
		break;
	case 1031+3 ... 3781+3:
		//Aボタン(125*22)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	//セーブをする
	case 3782+3 ... 3782+3+49:
		//マイナスおす(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 3782+3+50 ... 3782+3+7550:
		//Aボタン(60S=6875)ロード時間
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 3782+3+7551:
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
	case 330 ... 1549:
		//ロード時間(1219)	
		break;
	case 1550 ... 1569:
		//少し上へ(19)
		ReportData->LY = STICK_MIN;
		ReportData->Button |= SWITCH_B;
		break;
	case 1570 ... 1695:
		//右へ(125)
		ReportData->LX = STICK_MAX;
		ReportData->Button |= SWITCH_B;
		break;	
	case 1696 ... 1745:
		//ATMに話しかける(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 1746 ... 3496:
		//Bをおす(125*13+49)
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_B;
		break;
	case 3597 ... 3646:
		//-をおしてセーブする(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 3647 ... 5272:
		//マイナスをおしてから文字が読み終わるまで(13s=1625)
		ReportData->Button |= SWITCH_R; 
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A | SWITCH_R;
		break;
	case 5273 ... 7273:
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
