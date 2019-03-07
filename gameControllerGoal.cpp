//=====================================
//
//ゲームコントローラゴール処理[gameControllerGoal.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameController.h"

#include "sceneFade.h"

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

	if(entity->cntFrame == GAMECONTROLLER_GOAL_DURATION)
	{
		SetSceneFade(ResultScene);
	}
}