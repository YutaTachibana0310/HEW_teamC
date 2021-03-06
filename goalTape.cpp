//=====================================
//
//ゴールテープ処理[goalTape.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "goalTape.h"
#include "gameParameter.h"

/**************************************
マクロ定義
***************************************/
#define GOALTAPE_COLLIDER_LENGTH		(D3DXVECTOR3(1000.0f, 100.0f, 50.0f))
#define GOALTAPE_SIZE_X					(500.0f)
#define GOALTAPE_SIZE_Y					(10.0f)
#define GOALTAPE_POS_Y					(-10.0f)
#define GOALTAPE_TEXTURE_NAME			"data/TEXTURE/BG/goalTape.png"
#define GOALTAPE_TEXTURE_LOOP_X			(20)
#define GOALTAPE_TEXTURE_LOOP_Y			(1)
#define GOALTAPE_ANIMATION_VALUE		(0.1f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static GOALTAPE entity;
static LPDIRECT3DTEXTURE9 texture;
static float textureOffset;
/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexGoalTape(void);
void AnimationGoalTape(void);

/**************************************
初期化処理
***************************************/
void InitGoalTape(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)GOALTAPE_TEXTURE_NAME, pDevice);

	MakeVertexGoalTape();
	entity.pos.z = SYSTEMPARAMETER_PROGRESS_MAX;
	entity.pos.y = GOALTAPE_POS_Y;

	entity.collider.pos = &entity.pos;
	entity.collider.length = GOALTAPE_COLLIDER_LENGTH;
	entity.collider.offset = D3DXVECTOR3(0.0f, 0.0f, GOALTAPE_COLLIDER_LENGTH.z / 2.0f);

	textureOffset = 0.0f;
}

/**************************************
終了処理
***************************************/
void UninitGoalTape(int num)
{
	SAFE_RELEASE(vtxBuff);
}

/**************************************
更新処理
***************************************/
void UpdateGoalTape(void)
{
	entity.pos.z -= SYSTEMPARAMETER_PROGRESS_VALUE;

	textureOffset += GOALTAPE_ANIMATION_VALUE;
	AnimationGoalTape();
}

/**************************************
描画処理
***************************************/
void DrawGoalTape(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX mtxWorld, mtxTranslate;

	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixTranslation(&mtxTranslate, entity.pos.x, entity.pos.y, entity.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);

#ifdef _DEBUG
	DrawBoundingCube(&entity.collider);
#endif
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexGoalTape(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-GOALTAPE_SIZE_X / 2.0f, GOALTAPE_SIZE_Y / 2.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(GOALTAPE_SIZE_X / 2.0f, GOALTAPE_SIZE_Y / 2.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-GOALTAPE_SIZE_X / 2.0f, -GOALTAPE_SIZE_Y / 2.0f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(GOALTAPE_SIZE_X / 2.0f, -GOALTAPE_SIZE_Y / 2.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(GOALTAPE_TEXTURE_LOOP_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, GOALTAPE_TEXTURE_LOOP_Y);
	pVtx[3].tex = D3DXVECTOR2(GOALTAPE_TEXTURE_LOOP_X, GOALTAPE_TEXTURE_LOOP_Y);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}

/**************************************
アドレス取得処理
***************************************/
GOALTAPE *GetGoalTapeAdr(void)
{
	return &entity;
}

/**************************************
アニメーション処理
***************************************/
void AnimationGoalTape(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(textureOffset, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(textureOffset + GOALTAPE_TEXTURE_LOOP_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(textureOffset, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(textureOffset + GOALTAPE_TEXTURE_LOOP_X, 1.0f);

	vtxBuff->Unlock();
}