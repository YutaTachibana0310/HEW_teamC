//=====================================
//
//�Q�[���p�����[�^�w�b�_[gameParameter.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPARAMETER_H_
#define _GAMEPARAMETER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct _GAMEPARAMETER{
	float playerSpeed;			//�v���C���[�̃X�s�[�h
	float playerMoveDist;		//�v���C���[�̈ړ�����

}GAMEPARAMETER;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitGameParameter(int num);
void UninitGameParameter(int num);
void UpdateGameParameter(void);
void DrawGameParameter(void);
GAMEPARAMETER *GetGameParameterAdr(int n);

#endif