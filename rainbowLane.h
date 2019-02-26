//=====================================
//
//レインボーレーンヘッダ[rainbowLane.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _RAINBOWLANE_H_
#define _RAINBOWLANE_H_

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
void InitRainbowLane(int num);
void UninitRainbowLane(int num);
void UpdateRainbowLane(void);
void DrawRainbowLane(void);

#endif