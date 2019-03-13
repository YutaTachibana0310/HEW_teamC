//=====================================
//
//���U���g�V�[��GUI����[resultSceneGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "GUIManager.h"

#include "resultGUI.h"
#include "resultTelop.h"
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
void InitResultSceneGUI(void)
{
	InitResultGUI(0);
	InitResultTelop(0);
}

/**************************************
�I������
***************************************/
void UninitResultSceneGUI(void)
{
	UninitResultGUI(0);
	UninitResultTelop(0);
}

/**************************************
�X�V����
***************************************/
void UpdateResultSceneGUI(void)
{
	UpdateResultGUI();
	UpdateResultTelop();
}

/**************************************
�`�揈��
***************************************/
void DrawResultSceneGUI(void)
{
	//���ʂ�`��
	int winner = CheckWinnerPlayer();
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		//TODO : �Q�[�����ʂ�GameParameter����擾���ăZ�b�g����
		SetResultGUI(i, i == winner);
		DrawResultGUI();
	}

	//�������͂��҂傤��`��
	DrawResultTelop();
}
