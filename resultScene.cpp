//=====================================
//
//リザルトシーン処理[resulScene.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "resultScene.h"
#include "gameParameter.h"

#include "meshCylinder.h"
#include "rainbowLane.h"

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
HRESULT InitResultScene(int num)
{
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
}

/**************************************
描画処理
***************************************/
void DrawResultScene(int n)
{
	DrawMeshCylinder(n);
	DrawRainbowLane(n);
}
