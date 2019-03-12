//=======================================================================================================
//エフェクトの処理
//=======================================================================================================
#ifndef _SPEEDMETER_H_
#define _SPEEDMETER_H_

#include "main.h"

#define CIRCLE_MAX					(2)
#define METER_MAX					(2)
//*******************************************************************************************************
//構造体定義
//*******************************************************************************************************
typedef struct	// メーター構造体
{
	D3DXVECTOR3			pos;										// ポリゴンの移動量
	D3DXVECTOR3			rot;										// ポリゴンの回転量

	VERTEX_2D			vertexWk[NUM_VERTEX];						// 頂点情報格納ワーク
	LPDIRECT3DTEXTURE9	texture;									// テクスチャ情報
	VERTEX_2D			vertexWkSpeedMeter[NUM_VERTEX];				// 頂点情報格納ワーク	

	float				radius;										// 半径
	float				baseAngle;									// 角度
} METER;	
//*******************************************************************************************************
//プロトタイプ宣言
//*******************************************************************************************************
HRESULT InitSpeedGUI(void);
void UninitSpeedGUI(void);
void UpdateSpeedGUI(void);
void DrawSpeedGUI(void);

void SetVertexMeter(int meterID, float percent);
#endif