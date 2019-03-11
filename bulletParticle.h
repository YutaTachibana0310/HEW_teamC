//=====================================
//
//�o���b�g�p�[�e�B�N���w�b�_[bulletParticle.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _BULLETPARTICLE_H_
#define _BULLETPARTICLE_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	bool active;
	D3DXVECTOR3 pos;
	int cntFrame;
	int lifeFrame;
	D3DXVECTOR3 moveDir;
	float initSpeed;
}BULLETPARTICLE;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitBulletParticle(int num);
void UninitBulletParticle(int num);
void UpdateBulletParticle(void);
void DrawBulletParticle(void);
void SetBulletParticle(D3DXVECTOR3 pos);
#endif