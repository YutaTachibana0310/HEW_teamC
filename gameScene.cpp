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

#include "playerMarker.h"
/**************************************
マクロ定義
***************************************/
#define PLAYERMARKER_POS_OFFSET		(D3DXVECTOR3(0.0f, 10.0f, 0.0f))

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
	InitPlayerMarker(num);

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
	UninitPlayerMarker(num);

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
	UpdatePlayerMarker();
}

/**************************************
描画処理
***************************************/
void DrawGameScene(int n)
{
	DrawMeshCylinder(n);
	DrawPlayer();
	DrawRainbowLane(n);

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		D3DXVECTOR3 pos = GetPositionPlayer(i) + PLAYERMARKER_POS_OFFSET;
		SetPlayerMarker(i, pos);
		DrawPlayerMarker();
	}
}