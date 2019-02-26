//=====================================
//
//シーンマネージャ処理[sceneManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "sceneManager.h"
#include "GUIManager.h"

#include "gameScene.h"


/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef void(*SceneFunc)(void);			//シーンの各処理の関数ポインタ定義
typedef HRESULT(*SceneInit)(int num);	//シーンの初期化処理の関数ポインタ定義
typedef void(*SceneUninit)(int num);	//シーンの終了処理の関数ポインタ定義

/**************************************
グローバル変数
***************************************/
static int* currentSceneId;
static int nextScene;

//初期化処理テーブル
static SceneInit Init[DefineSceneMax] = {
	InitGameScene,
};

//終了処理テーブル
static SceneUninit Uninit[DefineSceneMax] = {
	UninitGameScene,
};

//更新処理テーブル
static SceneFunc Update[DefineSceneMax] = {
	UpdateGameScene,
};

//描画処理テーブル
static SceneFunc Draw[DefineSceneMax] = {
	DrawGameScene
};

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitSceneManager(int* ptr)
{

	/*for (int i = 0; i < DefineSceneMax; i++)
	{
		Init[i](num);
	}*/

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
void DrawSceneManager(void)
{
	Draw[*currentSceneId]();
}

/**************************************
シーンセット処理
***************************************/
void SetScene(DefineScene sceneId)
{
	nextScene = sceneId;
	UninitScene(1);
	*currentSceneId = sceneId;
	//InitGUIManager(1);
	InitScene(1);
}

/**************************************
ネクストシーン取得処理
***************************************/
int GetNextScene(void)
{
	return nextScene;
}