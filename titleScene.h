//=====================================
//
//タイトルシーンヘッダ[titleScene.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

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
HRESULT InitTitleScene(int num);
void UninitTitleScene(int num);
void UpdateTitleScene(void);
void DrawTitleScene(int i);

bool GetEntryState(int playerID);	//エントリー取得処理

#endif