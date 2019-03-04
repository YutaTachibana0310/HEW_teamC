//=====================================
//
//�Q�[���R���g���[���X�^�[�g����[gameControllerStart.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameController.h"

#include "countDownGUI.h"
/**************************************
�}�N����`
***************************************/
#define GAMECONTROLLER_START_DURATION	(240)

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