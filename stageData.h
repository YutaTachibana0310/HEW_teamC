//=====================================
//
//�X�e�[�W�f�[�^�w�b�_[stageData.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _STAGEDATA_H_
#define _STAGEDATA_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	int popFrame;
	int laneIndex;
}STAGE_STARDATA;

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitStageData(int num);
void UninitStageData(int num);
void UpdateStageData(void);
void DrawStageData(void);

#endif