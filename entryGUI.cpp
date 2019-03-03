//=====================================
//
//エントリーGUI処理[entryGUI.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "entryGUI.h"

/**************************************
マクロ定義
***************************************/
#define ENTRYGUI_TEXTURE_NAME		"data/TEXTURE/UI/entryGUI.png"
#define ENTRYGUI_SIZE_X				(600.0f)
#define ENTRYGUI_SIZE_Y				(ENTRYGUI_SIZE_X / 8.0f)
#define ENTRYGUI_POS				(D3DXVECTOR3(WINDOW_CENTER_X, WINDOW_HEIGHT - 200.0f, 0.0f))
#define ENTRYGUI_OFFSET_X			(SCREEN_WIDTH / 2.0f)

/**************************************
構造体定義
***************************************/
enum ENTRYGUI_TEXTURE_INDEX {
	ENTRYGUI_TEXTURE_WAITINPUT,
	ENTRYGUI_TEXTURE_COMPLETE_ENTRY,
	ENTRYGUI_TEXTURE_INDEX_MAX
};

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexEntryGUI(void);

/**************************************
初期化処理
***************************************/
void InitEntryGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)ENTRYGUI_TEXTURE_NAME, pDevice);
	MakeVertexEntryGUI();
}

/**************************************
終了処理
***************************************/
void UninitEntryGUI(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateEntryGUI(void)
{

}

/**************************************
描画処理
***************************************/
void DrawEntryGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexEntryGUI(void)
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
頂点設定処理
***************************************/
void SetEntryGUI(int playerID, bool isCompleted)
{
	float sizeY = 1.0f / ENTRYGUI_TEXTURE_INDEX_MAX;
	int y = isCompleted ? ENTRYGUI_TEXTURE_COMPLETE_ENTRY : ENTRYGUI_TEXTURE_WAITINPUT;

	vtxWk[0].tex = D3DXVECTOR2(0.0f, sizeY * y);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, sizeY * y);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, sizeY * (y + 1));
	vtxWk[3].tex = D3DXVECTOR2(1.0f, sizeY * (y + 1));

	float offsetX = playerID == 0 ? -ENTRYGUI_OFFSET_X : ENTRYGUI_OFFSET_X;
	D3DXVECTOR3 pos = ENTRYGUI_POS;
	pos.x += offsetX;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-ENTRYGUI_SIZE_X / 2.0f, -ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( ENTRYGUI_SIZE_X / 2.0f, -ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-ENTRYGUI_SIZE_X / 2.0f,  ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( ENTRYGUI_SIZE_X / 2.0f,  ENTRYGUI_SIZE_Y / 2.0f, 0.0f);
}