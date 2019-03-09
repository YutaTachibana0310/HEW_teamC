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
#include "countDownGUI.h"
#include "goalTelop.h"
#include "speedMeter.h"
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
	InitCountDownGUI(0);
	InitGoalTelop(0);
	InitSpeedGUI();
}

/**************************************
�I������
***************************************/
void UninitGameSceneGUI(void)
{
	UninitProgressGauge(0);
	UninitProgressMarker(0);
	UninitCountDownGUI(0);
	UninitGoalTelop(0);
	UninitSpeedGUI();
}

/**************************************
�X�V����
***************************************/
void UpdateGameSceneGUI(void)
{
	UpdateProgressGauge();
	UpdateProgressMarker();
	UpdateCountDownGUI();
	UpdateGoalTelop();
	UpdateSpeedGUI();
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
}
