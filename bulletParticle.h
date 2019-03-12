//=====================================
//
//バレットパーティクルヘッダ[bulletParticle.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _BULLETPARTICLE_H_
#define _BULLETPARTICLE_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
typedef struct {
	bool active;
	D3DXVECTOR3 pos;
	int cntFrame;
	int lifeFrame;
	D3DXVECTOR3 moveDir;
	float initSpeed;
}BULLETPARTICLE;
/**************************************
プロトタイプ宣言
***************************************/
void InitBulletParticle(int num);
void UninitBulletParticle(int num);
void UpdateBulletParticle(void);
void DrawBulletParticle(void);
void SetBulletParticle(D3DXVECTOR3 pos);
#endif