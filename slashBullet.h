//=====================================
//
//スラッシュバレットヘッダ[slashBullet.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _SLASHBULLET_H_
#define _SLASHBULLET_H_

#include "main.h"
#include "collider.h"
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
	D3DXVECTOR3 rot;
	int cntFrame;

	COLLIDER_CUBE collider;

	int parentPlayerID;

}SLASHBULLET;
/**************************************
プロトタイプ宣言
***************************************/
void InitSlashBullet(int num);
void UninitSlashBullet(int num);
void UpdateSlashBullet(void);
void DrawSlashBullet(void);
void SetSlashBullet(D3DXVECTOR3 pos, int playerID, float x, float y);
SLASHBULLET* GetSlashBulletAdr(int n);
#endif