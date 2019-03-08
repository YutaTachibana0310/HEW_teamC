//=====================================
//
//タイトルシーン処理[template.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "titleScene.h"
#include "input.h"
#include "sceneFade.h"

#include "meshCylinder.h"
#include "rainbowLane.h"
#include "gameParameter.h"
#include "player.h"

/**************************************
マクロ定義
***************************************/
#define TITLESCENE_SCROLLSPEED_DEFAULT		(1.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static bool entryState[TARGETPLAYER_MAX];	//エントリー状態

/**************************************
プロトタイプ宣言
***************************************/
bool IsCompleteEntry(void);		//エントリー完了判定処理

/**************************************
初期化処理
***************************************/
HRESULT InitTitleScene(int num)
{
	//エントリー状態を初期化
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		entryState[i] = false;
	}

	InitGameParameter(num);
	InitMeshCylinder(num);
	InitRainbowLane(num);
	InitPlayer();

	//背景のスクロールスピードを設定
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetSpeedGameParameter(i, TITLESCENE_SCROLLSPEED_DEFAULT);

	}

	return S_OK;
}

/**************************************
終了処理
***************************************/
void UninitTitleScene(int num)
{
	UninitGameParameter(num);
	UninitMeshCylinder(num);
	UninitRainbowLane(num);
	UninitPlayer();
}

/**************************************
更新処理
***************************************/
void UpdateTitleScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();
	UpdatePlayer();

	//エントリー検出処理
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		//NOTE : ポーズボタンとスタートボタンは同一のボタン
		//スタートボタンの入力が無ければcontinue
		if (!GetPauseButtonTrigger(i))
			continue;

		//入力があればエントリー完了状態へ遷移
		entryState[i] = true;
	}

	//テスト機能
	if (GetKeyboardTrigger(DIK_O))
		entryState[0] = true;
	if (GetKeyboardTrigger(DIK_P))
		entryState[1] = true;

	//エントリーが完了したらシーン遷移
	if(IsCompleteEntry())
		SetSceneFade(GameScene);
}

/**************************************
描画処理
***************************************/
void DrawTitleScene(int i)
{
	DrawMeshCylinder(i);
	DrawRainbowLane(i);
	DrawPlayer();
}

/**************************************
エントリー状態取得処理
***************************************/
bool GetEntryState(int playerID)
{
	return entryState[playerID];
}

/**************************************
エントリー完了判定処理
***************************************/
bool IsCompleteEntry(void)
{
	if (!entryState[0])
		return false;

	if (!entryState[1])
		return false;

	return true;
}