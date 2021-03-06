//=====================================
//
//リザルトシーンGUI処理[resultSceneGUI.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "GUIManager.h"

#include "resultGUI.h"
#include "resultTelop.h"
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

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitResultSceneGUI(void)
{
	InitResultGUI(0);
	InitResultTelop(0);
}

/**************************************
終了処理
***************************************/
void UninitResultSceneGUI(void)
{
	UninitResultGUI(0);
	UninitResultTelop(0);
}

/**************************************
更新処理
***************************************/
void UpdateResultSceneGUI(void)
{
	UpdateResultGUI();
	UpdateResultTelop();
}

/**************************************
描画処理
***************************************/
void DrawResultSceneGUI(void)
{
	//順位を描画
	int winner = CheckWinnerPlayer();
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		//TODO : ゲーム結果をGameParameterから取得してセットする
		SetResultGUI(i, i == winner);
		DrawResultGUI();
	}

	//けっかはっぴょうを描画
	DrawResultTelop();
}
