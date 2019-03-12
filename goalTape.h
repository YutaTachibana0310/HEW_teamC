//=====================================
//
//ゴールテープヘッダ[goalTape.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _GOALTAPE_H_
#define _GOALTAPE_H_

#include "main.h"
#include "collider.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef struct {
	D3DXVECTOR3 pos;
	COLLIDER_CUBE collider;
}GOALTAPE;
/**************************************
プロトタイプ宣言
***************************************/
void InitGoalTape(int num);
void UninitGoalTape(int num);
void UpdateGoalTape(void);
void DrawGoalTape(void);
GOALTAPE *GetGoalTapeAdr(void);
#endif