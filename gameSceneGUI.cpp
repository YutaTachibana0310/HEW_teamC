//=====================================
//
//�o�g���V�[��GUI����[gameSceneGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "GUIManager.h"

#include "progressGauge.h"
#include "progressMarker.h"
#include "gameParameter.h"
#include "score.h"
#include "countDownGUI.h"
#include "goalTelop.h"
#include "speedMeter.h"
#include "timeGUI.h"

/**************************************
�}�N����`
***************************************/

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
����������
***************************************/
void InitGameSceneGUI(void)
{
	InitProgressGauge(0);
	InitProgressMarker(0);
	InitScore(0);
	InitCountDownGUI(0);
	InitGoalTelop(0);
	InitSpeedGUI();
	InitTimeGUI(0);
}

/**************************************
�I������
***************************************/
void UninitGameSceneGUI(void)
{
	UninitProgressGauge(0);
	UninitProgressMarker(0);
	UninitScore(0);
	UninitCountDownGUI(0);
	UninitGoalTelop(0);
<<<<<<< HEAD
	UninitSpeedGUI();
=======
	UninitTimeGUI(0);
>>>>>>> 5dc48cf3603ec8189f0331076ac436f9843a63d5
}

/**************************************
�X�V����
***************************************/
void UpdateGameSceneGUI(void)
{
	UpdateProgressGauge();
	UpdateProgressMarker();
	UpdateScore();
	UpdateCountDownGUI();
	UpdateGoalTelop();
	UpdateSpeedGUI();
	UpdateTimeGUI();
}

/**************************************
�`�揈��
***************************************/
void DrawGameSceneGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	//�v���O���X�Q�[�W�`��
	DrawProgressGauge();

	//�v���O���X�}�[�J�[�`��
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float progress = param->playerMoveDist / GAMEPARAMETER_MOVEDIST_MAX;
		SetProgressMarker(i, progress);
		DrawProgressMarker();
	}

	//�X�s�[�h���[�^�[�`��
	for (int i = 0; i < METER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		float meter = param->playerSpeed / 5;
		SetVertexMeter(i, meter);
		DrawSpeedGUI();
	}

	//�X�R�A�̕`��
	int score1P = GetGameParameterAdr(0)->score;
	int score2P = GetGameParameterAdr(1)->score;
	DrawScore(score1P, score2P);

	//�J�E���g�_�E��GUI��`��
	DrawCountDownGUI();

	//�S�[���e���b�v��`��
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);

		//�v���C���[���S�[���O�Ȃ�continue
		if (!param->isPlayerGoaled)
			continue;

		DrawGoalTelop(i);
	}

	//�^�C��GUI��`��
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		DrawTimeGUI(GetGameParameterAdr(0)->deltaTime, GetGameParameterAdr(1)->deltaTime);
	}
}
