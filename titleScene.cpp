//=====================================
//
//タイトルシーン処理[template.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "titleScene.h"
#include "input.h"

#include "meshCylinder.h"
#include "rainbowLane.h"
#include "gameParameter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static bool isEntryCompleted[TARGETPLAYER_MAX];

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
HRESULT InitTitleScene(int num)
{
	//エントリー状態を初期化
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		isEntryCompleted[i] = false;
	}

	InitGameParameter(num);
	InitMeshCylinder(num);
	InitRainbowLane(num);
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
}

/**************************************
更新処理
***************************************/
void UpdateTitleScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();

	//エントリー検出処理
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		//NOTE : ポーズボタンとスタートボタンは同一のボタン
		//スタートボタンの入力が無ければcontinue
		if (!GetPauseButtonTrigger(i))
			continue;

		//入力があればエントリー完了状態へ遷移
		isEntryCompleted[i] = true;
	}

	//テスト機能
	if (GetKeyboardTrigger(DIK_O))
		isEntryCompleted[0] = true;
	if (GetKeyboardTrigger(DIK_P))
		isEntryCompleted[1] = true;
}

/**************************************
描画処理
***************************************/
void DrawTitleScene(int i)
{
	DrawMeshCylinder(i);
	DrawRainbowLane(i);
}

/**************************************
エントリー状態取得処理
***************************************/
bool IsEntryCompleted(int playerID)
{
	return isEntryCompleted[playerID];
}