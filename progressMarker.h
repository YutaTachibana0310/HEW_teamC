//=====================================
//
//�v���O���X�}�[�J�[�w�b�_[progressMarker.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PROGRESSNARKER_H_
#define _PROGRESSNARKER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitProgressMarker(int num);
void UninitProgressMarker(int num);
void UpdateProgressMarker(void);
void DrawProgressMarker(void);

void SetProgressMarker(int targetID, float percent);
#endif