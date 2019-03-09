//=====================================
//
//スクロールスピードコントローラヘッダ[scrollSpeedController.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _SCROLLSPEEDCONTROLLER_H_
#define _SCROLLSPEEDCONTROLLER_H_

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
void InitScrollSpeedController(int num);
void UpdateScrollSpeedController(void);
void SetTargetScrollSpeed(int playerID, float setSpeed);
#endif