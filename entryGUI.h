//=====================================
//
//�G���g���[GUI�w�b�_[entryGUI.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _ENTRYGUI_H_
#define _ENTRYGUI_H_

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
void InitEntryGUI(int num);
void UninitEntryGUI(int num);
void UpdateEntryGUI(void);
void DrawEntryGUI(void);

void SetEntryGUI(int playerID, bool isCompleted);

#endif