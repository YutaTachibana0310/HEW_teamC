//=====================================
//
//���C���{�[���[������[rainbowLane.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "rainbowLane.h"
#include "gameParameter.h"

/**************************************
�}�N����`
***************************************/
#define RAINBOWLANE_TEXTURE_NAME	"data/TEXTURE/BG/rainbowLane.jpg"	//�e�N�X�`���̃p�X
#define RAINBOWLANE_BACK_END		(-1000.0f)							//���[���̌��̒[
#define RAINBOWLANE_FRONT_END		(20000.0f)							//���[���̑O�̒[
#define RAINBOWLANE_WIDTH			(5.0f)								//���[���̕�
#define RAINBOWLANE_TEXTURELOOP		(200.0f)							//�e�N�X�`�����[�v��
#define RAINBOWLANE_SCROLLSPEED		(-0.05f)							//�X�N���[�����x
#define RAINBOWLANE_NUM_MAX			(3)									//���[���ő吔
#define RAINBOWLANE_BASEPOS_Y		(-50.0f)							//���[���̊�ʒu(Y)
#define RAINBOWLANE_OFFSET_X		(50.0f)								//���[���̃I�t�Z�b�g(X)
#define RAINBOWLANE_OFFSET_Y		(30.0f)								//���[���̃I�t�Z�b�g(Y)
#define RAINBOWLANE_ROT_VALUE		(D3DXToRadian(40.0f))				//���[���̉�]��

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;				//���_�o�b�t�@
static LPDIRECT3DTEXTURE9 texture;					//�e�N�X�`��
static int cntFrame;								//�J�E���g�t���[��



//�e���[���̍��W
static D3DXVECTOR3 lanePos[RAINBOWLANE_NUM_MAX] = {
	D3DXVECTOR3(-RAINBOWLANE_OFFSET_X, RAINBOWLANE_BASEPOS_Y + RAINBOWLANE_OFFSET_Y, 0.0f),
	D3DXVECTOR3(0.0f, RAINBOWLANE_BASEPOS_Y, 0.0f),
	D3DXVECTOR3(RAINBOWLANE_OFFSET_X, RAINBOWLANE_BASEPOS_Y + RAINBOWLANE_OFFSET_Y, 0.0f),
};	



//�e���[���̉�]��
static D3DXVECTOR3 laneRot[RAINBOWLANE_NUM_MAX] = {
	D3DXVECTOR3(0.0f, 0.0f, -RAINBOWLANE_ROT_VALUE),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, RAINBOWLANE_ROT_VALUE),
};

/**************************************
�v���g�^�C�v�錾
***************************************/
void SetVertexRainbowLane(void);			//���_�ݒ菈��
void ScrollRainbowLane(int n);				//�X�N���[������

/**************************************
lanePos.y��Get�֐�
***************************************/
D3DXVECTOR3 GetLanePos(int num)
{
	return lanePos[num];
}

/**************************************
l���[���̉�]��Get�֐�
***************************************/
D3DXVECTOR3 GetLaneRot(int num)
{
	return laneRot[num];
}

/**************************************
����������
***************************************/
void InitRainbowLane(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	//�e�N�X�`����ǂݍ���
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
}

/**************************************
�`�揈��
***************************************/
void DrawRainbowLane(int n)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld, mtxTranslate, mtxRot;

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//�e�N�X�`�����X�N���[��
	ScrollRainbowLane(n);

	//��]�Ń��[���̖��邳���ς��Ȃ��悤�Ƀ��C�e�B���O�̓I�t��
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < RAINBOWLANE_NUM_MAX; i++)
	{
		D3DXMatrixIdentity(&mtxWorld);

		//��]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, laneRot[i].y, laneRot[i].x, laneRot[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//�ړ�
		D3DXMatrixTranslation(&mtxTranslate, lanePos[i].x, lanePos[i].y, lanePos[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
		
		//���[���h�ϊ��s����Z�b�g
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	//���C�e�B���O�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
���_�ݒ菈��
***************************************/
void SetVertexRainbowLane(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[1].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[2].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);
	pVtx[3].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);

	//UV���W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, RAINBOWLANE_TEXTURELOOP);

	//�@���ݒ�
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�f�B�t���[�Y�ݒ�
	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	vtxBuff->Unlock();
}

/**************************************
�X�N���[������
***************************************/
void ScrollRainbowLane(int n)
{
	VERTEX_3D *pVtx;
	GAMEPARAMETER *param = GetGameParameterAdr(n);

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//UV���W�̃I�t�Z�b�g���v�Z
	float offset = cntFrame * RAINBOWLANE_SCROLLSPEED * param->playerSpeed;

	pVtx[0].tex = D3DXVECTOR2(0.0f, offset);
	pVtx[1].tex = D3DXVECTOR2(1.0f, offset);
	pVtx[2].tex = D3DXVECTOR2(0.0f, offset + RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, offset + RAINBOWLANE_TEXTURELOOP);

	vtxBuff->Unlock();
}