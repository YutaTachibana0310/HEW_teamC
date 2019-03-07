//=====================================
//
//タイムGUI処理[timeGUI.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "timeGUI.h"

/**************************************
マクロ定義
***************************************/
#define TIMEGUI_NUMTEX_NAME				"data/TEXTURE/SCORE/number002.png"
#define TIMEGUI_NUMTEX_SIZE_X			(40.0f)
#define TIMEGUI_NUMTEX_SIZE_Y			(50.0f)
#define TIMEGUI_NUMTEX_BASEPOS_1P		(D3DXVECTOR3(SCREEN_WIDTH - TIMEGUI_NUMTEX_SIZE_X, 110.0f, 0.0f))
#define TIMEGUI_NUMTEX_BASEPOS_2P		(D3DXVECTOR3(WINDOW_WIDTH - TIMEGUI_NUMTEX_SIZE_X, 110.0f, 0.0f))
#define TIMEGUI_NUMTEX_OFFSET			(-25.0f)
#define TIMEGUI_NUMTEX_DIV_X			(10)
#define TIMEGUI_NUMTEX_DECIMAL_DIGIT	(2)
#define TIMEGUI_NUMTEX_OFFSET_INT		(-10.0f)

#define TIMEGUI_TEXTTEX_NAME			"data/TEXTURE/SCORE/timeText.png"
#define TIMEGUI_TEXTTEX_SIZE_X			(240.0f)
#define TIMEGUI_TEXTTEX_SIZE_Y			(TIMEGUI_TEXTTEX_SIZE_X / 3.0f)
#define TIMEGUI_TEXTTEX_BASEPOS_1P		(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 50.0f, 0.0f))
#define TIMEGUI_TEXTTEX_BASEPOS_2P		(D3DXVECTOR3(WINDOW_WIDTH - 400.0f, 50.0f, 0.0f))

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 numTex, textTex;
static VERTEX_2D vtxWk[NUM_VERTEX];

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexTimeGUI(void);
void SetTimeGUI(int num, int digit, bool is1P);
void SetTimeText(bool is2P);

/**************************************
初期化処理
***************************************/
void InitTimeGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	numTex = CreateTextureFromFile((LPSTR)TIMEGUI_NUMTEX_NAME, pDevice);
	textTex = CreateTextureFromFile((LPSTR)TIMEGUI_TEXTTEX_NAME, pDevice);
	MakeVertexTimeGUI();
}

/**************************************
終了処理
***************************************/
void UninitTimeGUI(int num)
{
	SAFE_RELEASE(numTex);
	SAFE_RELEASE(textTex);
}

/**************************************
更新処理
***************************************/
void UpdateTimeGUI(void)
{

}

/**************************************
描画処理
***************************************/
void DrawTimeGUI(float time1P, float time2P)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//TIMEを描画
	pDevice->SetTexture(0, textTex);
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetTimeText(i == 0);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}

	//タイムの数字を描画
	pDevice->SetTexture(0, numTex);
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		int time = i == 0 ? time1P * 100 : time2P * 100;
		int digitMax = time == 0 ? 1 : (int)log10f((float)time) + 1;
		for (int digit = 0; digit < digitMax; digit++, time /= 10)
		{
			int num = time % 10;
			SetTimeGUI(num, digit, i == 0);
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
		}
	}
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexTimeGUI(void)
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
テキスト頂点設定処理
***************************************/
void SetTimeText(bool is1P)
{
	//頂点座標設定
	D3DXVECTOR3 pos = is1P ? TIMEGUI_TEXTTEX_BASEPOS_1P : TIMEGUI_TEXTTEX_BASEPOS_2P;
	vtxWk[0].vtx = pos + D3DXVECTOR3(-TIMEGUI_TEXTTEX_SIZE_X / 2.0f, -TIMEGUI_TEXTTEX_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3(TIMEGUI_TEXTTEX_SIZE_X / 2.0f, -TIMEGUI_TEXTTEX_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-TIMEGUI_TEXTTEX_SIZE_X / 2.0f, TIMEGUI_TEXTTEX_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3(TIMEGUI_TEXTTEX_SIZE_X / 2.0f, TIMEGUI_TEXTTEX_SIZE_Y / 2.0f, 0.0f);

	//UV座標設定
	vtxWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

/**************************************
数字頂点設定処理
***************************************/
void SetTimeGUI(int num, int digit, bool is1P)
{
	//頂点座標設定
	D3DXVECTOR3 pos = is1P ? TIMEGUI_NUMTEX_BASEPOS_1P : TIMEGUI_NUMTEX_BASEPOS_2P;
	pos.x += digit * TIMEGUI_NUMTEX_OFFSET;
	if (digit >= TIMEGUI_NUMTEX_DECIMAL_DIGIT) pos.x += TIMEGUI_NUMTEX_OFFSET_INT;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-TIMEGUI_NUMTEX_SIZE_X / 2.0f, -TIMEGUI_NUMTEX_SIZE_Y / 2.0f, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3(TIMEGUI_NUMTEX_SIZE_X / 2.0f, -TIMEGUI_NUMTEX_SIZE_Y / 2.0f, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-TIMEGUI_NUMTEX_SIZE_X / 2.0f, TIMEGUI_NUMTEX_SIZE_Y / 2.0f, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3(TIMEGUI_NUMTEX_SIZE_X / 2.0f, TIMEGUI_NUMTEX_SIZE_Y / 2.0f, 0.0f);

	//UV座標設定
	float sizeX = 1.0f / TIMEGUI_NUMTEX_DIV_X;
	vtxWk[0].tex = D3DXVECTOR2(num * sizeX, 0.0f);
	vtxWk[1].tex = D3DXVECTOR2((num + 1) * sizeX, 0.0f);
	vtxWk[2].tex = D3DXVECTOR2(num * sizeX, 1.0f);
	vtxWk[3].tex = D3DXVECTOR2((num + 1) * sizeX, 1.0f);
}