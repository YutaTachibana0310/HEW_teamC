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

/**************************************
構造体定義
***************************************/
typedef struct {
	float speed;		//プレイヤーのスピード

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