//=====================================
//
//�^�C�g���V�[������[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "titleScene.h"
#include "input.h"
#include "sceneFade.h"

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
static bool entryState[TARGETPLAYER_MAX];	//�G���g���[���

/**************************************
�v���g�^�C�v�錾
***************************************/
bool IsCompleteEntry(void);		//�G���g���[�������菈��

/**************************************
����������
***************************************/
HRESULT InitTitleScene(int num)
{
	//�G���g���[��Ԃ�������
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		entryState[i] = false;
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
		entryState[i] = true;
	}

	//�e�X�g�@�\
	if (GetKeyboardTrigger(DIK_O))
		entryState[0] = true;
	if (GetKeyboardTrigger(DIK_P))
		entryState[1] = true;

	//�G���g���[������������V�[���J��
	if(IsCompleteEntry())
		SetSceneFade(GameScene);
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
bool GetEntryState(int playerID)
{
	return entryState[playerID];
}

/**************************************
�G���g���[�������菈��
***************************************/
bool IsCompleteEntry(void)
{
	if (!entryState[0])
		return false;

	if (!entryState[1])
		return false;

	return true;
}