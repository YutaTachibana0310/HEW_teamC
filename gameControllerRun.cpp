//=====================================
//
//�Q�[���R���g���[����������[gameControllerRun.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameController.h"

#include "gameParameter.h"

/**************************************
�}�N����`
***************************************/
#define GAMECONTROLLER_RUN_STARTSPEED		(2.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
���ꏈ��
***************************************/
void EnterGameControllerRun(GAMECONTROLLER *entity)
{
	entity->cntFrame = 0;
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetSpeedGameParameter(i, GAMECONTROLLER_RUN_STARTSPEED);
	}
}

#include "input.h"
/**************************************
�X�V����
***************************************/
void UpdateGameControllerRun(GAMECONTROLLER *entity)
{
	//�e�X�g�p�@�\
	if (GetKeyboardPress(DIK_W))
	{
		GetGameParameterAdr(0)->playerSpeed += 0.05f;
	}
	if (GetKeyboardPress(DIK_E))
	{
		GetGameParameterAdr(1)->playerSpeed += 0.05f;
	}

	//�v���C���[�̈ړ����������Z
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		param->playerMoveDist += param->playerSpeed;
	}

	//�v���C���[�������S�[��������X�e�[�g�J��
	if (CheckPlayerGoaled(0) && CheckPlayerGoaled(1))
	{
		ChangeStateGameController(GAMECONTROLLER_GOAL);
	}
}
