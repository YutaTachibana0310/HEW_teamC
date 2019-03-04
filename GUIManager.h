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
void UpdateGUIManager(int currentScene);
void DrawGUIManager(int currentScene);

//�e�V�[��GU����������
void InitGameSceneGUI(void);
void InitTitleSceneGUI(void);
void InitResultSceneGUI(void);

//�e�V�[��GUI�I������
void UninitGameSceneGUI(void);
void UninitTitleSceneGUI(void);
void UninitResultSceneGUI(void);

//�e�V�[��GUI�X�V����
void UpdateGameSceneGUI(void);
void UpdateTitleSceneGUI(void);
void UpdateResultSceneGUI(void);

//�e�V�[��GUI�`�揈��
void DrawGameSceneGUI(void);
void DrawTitleSceneGUI(void);
void DrawResultSceneGUI(void);

#endif