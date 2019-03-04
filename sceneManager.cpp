//=====================================
//
//�V�[���}�l�[�W������[sceneManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "sceneManager.h"
#include "GUIManager.h"

#include "gameScene.h"
#include "titleScene.h"
#include "resultScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*SceneFunc)(void);			//�V�[���̊e�����̊֐��|�C���^��`
typedef HRESULT(*SceneInit)(int num);	//�V�[���̏����������̊֐��|�C���^��`
typedef void(*SceneUninit)(int num);	//�V�[���̏I�������̊֐��|�C���^��`
typedef void(*SceneDraw)(int n);		//�V�[���̕`�揈���̊֐��|�C���^��`

/**************************************
�O���[�o���ϐ�
***************************************/
static int* currentSceneId;
static int nextScene;

//�����������e�[�u��
static SceneInit Init[DefineSceneMax] = {
	InitGameScene,
	InitTitleScene,
	InitResultScene,
};

//�I�������e�[�u��
static SceneUninit Uninit[DefineSceneMax] = {
	UninitGameScene,
	UninitTitleScene,
	UninitResultScene
};

//�X�V�����e�[�u��
static SceneFunc Update[DefineSceneMax] = {
	UpdateGameScene,
	UpdateTitleScene,
	UpdateResultScene
};

//�`�揈���e�[�u��
static SceneDraw Draw[DefineSceneMax] = {
	DrawGameScene,
	DrawTitleScene,
	DrawResultScene
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitSceneManager(int* ptr)
{
	currentSceneId = ptr;
}

/**************************************
�ʃV�[������������
***************************************/
void InitScene(int num)
{
	Init[*currentSceneId](num);
}

/**************************************
�I������
***************************************/
void UninitSceneManager(int num)
{
	Uninit[*currentSceneId](num);
}

/**************************************
�ʃV�[���I������
***************************************/
void UninitScene(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateSceneManager(void)
{
	Update[*currentSceneId]();
}

/**************************************
�`�揈��
***************************************/
void DrawSceneManager(int n)
{
	Draw[*currentSceneId](n);
}

/**************************************
�V�[���Z�b�g����
***************************************/
void SetScene(DefineScene sceneId)
{
	nextScene = sceneId;

	//���݂̃V�[�����I��
	UninitScene(1);
	UninitGUIManager(*currentSceneId);

	//�V�[����؂�ւ�
	*currentSceneId = sceneId;

	//�V�[��������
	InitScene(1);
	InitGUIManager(*currentSceneId);
}

/**************************************
�l�N�X�g�V�[���擾����
***************************************/
int GetNextScene(void)
{
	return nextScene;
}