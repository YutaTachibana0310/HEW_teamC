//=====================================
//
//�G���g���[GUI����[entryGUI.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "entryGUI.h"

/**************************************
�}�N����`
***************************************/
#define ENTRYGUI_TEXTURE_NAME		"data/TEXTURE/UI/entryGUI.png"
#define ENTRYGUI_SIZE_X				(600.0f)
#define ENTRYGUI_SIZE_Y				(ENTRYGUI_SIZE_X / 8.0f)
#define ENTRYGUI_POS				(D3DXVECTOR3(WINDOW_CENTER_X, WINDOW_HEIGHT - 200.0f, 0.0f))
#define ENTRYGUI_OFFSET_X			(SCREEN_WIDTH / 2.0f)

/**************************************
�\���̒�`
***************************************/
enum ENTRYGUI_TEXTURE_INDEX {
	ENTRYGUI_TEXTURE_WAITINPUT,
	ENTRYGUI_TEXTURE_COMPLETE_ENTRY,
	ENTRYGUI_TEXTURE_INDEX_MAX
};

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexEntryGUI(void);

/**************************************
����������
***************************************/
void InitEntryGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)ENTRYGUI_TEXTURE_NAME, pDevice);
	MakeVertexEntryGUI();
}

/**************************************
�I������
***************************************/
void UninitEntryGUI(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void UpdateEntryGUI(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawEntryGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexEntryGUI(void)
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
void SetEntryGUI(int playerID, bool isCompleted)
{
	float sizeY = 1.0f / ENTRYGUI_TEXTURE_INDEX_MAX;
	int y = isCompleted ? ENTRYGUI_TEXTURE_COMPLETE_ENTRY : ENTRYGUI_TEXTURE_WAITINPUT;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, sizeY * y);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, sizeY * y);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, sizeY * (y + 1));
	vtxWk[3].tex = D3DXVECTOR2(1.0f, sizeY * (y + 1));

	float offsetX = playerID == 0 ? -ENTRYGUI_OFFSET_X : ENTRYGUI_OFFSET_X;
	D3DXVECTOR3 pos = ENTRYGUI_POS;
	pos.x += offsetX;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-ENTRYGUI_SIZE_X / 2.0f, -ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( ENTRYGUI_SIZE_X / 2.0f, -ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-ENTRYGUI_SIZE_X / 2.0f,  ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( ENTRYGUI_SIZE_X / 2.0f,  ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
}