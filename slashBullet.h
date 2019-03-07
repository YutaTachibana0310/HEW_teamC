//=====================================
//
//�X���b�V���o���b�g�w�b�_[slashBullet.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SLASHBULLET_H_
#define _SLASHBULLET_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/
#define SLASHBULLET_NUM_MAX		(32)

/**************************************
�\���̒�`
***************************************/
typedef struct _SLASHBULLET {
	bool active;
	D3DXVECTOR3 pos;
	int cntFrame;

}SLASHBULLET;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSlashBullet(int num);
void UninitSlashBullet(int num);
void UpdateSlashBullet(void);
void DrawSlashBullet(void);

#endif