#include "Joystick.h"
#include "Modules.h"

typedef enum {
	OPEN_ATUMORI,
	//GETING_MAL,
	//YEAR_UP,
	DONE,
} State_t;

static State_t state = GETING_MAL;
static uint16_t duration_count = 0;

static uint8_t openatumori(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	switch (count) {
	casa 0 ... 49:
		//SWITCHのホーム画面に行く(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 50 .... 99:
　　　　　　　　　//設定まで移動(49)
	 	ReportData->HAT = HAT_BUTTON_RIGHT;
		break;
	/* あつ森を起動する
	case 0 ... 49:
		//SWITCHのホーム画面に行く(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 50 ... 99:
		//あつ森の起動場所までいく(49)
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 100 ... 6349:
		//あつ森を起動(50S)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	case 6350:
		return 1;*/
	case 100:
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
