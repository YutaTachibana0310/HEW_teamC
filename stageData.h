//=====================================
//
//ステージデータヘッダ[stageData.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _STAGEDATA_H_
#define _STAGEDATA_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef struct {
	int popFrame;
	int laneIndex;
}STAGE_STARDATA;

/**************************************
プロトタイプ宣言
***************************************/
void InitStageData(int num);
void UninitStageData(int num);
void UpdateStageData(void);
void DrawStageData(void);

#endif