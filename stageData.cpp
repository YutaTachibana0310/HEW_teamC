//=====================================
//
//�X�e�[�W�f�[�^����[stageData.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "stageData.h"
#include <stdio.h>
#include "rainbowLane.h"
#include "star.h"

/**************************************
�}�N����`
***************************************/
#define STAGEDATA_FILE_PATH		"data/STAGE/stageData.dat"
#define STAGEDATA_SETPOS_Z		(4000.0f)
#define STAGEDATA_SETPOS_MAX	(3)
#define STAGEDATA_SET_MOVEDIR	(D3DXVECTOR3(0.0f, 0.0f, -1.0f) * 20.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static STAGE_STARDATA *head;
static int dataMax;
static int cntFrame;
static int currentIndex;

static D3DXVECTOR3 setPos[STAGEDATA_SETPOS_MAX];
/**************************************
�v���g�^�C�v�錾
***************************************/
void LoadStageData(void);
void ReleaseStageData(void);

/**************************************
����������
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
�I������
***************************************/
void UninitStageData(int num)
{
	ReleaseStageData();
}

/**************************************
�X�V����
***************************************/
void UpdateStageData(void)
{
	if (currentIndex >= dataMax)
		return;

	cntFrame++;
	STAGE_STARDATA *ptr = &head[currentIndex];
	for (; currentIndex < dataMax && cntFrame >= ptr->popFrame; ptr++, currentIndex++)
	{
		//�X�^�[����
		SetStar(setPos[ptr->laneIndex], STAGEDATA_SET_MOVEDIR);
	}

}

/**************************************
�`�揈��
***************************************/
void DrawStageData(void)
{

}

/**************************************
���[�h����
***************************************/
void LoadStageData(void)
{
	FILE *fp = NULL;

	//�t�@�C���ǂݍ���
	fp = fopen(STAGEDATA_FILE_PATH, "r");
	if (fp == NULL)
	{
		dataMax = 0;
		return;
	}

	//�������m��
	int loadResult = fscanf(fp, "%d", &dataMax);
	if (loadResult == EOF)
		return;

	head = (STAGE_STARDATA*)malloc(sizeof(STAGE_STARDATA) * dataMax);
	ZeroMemory(head, sizeof(STAGE_STARDATA) * dataMax);

	//�f�[�^�ǂݍ���
	STAGE_STARDATA *ptr = head;
	int sumPopFrame = 0;
	for (int i = 0; i < dataMax; i++, ptr++)
	{
		fscanf(fp, "%d,%d", &ptr->popFrame, &ptr->laneIndex);
		ptr->popFrame += sumPopFrame;
		sumPopFrame = ptr->popFrame;
	}

	//�t�@�C���N���[�Y
	fclose(fp);
}

/**************************************
�����[�X����
***************************************/
void ReleaseStageData(void)
{
	free(head);
	head = NULL;
	dataMax = 0;
}