//=====================================
//
//レインボーレーン処理[rainbowLane.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "rainbowLane.h"

/**************************************
マクロ定義
***************************************/
#define RAINBOWLANE_TEXTURE_NAME	"data/TEXTURE/BG/rainbowLane.jpg"
#define RAINBOWLANE_BACK_END		(-1000.0f)
#define RAINBOWLANE_FRONT_END		(20000.0f)
#define RAINBOWLANE_WIDTH			(5.0f)
#define RAINBOWLANE_TEXTURELOOP		(200.0f)
#define RAINBOWLANE_SCROLLSPEED		(-0.05f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;
static LPDIRECT3DTEXTURE9 texture;
static int cntFrame;

/**************************************
プロトタイプ宣言
***************************************/
void SetVertexRainbowLane(void);
void ScrollRainbowLane(void);

/**************************************
初期化処理
***************************************/
void InitRainbowLane(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	texture = CreateTextureFromFile((LPSTR)RAINBOWLANE_TEXTURE_NAME, pDevice);

	SetVertexRainbowLane();
}

/**************************************
終了処理
***************************************/
void UninitRainbowLane(int num)
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateRainbowLane(void)
{
	cntFrame++;
	ScrollRainbowLane();
}

/**************************************
描画処理
***************************************/
void DrawRainbowLane(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	D3DXMatrixIdentity(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
頂点設定処理
***************************************/
void SetVertexRainbowLane(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[1].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[2].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);
	pVtx[3].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, RAINBOWLANE_TEXTURELOOP);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxBuff->Unlock();
}

/**************************************
スクロール処理
***************************************/
void ScrollRainbowLane(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float offset = cntFrame * RAINBOWLANE_SCROLLSPEED;

	pVtx[0].tex = D3DXVECTOR2(0.0f, offset);
	pVtx[1].tex = D3DXVECTOR2(1.0f, offset);
	pVtx[2].tex = D3DXVECTOR2(0.0f, offset + RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, offset + RAINBOWLANE_TEXTURELOOP);

	vtxBuff->Unlock();
}