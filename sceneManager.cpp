//=====================================
//
//�V�[���}�l�[�W������[sceneManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "sceneManager.h"
#include "GUIManager.h"

#include "gameScene.h"


/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*SceneFunc)(void);			//�V�[���̊e�����̊֐��|�C���^��`
typedef HRESULT(*SceneInit)(int num);	//�V�[���̏����������̊֐��|�C���^��`
typedef void(*SceneUninit)(int num);	//�V�[���̏I�������̊֐��|�C���^��`

/**************************************
�O���[�o���ϐ�
***************************************/
static int* currentSceneId;
static int nextScene;

//�����������e�[�u��
static SceneInit Init[DefineSceneMax] = {
	InitGameScene,
};

//�I�������e�[�u��
static SceneUninit Uninit[DefineSceneMax] = {
	UninitGameScene,
};

//�X�V�����e�[�u��
static SceneFunc Update[DefineSceneMax] = {
	UpdateGameScene,
};

//�`�揈���e�[�u��
static SceneFunc Draw[DefineSceneMax] = {
	DrawGameScene
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitSceneManager(int* ptr)
{

	/*for (int i = 0; i < DefineSceneMax; i++)
	{
		Init[i](num);
	}*/

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
void DrawSceneManager(void)
{
	Draw[*currentSceneId]();
}

/**************************************
�V�[���Z�b�g����
***************************************/
void SetScene(DefineScene sceneId)
{
	nextScene = sceneId;
	UninitScene(1);
	*currentSceneId = sceneId;
	//InitGUIManager(1);
	InitScene(1);
}

/**************************************
�l�N�X�g�V�[���擾����
***************************************/
int GetNextScene(void)
{
	return nextScene;
}