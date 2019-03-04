//=====================================
//
//���U���g�V�[������[resulScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "resultScene.h"
#include "gameParameter.h"
#include "sceneFade.h"

#include "meshCylinder.h"
#include "rainbowLane.h"

/**************************************
�}�N����`
***************************************/
#define RESULTSCENE_DURATION		(300)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitResultScene(int num)
{
	cntFrame = 0;

	InitMeshCylinder(num);
	InitRainbowLane(num);
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitResultScene(int num)
{
	UninitMeshCylinder(num);
	UninitRainbowLane(num);
}

/**************************************
�X�V����
***************************************/
void UpdateResultScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();

	cntFrame++;
	if (cntFrame == RESULTSCENE_DURATION)
	{
		SetSceneFade(TitleScene);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawResultScene(int n)
{
	DrawMeshCylinder(n);
	DrawRainbowLane(n);
}
