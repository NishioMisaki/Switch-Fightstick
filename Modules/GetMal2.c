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
	case 50 ... 110:
		//設定まで移動下(60)
	 	ReportData->HAT = HAT_BOTTOM;
		break;
	case 111 ... 169:
		//設定まで移動右(48+10)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 170 ... 218:
		//Aボタン(49)
		if( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 219 ...424:
		//本体設定まで移動(125+80)
		ReportData->LY = STICK_MAX;
		break;
	case 425 ... 474:
		//Aボタン(49)
		ReportData->Button |= SWITCH_A;
		break;
	case 475 ... 544:
		//日付と時刻まで移動(70)
		ReportData->LY = STICK_MAX;
		break;
	case 545 ... 594:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 595 ... 640:
		//現在の日付と時刻(40+5)
		ReportData->LY = STICK_MAX;
		break;
	case 641 ... 690:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 691 ... 741:
		//時まで移動(50)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 742 ... 791:
		//時間を進める(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_TOP;
		break;
	case 792 ... 841:
		//決定まで移動(49)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 842 ... 891:
		//決定をAボタンでおす
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	//あつ森起動	
	case 0+892 ... 49+892:
		//SWITCHのホーム画面に行く(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_HOME;
		break;
	case 50+892 ... 99+892:
		//あつ森の起動場所までいく(49)
		ReportData->HAT = HAT_TOP_LEFT;
		break;
	case 100+892 ... 149+892:
		//Aボタン(あつ森の画面へ)(49)
		if (count % 50 < 25)
			ReportData->Button |= SWITCH_A;
		break;	
	//セーブをする
	case 150+892 ... 209+892+49:
		//マイナスおす(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 210+892+50 ... 335+892+10000+200:
		//R+Aボタン(80+1S=8750+200)-を押した後、しずえさんの会話が終わるまで
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A | SWITCH_R;
		break;
	case 335+892+10001+200:
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
	case 50 ... 110 :
		//設定まで移動下(60)
	 	ReportData->HAT = HAT_BOTTOM;
		break;
	case 111 ... 169:
		//設定まで移動右(48+10)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 170 ... 218:
		//Aボタン(49)
		if( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 219 ...424:
		//本体設定まで移動(125+80)
		ReportData->LY = STICK_MAX;
		break;
	case 425 ... 474:
		//Aボタン(49)
		ReportData->Button |= SWITCH_A;
		break;
	case 475 ... 544:
		//日付と時刻まで移動(70)
		ReportData->LY = STICK_MAX;
		break;
	case 545 ... 594:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 595 ... 640:
		//現在の日付と時刻(40+5)
		ReportData->LY = STICK_MAX;
		break;
	case 641 ... 690:
		//Aボタン
		ReportData->Button |= SWITCH_A;
		break;
	case 691 ... 741:
		//時まで移動(49+1)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 742 ... 791:
		//時間を戻す(49)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 792 ... 841:
		//分まで移動(49)
		if( count % 50 < 25 )
			ReportData->HAT = HAT_RIGHT;
		break;
	case 842 ... 891+80:
		//時間を戻す(49+80)
		if ( count % 50 < 25 )
			ReportData->HAT = HAT_BOTTOM;
		break;
	case 892+80 ... 941+80:
		//決定まで移動(49)
		ReportData->HAT = HAT_RIGHT;
		break;
	case 942+80 ... 991+80:
		//決定をAボタンでおす(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 992+80 ... 1041+80:
		//HOMEにいく(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_HOME;
		break;
	case 1042+80 ... 3792+80:
		//Aボタン(125*22)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	//セーブをする
	case 3793+80 ... 3793+80+49:
		//マイナスおす(49)
		if ( count % 50 < 25)
			ReportData->Button |= SWITCH_SELECT;
		break;
	case 3793+80+50 ... 3793+80+7550:
		//Aボタン(60S=6875)ロード時間
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 3793+80+7551:
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
	case 330 ... 1549-125:
		//ロード時間(1219-125)	
		break;
	case 1550-125 ... 1569-125:
		//少し上へ(19)
		ReportData->LY = STICK_MIN;
		ReportData->Button |= SWITCH_B;
		break;
	case 1570-125 ... 1695-125:
		//右へ(125)
		ReportData->LX = STICK_MAX;
		ReportData->Button |= SWITCH_B;
		break;	
	case 1696-125 ... 1745-125:
		//ATMに話しかける(49)
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_A;
		break;
	case 1746-125 ... 3496-125:
		//Bをおす(125*13+49)
		ReportData->Button |= SWITCH_R;
		if ( count % 50 < 25 )
			ReportData->Button |= SWITCH_B;
		break;
  case 3497-125:
    return 1:
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
