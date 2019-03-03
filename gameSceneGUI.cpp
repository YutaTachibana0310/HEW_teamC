//=====================================
//
//�o�g���V�[��GUI����[battleSceneGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "GUIManager.h"

#include "progressGauge.h"
#include "progressMarker.h"
#include "gameParameter.h"

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
}

/**************************************
�I������
***************************************/
void UninitGameSceneGUI(void)
{
	UninitProgressGauge(0);
	UninitProgressMarker(0);
}

/**************************************
�X�V����
***************************************/
void UpdateGameSceneGUI(void)
{
	UpdateProgressGauge();
	UpdateProgressMarker();
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
}
