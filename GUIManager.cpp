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

#include "progressGauge.h"

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
}

/**************************************
終了処理
***************************************/
void UninitGUIManager(int num)
{
	UninitProgressGauge(num);
}

/**************************************
更新処理
***************************************/
void UpdateGUIManager(void)
{
	UpdateProgressGauge();
}

/**************************************
描画処理
***************************************/
void DrawGUIManager(int n)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	DrawProgressGauge();
}