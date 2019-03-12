//=====================================
//
//カウントダウンGUI処理[template.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "countDownGUI.h"
#include "Easing.h"

#include "soundEffectManager.h"

/**************************************
マクロ定義
***************************************/
#define COUNTDOWNGUI_TEXTURE_NAME		"data/TEXTURE/UI/countDownGUI.png"
#define COUNTDOWNGUI_SIZE_X				(300.0f)
#define COUNTDONWGUI_SIZE_Y				(300.0f)
#define COUNTDOWNGUI_POS				(D3DXVECTOR3(WINDOW_CENTER_X, 300.0f, 0.0f))
#define COUNTDOWNGUI_OFFSET_X			(SCREEN_WIDTH / 2.0f)
#define COUNTDOWNGUI_TEX_DIV_X			(2)
#define COUNTDOWNGUI_TEX_DIV_Y			(2)
#define COUNTDOWNGUI_ANIM_DURATION		(60)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DTEXTURE9 texture;
static VERTEX_2D vtxWk[NUM_VERTEX];
static int cntFrame;
static float scale;
static bool active;
static int animPattern;

/**************************************
プロトタイプ宣言
***************************************/
void MakeVertexCountDownGUI(void);
void SetVertexCountDownGUI(int i);
void SetTextureCountDownGUI(int pattern);

/**************************************
初期化処理
***************************************/
void InitCountDownGUI(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	texture = CreateTextureFromFile((LPSTR)COUNTDOWNGUI_TEXTURE_NAME, pDevice);

	MakeVertexCountDownGUI();

	active = false;
}

/**************************************
終了処理
***************************************/
void UninitCountDownGUI(int num)
{
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateCountDownGUI(void)
{
	if (!active)
		return;

	cntFrame++;

	//スケールをトゥイーニング
	float t = (float)cntFrame / COUNTDOWNGUI_ANIM_DURATION;
	scale = EaseOutExponential(t, 0.0f, 1.0f);

	//テクスチャアニメーション
	if (cntFrame == COUNTDOWNGUI_ANIM_DURATION)
	{
		cntFrame = 0;
		animPattern++;

		if (animPattern == COUNTDOWNGUI_TEX_DIV_X * COUNTDOWNGUI_TEX_DIV_Y)
			active = false;
	}
}

/**************************************
描画処理
***************************************/
void DrawCountDownGUI(void)
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTexture(0, texture);

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		SetVertexCountDownGUI(i);
		SetTextureCountDownGUI(animPattern);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vtxWk, sizeof(VERTEX_2D));
	}
}

/**************************************
頂点作成処理
***************************************/
void MakeVertexCountDownGUI(void)
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
UV座標設定処理
***************************************/
void SetTextureCountDownGUI(int pattern)
{
	float sizeX = 1.0f / COUNTDOWNGUI_TEX_DIV_X;
	float sizeY = 1.0f / COUNTDOWNGUI_TEX_DIV_Y;
	int x = pattern % COUNTDOWNGUI_TEX_DIV_X;
	int y = pattern / COUNTDOWNGUI_TEX_DIV_Y;

	vtxWk[0].tex = D3DXVECTOR2(x * sizeX, y * sizeY);
	vtxWk[1].tex = D3DXVECTOR2((x + 1) * sizeX, y * sizeY);
	vtxWk[2].tex = D3DXVECTOR2(x * sizeX, (y + 1) * sizeY);
	vtxWk[3].tex = D3DXVECTOR2((x + 1) * sizeX, (y + 1) * sizeY);
}

/**************************************
頂点座標設定処理
***************************************/
void SetVertexCountDownGUI(int i)
{
	D3DXVECTOR3 pos = COUNTDOWNGUI_POS;
	float offsetX = i == 0 ? -COUNTDOWNGUI_OFFSET_X : COUNTDOWNGUI_OFFSET_X;
	pos.x += offsetX;

	vtxWk[0].vtx = pos + D3DXVECTOR3(-COUNTDOWNGUI_SIZE_X / 2.0f * scale, -COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
	vtxWk[1].vtx = pos + D3DXVECTOR3( COUNTDOWNGUI_SIZE_X / 2.0f * scale, -COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
	vtxWk[2].vtx = pos + D3DXVECTOR3(-COUNTDOWNGUI_SIZE_X / 2.0f * scale,  COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
	vtxWk[3].vtx = pos + D3DXVECTOR3( COUNTDOWNGUI_SIZE_X / 2.0f * scale,  COUNTDONWGUI_SIZE_Y / 2.0f * scale, 0.0f);
}

/**************************************
カウントダウンGUIセット処理
***************************************/
void SetCountDownGUI(void)
{
	active = true;
	cntFrame = 0;
	animPattern = 0;
	PlaySE(SOUND_COUNTDOWN);
}