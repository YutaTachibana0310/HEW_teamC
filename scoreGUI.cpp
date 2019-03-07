//=============================================================================
//
// �v���C���[�o���b�g���� [scoreGUI.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "scoreGUI.h"
#include "dataContainer.h"
#include "debugWindow.h"
#include "numGUI.h"
#include "baseGUI.h"
#include "playerModel.h"
#include "Easing.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/
#define SCOREGUI_TEXTURE_NAME	_T("data/TEXTURE/UI/scoreGUI.png")		// UI�̃e�N�X�`��
#define SCOREGUI_TEXTURE_SIZE_X					(240)					// �e�N�X�`���T�C�YX
#define SCOREGUI_TEXTURE_SIZE_Y					(100)					// �e�N�X�`���T�C�YY
#define SCOREGUI_INITPOS						(D3DXVECTOR3(210.0f, 100.0f, 0.0f))

#define SCOREGUI_NUMTEX_SIZE_X					(30.0f)					// �����e�N�X�`���T�C�Y
#define SCOREGUI_NUMTEX_SIZE_Y					(40.0f)					// �����e�N�X�`���T�C�Y
#define SCOREGUI_NUM_OFFSETPOS					(-30.0f)				// �����̃I�t�Z�b�g���W
#define SCOREGUI_NUM_INITPOS					(D3DXVECTOR3(300.0f, 120.0f, 0.0f))	//�����e�N�X�`���̏������W

/*****************************************************************************
�v���g�^�C�v�錾
*****************************************************************************/

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static BaseGUI* back;
static float alpha;

/******************************************************************************
����������
******************************************************************************/
HRESULT InitScoreGUI(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		//�x�[�XGUI�C���X�^���X�쐬
		initialized = true;
		back = new BaseGUI((LPSTR)SCOREGUI_TEXTURE_NAME, SCOREGUI_TEXTURE_SIZE_X, SCOREGUI_TEXTURE_SIZE_Y);
	}

	alpha = 1.0f;
	return S_OK;
}

/******************************************************************************
�I������
******************************************************************************/
void UninitScoreGUI(int num)
{
	if (num == 0)
	{
		//�C���X�^���X���
		delete back;
	}
}

/******************************************************************************
�X�V����
******************************************************************************/
void UpdateScoreGUI(void)
{

}

/******************************************************************************
�`�揈��
******************************************************************************/
void DrawScoreGUI(float alpha)
{
	NumGUI* numGui = NumGUI::GetInstance();

	//�`��
	back->SetVertex(SCOREGUI_INITPOS);
	back->SetAlpha(alpha);
	back->Draw();

	//�X�R�A������`��
	int score = GetCurrentScore();
	int digitMax = (score == 0) ? 1 : (int)log10f((float)score) + 1;
	int num = 0;
	for (int i = 0; i < digitMax; i++, score /= 10)
	{
		num = score % 10;

		//���_���W��ݒ�
		D3DXVECTOR3 pos = SCOREGUI_NUM_INITPOS + D3DXVECTOR3(SCOREGUI_NUM_OFFSETPOS * i, 0.0f, 0.0f);
		numGui->SetVertex(pos, SCOREGUI_NUMTEX_SIZE_X, SCOREGUI_NUMTEX_SIZE_Y);

		// �e�N�X�`�����W��ݒ�
		numGui->SetTexture(num);

		// �|���S���̕`��
		numGui->Draw(NumScore);
	}
}
