//=====================================
//
//�X���b�V���o���b�g����[slashBullet.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "slashBullet.h"
#include "camera.h"

/**************************************
�}�N����`
***************************************/
#define SLASHBULLET_TEXTURE_NAME		"data/TEXTURE/EFFECT/pipo-btleffect130.png"
#define SLASHBULLET_SIZE_X				(35.0f)
#define SLASHBULLET_SIZE_Y				(SLASHBULLET_SIZE_X * 0.75f)
#define SLASHBULLET_TEX_DIV_X			(2)
#define SLASHBULLET_TEX_DIV_Y			(12)
#define SLASHBULLET_ANIM_PATTERN_MAX	(SLASHBULLET_TEX_DIV_X*SLASHBULLET_TEX_DIV_Y)
#define SLASHBULLET_MOVE_SPEED			(10.0f)
#define SLASHBULLET_MOVE_BORDER_Z		(5000.0f)
#define SLASHBULLET_COLLIDER_LENGTH		(D3DXVECTOR3(10.0f, 10.0f, 10.0f))

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static SLASHBULLET bullet[SLASHBULLET_NUM_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexSlashBullet(void);
void SetTextureSlashBullet(void);

/**************************************
����������
***************************************/
void InitSlashBullet(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)SLASHBULLET_TEXTURE_NAME, pDevice);
	MakeVertexSlashBullet();

	//�p�����[�^������
	SLASHBULLET *ptr = &bullet[0];
	for (int i = 0; i < SLASHBULLET_NUM_MAX; i++, ptr++)
	{
		ptr->cntFrame = 0;
		ptr->active = false;

		ptr->collider.pos = &ptr->pos;
		ptr->collider.length = SLASHBULLET_COLLIDER_LENGTH;
		ptr->collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

/**************************************
�I������
***************************************/
void UninitSlashBullet(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(vtxBuff);
}

/**************************************
�X�V����
***************************************/
void UpdateSlashBullet(void)
{
	SLASHBULLET *ptr = &bullet[0];
	for (int i = 0; i < SLASHBULLET_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		ptr->cntFrame++;

		ptr->pos.z += SLASHBULLET_MOVE_SPEED;

		//�ړ��\�͈͂𒴂��Ă������A�N�e�B�u��
		if (ptr->pos.z > SLASHBULLET_MOVE_BORDER_Z)
		{
			ptr->active = false;
		}
	}

	SetTextureSlashBullet();
}

/**************************************
�`�揈��
***************************************/
void DrawSlashBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX mtxWorld, mtxRot, mtxTranslate, mtxView;
	SLASHBULLET *ptr = &bullet[0];

	//�r���[�s����擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	for (int i = 0; i < SLASHBULLET_NUM_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		D3DXMatrixIdentity(&mtxWorld);

		//��]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, ptr->rot.y, ptr->rot.x, ptr->rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//�ړ�
		D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);


		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//�`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * NUM_VERTEX, NUM_POLYGON);

	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
���_�o�b�t�@�쐬����
***************************************/
void MakeVertexSlashBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * SLASHBULLET_NUM_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < SLASHBULLET_NUM_MAX; i++, pVtx += NUM_VERTEX)
	{
		//���_���W�̃Z�b�g
		pVtx[0].vtx = D3DXVECTOR3(-SLASHBULLET_SIZE_X / 2.0f, SLASHBULLET_SIZE_Y / 2.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SLASHBULLET_SIZE_X / 2.0f, SLASHBULLET_SIZE_Y / 2.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-SLASHBULLET_SIZE_X / 2.0f, -SLASHBULLET_SIZE_Y / 2.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SLASHBULLET_SIZE_X / 2.0f, -SLASHBULLET_SIZE_Y / 2.0f, 0.0f);

		//UV���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�f�B�t���[�Y�̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�@���̐ݒ�
		pVtx[0].nor =
			pVtx[1].nor =
			pVtx[2].nor =
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	vtxBuff->Unlock();
}

/**************************************
UV�ݒ菈��
***************************************/
void SetTextureSlashBullet(void)
{
	VERTEX_3D *pVtx;
	float sizeX = 1.0f / SLASHBULLET_TEX_DIV_X;
	float sizeY = 1.0f / SLASHBULLET_TEX_DIV_Y;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	SLASHBULLET *ptr = &bullet[0];

	for (int i = 0; i < SLASHBULLET_NUM_MAX; i++, pVtx += 4)
	{
		if (!ptr->active)
			continue;

		int pattern = ptr->cntFrame % SLASHBULLET_ANIM_PATTERN_MAX;
		int x = pattern % SLASHBULLET_TEX_DIV_X;
		int y = pattern / SLASHBULLET_TEX_DIV_X;
		pVtx[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
		pVtx[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
		pVtx[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
		pVtx[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
	}
}

/**************************************
�Z�b�g����
***************************************/
void SetSlashBullet(D3DXVECTOR3 pos, int playerID, float x, float y)
{
	SLASHBULLET *ptr = &bullet[0];
	for (int i = 0; i < SLASHBULLET_NUM_MAX; i++, ptr++)
	{
		if (ptr->active)
			continue;

		ptr->pos = pos;
		ptr->rot.z = atan2f(y, x);

		ptr->active = true;
		ptr->parentPlayerID = playerID;
		return;
	}
}

/**************************************
�A�h���X�擾����
***************************************/
SLASHBULLET* GetSlashBulletAdr(int n)
{
	return &bullet[0];
}