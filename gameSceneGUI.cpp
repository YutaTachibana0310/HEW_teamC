//=====================================
//
//バトルシーンGUI処理[gameSceneGUI.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "GUIManager.h"

#include "progressGauge.h"
#include "progressMarker.h"
#include "gameParameter.h"
#include "countDownGUI.h"
#include "goalTelop.h"
#include "speedMeter.h"
/**************************************
マクロ定義
***************************************/

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
初期化処理
***************************************/
void InitGameSceneGUI(void)
{
	InitProgressGauge(0);
	InitProgressMarker(0);
	InitCountDownGUI(0);
	InitGoalTelop(0);
	InitSpeedGUI();
}

/**************************************
終了処理
***************************************/
void UninitGameSceneGUI(void)
{
	UninitProgressGauge(0);
	UninitProgressMarker(0);
	UninitCountDownGUI(0);
	UninitGoalTelop(0);
	UninitSpeedGUI();
}

/**************************************
更新処理
***************************************/
void UpdateGameSceneGUI(void)
{
	UpdateProgressGauge();
	UpdateProgressMarker();
	UpdateCountDownGUI();
	UpdateGoalTelop();
	UpdateSpeedGUI();
}

/**************************************
描画処理
***************************************/
void DrawGameSceneGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	//プログレスゲージ描画
	DrawProgressGauge();

	//プログレスマーカー描画
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float progress = param->playerMoveDist / GAMEPARAMETER_MOVEDIST_MAX;
		SetProgressMarker(i, progress);
		DrawProgressMarker();
	}


	//スピードメーター描画
	for (int i = 0; i < METER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float meter = param->playerSpeed / 5;
		SetVertexMeter(i, meter);
		DrawSpeedGUI();
	}


	//カウントダウンGUIを描画
	DrawCountDownGUI();

	//ゴールテロップを描画
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);

		//プレイヤーがゴール前ならcontinue
		if (!param->isPlayerGoaled)
			continue;

		DrawGoalTelop(i);
	}
}
