//=====================================
//
//�|�X�g�G�t�F�N�g�}�l�[�W������[postEffectManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "postEffectManager.h"

/**************************************
�}�N����`
***************************************/
#define POSTEFFECT_MAX			(8)
#define POSTEFFECT_BLUR_LOOP	(2)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static char activeEffect = 0;

/**************************************
�v���g�^�C�v�錾
***************************************/
void SetVertexPostEffect(int targetID);

/**************************************
����������
***************************************/
void InitPostEffectManager(int num)
{
	bool initialized = false;

	//�|�X�g�G�t�F�N�g������

	//���_�o�b�t�@���쐬�ς݂ł���΃��^�[��
	if (initialized)
		return;

	//���_�o�b�t�@�쐬
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	VERTEX_2D *pVtx = NULL;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(0.0, 0.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, 0.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f / (float)SCREEN_WIDTH, 0.0f + 0.5f / (float)SCREEN_HEIGHT);
	pVtx[1].tex = D3DXVECTOR2(1.0f + 0.5f / (float)SCREEN_WIDTH, 0.0f + 0.5f / (float)SCREEN_HEIGHT);
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f / (float)SCREEN_WIDTH, 1.0f + 0.5f / (float)SCREEN_HEIGHT);
	pVtx[3].tex = D3DXVECTOR2(1.0f + 0.5f / (float)SCREEN_WIDTH, 1.0f + 0.5f / (float)SCREEN_HEIGHT);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();

	initialized = true;
}

/**************************************
�I������
***************************************/
void UninitPostEffectManager(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(vtxBuff);
	}
}

/**************************************
�X�V����
***************************************/
void UpdatePostEffectManager(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawPostEffectManager(LPDIRECT3DTEXTURE9 tex[2], LPDIRECT3DSURFACE9 suf[2], LPDIRECT3DSURFACE9 back, int targetID)
{
	int cntDraw = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�|�X�g�G�t�F�N�g�p�ɐݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	//���ʂ��o�b�N�o�b�t�@�֕`��
	pDevice->SetRenderTarget(0, back);
	SAFE_RELEASE(back);

	SetVertexPostEffect(targetID);
	pDevice->SetTexture(0, tex[cntDraw % 2]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//�ݒ�����ɖ߂�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**************************************
�G�t�F�N�g�g�p�󋵔��菈��
***************************************/
bool CheckActivePostEffect(char effect)
{
	if (effect >= EFFECT_MAX)
		return false;

	char active = activeEffect;

	active = active >> effect;
	active = active << (POSTEFFECT_MAX - 1);

	char hoge = active & (1 << (POSTEFFECT_MAX - 1));
	bool res = (active & (1 << (POSTEFFECT_MAX - 1))) ? true : false;
	return res;
}

/**************************************
�G�t�F�N�g�g�p�ݒ菈��
***************************************/
bool SetPostEffectUse(char effect, bool state)
{
	if (effect >= EFFECT_MAX)
		return false;

	//�A�N�e�B�u�ɂ���ꍇ
	if (state)
	{
		char set = (1 << effect);
		activeEffect |= set;
		return true;
	}
	//��A�N�e�B�u�ɂ���ꍇ
	else
	{
		char set = ~(1 << effect);
		activeEffect &= set;
		return true;
	}
}

/**************************************
���_���W�ݒ菈��
***************************************/
void SetVertexPostEffect(int targetID)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(targetID * SCREEN_WIDTH / 2.0f, 0.0f, 0.0f);

	VERTEX_2D *pVtx = NULL;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = pos + D3DXVECTOR3(0.0, 0.0f, 0.0f);
	pVtx[1].vtx = pos + D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, 0.0f, 0.0f);
	pVtx[2].vtx = pos + D3DXVECTOR3(0.0, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].vtx = pos + D3DXVECTOR3((float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT, 0.0f);

	vtxBuff->Unlock();
}