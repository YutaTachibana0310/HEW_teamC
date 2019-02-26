//=====================================
//
//���C���{�[���[������[rainbowLane.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "rainbowLane.h"

/**************************************
�}�N����`
***************************************/
#define RAINBOWLANE_TEXTURE_NAME	"data/TEXTURE/BG/rainbowLane.jpg"
#define RAINBOWLANE_BACK_END		(-1000.0f)
#define RAINBOWLANE_FRONT_END		(20000.0f)
#define RAINBOWLANE_WIDTH			(5.0f)
#define RAINBOWLANE_TEXTURELOOP		(200.0f)
#define RAINBOWLANE_SCROLLSPEED		(-0.05f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DTEXTURE9 texture;
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/
void SetVertexRainbowLane(void);
void ScrollRainbowLane(void);

/**************************************
����������
***************************************/
void InitRainbowLane(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	texture = CreateTextureFromFile((LPSTR)RAINBOWLANE_TEXTURE_NAME, pDevice);

	SetVertexRainbowLane();
}

/**************************************
�I������
***************************************/
void UninitRainbowLane(int num)
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void UpdateRainbowLane(void)
{
	cntFrame++;
	ScrollRainbowLane();
}

/**************************************
�`�揈��
***************************************/
void DrawRainbowLane(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	D3DXMatrixIdentity(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
���_�ݒ菈��
***************************************/
void SetVertexRainbowLane(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[1].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[2].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);
	pVtx[3].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, RAINBOWLANE_TEXTURELOOP);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
�X�N���[������
***************************************/
void ScrollRainbowLane(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float offset = cntFrame * RAINBOWLANE_SCROLLSPEED;

	pVtx[0].tex = D3DXVECTOR2(0.0f, offset);
	pVtx[1].tex = D3DXVECTOR2(1.0f, offset);
	pVtx[2].tex = D3DXVECTOR2(0.0f, offset + RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, offset + RAINBOWLANE_TEXTURELOOP);

	vtxBuff->Unlock();
}