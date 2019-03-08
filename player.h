//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : GP11A341 12 境野輝実
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "collider.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				// 現在の位置
	D3DXVECTOR3 move;				// 移動量
	D3DXVECTOR3 rot;				// 現在の向き
	D3DXVECTOR3 rotDest;			// 目的の向き
	float radius;					// 半径

	int prevLane;					// 前にいたレーンの番号
	int currentLane;				// 今いるレーンの番号
	int moveCntFrame;				// フレームカウント
	bool moveFlag;					// 移動フラグ

	float prevPosZ;					// 移動元の位置
	float currentPosZ;				// 移動先の位置
	int accelCntFrame;				// 加減速のフレームカウント
	bool accelerationFlag;			// 加減速フラグ

	COLLIDER_CUBE	collider;		// 当たり判定
	int				shotInterbal;	// ショットインターバル
} PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int num);

D3DXVECTOR3 GetPositionPlayer(int playerID);
D3DXVECTOR3 GetRotationPlayer(int playerID);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);

void SetPlayerAcceleration(int playerId, bool isAccelerator);

#endif
