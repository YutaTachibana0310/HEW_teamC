//=====================================
//
//エントリーGUIヘッダ[entryGUI.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _ENTRYGUI_H_
#define _ENTRYGUI_H_

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
void InitEntryGUI(int num);
void UninitEntryGUI(int num);
void UpdateEntryGUI(void);
void DrawEntryGUI(void);

void SetEntryGUI(int playerID, bool isCompleted);

#endif