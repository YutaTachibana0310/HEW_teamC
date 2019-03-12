//=====================================
//
//ステージデータ処理[stageData.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "stageData.h"
#include <stdio.h>

/**************************************
マクロ定義
***************************************/
#define STAGEDATA_FILE_PATH		"data/STAGE/stageData.dat"

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
	for (; currentIndex < dataMax && cntFrame < ptr->popFrame; ptr++, currentIndex++)
	{
		//スター生成

		
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