//=====================================
//
//スクロールスピードコントローラ処理[scrollSpeedController.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "scrollSpeedController.h"

#include "gameParameter.h"

/**************************************
マクロ定義
***************************************/
#define SCROLLSPEEDCONTROLLER_DELTA_VALUE	(0.8f)
#define SCROLLSPEEDCONTROLLER_DELTA_MAX		(0.5f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static float targetSpeed[TARGETPLAYER_MAX];
static int cntFrame[TARGETPLAYER_MAX];

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitScrollSpeedController(int num)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		targetSpeed[i] = GetGameParameterAdr(i)->playerSpeed;
	}
}

/**************************************
更新処理
***************************************/
void UpdateScrollSpeedController(void)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float diff = targetSpeed[i] - param->playerSpeed;
		float setSpeed = Clampf(-SCROLLSPEEDCONTROLLER_DELTA_MAX, SCROLLSPEEDCONTROLLER_DELTA_MAX, diff * SCROLLSPEEDCONTROLLER_DELTA_VALUE);
		param->playerSpeed = setSpeed;

		cntFrame[i]++;
		if (cntFrame[i] == 30)
		{
			targetSpeed[i] = 2.0f;
		}
	}
}

/**************************************
ターゲットスピードセット処理
***************************************/
void SetTargetScrollSpeed(int playerID, float targetSpeed)
{

}