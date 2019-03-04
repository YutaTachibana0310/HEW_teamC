//=====================================
//
//リザルトシーン処理[resulScene.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "resultScene.h"
#include "gameParameter.h"
#include "sceneFade.h"

#include "meshCylinder.h"
#include "rainbowLane.h"

/**************************************
マクロ定義
***************************************/
#define RESULTSCENE_DURATION		(300)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static int cntFrame;

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
HRESULT InitResultScene(int num)
{
	cntFrame = 0;

	InitMeshCylinder(num);
	InitRainbowLane(num);
	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitResultScene(int num)
{
	UninitMeshCylinder(num);
	UninitRainbowLane(num);
}

/**************************************
更新処理
***************************************/
void UpdateResultScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();

	cntFrame++;
	if (cntFrame == RESULTSCENE_DURATION)
	{
		SetSceneFade(TitleScene);
	}
}

/**************************************
描画処理
***************************************/
void DrawResultScene(int n)
{
	DrawMeshCylinder(n);
	DrawRainbowLane(n);
}
