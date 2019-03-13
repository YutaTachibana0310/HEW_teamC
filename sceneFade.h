//=====================================
//
//�V�[���t�F�[�h�w�b�_[sceneFade.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SCENEFADE_H_
#define _SCENEFADE_H_

#include "main.h"
#include "sceneManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
enum SceneFadeState
{
	SceneFadeIn,
	SceneFadeWait,
	SceneFadeOut,
	SceneFadeNone,
	SceneFadeStateMax
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSceneFade(int num);
void UninitSceneFade(int num);
void UpdateSceneFade(void);
void DrawSceneFade(void);

void ChangeStateSceneFade(SceneFadeState state);
bool SetSceneFade(DefineScene next);
#endif