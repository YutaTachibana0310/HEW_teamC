//=====================================
//
//リザルトシーン処理[resulScene.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "resultScene.h"
#include "bgmManager.h"
#include "soundEffectManager.h"

#include "gameParameter.h"
#include "sceneFade.h"
#include "gameParameter.h"

#include "meshCylinder.h"
#include "rainbowLane.h"
#include "player.h"

/**************************************
マクロ定義
***************************************/
#define RESULTSCENE_DURATION			(300)
#define RESULTSCENE_SCROLL_SPEED		(1.0f)
#define RESULTSCENE_BGM_FADEDURATION	(60)
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
	InitPlayer();

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GetGameParameterAdr(i)->playerSpeed = RESULTSCENE_SCROLL_SPEED;
	}

	//BGM再生
	FadeInBGM(BGM_RESULT, BGM_FADE_DURATION);

	//歓声再生
	PlaySE(SOUND_CHEER);

	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitResultScene(int num)
{
	UninitMeshCylinder(num);
	UninitRainbowLane(num);
	UninitPlayer();
}

/**************************************
更新処理
***************************************/
void UpdateResultScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();
	UpdatePlayer();

	cntFrame++;
	if (cntFrame == RESULTSCENE_DURATION)
	{
		FadeOutBGM(BGM_RESULT, RESULTSCENE_BGM_FADEDURATION);
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
	DrawPlayer();
}
