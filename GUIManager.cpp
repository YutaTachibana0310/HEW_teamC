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
//初期化処理テーブル
static FuncGUI Init[DefineSceneMax] = {
	InitGameSceneGUI,
	InitTitleSceneGUI,
};

//終了処理テーブル
static FuncGUI Uninit[DefineSceneMax] = {
	UninitGameSceneGUI,
	UninitTitleSceneGUI
};

//更新処理テーブル
static FuncGUI Update[DefineSceneMax] = {
	UpdateGameSceneGUI,
	UpdateTitleSceneGUI,
};

//描画処理テーブル
static FuncGUI Draw[DefineSceneMax] = {
	DrawGameSceneGUI,
	DrawTitleSceneGUI
};

/**************************************
初期化処理
***************************************/
void InitGUIManager(int currentScene)
{
	Init[currentScene]();
}

/**************************************
終了処理
***************************************/
void UninitGUIManager(int currentScene)
{
	Uninit[currentScene]();
}

/**************************************
更新処理
***************************************/
void UpdateGUIManager(int currentScene)
{
	Update[currentScene]();
}

/**************************************
描画処理
***************************************/
void DrawGUIManager(int currentScene)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	Draw[currentScene]();
}
