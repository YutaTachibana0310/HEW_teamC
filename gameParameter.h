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
�\���̒�`
***************************************/
typedef struct _GAMEPARAMETER{
	float playerSpeed;			//�v���C���[�̃X�s�[�h
	float playerMoveDist;		//�v���C���[�̈ړ�����
	int score;					//���݂̃X�R�A
	float deltaTime;			//�^�C��
	bool isPlayerGoaled;		//�S�[�����Ă��邩�ǂ���
	int posOffset;				//����O�i/��ނ�����
}GAMEPARAMETER;

typedef struct {
	float currentProgress;
	int winnerID;
}SYSTEMPARAMETER;

/**************************************
�v���g�^�C�v�錾
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