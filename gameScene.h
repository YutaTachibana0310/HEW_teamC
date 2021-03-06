//=====================================
//
//ゲームシーンヘッダ[gameScene.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

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
HRESULT InitGameScene(int num);
void UninitGameScene(int num);
void UpdateGameScene(void);
void DrawGameScene(int n);

#endif