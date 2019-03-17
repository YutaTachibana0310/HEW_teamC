//=====================================
//
//�V�[���t�F�[�h����[sceneFade.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "sceneFade.h"

/**************************************
�}�N����`
***************************************/
#define SCENEFADE_INOUT_DURATION		(60)
#define SCENEFADE_WAIT_DURATION			(30)

/**************************************
�\���̒�`
***************************************/
typedef void(*funcSceneFade)(void);

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexSceneFade(void);
void SetDiffuseSceneFade(float alpha);

void UpdateSceneFadeIn(void);
void UpdateSceneFadeWait(void);
void UpdateSceneFadeOut(void);
void UpdateSceneFadeNone(void);

/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static int cntFrame;
static DefineScene nextScene;
static SceneFadeState currentState;

//�X�V�����̊֐��e�[�u��
static funcSceneFade Update[SceneFadeStateMax]
{
	UpdateSceneFadeIn,
	UpdateSceneFadeWait,
	UpdateSceneFadeOut,
	UpdateSceneFadeNone
};

/**************************************
����������
***************************************/
void InitSceneFade(int num)
{
	MakeVertexSceneFade();
	ChangeStateSceneFade(SceneFadeNone);
}

/**************************************
�I������
***************************************/
void UninitSceneFade(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateSceneFade(void)
{
	Update[currentState]();
}

/**************************************
�`�揈��
***************************************/
void DrawSceneFade(void)
{
	if (currentState == SceneFadeNone)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, NULL);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
�t�F�[�h��ԕύX����
***************************************/
void ChangeStateSceneFade(SceneFadeState state)
{
	currentState = state;
	cntFrame = 0;
}

/**************************************
�V�[���t�F�[�h�Z�b�g����
***************************************/
bool SetSceneFade(DefineScene next)
{
	if (currentState != SceneFadeNone)
		return false;

	nextScene = next;
	ChangeStateSceneFade(SceneFadeIn);
	return true;
}

/**************************************
�t�F�[�h�C������
***************************************/
void UpdateSceneFadeIn(void)
{
	cntFrame++;

	float alpha = (float)cntFrame / SCENEFADE_INOUT_DURATION;
	SetDiffuseSceneFade(alpha);

	if (cntFrame == SCENEFADE_INOUT_DURATION)
		ChangeStateSceneFade(SceneFadeWait);
}

/**************************************
�t�F�[�h�E�F�C�g����
***************************************/
void UpdateSceneFadeWait(void)
{
	cntFrame++;

	SetDiffuseSceneFade(1.0f);

	if (cntFrame == SCENEFADE_WAIT_DURATION)
	{
		SetScene(nextScene);
		ChangeStateSceneFade(SceneFadeOut);
	}

}

/**************************************
�t�F�[�h�A�E�g����
***************************************/
void UpdateSceneFadeOut(void)
{
	cntFrame++;
	float alpha = (float)cntFrame / SCENEFADE_INOUT_DURATION;
	alpha = 1.0f - alpha;
	SetDiffuseSceneFade(alpha);

	if (cntFrame == SCENEFADE_INOUT_DURATION)
		ChangeStateSceneFade(SceneFadeNone);

}

/**************************************
�t�F�[�h��������
***************************************/
void UpdateSceneFadeNone(void)
{
	//�������Ȃ�
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexSceneFade(void)
{
	vtxWk[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vtxWk[1].vtx = D3DXVECTOR3(WINDOW_WIDTH, 0.0f, 0.0f);
	vtxWk[2].vtx = D3DXVECTOR3(0.0f, WINDOW_HEIGHT, 0.0f);
	vtxWk[3].vtx = D3DXVECTOR3(WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
}

/**************************************
�f�B�t���[�Y�ݒ菈��
***************************************/
void SetDiffuseSceneFade(float alpha)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
}