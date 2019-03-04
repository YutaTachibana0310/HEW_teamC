//=====================================
//
//�S�[���e���b�v����[goalTelop.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "goalTelop.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/
#define GOALTELOP_TEXTURE_NAME		"data/TEXTURE/UI/goalTelop.png"
#define GOALTELOP_SIZE_X			(300)
#define GOALTELOP_SIZE_Y			(150)
#define GOALTELOP_POS				(D3DXVECTOR3(WINDOW_CENTER_X, 350.0f, 0.0f))
#define GOALTELOP_OFFSET_X			(SCREEN_WIDTH / 2.0f)
#define GOALTELOP_ANIM_DURATION		(60)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];

static bool active[TARGETPLAYER_MAX];
static float scale[TARGETPLAYER_MAX];
static int cntFrame[TARGETPLAYER_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexGoalTelop(void);
void SetVertexGoalTelop(int playerID);;

/**************************************
����������
***************************************/
void InitGoalTelop(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)GOALTELOP_TEXTURE_NAME, pDevice);
	MakeVertexGoalTelop();
}

/**************************************
�I������
***************************************/
void UninitGoalTelop(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void UpdateGoalTelop(void)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		if (!active[i])
			continue;

		cntFrame[i]++;
		float t = (float)cntFrame[i] / (float)GOALTELOP_ANIM_DURATION;
		scale[i] = EaseOutExponential(t, 0.0f, 1.0f);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawGoalTelop(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	SetVertexGoalTelop(i);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexGoalTelop(void)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
���_�ݒ菈��
***************************************/
void SetVertexGoalTelop(int playerID)
{
	D3DXVECTOR3 pos = GOALTELOP_POS;
	float offsetX = playerID == 0 ? -GOALTELOP_OFFSET_X : GOALTELOP_OFFSET_X;
	pos.x += offsetX;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-GOALTELOP_SIZE_X / 2.0f * scale[playerID], -GOALTELOP_SIZE_Y / 2.0f * scale[playerID], 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( GOALTELOP_SIZE_X / 2.0f * scale[playerID], -GOALTELOP_SIZE_Y / 2.0f * scale[playerID], 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-GOALTELOP_SIZE_X / 2.0f * scale[playerID],  GOALTELOP_SIZE_Y / 2.0f * scale[playerID], 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( GOALTELOP_SIZE_X / 2.0f * scale[playerID],  GOALTELOP_SIZE_Y / 2.0f * scale[playerID], 0.0f);
}

/**************************************
�S�[���e���b�v�Z�b�g����
***************************************/
void SetGoalTelop(int playerID)
{
	active[playerID] = true;
	cntFrame[playerID] = 0;
	scale[playerID] = 0.0f;
}