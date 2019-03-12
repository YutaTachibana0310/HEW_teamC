//=====================================
//
//�X���b�V���o���b�g�w�b�_[slashBullet.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SLASHBULLET_H_
#define _SLASHBULLET_H_

#include "main.h"
#include "collider.h"
/**************************************
�}�N����`
***************************************/
#define SLASHBULLET_NUM_MAX		(32)
#define SLASHBULLET_MOVE_BORDER_Z		(1250.0f)


/**************************************
�\���̒�`
***************************************/
typedef struct _SLASHBULLET {
	bool active;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int cntFrame;

	COLLIDER_CUBE collider;

	int parentPlayerID;

}SLASHBULLET;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSlashBullet(int num);
void UninitSlashBullet(int num);
void UpdateSlashBullet(void);
void DrawSlashBullet(void);
int	 SetSlashBullet(D3DXVECTOR3 pos, int playerID, float x, float y);
void SetSlashBulletPos(D3DXVECTOR3 pos, int bulletID);

SLASHBULLET* GetSlashBulletAdr(int n);
#endif