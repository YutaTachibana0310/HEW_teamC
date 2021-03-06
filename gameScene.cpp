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
#include "stageData.h"

#include "star.h"
#include "slashBullet.h"
#include "bullet.h"
#include "effect.h"
#include "bulletParticle.h"
#include "goalTape.h"

#include "bgmManager.h"
#include "collisionManager.h"
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
	InitSlashBullet(num);
	InitStar();
	InitBullet();
	InitEffect();
	InitBulletParticle(num);
	InitGoalTape(num);
	InitStageData(num);

	InitGameController(num);

	//bgm再生
	FadeInBGM(BGM_GAME, 300);

	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitGameScene(int num)
{
	UninitGameParameter(num);
	UninitStageData(num);

	UninitMeshCylinder(num);
	UninitPlayer();
	UninitRainbowLane(num);
	UninitSlashBullet(num);
	UninitEffect();
	UninitBulletParticle(num);
	UninitGoalTape(num);

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
	UpdateEffect();
	UpdateBulletParticle();

	UpdateBullet();
	UpdateStar();

	UpdateCollisionManager();
}

/**************************************
描画処理
***************************************/
void DrawGameScene(int n)
{
	DrawMeshCylinder(n);
	DrawPlayer();
	DrawRainbowLane(n);
	DrawGoalTape();

	DrawStar();

	DrawSlashBullet();
	DrawEffect();

	DrawBulletParticle();
}