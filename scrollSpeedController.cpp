//=====================================
//
//�X�N���[���X�s�[�h�R���g���[������[scrollSpeedController.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "scrollSpeedController.h"

#include "gameParameter.h"

/**************************************
�}�N����`
***************************************/
#define SCROLLSPEEDCONTROLLER_DELTA_VALUE	(0.8f)
#define SCROLLSPEEDCONTROLLER_DELTA_MAX		(0.5f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static float targetSpeed[TARGETPLAYER_MAX];
static int cntFrame[TARGETPLAYER_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitScrollSpeedController(int num)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		targetSpeed[i] = GetGameParameterAdr(i)->playerSpeed;
	}
}

/**************************************
�X�V����
***************************************/
void UpdateScrollSpeedController(void)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float diff = targetSpeed[i] - param->playerSpeed;
		float setSpeed = Clampf(-SCROLLSPEEDCONTROLLER_DELTA_MAX, SCROLLSPEEDCONTROLLER_DELTA_MAX, diff * SCROLLSPEEDCONTROLLER_DELTA_VALUE);
		param->playerSpeed = setSpeed;

		cntFrame[i]++;
		if (cntFrame[i] == 30)
		{
			targetSpeed[i] = 2.0f;
		}
	}
}

/**************************************
�^�[�Q�b�g�X�s�[�h�Z�b�g����
***************************************/
void SetTargetScrollSpeed(int playerID, float targetSpeed)
{

}