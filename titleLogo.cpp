//=====================================
//
//タイトルロゴ処理[titleLogo.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "titleLogo.h"

/**************************************
マクロ定義
***************************************/
#define TITLELOGO_TEXTURE_NAME		"data/TEXTURE/UI/titleLogo.png"
#define TITLELOGO_SIZE_X			(800.0f)
#define TITLELOGO_SIZE_Y			(400.0f)
#define TITLELOGO_POS				(D3DXVECTOR3(WINDOW_CENTER_X, 300.0f, 0.0f))

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static VERTEX_2D vtxWk[NUM_VERTEX];
static LPDIRECT3DTEXTURE9 texture;

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexTitleLogo(void);

/**************************************
初期化処理
***************************************/
void InitTitleLogo(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)TITLELOGO_TEXTURE_NAME, pDevice);
	MakeVertexTitleLogo();
}

/**************************************
終了処理
***************************************/
void UninitTitleLogo(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateTitleLogo(void)
{

}

/**************************************
描画処理
***************************************/
void DrawTitleLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexTitleLogo(void)
{
	vtxWk[0].vtx = TITLELOGO_POS + D3DXVECTOR3(-TITLELOGO_SIZE_X / 2.0f, -TITLELOGO_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = TITLELOGO_POS + D3DXVECTOR3( TITLELOGO_SIZE_X / 2.0f, -TITLELOGO_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = TITLELOGO_POS + D3DXVECTOR3(-TITLELOGO_SIZE_X / 2.0f,  TITLELOGO_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = TITLELOGO_POS + D3DXVECTOR3( TITLELOGO_SIZE_X / 2.0f,  TITLELOGO_SIZE_Y / 2.0f, 0.0f);

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
