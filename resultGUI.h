//=====================================
//
//���U���gGUI�w�b�_[resultGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _RESULTGUI_H_
#define _RESULTGUI_H_

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
void InitResultGUI(int num);
void UninitResultGUI(int num);
void UpdateResultGUI(void);
void DrawResultGUI(void);

void SetResultGUI(int playerID, bool isWinner);

#endif