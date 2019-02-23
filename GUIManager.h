//=====================================
//
//GUI�}�l�[�W���w�b�_[GUIManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
enum GUI_NUMTEXTURE
{
	GUI_NUMSCORE,
	GUI_NUMLOCKON,
	GUI_NUMBONUSTIME,
	GUI_NUMRANKING,
	GUI_NUMTEX_MAX
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitGUIManager(int num);
void UninitGUIManager(int num);
void UpdateGUIManager(void);
void DrawGUIManager(void);
void DrawGUINum(GUI_NUMTEXTURE textureID, int num, VERTEX_2D *vtxWk);
#endif