//=====================================
//
//リザルトGUIヘッダ[resultGUI.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _RESULTGUI_H_
#define _RESULTGUI_H_

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
void InitResultGUI(int num);
void UninitResultGUI(int num);
void UpdateResultGUI(void);
void DrawResultGUI(void);

void SetResultGUI(int playerID, bool isWinner);

#endif