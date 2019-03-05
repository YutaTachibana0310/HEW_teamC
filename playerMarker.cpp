//=====================================
//
//プレイヤーマーカー処理[playerMarker.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "playerMarker.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERMARKER_TEXTURE_NAME		"data/TEXTURE/UI/playerMarker.png"
#define PLAYERMARKER_SIZE_X				(100.0f)
#define PLAYERMARKER_SIZE_Y				(100.0f)

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
void MakeVertexPlayerMarker(void);

/**************************************
初期化処理
***************************************/
void InitPlayerMarker(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)PLAYERMARKER_TEXTURE_NAME, pDevice);
	MakeVertexPlayerMarker();
}

/**************************************
終了処理
***************************************/
void UninitPlayerMarker(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdatePlayerMarker(void)
{

}

/**************************************
描画処理
***************************************/
void DrawPlayerMarker(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, texture);

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexPlayerMarker(void)
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
プレイヤーマーカーセット処理
***************************************/
void SetPlayerMarker(int playerID, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX view, projection;
	D3DVIEWPORT9 viewPort;

	//ビュー行列、プロジェクション行列、ビューポート行列を取得
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetViewport(&viewPort);

	//ビュー変換、プロジェクション変換をする
	D3DXVECTOR3 screenPos;
	D3DXVec3TransformCoord(&screenPos, &pos, &view);
	D3DXVec3TransformCoord(&screenPos, &screenPos, &projection);
	
	//ビューポート変換を行う
	D3DXVECTOR3 setPos;
	setPos.x = screenPos.x * (viewPort.Width / 2.0f) + viewPort.Width / 2.0f + viewPort.X;
	setPos.y = screenPos.y * (-(float)viewPort.Height / 2.0f) + viewPort.Height / 2.0f + viewPort.Y;
	setPos.z = 0.0f;

	//座標を画面内に収める
	setPos.x = Clampf((float)viewPort.X + PLAYERMARKER_SIZE_X / 2.0f, (float)(viewPort.X + viewPort.Width) - PLAYERMARKER_SIZE_X / 2.0f, setPos.x);
	setPos.y = Clampf((float)viewPort.Y + PLAYERMARKER_SIZE_Y / 2.0f, (float)(viewPort.Y + viewPort.Height) - PLAYERMARKER_SIZE_Y / 2.0f, setPos.y);

	//頂点座標をセット
	vtxWk[0].vtx = setPos + D3DXVECTOR3(-PLAYERMARKER_SIZE_X / 2.0f, -PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = setPos + D3DXVECTOR3( PLAYERMARKER_SIZE_X / 2.0f, -PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = setPos + D3DXVECTOR3(-PLAYERMARKER_SIZE_X / 2.0f,  PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = setPos + D3DXVECTOR3( PLAYERMARKER_SIZE_X / 2.0f,  PLAYERMARKER_SIZE_Y / 2.0f, 0.0f);

	//UV座標をセット
	float sizeY = 1.0f / TARGETPLAYER_MAX;
	vtxWk[0].tex = D3DXVECTOR2(0.0f, playerID * sizeY);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, playerID * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, (playerID + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, (playerID + 1) * sizeY);
}