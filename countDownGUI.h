//=====================================
//
//カウントダウンGUIヘッダ[countDownGUI.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _COUNTDOWNGUI_H_
#define _COUNTDOWNGUI_H_

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
void InitCountDownGUI(int num);
void UninitCountDownGUI(int num);
void UpdateCountDownGUI(void);
void DrawCountDownGUI(void);

void SetCountDownGUI(void);

#endif