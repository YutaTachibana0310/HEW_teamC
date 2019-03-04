//=====================================
//
//プログレスマーカーヘッダ[progressMarker.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _PROGRESSNARKER_H_
#define _PROGRESSNARKER_H_

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
void InitProgressMarker(int num);
void UninitProgressMarker(int num);
void UpdateProgressMarker(void);
void DrawProgressMarker(void);

void SetProgressMarker(int targetID, float percent);
#endif