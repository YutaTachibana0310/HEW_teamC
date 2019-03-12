//=====================================
//
//�S�[���e�[�v�w�b�_[goalTape.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _GOALTAPE_H_
#define _GOALTAPE_H_

#include "main.h"
#include "collider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef struct {
	D3DXVECTOR3 pos;
	COLLIDER_CUBE collider;
}GOALTAPE;
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitGoalTape(int num);
void UninitGoalTape(int num);
void UpdateGoalTape(void);
void DrawGoalTape(void);
GOALTAPE *GetGoalTapeAdr(void);
#endif