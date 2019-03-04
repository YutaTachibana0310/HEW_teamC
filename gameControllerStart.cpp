//=====================================
//
//�Q�[���R���g���[���X�^�[�g����[gameControllerStart.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameController.h"

#include "countDownGUI.h"
#include "gameParameter.h"

/**************************************
�}�N����`
***************************************/
#define GAMECONTROLLER_START_DURATION		(180)
#define GAMECONTROLLER_START_SCROLLSPEED	(1.0f)
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
void EnterGameControllerStart(GAMECONTROLLER *entity)
{
	entity->cntFrame = 0;

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetSpeedGameParameter(i, GAMECONTROLLER_START_SCROLLSPEED);
	}

	SetCountDownGUI();
}

/**************************************
�X�V����
***************************************/
void UpdateGameControllerStart(GAMECONTROLLER *entity)
{
	entity->cntFrame++;

	//�^�C�~���O�������烌�[�X�J�n
	if (entity->cntFrame == GAMECONTROLLER_START_DURATION)
	{
		ChangeStateGameController(GAMECONTROLLER_RUN);
	}
}