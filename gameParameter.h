//=====================================
//
//ゲームパラメータヘッダ[gameParameter.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/
#define GAMEPARAMETER_MOVEDIST_MAX		(5000.0f)

/**************************************
構造体定義
***************************************/
typedef struct _GAMEPARAMETER{
	float playerSpeed;			//プレイヤーのスピード
	float playerMoveDist;		//プレイヤーの移動距離
	int score;					//現在のスコア
	float deltaTime;			//タイム
}GAMEPARAMETER;
/**************************************
プロトタイプ宣言
***************************************/
void InitGameParameter(int num);
void UninitGameParameter(int num);
void UpdateGameParameter(void);
void DrawGameParameter(void);
GAMEPARAMETER *GetGameParameterAdr(int n);

#endif