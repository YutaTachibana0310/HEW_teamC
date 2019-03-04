//=====================================
//
//ゲームシーン処理[gameScene.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameScene.h"

#include "meshCylinder.h"
#include "player.h"
#include "rainbowLane.h"
#include "gameParameter.h"
#include "gameController.h"

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
HRESULT InitGameScene(int num)
{
	InitGameParameter(num);

	InitMeshCylinder(num);
	InitPlayer();
	InitRainbowLane(num);

	InitGameController(num);

	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitGameScene(int num)
{
	UninitGameParameter(num);

	UninitMeshCylinder(num);
	UninitPlayer();
	UninitRainbowLane(num);

	UninitGameController(num);
}

/**************************************
更新処理
***************************************/
void UpdateGameScene(void)
{
	UpdateGameParameter();
	UpdateGameController();

	UpdateMeshCylinder();
	UpdatePlayer();
	UpdateRainbowLane();
}

/**************************************
描画処理
***************************************/
void DrawGameScene(int n)
{
	DrawMeshCylinder(n);
	DrawPlayer();
	DrawRainbowLane(n);
}