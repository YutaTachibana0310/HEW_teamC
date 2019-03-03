//=====================================
//
//GUI�}�l�[�W������[GUIManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "GUIManager.h"
#include "sceneManager.h"
#include "Easing.h"
#include "debugWindow.h"
#include "gameParameter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*FuncGUI)(void);

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
//�����������e�[�u��
static FuncGUI Init[DefineSceneMax] = {
	InitGameSceneGUI,
	InitTitleSceneGUI,
};

//�I�������e�[�u��
static FuncGUI Uninit[DefineSceneMax] = {
	UninitGameSceneGUI,
	UninitTitleSceneGUI
};

//�X�V�����e�[�u��
static FuncGUI Update[DefineSceneMax] = {
	UpdateGameSceneGUI,
	UpdateTitleSceneGUI,
};

//�`�揈���e�[�u��
static FuncGUI Draw[DefineSceneMax] = {
	DrawGameSceneGUI,
	DrawTitleSceneGUI
};

/**************************************
����������
***************************************/
void InitGUIManager(int currentScene)
{
	Init[currentScene]();
}

/**************************************
�I������
***************************************/
void UninitGUIManager(int currentScene)
{
	Uninit[currentScene]();
}

/**************************************
�X�V����
***************************************/
void UpdateGUIManager(int currentScene)
{
	Update[currentScene]();
}

/**************************************
�`�揈��
***************************************/
void DrawGUIManager(int currentScene)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetFVF(FVF_VERTEX_2D);

	Draw[currentScene]();
}
