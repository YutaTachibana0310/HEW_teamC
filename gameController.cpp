//=====================================
//
//�Q�[���R���g���[������[gameController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*FuncGameController)(GAMECONTROLLER *entity);

/**************************************
�O���[�o���ϐ�
***************************************/
static GAMECONTROLLER controller;

//���ꏈ���e�[�u��
static FuncGameController OnEnter[GAMECONTROLLER_STATEMAX] = {
	EnterGameControllerStart
};

//�X�V�����e�[�u��
static FuncGameController OnUpdate[GAMECONTROLLER_STATEMAX] = {
	UpdateGameControllerStart
};

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitGameController(int num)
{
	//�X�^�[�g��Ԃ���J�n
	controller.currentState = GAMECONTROLLER_START;
	ChangeStateGameController(controller.currentState);
}

/**************************************
�I������
***************************************/
void UninitGameController(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateGameController(void)
{
	OnUpdate[controller.currentState](&controller);
}

/**************************************
�`�揈��
***************************************/
void DrawGameController(void)
{

}

/**************************************
��ԑJ�ڏ���
***************************************/
void ChangeStateGameController(int next)
{
	//�J�ڑO�̃X�e�[�g���L��
	controller.prevState = controller.currentState;

	//�X�e�[�g��J��
	controller.currentState = next;

	//�J�ڂ����X�e�[�g�̓��ꏈ�������s
	OnEnter[controller.currentState](&controller);
}