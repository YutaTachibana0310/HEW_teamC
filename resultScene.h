//=====================================
//
//リザルトシーンヘッダ[resultScene.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

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
HRESULT InitResultScene(int num);
void UninitResultScene(int num);
void UpdateResultScene(void);
void DrawResultScene(int n);

#endif