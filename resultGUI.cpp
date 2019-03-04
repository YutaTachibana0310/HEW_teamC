//=====================================
//
//リザルトGUI処理[resultGUI.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "resultGUI.h"

/**************************************
マクロ定義
***************************************/
#define RESULTGUI_TEXTURE_NAME			"data/TEXTURE/UI/rankingResult.png"
#define RESULTGUI_SIZE_X				(200.0f)
#define RESULTGUI_SIZE_Y				(RESULTGUI_SIZE_X*1.24f)
#define RESULTGUI_POS					(D3DXVECTOR3(WINDOW_CENTER_X, 300.0f, 0.0f))
#define RESULTGUI_OFFSET_X				(SCREEN_WIDTH / 2.0f)
#define RESULTGUI_TEX_DIV_X				(2)

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
void MakeVertexResultGUI(void);

/**************************************
初期化処理
***************************************/
void InitResultGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)RESULTGUI_TEXTURE_NAME, pDevice);

	MakeVertexResultGUI();
}

/**************************************
終了処理
***************************************/
void UninitResultGUI(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateResultGUI(void)
{

}

/**************************************
描画処理
***************************************/
void DrawResultGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetTexture(0, texture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexResultGUI(void)
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
リザルトGUIセット処理
***************************************/
void SetResultGUI(int playerID, bool isWinner)
{
	//UV座標設定処理
	float sizeX = 1.0f / RESULTGUI_TEX_DIV_X;
	int x = isWinner ? 0 : 1;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, 1.0f);

	//頂点座標設定処理
	float offset = playerID == 0 ? -RESULTGUI_OFFSET_X : RESULTGUI_OFFSET_X;
	D3DXVECTOR3 pos = RESULTGUI_POS;
	pos.x += offset;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-RESULTGUI_SIZE_X / 2.0f, -RESULTGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( RESULTGUI_SIZE_X / 2.0f, -RESULTGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-RESULTGUI_SIZE_X / 2.0f,  RESULTGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( RESULTGUI_SIZE_X / 2.0f,  RESULTGUI_SIZE_Y / 2.0f, 0.0f);
}