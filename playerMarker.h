//=====================================
//
//�v���C���[�}�[�J�[�w�b�_[playerMarker.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERMARKER_H_
#define _PLAYERMARKER_H_

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
void InitPlayerMarker(int num);
void UninitPlayerMarker(int num);
void UpdatePlayerMarker(void);
void DrawPlayerMarker(void);

void SetPlayerMarker(int playerID, D3DXVECTOR3 pos);

#endif