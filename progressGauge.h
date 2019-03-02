//=====================================
//
//進行ゲージヘッダ[progressGauge.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _PROGRESSGAUGE_H_
#define _PROGRESSGAUGE_H_

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
void InitProgressGauge(int num);
void UninitProgressGauge(int num);
void UpdateProgressGauge(void);
void DrawProgressGauge(void);

#endif