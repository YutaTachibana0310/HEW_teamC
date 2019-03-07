//=====================================
//
//�X�R�A�\������[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "score.h"

/**************************************
�}�N����`
***************************************/
#define SCORE_TEXTURE_NAME		"data/TEXTURE/SCORE/number002.png"
#define SCORE_TEXTURE_SIZE_X	(80.0f)
#define SCORE_TEXTURE_SIZE_Y	(100.0f)
#define SCORE_BASEPOS_1P		(D3DXVECTOR3(300.0f, 110.0f, 0.0f))
#define SCORE_BASEPOS_2P		(D3DXVECTOR3(SCREEN_WIDTH + 300.0f, 110.0f, 0.0f))
#define SCORE_OFFSET			(-50.0f)
#define SCORE_TEX_DIV_X			(10)
#define SCORE_TEX_DIV_Y			(1)

#define SCORE_TEXTEX_NAME			"data/TEXTURE/SCORE/scoreText.png"
#define SCORE_TEXT_SIZE_X			(320.0f)
#define SCORE_TEXT_SIZE_Y			(SCORE_TEXT_SIZE_X / 4.0f)
#define SCORE_TEXTTEX_BASEPOS_1P	(D3DXVECTOR3(SCORE_TEXT_SIZE_X / 2.0f, 30.0f, 0.0f))
#define SCORE_TEXTTEX_BASEPOS_2P	(D3DXVECTOR3(SCORE_TEXT_SIZE_X / 2.0f + SCREEN_WIDTH, 30.0f, 0.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture, textTex;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexScore(void);
void SetScoreVertex(int num, int digit, bool is1P);
void SetScoreTextVertex(bool is1P);

/**************************************
����������
***************************************/
void InitScore(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)SCORE_TEXTURE_NAME, pDevice);
	textTex = CreateTextureFromFile((LPSTR)SCORE_TEXTEX_NAME, pDevice);
	MakeVertexScore();
}

/**************************************
�I������
***************************************/
void UninitScore(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(textTex);
}

/**************************************
�X�V����
***************************************/
void UpdateScore(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawScore(int score1P, int score2P)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//SCORE��`��
	pDevice->SetTexture(0, textTex);
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetScoreTextVertex(i == 0);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}

	//1P�̃X�R�A��`��
	pDevice->SetTexture(0, texture);
	{
		int digitMax = score1P == 0 ? 1 : (int)log10f((float)score1P) + 1;
		for (int i = 0; i < digitMax; i++, score1P /= 10)
		{
			int num = score1P % 10;
			SetScoreVertex(num, i, true);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		}
	}
	//2P�̃X�R�A��`��
	{
		int digitMax = score2P == 0 ? 1 : (int)log10f((float)score2P) + 1;
		for (int i = 0; i < digitMax; i++, score2P /= 10)
		{
			int num = score2P % 10;
			SetScoreVertex(num, i, false);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		}
	}
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexScore(void)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
}

/**************************************
���_�ݒ菈��
***************************************/
void SetScoreVertex(int num, int digit, bool is1P)
{
	//���_���W�̐ݒ�
	D3DXVECTOR3 pos = is1P ? SCORE_BASEPOS_1P : SCORE_BASEPOS_2P;
	pos.x += SCORE_OFFSET * digit;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-SCORE_TEXTURE_SIZE_X / 2.0f, -SCORE_TEXTURE_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3(SCORE_TEXTURE_SIZE_X / 2.0f, -SCORE_TEXTURE_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-SCORE_TEXTURE_SIZE_X / 2.0f, SCORE_TEXTURE_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3(SCORE_TEXTURE_SIZE_X / 2.0f, SCORE_TEXTURE_SIZE_Y / 2.0f, 0.0f);

	//UV���W�̐ݒ�
	float sizeX = 1.0f / SCORE_TEX_DIV_X;
	vtxWk[0].tex = D3DXVECTOR2(num * sizeX, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2((num + 1) * sizeX, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(num * sizeX, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2((num + 1) * sizeX, 1.0f);
}

/**************************************
���_�ݒ菈���i�e�L�X�g�p�j
***************************************/
void SetScoreTextVertex(bool is1P)
{
	//���_���W�̐ݒ�
	D3DXVECTOR3 pos = is1P ? SCORE_TEXTTEX_BASEPOS_1P : SCORE_TEXTTEX_BASEPOS_2P;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-SCORE_TEXT_SIZE_X / 2.0f, -SCORE_TEXT_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3(SCORE_TEXT_SIZE_X / 2.0f, -SCORE_TEXT_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-SCORE_TEXT_SIZE_X / 2.0f, SCORE_TEXT_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3(SCORE_TEXT_SIZE_X / 2.0f, SCORE_TEXT_SIZE_Y / 2.0f, 0.0f);

	//UV���W�̐ݒ�
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}