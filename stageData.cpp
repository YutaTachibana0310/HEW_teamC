//=====================================
//
//ステージデータ処理[stageData.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "stageData.h"
#include <stdio.h>
#include "rainbowLane.h"
#include "star.h"

/**************************************
マクロ定義
***************************************/
#define STAGEDATA_FILE_PATH		"data/STAGE/stageData.dat"
#define STAGEDATA_SETPOS_Z		(4000.0f)
#define STAGEDATA_SETPOS_MAX	(3)
#define STAGEDATA_SET_MOVEDIR	(D3DXVECTOR3(0.0f, 0.0f, -1.0f) * 20.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static STAGE_STARDATA *head;
static int dataMax;
static int cntFrame;
static int currentIndex;

static D3DXVECTOR3 setPos[STAGEDATA_SETPOS_MAX];
/**************************************
プロトタイプ宣言
***************************************/
void LoadStageData(void);
void ReleaseStageData(void);

/**************************************
初期化処理
***************************************/
void InitStageData(int num)
{
	LoadStageData();

	cntFrame = 0;
	currentIndex = 0;

	for (int i = 0; i < STAGEDATA_SETPOS_MAX; i++)
	{
		setPos[i] = GetLanePos(i);
		setPos[i].z = STAGEDATA_SETPOS_Z;
	}
}

/**************************************
終了処理
***************************************/
void UninitStageData(int num)
{
	ReleaseStageData();
}

/**************************************
更新処理
***************************************/
void UpdateStageData(void)
{
	if (currentIndex >= dataMax)
		return;

	cntFrame++;
	STAGE_STARDATA *ptr = &head[currentIndex];
	for (; currentIndex < dataMax && cntFrame >= ptr->popFrame; ptr++, currentIndex++)
	{
		//スター生成
		SetStar(setPos[ptr->laneIndex], STAGEDATA_SET_MOVEDIR);
	}

}

/**************************************
描画処理
***************************************/
void DrawStageData(void)
{

}

/**************************************
ロード処理
***************************************/
void LoadStageData(void)
{
	FILE *fp = NULL;

	//ファイル読み込み
	fp = fopen(STAGEDATA_FILE_PATH, "r");
	if (fp == NULL)
	{
		dataMax = 0;
		return;
	}

	//メモリ確保
	int loadResult = fscanf(fp, "%d", &dataMax);
	if (loadResult == EOF)
		return;

	head = (STAGE_STARDATA*)malloc(sizeof(STAGE_STARDATA) * dataMax);
	ZeroMemory(head, sizeof(STAGE_STARDATA) * dataMax);

	//データ読み込み
	STAGE_STARDATA *ptr = head;
	int sumPopFrame = 0;
	for (int i = 0; i < dataMax; i++, ptr++)
	{
		fscanf(fp, "%d,%d", &ptr->popFrame, &ptr->laneIndex);
		ptr->popFrame += sumPopFrame;
		sumPopFrame = ptr->popFrame;
	}

	//ファイルクローズ
	fclose(fp);
}

/**************************************
リリース処理
***************************************/
void ReleaseStageData(void)
{
	free(head);
	head = NULL;
	dataMax = 0;
}