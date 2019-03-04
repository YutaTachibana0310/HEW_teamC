//=====================================
//
//ゲームコントローラスタート処理[gameControllerStart.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameController.h"

#include "countDownGUI.h"
#include "gameParameter.h"

/**************************************
マクロ定義
***************************************/
#define GAMECONTROLLER_START_DURATION		(180)
#define GAMECONTROLLER_START_SCROLLSPEED	(1.0f)
/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
入場処理
***************************************/
void EnterGameControllerStart(GAMECONTROLLER *entity)
{
	entity->cntFrame = 0;

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetSpeedGameParameter(i, GAMECONTROLLER_START_SCROLLSPEED);
	}

	SetCountDownGUI();
}

/**************************************
更新処理
***************************************/
void UpdateGameControllerStart(GAMECONTROLLER *entity)
{
	entity->cntFrame++;

	//タイミングが来たらレース開始
	if (entity->cntFrame == GAMECONTROLLER_START_DURATION)
	{
		ChangeStateGameController(GAMECONTROLLER_RUN);
	}
}