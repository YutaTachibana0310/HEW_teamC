//=====================================
//
//�Q�[���R���g���[���S�[������[gameControllerGoal.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameController.h"

#include "sceneFade.h"

/**************************************
�}�N����`
***************************************/
#define GAMECONTROLLER_GOAL_DURATION		(180)

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
void EnterGameControllerGoal(GAMECONTROLLER *entity)
{
	entity->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void UpdateGameControllerGoal(GAMECONTROLLER *entity)
{
	entity->cntFrame++;

	if(entity->cntFrame == GAMECONTROLLER_GOAL_DURATION)
	{
		SetSceneFade(ResultScene);
	}
}