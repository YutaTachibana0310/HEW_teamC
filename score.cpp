//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author :�x���a��
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/SCORE/number002.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME_SCORE	"data/TEXTURE/SCORE/frame_score.png"    //�ǂݍ��ރe�N�X�`���t�@�C����
#define	SCORE_SIZE_X		(35.0f)									//�X�R�A�̐����̕�
#define	SCORE_SIZE_Y		(50.0f)									//�X�R�A�̐����̍���
#define	SCORE_INTERVAL_X	(0.0f)									//�X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(6)										//�X�R�A�̌���

#define SCORE_POS			(D3DXVECTOR3(WINDOW_CENTER_X, WINDOW_HEIGHT - 200.0f, 0.0f))
#define	SCORE_POS_X			(SCREEN_WIDTH - (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 600.0f)	//�X�R�A�̕\����ʒu�w���W
#define	SCORE_POS_Y			(25.0f)																	//�X�R�A�̕\����ʒu�x���W
#define SCORE_POW			(10.0f)									//�X�R�A�̃p�E�H
#define SCORE_VERTEX		(4)										//�X�R�A�̒��_��
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureScore(int score, int number);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureScore[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffScore = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXVECTOR3				posScore;					// �ʒu
D3DXVECTOR3				rotScore;					// ����

int						score;						// �X�R�A

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �X�R�A�̏�����
	score = 0;

	// ���_���̍쐬
	MakeVertexScore(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE,			// �t�@�C���̖��O
		&pD3DTextureScore[0]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FRAME_SCORE,		// �t�@�C���̖��O
		&pD3DTextureScore[1]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if (pD3DTextureScore[0] != NULL)
	{// �e�N�X�`���̊J��
		pD3DTextureScore[0]->Release();
		pD3DTextureScore[0] = NULL;
	}
	if (pD3DTextureScore[1] != NULL)
	{// �e�N�X�`���̊J��
		pD3DTextureScore[1]->Release();
		pD3DTextureScore[1] = NULL;
	}

	if (pD3DVtxBuffScore != NULL)
	{// ���_�o�b�t�@�̊J��
		pD3DVtxBuffScore->Release();
		pD3DVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (score % (int)(powf(SCORE_POW, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(SCORE_POW, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureScore(nCntPlace, number);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, pD3DVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pD3DTextureScore[0]);

	// �|���S���̕`��
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * SCORE_VERTEX), NUM_POLYGON);
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pD3DTextureScore[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * SCORE_VERTEX), NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + SCORE_VERTEX),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pD3DVtxBuffScore,								// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += SCORE_VERTEX)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y - 30, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 20, SCORE_POS_Y - 30, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 20, SCORE_POS_Y + 55, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		pD3DVtxBuffScore->Unlock();
	}

	return S_OK;
}

////=============================================================================
//// �e�N�X�`�����W�̐ݒ�
////=============================================================================
//void SetTextureScore(int idx, int number)
//{
//	VERTEX_2D *pVtx;
//
//	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//	pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	pVtx += (idx * SCORE_VERTEX);
//
//	// ���_���W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.14f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.14f, 1.0f);
//
//	// ���_�f�[�^���A�����b�N����
//	pD3DVtxBuffScore->Unlock();
//}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScore(int score, int number)
{
	VERTEX_2D *Vtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pD3DVtxBuffScore->Lock(0, 0, (void**)&Vtx, 0);

	Vtx += (score * SCORE_VERTEX);

	// ���_���W�̐ݒ�
	Vtx[0].tex = D3DXVECTOR2( 0.1f, 0.0f);
	Vtx[1].tex = D3DXVECTOR2( 0.1f + 0.14f, 0.0f);
	Vtx[2].tex = D3DXVECTOR2( 0.1f, 1.0f);
	Vtx[3].tex = D3DXVECTOR2( 0.1f + 0.14f, 1.0f);


	////���_���W�ݒ�
	//float offsetX = number == 0 ? -SCORE_SIZE_X : SCORE_SIZE_X;
	//D3DXVECTOR3 pos = SCORE_POS;
	//pos.x += offsetX;

	//Vtx[0].vtx = pos + D3DXVECTOR3(-SCORE_SIZE_X / 2.0f, -SCORE_SIZE_Y / 2.0f, 0.0f);
	//Vtx[1].vtx = pos + D3DXVECTOR3(	SCORE_SIZE_X / 2.0f, -SCORE_SIZE_Y / 2.0f, 0.0f);
	//Vtx[2].vtx = pos + D3DXVECTOR3(-SCORE_SIZE_X / 2.0f,  SCORE_SIZE_Y / 2.0f, 0.0f);
	//Vtx[3].vtx = pos + D3DXVECTOR3(	SCORE_SIZE_X / 2.0f,  SCORE_SIZE_Y / 2.0f, 0.0f);
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void ChangeScore(int value)
{
	score += value;
	if (score < 0)
	{
		score = 0;
	}
	else if (score >= (int)(powf(SCORE_POW, (float)(NUM_PLACE + 1))))
	{
		score = (int)(powf(SCORE_POW, (float)(NUM_PLACE + 1))) - 1;
	}
}

