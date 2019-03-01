//=====================================
//
//進行ゲージ処理[progressGauge.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "progressGauge.h"

/**************************************
マクロ定義
***************************************/
#define PROGRESSGAUGE_TEXTURE_NAME		"data/TEXTURE/UI/progressGauge.png"
#define PROGRESSGAUGE_TEXTURE_SIZE_Y	(WINDOW_HEIGHT)
#define PROGRESSGAUGE_TEXTURE_SIZE_X	(PROGRESSGAUGE_TEXTURE_SIZE_Y / 8.0f)
#define PROGRESSGAUGE_BASEPOS			(D3DXVECTOR3(WINDOW_CENTER_X, WINDOW_CENTER_Y, 0.0f))

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 gaugeTex;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
プロトタイプ宣言
***************************************/
void SetVertexProgressGauge(void);

/**************************************
初期化処理
***************************************/
void InitProgressGauge(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexProgressGauge();
	gaugeTex = CreateTextureFromFile((LPSTR)PROGRESSGAUGE_TEXTURE_NAME, pDevice);
}

/**************************************
終了処理
***************************************/
void UninitProgressGauge(int num)
{
	SAFE_RELEASE(gaugeTex);
}

/**************************************
更新処理
***************************************/
void UpdateProgressGauge(void)
{

}

/**************************************
描画処理
***************************************/
void DrawProgressGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, gaugeTex);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void SetVertexProgressGauge(void)
{
	vtxWk[0].vtx = D3DXVECTOR3(-PROGRESSGAUGE_TEXTURE_SIZE_X / 2.0f, -PROGRESSGAUGE_TEXTURE_SIZE_Y / 2.0f, 0.0f) + PROGRESSGAUGE_BASEPOS;
	vtxWk[1].vtx = D3DXVECTOR3( PROGRESSGAUGE_TEXTURE_SIZE_X / 2.0f, -PROGRESSGAUGE_TEXTURE_SIZE_Y / 2.0f, 0.0f) + PROGRESSGAUGE_BASEPOS;
	vtxWk[2].vtx = D3DXVECTOR3(-PROGRESSGAUGE_TEXTURE_SIZE_X / 2.0f,  PROGRESSGAUGE_TEXTURE_SIZE_Y / 2.0f, 0.0f) + PROGRESSGAUGE_BASEPOS;
	vtxWk[3].vtx = D3DXVECTOR3( PROGRESSGAUGE_TEXTURE_SIZE_X / 2.0f,  PROGRESSGAUGE_TEXTURE_SIZE_Y / 2.0f, 0.0f) + PROGRESSGAUGE_BASEPOS;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}