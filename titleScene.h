//=====================================
//
//�^�C�g���V�[���w�b�_[titleScene.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

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
HRESULT InitTitleScene(int num);
void UninitTitleScene(int num);
void UpdateTitleScene(void);
void DrawTitleScene(int i);

bool GetEntryState(int playerID);	//�G���g���[�擾����

#endif