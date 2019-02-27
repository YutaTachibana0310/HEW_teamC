//=====================================
//
//�Q�[���V�[������[gameScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameScene.h"

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
HRESULT InitGameScene(int num)
{
	InitGameParameter(num);

	InitMeshCylinder(num);
	InitRainbowLane(num);
	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitGameScene(int num)
{
	UninitGameParameter(num);

	UninitMeshCylinder(num);
	UninitRainbowLane(num);
}

/**************************************
�X�V����
***************************************/
void UpdateGameScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();
}

/**************************************
�`�揈��
***************************************/
void DrawGameScene(int n)
{
	DrawMeshCylinder(n);
	DrawRainbowLane(n);
}
