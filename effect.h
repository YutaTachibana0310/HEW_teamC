//=======================================================================================================
//エフェクトの処理
//=======================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*******************************************************************************************************
//マクロ定義
//*******************************************************************************************************
#define TEXTURE_EFFECT		 "data/TEXTURE/EFFECT/effect000.jpg"		//テクスチャファイルの読み込み
#define EFFECT_MAX			 (525)										//エフェクトの最大数
#define EFFECT_SIZE_X		 (20.0f)									//テクスチャのXサイズ
#define EFFECT_SIZE_Y		 (20.0f)									//テクスチャのYサイズ

#define VALUE_MOVE_EFFECT    (2.0f)										//移動速度

#define MOVE_SPEED			 (0.75f)									//移動

#define EFFECT_RADIUS		 (0.015f)									//半径
#define EFFECT_LIFE			 (80)										//エフェクトのライフ
//*******************************************************************************************************
//構造体定義
//*******************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//エフェクトの位置
	D3DXVECTOR3 rot;			//エフェクトの回転
	D3DXVECTOR3	scl;			//エフェクトの大きさ
	D3DXVECTOR3 move;			//エフェクトの移動

	D3DXCOLOR col;				//エフェクトの色

	float sizeX;				//エフェクトのX軸の大きさ
	float sizeY;				//エフェクトのY軸の大きさ

	int life;					//ライフ
	int timer;					//時間
	bool use;					//使用しているか
}EFFECT;

//*******************************************************************************************************
//プロトタイプ宣言
//*******************************************************************************************************
HRESULT InitEffect(void);										//エフェクトの初期化処理
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 Device);				//エフェクトの頂点座標
	
void DrawEffect(void);											//エフェクトの描画処理
void UpdateEffect(void);										//エフェクトの更新処理
void UninitEffect(void);										//エフェクトの終了処理

void SetVertexEffect(int IdxEffect, float sizeX, float sizeY);  //エフェクトの頂点のセット
void SetColorEffect(int IdxEffect, D3DXCOLOR col);				//エフェクトのカラーセット

static int SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float sizeX, float sizeY, int timer);
#endif