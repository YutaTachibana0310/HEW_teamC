//=====================================
//
//�v���C���[�}�[�J�[����[playerMarker.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "playerMarker.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERMARKER_TEXTURE_NAME		"data/TEXTURE/UI/playerMarker.png"
#define PLAYERMARKER_SIZE_X				(100.0f)
#define PLAYERMARKER_SIZE_Y				(100.0f)

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
void MakeVertexPlayerMarker(void);

/**************************************
����������
***************************************/
void InitPlayerMarker(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)PLAYERMARKER_TEXTURE_NAME, pDevice);
	MakeVertexPlayerMarker();
}

/**************************************
�I������
***************************************/
void UninitPlayerMarker(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerMarker(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawPlayerMarker(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexPlayerMarker(void)
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
�v���C���[�}�[�J�[�Z�b�g����
***************************************/
void SetPlayerMarker(int playerID, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX view, projection;
	D3DVIEWPORT9 viewPort;

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�|�[�g�s����擾
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetViewport(&viewPort);

	//�r���[�ϊ��A�v���W�F�N�V�����ϊ�������
	D3DXVECTOR3 screenPos;
	D3DXVec3TransformCoord(&screenPos, &pos, &view);
	D3DXVec3TransformCoord(&screenPos, &screenPos, &projection);
	
	//�r���[�|�[�g�ϊ����s��
	D3DXVECTOR3 setPos;
	setPos.x = screenPos.x * (viewPort.Width / 2.0f) + viewPort.Width / 2.0f + viewPort.X;
	setPos.y = screenPos.y * (-(float)viewPort.Height / 2.0f) + viewPort.Height / 2.0f + viewPort.Y;
	setPos.z = 0.0f;

	//���W����ʓ��Ɏ��߂�
	setPos.x = Clampf((float)viewPort.X + PLAYERMARKER_SIZE_X / 2.0f, (float)(viewPort.X + viewPort.Width) - PLAYERMARKER_SIZE_X / 2.0f, setPos.x);
	setPos.y = Clampf((float)viewPort.Y + PLAYERMARKER_SIZE_Y / 2.0f, (float)(viewPort.Y + viewPort.Height) - PLAYERMARKER_SIZE_Y / 2.0f, setPos.y);

	//���_���W���Z�b�g
	vtxWk[0].vtx = setPos + D3DXVECTOR3(-PLAYERMARKER_SIZE_X / 2.0f, -PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = setPos + D3DXVECTOR3( PLAYERMARKER_SIZE_X / 2.0f, -PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = setPos + D3DXVECTOR3(-PLAYERMARKER_SIZE_X / 2.0f,  PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = setPos + D3DXVECTOR3( PLAYERMARKER_SIZE_X / 2.0f,  PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);

	//UV���W���Z�b�g
	float sizeY = 1.0f / TARGETPLAYER_MAX;
	vtxWk[0].tex = D3DXVECTOR2(0.0f, playerID * sizeY);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, playerID * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, (playerID + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, (playerID + 1) * sizeY);
}