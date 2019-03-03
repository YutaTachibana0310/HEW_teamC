//=====================================
//
//�^�C�g���V�[������[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "titleScene.h"

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

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitTitleScene(int num)
{
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
}

/**************************************
�`�揈��
***************************************/
void DrawTitleScene(int i)
{
	DrawMeshCylinder(i);
	DrawRainbowLane(i);
}
