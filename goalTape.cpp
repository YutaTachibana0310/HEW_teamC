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
#define GOALTAPE_COLLIDER_LENGTH		(D3DXVECTOR3(500.0f, 100.0f, 0.0f))
#define GOALTAPE_SIZE_X					(500.0f)
#define GOALTAPE_SIZE_Y					(2.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static GOALTAPE entity;

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexGoalTape(void);

/**************************************
初期化処理
***************************************/
void InitGoalTape(int num)
{
	MakeVertexGoalTape();
	//entity.pos.z = SYSTEMPARAMETER_PROGRESS_MAX;
	entity.pos.z = 200.0f;
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
}

/**************************************
描画処理
***************************************/
void DrawGoalTape(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, NULL);
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX mtxWorld, mtxTranslate;
	
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixTranslation(&mtxTranslate, entity.pos.x, entity.pos.y, entity.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
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
	pVtx[1].vtx = D3DXVECTOR3( GOALTAPE_SIZE_X / 2.0f, GOALTAPE_SIZE_Y / 2.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-GOALTAPE_SIZE_X / 2.0f,-GOALTAPE_SIZE_Y / 2.0f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3( GOALTAPE_SIZE_X / 2.0f,-GOALTAPE_SIZE_Y / 2.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}