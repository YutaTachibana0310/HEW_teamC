//=====================================
//
//スラッシュバレットヘッダ[slashBullet.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _SLASHBULLET_H_
#define _SLASHBULLET_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/
#define SLASHBULLET_NUM_MAX		(32)

/**************************************
構造体定義
***************************************/
typedef struct _SLASHBULLET {
	bool active;
	D3DXVECTOR3 pos;
	int cntFrame;

}SLASHBULLET;
/**************************************
プロトタイプ宣言
***************************************/
void InitSlashBullet(int num);
void UninitSlashBullet(int num);
void UpdateSlashBullet(void);
void DrawSlashBullet(void);

#endif