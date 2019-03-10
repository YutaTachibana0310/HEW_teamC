//=====================================
//
//�J�E���g�_�E��GUI����[template.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "countDownGUI.h"
#include "Easing.h"

#include "soundEffectManager.h"

/**************************************
�}�N����`
***************************************/
#define COUNTDOWNGUI_TEXTURE_NAME		"data/TEXTURE/UI/countDownGUI.png"
#define COUNTDOWNGUI_SIZE_X				(300.0f)
#define COUNTDONWGUI_SIZE_Y				(300.0f)
#define COUNTDOWNGUI_POS				(D3DXVECTOR3(WINDOW_CENTER_X, 300.0f, 0.0f))
#define COUNTDOWNGUI_OFFSET_X			(SCREEN_WIDTH / 2.0f)
#define COUNTDOWNGUI_TEX_DIV_X			(2)
#define COUNTDOWNGUI_TEX_DIV_Y			(2)
#define COUNTDOWNGUI_ANIM_DURATION		(60)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];
static int cntFrame;
static float scale;
static bool active;
static int animPattern;

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexCountDownGUI(void);
void SetVertexCountDownGUI(int i);
void SetTextureCountDownGUI(int pattern);

/**************************************
����������
***************************************/
void InitCountDownGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)COUNTDOWNGUI_TEXTURE_NAME, pDevice);

	MakeVertexCountDownGUI();

	active = false;
}

/**************************************
�I������
***************************************/
void UninitCountDownGUI(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void UpdateCountDownGUI(void)
{
	if (!active)
		return;

	cntFrame++;

	//�X�P�[�����g�D�C�[�j���O
	float t = (float)cntFrame / COUNTDOWNGUI_ANIM_DURATION;
	scale = EaseOutExponential(t, 0.0f, 1.0f);

	//�e�N�X�`���A�j���[�V����
	if (cntFrame == COUNTDOWNGUI_ANIM_DURATION)
	{
		cntFrame = 0;
		animPattern++;

		if (animPattern == COUNTDOWNGUI_TEX_DIV_X * COUNTDOWNGUI_TEX_DIV_Y)
			active = false;
	}
}

/**************************************
�`�揈��
***************************************/
void DrawCountDownGUI(void)
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetVertexCountDownGUI(i);
		SetTextureCountDownGUI(animPattern);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexCountDownGUI(void)
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
UV���W�ݒ菈��
***************************************/
void SetTextureCountDownGUI(int pattern)
{
	float sizeX = 1.0f / COUNTDOWNGUI_TEX_DIV_X;
	float sizeY = 1.0f / COUNTDOWNGUI_TEX_DIV_Y;
	int x = pattern % COUNTDOWNGUI_TEX_DIV_X;
	int y = pattern / COUNTDOWNGUI_TEX_DIV_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

/**************************************
���_���W�ݒ菈��
***************************************/
void SetVertexCountDownGUI(int i)
{
	D3DXVECTOR3 pos = COUNTDOWNGUI_POS;
	float offsetX = i == 0 ? -COUNTDOWNGUI_OFFSET_X : COUNTDOWNGUI_OFFSET_X;
	pos.x += offsetX;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-COUNTDOWNGUI_SIZE_X / 2.0f * scale, -COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( COUNTDOWNGUI_SIZE_X / 2.0f * scale, -COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-COUNTDOWNGUI_SIZE_X / 2.0f * scale,  COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( COUNTDOWNGUI_SIZE_X / 2.0f * scale,  COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
}

/**************************************
�J�E���g�_�E��GUI�Z�b�g����
***************************************/
void SetCountDownGUI(void)
{
	active = true;
	cntFrame = 0;
	animPattern = 0;
	PlaySE(SOUND_COUNTDOWN);
}