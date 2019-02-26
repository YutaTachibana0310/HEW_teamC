//=====================================
//
//ゲームシーン処理[gameScene.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameScene.h"

#include "meshCylinder.h"

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
	InitMeshCylinder(num);
	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitGameScene(int num)
{
	UninitMeshCylinder(num);
}

/**************************************
更新処理
***************************************/
void UpdateGameScene(void)
{
	UpdateMeshCylinder();
}

/**************************************
描画処理
***************************************/
void DrawGameScene(void)
{
	DrawMeshCylinder();
}
