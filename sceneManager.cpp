//=====================================
//
//シーンマネージャ処理[sceneManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "sceneManager.h"
#include "GUIManager.h"

#include "gameScene.h"
#include "titleScene.h"
#include "resultScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef void(*SceneFunc)(void);			//シーンの各処理の関数ポインタ定義
typedef HRESULT(*SceneInit)(int num);	//シーンの初期化処理の関数ポインタ定義
typedef void(*SceneUninit)(int num);	//シーンの終了処理の関数ポインタ定義
typedef void(*SceneDraw)(int n);		//シーンの描画処理の関数ポインタ定義

/**************************************
グローバル変数
***************************************/
static int* currentSceneId;
static int nextScene;

//初期化処理テーブル
static SceneInit Init[DefineSceneMax] = {
	InitGameScene,
	InitTitleScene,
	InitResultScene,
};

//終了処理テーブル
static SceneUninit Uninit[DefineSceneMax] = {
	UninitGameScene,
	UninitTitleScene,
	UninitResultScene
};

//更新処理テーブル
static SceneFunc Update[DefineSceneMax] = {
	UpdateGameScene,
	UpdateTitleScene,
	UpdateResultScene
};

//描画処理テーブル
static SceneDraw Draw[DefineSceneMax] = {
	DrawGameScene,
	DrawTitleScene,
	DrawResultScene
};

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitSceneManager(int* ptr)
{
	currentSceneId = ptr;
}

/**************************************
個別シーン初期化処理
***************************************/
void InitScene(int num)
{
	Init[*currentSceneId](num);
}

/**************************************
終了処理
***************************************/
void UninitSceneManager(int num)
{
	Uninit[*currentSceneId](num);
}

/**************************************
個別シーン終了処理
***************************************/
void UninitScene(int num)
{

}

/**************************************
更新処理
***************************************/
void UpdateSceneManager(void)
{
	Update[*currentSceneId]();
}

/**************************************
描画処理
***************************************/
void DrawSceneManager(int n)
{
	Draw[*currentSceneId](n);
}

/**************************************
シーンセット処理
***************************************/
void SetScene(DefineScene sceneId)
{
	nextScene = sceneId;

	//現在のシーンを終了
	UninitScene(1);
	UninitGUIManager(*currentSceneId);

	//シーンを切り替え
	*currentSceneId = sceneId;

	//シーン初期化
	InitScene(1);
	InitGUIManager(*currentSceneId);
}

/**************************************
ネクストシーン取得処理
***************************************/
int GetNextScene(void)
{
	return nextScene;
}