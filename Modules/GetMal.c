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
	case 0 ... 29:
		//メニュー画面に行く
		if (count % 10 == 0)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 30 ... 69:
		//あつもりまでいく
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 70 ... 149:
		//あつもりを開く
		if (count % 10 == 0)
			ReportData->Button |= SWITCH_A;
		break;
	case 150:
		return 1;
	}
	return 0;
}

/*
static uint8_t getmal(USB_JoystickReport_Input_t* const ReportData, uint16_t count)
{
	
	switch (count) {
	
	//市役所まで移動
	case 0 ... 199:
		//Move down
		ReportData->LY = STICK_MIN;
		break;
	case 200 ... 599 :
		//Move down
		ReportData->LX = STICK_MAX;
	case 600 ... 619:
        //in office
		ReportData->LY = STICK_MAX;
		break;

	//ATMの前に移動
	case 620+1000 ... 620+1000+19:
		//Move up
		ReportData->LY = STICK_MAX;
		break;

	case 620+1000+20 ... 620+1000+20+99:
		// Move left
		ReportData->LX = STICK_MAX;
		break;

	//A連打
	case 620+1000+20+100 ... 620 + 1000 + 20 + 100 + 599:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;
	
	case 620 + 1000 + 20 + 100+ 600 ... 620 + 1000 + 20 + 100 + 600 + 49:
		if (count % 50 < 25)
			ReportData->Button = SWITCH_B;
		break;

	//セーブをする
	case 620 + 1000 + 20 + 100 + 600 + 50 ... 620 + 1000 + 20 + 100 + 600 + 50 + 49:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;

	case 620 + 1000 + 20 + 100 + 600 + 50 + 50 ... 620 + 1000 + 20 + 100 + 600 + 50 + 50 + 699:
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;

	case 620 + 1000 + 20 + 100 + 600 + 50 + 50 + 700 ... 620 + 1000 + 20 + 100 + 600 + 50 + 50 + 700 + 49: 
	        //Open home
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 620 + 1000 + 20 + 100 + 600 + 50 + 50 + 700 + 50:
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
			state = GETING_MAL;
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
