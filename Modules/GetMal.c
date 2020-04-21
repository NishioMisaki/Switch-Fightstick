#include "Joystick.h"
#include "Modules.h"

typedef enum {
	OPEN_ATUMORI,
	//GETING_MAL,
	//YEAR_UP,
	DONE,
} State_t;

static State_t state = OPEN_ATUMORI;
static uint16_t duration_count = 0;

static uint8_t openatumori(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {		
	case 0 ... 49:
		//SWITCHのホーム画面に行く(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;	
	case 50 ... 99 :
		//設定まで移動下(49)
		//
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
	case 100+881 ... 6349+881:
		//あつ森を起動(50S)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	//セーブをする
	case 6350+881 ... 6350+881+59:
		//マイナスおす(59)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 6350+881+60 ... 6350+881+185:
		//R+Aボタン(125)
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A | SWITCH_R;
		breaki;
	case 6350+881+186:
		return 1;

			
	}
	return 0;
}

/*
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
	case 3497 ...3546:
		//-をおしてセーブする
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 3547:
		return 1;
	}
	return 0;
}
*/
/*
static uint8_t yearup(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	//設定まで移動
	case 0 ... 49:
		if (count % 50 < 25)
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 50 ... 199:
		if (count % 50 < 25)
			ReportData->HAT = HAT_LEFT;
		break;

	case  200 ... 249:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;

	case 250 ... 349:
		//本体設定まで移動
		ReportData->LY = STICK_MIN;
		break;

	case 350 ...399:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;

	case 400 ... 599:
		//日付と時刻に移動
		if (count % 50 < 25)
			ReportData->HAT = HAT_BOTTOM;
		break;

	case 600 ... 649:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;

	case 650 ... 699:
		//日付と本体設定に移動
		ReportData->LY = STICK_MIN;
		break;

	case 700 ... 749:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;

	//一年進める

	case 750 ... 799:
		if (count % 50 < 25)
			ReportData->HAT = HAT_TOP;
		break;

	case 800 ... 849:
		ReportData->LX = STICK_MAX;
		break;

	case 850 ... 899:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	
	case 900:
		return 1;
	}
	return 0;
}
*/

void GetMal_Module(USB_JoystickReport_Input_t* const ReportData)
{
	switch (state) {
	case OPEN_ATUMORI:
		if (openatumori(ReportData, duration_count)) {
			state = DONE;
			duration_count = 0;
		}
		break;
	/*
	case GETING_MAL:
		if (getmal(ReportData, duration_count)) {
			state = YEAR_UP;
			duration_count = 0;
		}
		break;
	case YEAR_UP:
		if (yearup(ReportData, duration_count)) {
			state = DONE;
			duration_count = 0;
		}
		break;
	*/
	case DONE:
		break;
	}
	duration_count++;
}
