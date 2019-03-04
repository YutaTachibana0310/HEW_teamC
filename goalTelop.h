//=====================================
//
//ゴールテロップヘッダ[goalTelop.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _GOALTELOP_H_
#define _GOALTELOP_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void InitGoalTelop(int num);
void UninitGoalTelop(int num);
void UpdateGoalTelop(void);
void DrawGoalTelop(int i);
void SetGoalTelop(int playerID);
#endif