//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 李尚ミン 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "collider.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BULLET			_T("data/TEXTURE/shadow000.jpg")	// 読み込むテクスチャファイル名
#define	BULLET_POS_X			(SCREEN_CENTER_X)					// タイトルの表示位置
#define	BULLET_POS_Y			(SCREEN_CENTER_Y)					// タイトルの表示位置
#define	BULLET_SIZE_X			(50)								// タイトルの幅
#define	BULLET_SIZE_Y			(50)								// タイトルの高さ
#define BULLET_SIZE				(25.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	PLANE	range;
	float	length;
	bool	use;
	int		idxSlashBullet;
	COLLIDER_CUBE collider;
}BULLET;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UpdateBullet(void);
bool GetAttackTrigger(int playerNo);
void FreeSlashBullet(int bulletID);

BULLET *GetBulletAdr(int playerNo, int id);

#endif
