//=====================================
//
//リザルトテロップ処理[resultTelop.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "resultTelop.h"

/**************************************
マクロ定義
***************************************/
#define RESULTTELOP_TEXTURE_NAME		"data/TEXTURE/UI/resultTelop.png"
#define RESULTTELOP_SIZE_X				(800)
#define RESULTTELOP_SIZE_Y				(RESULTTELOP_SIZE_X/2.6f)
#define RESULTTELOP_POS					(D3DXVECTOR3(WINDOW_CENTER_X, 150.0f, 0.0f))

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexResultTelop(void);

/**************************************
初期化処理
***************************************/
void InitResultTelop(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)RESULTTELOP_TEXTURE_NAME, pDevice);
	MakeVertexResultTelop();
}

/**************************************
終了処理
***************************************/
void UninitResultTelop(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateResultTelop(void)
{

}

/**************************************
描画処理
***************************************/
void DrawResultTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexResultTelop(void)
{
	vtxWk[0].vtx = RESULTTELOP_POS + D3DXVECTOR3(-RESULTTELOP_SIZE_X / 2.0f, -RESULTTELOP_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = RESULTTELOP_POS + D3DXVECTOR3( RESULTTELOP_SIZE_X / 2.0f, -RESULTTELOP_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = RESULTTELOP_POS + D3DXVECTOR3(-RESULTTELOP_SIZE_X / 2.0f,  RESULTTELOP_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = RESULTTELOP_POS + D3DXVECTOR3( RESULTTELOP_SIZE_X / 2.0f,  RESULTTELOP_SIZE_Y / 2.0f, 0.0f);

	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
}