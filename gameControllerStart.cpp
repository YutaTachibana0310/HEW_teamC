//=====================================
//
//ゲームコントローラスタート処理[gameControllerStart.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameController.h"

#include "countDownGUI.h"
/**************************************
マクロ定義
***************************************/
#define GAMECONTROLLER_START_DURATION	(240)

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