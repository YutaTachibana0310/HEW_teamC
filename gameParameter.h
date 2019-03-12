//=====================================
//
//ゲームパラメータヘッダ[gameParameter.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/
//#define GAMEPARAMETER_MOVEDIST_MAX		(500.0f)
#define GAMEPARAMETER_MOVEDIST_MAX		(2000.0f)

#define GAMEPARAMETER_SPEED_MIN			(0.5f)
#define GAMEPARAMETER_SPEED_MAX			(5.0f)
#define GAMEPARAMETER_SPEED_ADDVALUE	(0.3f)
#define GAMEPARAMETER_SPEED_DECLVALUE	(-0.3f)

#define SYSTEMPARAMTER_VALUE_MAGNI		(20.0f)
#define SYSTEMPARAMETER_PROGRESS_VALUE	(1.0f*SYSTEMPARAMTER_VALUE_MAGNI)
#define SYSTEMPARAMETER_PROGRESS_MAX	(60*60.0f*SYSTEMPARAMTER_VALUE_MAGNI)

/**************************************
構造体定義
***************************************/
typedef struct _GAMEPARAMETER{
	float playerSpeed;			//プレイヤーのスピード
	float playerMoveDist;		//プレイヤーの移動距離
	int score;					//現在のスコア
	float deltaTime;			//タイム
	bool isPlayerGoaled;		//ゴールしているかどうか
	int posOffset;				//何回前進/後退したか
}GAMEPARAMETER;

typedef struct {
	float currentProgress;
	int winnerID;
}SYSTEMPARAMETER;

/**************************************
プロトタイプ宣言
***************************************/
void InitGameParameter(int num);
void UninitGameParameter(int num);
void UpdateGameParameter(void);
void DrawGameParameter(void);
GAMEPARAMETER *GetGameParameterAdr(int n);
void SetSpeedGameParameter(int id, float speed);
bool CheckPlayerGoaled(int id);
SYSTEMPARAMETER *GetSystemParameterAdr(void);
#endif