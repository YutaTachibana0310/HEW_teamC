//=====================================
//
//�X�e�[�W�f�[�^����[stageData.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "stageData.h"
#include <stdio.h>

/**************************************
�}�N����`
***************************************/
#define STAGEDATA_FILE_PATH		"data/STAGE/stageData.dat"

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
	for (; currentIndex < dataMax && cntFrame < ptr->popFrame; ptr++, currentIndex++)
	{
		//�X�^�[����

		
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