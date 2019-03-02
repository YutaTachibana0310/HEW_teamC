//=====================================
//
//プログレスマーカー処理[progressMarker.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "progressMarker.h"
#include "Easing.h"

/**************************************
マクロ定義
***************************************/
#define PROGRESSMARKER_TEXTURE_NAME		"data/TEXTURE/UI/progressMarker.png"
#define PROGRESSMARKER_SIZE_X	(50.0f)
#define PROGRESSMARKER_SIZE_Y	(50.0f)
#define PROGRESSMARKER_TEXTURE_DIV_X	(2)
#define PROGRESSMARKER_TEXTURE_DIV_Y	(1)
#define PROGRESSMARKER_POS_OFFSET_X		(40)
#define PROGRESSMARKER_POS_TOP			(100.0f)
#define PROGRESSMARKER_POS_BOTTOM		(SCREEN_HEIGHT - 30.0f)

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
void MakeVertexProgressMarker(void);

/**************************************
初期化処理
***************************************/
void InitProgressMarker(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)PROGRESSMARKER_TEXTURE_NAME, pDevice);
	MakeVertexProgressMarker();
}

/**************************************
終了処理
***************************************/
void UninitProgressMarker(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateProgressMarker(void)
{

}

/**************************************
描画処理
***************************************/
void DrawProgressMarker(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexProgressMarker(void)
{
	vtxWk[0].diffuse =
		vtxWk[1].diffuse =
		vtxWk[2].diffuse =
		vtxWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	vtxWk[0].rhw =
		vtxWk[1].rhw =
		vtxWk[2].rhw =
		vtxWk[3].rhw = 1.0f;
}

/**************************************
マーカーセット処理
***************************************/
void SetProgressMarker(int targetID, float percent)
{
	//UV座標設定
	float sizeX = 1.0f / PROGRESSMARKER_TEXTURE_DIV_X;
	float sizeY = 1.0f / PROGRESSMARKER_TEXTURE_DIV_Y;
	int x = targetID % PROGRESSMARKER_TEXTURE_DIV_X;
	int y = targetID / PROGRESSMARKER_TEXTURE_DIV_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);

	//頂点座標設定
	D3DXVECTOR3 pos;
	pos.x = WINDOW_CENTER_X;
	pos.x += (targetID == 0) ? -PROGRESSMARKER_POS_OFFSET_X : PROGRESSMARKER_POS_OFFSET_X;
	pos.y = EaseLinear(percent, PROGRESSMARKER_POS_BOTTOM, PROGRESSMARKER_POS_TOP);

	vtxWk[0].vtx = pos + D3DXVECTOR3(-PROGRESSMARKER_SIZE_X / 2.0f, -PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( PROGRESSMARKER_SIZE_X / 2.0f, -PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-PROGRESSMARKER_SIZE_X / 2.0f,  PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( PROGRESSMARKER_SIZE_X / 2.0f,  PROGRESSMARKER_SIZE_Y / 2.0f, 0.0f);
}