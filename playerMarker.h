//=====================================
//
//プレイヤーマーカーヘッダ[playerMarker.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _PLAYERMARKER_H_
#define _PLAYERMARKER_H_

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
void InitPlayerMarker(int num);
void UninitPlayerMarker(int num);
void UpdatePlayerMarker(void);
void DrawPlayerMarker(void);

void SetPlayerMarker(int playerID, D3DXVECTOR3 pos);

#endif