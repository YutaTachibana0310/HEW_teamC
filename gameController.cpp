//=====================================
//
//ゲームコントローラ処理[gameController.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef void(*FuncGameController)(GAMECONTROLLER *entity);

/**************************************
グローバル変数
***************************************/
static GAMECONTROLLER controller;

//入場処理テーブル
static FuncGameController OnEnter[GAMECONTROLLER_STATEMAX] = {
	EnterGameControllerStart
};

//更新処理テーブル
static FuncGameController OnUpdate[GAMECONTROLLER_STATEMAX] = {
	UpdateGameControllerStart
};

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
***************************************/
void InitGameController(int num)
{
	//スタート状態から開始
	controller.currentState = GAMECONTROLLER_START;
	ChangeStateGameController(controller.currentState);
}

/**************************************
終了処理
***************************************/
void UninitGameController(int num)
{

}

/**************************************
更新処理
***************************************/
void UpdateGameController(void)
{
	OnUpdate[controller.currentState](&controller);
}

/**************************************
描画処理
***************************************/
void DrawGameController(void)
{

}

/**************************************
状態遷移処理
***************************************/
void ChangeStateGameController(int next)
{
	//遷移前のステートを記憶
	controller.prevState = controller.currentState;

	//ステートを遷移
	controller.currentState = next;

	//遷移したステートの入場処理を実行
	OnEnter[controller.currentState](&controller);
}