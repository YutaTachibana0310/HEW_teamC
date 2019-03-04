//=====================================
//
//ゲームコントローラヘッダ[gameController.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
//ゲームコントローラ構造体
typedef struct {
	int cntFrame;

	int currentState;
	int prevState;
}GAMECONTROLLER;

//ゲームコントローラの各ステート
enum GAMECONTROLLER_STATE {
	GAMECONTROLLER_START,
	GAMECONTROLLER_STATEMAX
};
/**************************************
プロトタイプ宣言
***************************************/
void InitGameController(int num);
void UninitGameController(int num);
void UpdateGameController(void);
void DrawGameController(void);

//状態遷移処理
void ChangeStateGameController(int next);

//各入場処理
void EnterGameControllerStart(GAMECONTROLLER *entity);

//各更新処理
void UpdateGameControllerStart(GAMECONTROLLER *entity);

#endif