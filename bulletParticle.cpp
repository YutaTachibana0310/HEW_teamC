//=====================================
//
//バレットパーティクル処理[blletParticle.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "bulletParticle.h"
#include "camera.h"
#include "Easing.h"
#include "EasingVector.h"

/**************************************
マクロ定義
***************************************/
#define BULLETPARTICLE_TEXTURE_NAME		"data/TEXTURE/EFFECT/bulletParticle.png"
#define BULLETPARTICLE_SIZE_X			(15.0f)
#define BULLETPARTICLE_SIZE_Y			(15.0f)
#define BULLETPARTICLE_MAX				(256)
#define BULLETPARTICLE_LIFE_MIN			(40)
#define BULLETPARTICLE_LIFE_MAX			(60)
#define BULLETPARTICLE_INITSPEED		(5.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static BULLETPARTICLE particle[BULLETPARTICLE_MAX];

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexBulletParticle(void);
void FadeBulletParticle(void);
void MoveBulletParticle(void);
void CheckLifeBulletParticle(void);

/**************************************
初期化処理
***************************************/
void InitBulletParticle(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)BULLETPARTICLE_TEXTURE_NAME, pDevice);
	MakeVertexBulletParticle();

	BULLETPARTICLE *ptr = &particle[0];
	for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
	{
		ptr->active = false;
	}
}

/**************************************
終了処理
***************************************/
void UninitBulletParticle(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(vtxBuff);
}

/**************************************
更新処理
***************************************/
void UpdateBulletParticle(void)
{
	CheckLifeBulletParticle();
	MoveBulletParticle();
	FadeBulletParticle();
}

/**************************************
描画処理
***************************************/
void DrawBulletParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	DWORD defCmp;
	pDevice->GetRenderState(D3DRS_ZFUNC, &defCmp);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	BULLETPARTICLE *ptr = &particle[0];
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

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ZFUNC, defCmp);
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexBulletParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * BULLETPARTICLE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	BULLETPARTICLE *ptr = &particle[0];
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

/**************************************
フェード処理
***************************************/
void FadeBulletParticle(void)
{
	VERTEX_3D *pVtx = NULL;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	BULLETPARTICLE *ptr = &particle[0];
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

	vtxBuff->Unlock();
}

/**************************************
移動処理
***************************************/
void MoveBulletParticle(void)
{
	BULLETPARTICLE *ptr = &particle[0];
	for (int i = 0; i < BULLETPARTICLE_MAX; i++, ptr++)
	{
		if (!ptr->active)
			continue;

		float t = (float)ptr->cntFrame / ptr->lifeFrame;
		float speed = EaseOutCubic(t, ptr->initSpeed, 0.0f);
		ptr->pos += ptr->moveDir * speed;
	}
}

/**************************************
寿命判定処理
***************************************/
void CheckLifeBulletParticle(void)
{
	BULLETPARTICLE *ptr = &particle[0];
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

/**************************************
セット処理
***************************************/
void SetBulletParticle(D3DXVECTOR3 pos)
{
	BULLETPARTICLE *ptr = &particle[0];
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

