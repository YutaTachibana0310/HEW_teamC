//=====================================
//
//ゲームコントローララン処理[gameControllerRun.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameController.h"

#include "gameParameter.h"
#include "scrollSpeedController.h"
#include "goalTape.h"

/**************************************
マクロ定義
***************************************/
#define GAMECONTROLLER_RUN_STARTSPEED		(2.0f)

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
void EnterGameControllerRun(GAMECONTROLLER *entity)
{
	entity->cntFrame = 0;
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetSpeedGameParameter(i, GAMECONTROLLER_RUN_STARTSPEED);
	}
	//InitScrollSpeedController(0);
}

#include "input.h"
#include "player.h"
/**************************************
更新処理
***************************************/
void UpdateGameControllerRun(GAMECONTROLLER *entity)
{
	//テスト用機能
	if (GetKeyboardPress(DIK_W))
	{
		GetGameParameterAdr(0)->playerSpeed += 0.05f;
	}
	if (GetKeyboardPress(DIK_E))
	{
		GetGameParameterAdr(1)->playerSpeed += 0.05f;
	}
	if (GetKeyboardTrigger(DIK_K))
	{
		SetPlayerAcceleration(0, true);
	}
	if (GetKeyboardTrigger(DIK_L))
	{
		SetPlayerAcceleration(1, true);
	}

	UpdateGoalTape();

	//プレイヤーの移動距離を加算
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		param->playerMoveDist += param->playerSpeed;
	}
	GetSystemParameterAdr()->currentProgress += SYSTEMPARAMETER_PROGRESS_VALUE;

	//ゲームパラメータの時間を加算
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);

		if (param->isPlayerGoaled)
			continue;

		param->deltaTime += 1.0f / 60.0f;
	}

	//プレイヤーが両方ゴールしたらステート遷移
	if (CheckPlayerGoaled(0) && CheckPlayerGoaled(1))
	{
		ChangeStateGameController(GAMECONTROLLER_GOAL);
	}
}
