//=====================================
//
//�o���b�g�p�[�e�B�N������[blletParticle.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "bulletParticle.h"
#include "camera.h"
#include "Easing.h"
#include "EasingVector.h"

/**************************************
�}�N����`
***************************************/
#define BULLETPARTICLE_TEXTURE_NAME		"data/TEXTURE/EFFECT/bulletParticle.png"
#define BULLETPARTICLE_SIZE_X			(15.0f)
#define BULLETPARTICLE_SIZE_Y			(15.0f)
#define BULLETPARTICLE_MAX				(256)
#define BULLETPARTICLE_LIFE_MIN			(40)
#define BULLETPARTICLE_LIFE_MAX			(60)
#define BULLETPARTICLE_INITSPEED		(5.0f)

#define BULLETPARTICLE_TEX_NAME_BLUE	"data/TEXTURE/EFFECT/bulletParticle_00.png"
#define BULLETPARTICLE_TEX_NAME_RED		"data/TEXTURE/EFFECT/bulletParticle_01.png"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DTEXTURE9 texture[TARGETPLAYER_MAX];
static LPDIRECT3DVERTEXBUFFER9 vtxBuff[TARGETPLAYER_MAX];
static BULLETPARTICLE particle[TARGETPLAYER_MAX][BULLETPARTICLE_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
void MakeVertexBulletParticle(void);
void FadeBulletParticle(void);
void MoveBulletParticle(void);
void CheckLifeBulletParticle(void);

/**************************************
����������
***************************************/
void InitBulletParticle(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture[0] = CreateTextureFromFile((LPSTR)BULLETPARTICLE_TEX_NAME_BLUE, pDevice);
	texture[1] = CreateTextureFromFile((LPSTR)BULLETPARTICLE_TEX_NAME_RED, pDevice);
	MakeVertexBulletParticle();

	for (int j = 0; j < TARGETPLAYER_MAX; j++)
	{
		BULLETPARTICLE *ptr = &particle[j][0];
		for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
		{
			ptr->active = false;
		}
	}
}

/**************************************
�I������
***************************************/
void UninitBulletParticle(int num)
{
	SAFE_RELEASE(texture[0]);
	SAFE_RELEASE(texture[1]);
	SAFE_RELEASE(vtxBuff[0]);
	SAFE_RELEASE(vtxBuff[1]);
}

/**************************************
�X�V����
***************************************/
void UpdateBulletParticle(void)
{
	CheckLifeBulletParticle();
	MoveBulletParticle();
	FadeBulletParticle();
}

/**************************************
�`�揈��
***************************************/
void DrawBulletParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	DWORD defCmp;
	pDevice->GetRenderState(D3DRS_ZFUNC, &defCmp);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for (int j = 0; j < TARGETPLAYER_MAX; j++)
	{
		pDevice->SetTexture(0, texture[j]);

		pDevice->SetStreamSource(0, vtxBuff[j], 0, sizeof(VERTEX_3D));


		BULLETPARTICLE *ptr = &particle[j][0];
		D3DXMATRIX mtxWorld, mtxTranslate, mtxRot;
		for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
		{
			if (!ptr->active)
				continue;

			D3DXMatrixIdentity(&mtxWorld);

			//GetInvCameraRotMtx(&mtxRot);
			//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			D3DXMatrixTranslation(&mtxTranslate, ptr->pos.x, ptr->pos.y, ptr->pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * NUM_VERTEX, NUM_POLYGON);
		}
	}
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ZFUNC, defCmp);
}

/**************************************
���_�쐬����
***************************************/
void MakeVertexBulletParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int j = 0; j < TARGETPLAYER_MAX; j++)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLETPARTICLE_MAX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&vtxBuff[j],
			NULL);

		VERTEX_3D *pVtx;
		vtxBuff[j]->Lock(0, 0, (void**)&pVtx, 0);

		BULLETPARTICLE *ptr = &particle[j][0];
		for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++, pVtx += 4)
		{
			pVtx[0].vtx = D3DXVECTOR3(-BULLETPARTICLE_SIZE_X / 2.0f, BULLETPARTICLE_SIZE_Y / 2.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLETPARTICLE_SIZE_X / 2.0f, BULLETPARTICLE_SIZE_Y / 2.0f, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLETPARTICLE_SIZE_X / 2.0f, -BULLETPARTICLE_SIZE_Y / 2.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLETPARTICLE_SIZE_X / 2.0f, -BULLETPARTICLE_SIZE_Y / 2.0f, 0.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx[0].nor =
				pVtx[1].nor =
				pVtx[2].nor =
				pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
}

/**************************************
�t�F�[�h����
***************************************/
void FadeBulletParticle(void)
{
	for (int j = 0; j < TARGETPLAYER_MAX; j++)
	{
		VERTEX_3D *pVtx = NULL;
		vtxBuff[j]->Lock(0, 0, (void**)&pVtx, 0);

		BULLETPARTICLE *ptr = &particle[j][0];
		for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++, pVtx += 4)
		{
			if (!ptr->active)
				continue;

			float t = (float)ptr->cntFrame / ptr->lifeFrame;
			float alpha = EaseOutCubic(t, 1.0f, 0.0f);
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
		}

		vtxBuff[j]->Unlock();
	}
}

/**************************************
�ړ�����
***************************************/
void MoveBulletParticle(void)
{
	for (int j = 0; j < TARGETPLAYER_MAX; j++)
	{
		BULLETPARTICLE *ptr = &particle[j][0];
		for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
		{
			if (!ptr->active)
				continue;

			float t = (float)ptr->cntFrame / ptr->lifeFrame;
			float speed = EaseOutCubic(t, ptr->initSpeed, 0.0f);
			ptr->pos += ptr->moveDir * speed;
		}
	}
}

/**************************************
�������菈��
***************************************/
void CheckLifeBulletParticle(void)
{
	for (int j = 0; j < TARGETPLAYER_MAX; j++)
	{
		BULLETPARTICLE *ptr = &particle[j][0];
		for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
		{
			if (!ptr->active)
				continue;

			ptr->cntFrame++;

			if (ptr->cntFrame >= ptr->lifeFrame)
			{
				ptr->active = false;
			}
		}
	}
}

/**************************************
�Z�b�g����
***************************************/
void SetBulletParticle(D3DXVECTOR3 pos, int playerID)
{
	BULLETPARTICLE *ptr = &particle[playerID][0];
	for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
	{
		if (ptr->active)
			continue;

		ptr->active = true;
		ptr->pos = pos;
		ptr->cntFrame = 0;
		ptr->lifeFrame = RandomRange(BULLETPARTICLE_LIFE_MIN, BULLETPARTICLE_MAX);
		ptr->initSpeed = BULLETPARTICLE_INITSPEED;
		ptr->moveDir = D3DXVECTOR3(RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f), RandomRangef(-1.0f, 1.0f));
		D3DXVec3Normalize(&ptr->moveDir, &ptr->moveDir);
		return;
	}
}

