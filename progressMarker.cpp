//=====================================
//
//�v���O���X�}�[�J�[����[progressMarker.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "progressMarker.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define PROGRESSMARKER_TEXTURE_NAME		"data/TEXTURE/UI/progressMarker.png"
#define PROGRESSMARKER_SIZE_X	(50.0f)
#define PROGRESSMARKER_SIZE_Y	(50.0f)
#define PROGRESSMARKER_TEXTURE_DIV_X	(2)
#define PROGRESSMARKER_TEXTURE_DIV_Y	(1)
#define PROGRESSMARKER_POS_OFFSET_X		(40)
#define PROGRESSMARKER_POS_TOP			(100.0f)
#define PROGRESSMARKER_POS_BOTTOM		(SCREEN_HEIGHT - 30.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static LPDIRECT3DTEXTURE9 texture;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexProgressMarker(void);

/**************************************
����������
***************************************/
void InitProgressMarker(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)PROGRESSMARKER_TEXTURE_NAME, pDevice);
	MakeVertexProgressMarker();
}

/**************************************
�I������
***************************************/
void UninitProgressMarker(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void UpdateProgressMarker(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawProgressMarker(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexProgressMarker(void)
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
�}�[�J�[�Z�b�g����
***************************************/
void SetProgressMarker(int targetID, float percent)
{
	//UV���W�ݒ�
	float sizeX = 1.0f / PROGRESSMARKER_TEXTURE_DIV_X;
	float sizeY = 1.0f / PROGRESSMARKER_TEXTURE_DIV_Y;
	int x = targetID % PROGRESSMARKER_TEXTURE_DIV_X;
	int y = targetID / PROGRESSMARKER_TEXTURE_DIV_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);

	//���_���W�ݒ�
	D3DXVECTOR3 pos;
	pos.x = WINDOW_CENTER_X;
	pos.x += (targetID == 0) ? -PROGRESSMARKER_POS_OFFSET_X : PROGRESSMARKER_POS_OFFSET_X;
	pos.y = EaseLinear(percent, PROGRESSMARKER_POS_BOTTOM, PROGRESSMARKER_POS_TOP);

	vtxWk[0].vtx = pos + D3DXVECTOR3(-PROGRESSMARKER_SIZE_X / 2.0f, -PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( PROGRESSMARKER_SIZE_X / 2.0f, -PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-PROGRESSMARKER_SIZE_X / 2.0f,  PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( PROGRESSMARKER_SIZE_X / 2.0f,  PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
}