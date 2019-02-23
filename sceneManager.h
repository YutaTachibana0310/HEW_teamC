//=====================================
//
//�V�[���}�l�[�W���w�b�_[sceneManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
enum DefineScene
{
	LogoScene = 0,
	TitleScene,
	BattleScene,
	ResultScene,
	TutorialScene,
	GamveoverScene,
	StageClearScene,
	NameEntryScene,
	DefineSceneMax
};

enum SceneResult
{
	SceneRunning,
	SceneFinished,
	SceneResultMax
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitSceneManager(int* ptr);
void UninitSceneManager(int num);
void UninitScene(int num);
void UpdateSceneManager(void);
void DrawSceneManager(void);
void SetScene(DefineScene sceneId);
int GetNextScene(void);
#endif