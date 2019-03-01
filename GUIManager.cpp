//=====================================
//
//GUI�}�l�[�W������[GUIManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "GUIManager.h"
#include "sceneManager.h"
#include "Easing.h"
#include "debugWindow.h"

#include "progressGauge.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
typedef void(*FuncGUI)(void);

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void InitGUIManager(int num)
{
	InitProgressGauge(num);
}

/**************************************
�I������
***************************************/
void UninitGUIManager(int num)
{
	UninitProgressGauge(num);
}

/**************************************
�X�V����
***************************************/
void UpdateGUIManager(void)
{
	UpdateProgressGauge();
}

/**************************************
�`�揈��
***************************************/
void DrawGUIManager(int n)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	DrawProgressGauge();
}