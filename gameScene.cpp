//=====================================
//
//ゲームシーン処理[gameScene.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameScene.h"
#include "bgmManager.h"

#include "meshCylinder.h"
#include "player.h"
#include "rainbowLane.h"
#include "gameParameter.h"
#include "gameController.h"

#include "star.h"
#include "slashBullet.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERMARKER_POS_OFFSET		(D3DXVECTOR3(0.0f, 10.0f, 0.0f))
#define GAMESCENE_BGM_FADEDURATION	(60)

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
	InitSlashBullet(num);
	InitStar();

	//BGM再生
	FadeInBGM(BGM_GAME, BGM_FADE_DURATION);

	//ゲームコントローラ初期化
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
	UninitSlashBullet(num);

	UninitGameController(num);

	UninitStar();
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
	UpdateSlashBullet();

	UpdateStar();
}

/**************************************
描画処理
***************************************/
void DrawGameScene(int n)
{
	DrawMeshCylinder(n);
	DrawPlayer();
	DrawRainbowLane(n);
	DrawSlashBullet();

	DrawStar();
}