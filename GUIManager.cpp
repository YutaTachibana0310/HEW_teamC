//=====================================
//
//GUIマネージャ処理[GUIManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "GUIManager.h"
#include "sceneManager.h"
#include "Easing.h"
#include "debugWindow.h"
#include "gameParameter.h"

#include "progressGauge.h"
#include "progressMarker.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef void(*FuncGUI)(void);

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void InitGUIManager(int num)
{
	InitProgressGauge(num);
	InitProgressMarker(num);
}

/**************************************
終了処理
***************************************/
void UninitGUIManager(int num)
{
	UninitProgressGauge(num);
	UninitProgressMarker(num);
}

/**************************************
更新処理
***************************************/
void UpdateGUIManager(void)
{
	UpdateProgressGauge();
	UpdateProgressMarker();
}

/**************************************
描画処理
***************************************/
void DrawGUIManager(int n)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	//プログレスゲージ描画
	DrawProgressGauge();

	//プログレスマーカー描画
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float progress = param->playerMoveDist / GAMEPARAMETER_MOVEDIST_MAX;
		SetProgressMarker(i, progress);
		DrawProgressMarker();
	}
}