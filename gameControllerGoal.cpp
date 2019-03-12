//=====================================
//
//ゲームコントローラゴール処理[gameControllerGoal.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameController.h"
#include "bgmManager.h"

#include "sceneFade.h"
#include "goalTape.h"

/**************************************
マクロ定義
***************************************/
#define GAMECONTROLLER_GOAL_DURATION		(180)

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
void EnterGameControllerGoal(GAMECONTROLLER *entity)
{
	entity->cntFrame = 0;
}

/**************************************
更新処理
***************************************/
void UpdateGameControllerGoal(GAMECONTROLLER *entity)
{
	entity->cntFrame++;

	UpdateGoalTape();

	if(entity->cntFrame == GAMECONTROLLER_GOAL_DURATION)
	{
		FadeOutBGM(BGM_GAME, BGM_FADE_DURATION);
		SetSceneFade(ResultScene);
	}
}