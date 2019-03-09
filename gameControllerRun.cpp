//=====================================
//
//�Q�[���R���g���[����������[gameControllerRun.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameController.h"

#include "gameParameter.h"
#include "scrollSpeedController.h"

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
	InitScrollSpeedController(0);
}

#include "input.h"
#include "player.h"
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
	if (GetKeyboardTrigger(DIK_K))
	{
		GetPlayer(0)->pos.z += 50.0f;
	}
	if (GetKeyboardTrigger(DIK_L))
	{
		GetPlayer(1)->pos.z += 50.0f;
	}

	//�v���C���[�̈ړ����������Z
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		param->playerMoveDist += param->playerSpeed;
	}

	//�Q�[���p�����[�^�̎��Ԃ����Z
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);

		if (param->isPlayerGoaled)
			continue;

		param->deltaTime += 1.0f / 60.0f;
	}

	//�v���C���[�������S�[��������X�e�[�g�J��
	if (CheckPlayerGoaled(0) && CheckPlayerGoaled(1))
	{
		ChangeStateGameController(GAMECONTROLLER_GOAL);
	}
}
