//=====================================
//
//�^�C�g���V�[������[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "titleScene.h"
#include "input.h"

#include "meshCylinder.h"
#include "rainbowLane.h"
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
static bool isEntryCompleted[TARGETPLAYER_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitTitleScene(int num)
{
	//�G���g���[��Ԃ�������
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		isEntryCompleted[i] = false;
	}

	InitGameParameter(num);
	InitMeshCylinder(num);
	InitRainbowLane(num);
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitTitleScene(int num)
{
	UninitGameParameter(num);
	UninitMeshCylinder(num);
	UninitRainbowLane(num);
}

/**************************************
�X�V����
***************************************/
void UpdateTitleScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();

	//�G���g���[���o����
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		//NOTE : �|�[�Y�{�^���ƃX�^�[�g�{�^���͓���̃{�^��
		//�X�^�[�g�{�^���̓��͂��������continue
		if (!GetPauseButtonTrigger(i))
			continue;

		//���͂�����΃G���g���[������Ԃ֑J��
		isEntryCompleted[i] = true;
	}

	//�e�X�g�@�\
	if (GetKeyboardTrigger(DIK_O))
		isEntryCompleted[0] = true;
	if (GetKeyboardTrigger(DIK_P))
		isEntryCompleted[1] = true;
}

/**************************************
�`�揈��
***************************************/
void DrawTitleScene(int i)
{
	DrawMeshCylinder(i);
	DrawRainbowLane(i);
}

/**************************************
�G���g���[��Ԏ擾����
***************************************/
bool IsEntryCompleted(int playerID)
{
	return isEntryCompleted[playerID];
}