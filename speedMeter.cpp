//=============================================================================
//
// タイトル画面処理 [speedMeter.cpp]
// Author : GP11A341 32 堀内和希
//
//=============================================================================
#include "speedMeter.h"
#include "Easing.h"
#include "gameParameter.h"

//*******************************************************************************************************
//マクロ定義
//*******************************************************************************************************
#define TEXTURE_SPEED_CIRCLE		"data/TEXTURE/EFFECT/speedGauge_circle.png"
#define TEXTURE_SPEED_METER			"data/TEXTURE/EFFECT/speedGauge_meter.png"

#define CIRCLE_MAX					(2)					//サークルの数
#define METER_MAX					(2)					//メーターの数
#define TEXTURE_CIRCLE_SIZE_X		(250.0f)			//サークルの横軸サイズ
#define TEXTURE_CIRCLE_SIZE_Y		(250.0f)			//サークルの縦軸サイズ
#define TEXTURE_METER_SIZE_X		(250.0f)			//メーターの横軸サイズ
#define TEXTURE_METER_SIZE_Y		(250.0f)			//メーターの縦軸サイズ

#define SPEEDCIRCLE_ZERO_POS_X		(130)						//左のサークルの位置							
#define SPEEDCIRCLE_ZERO_POS_Y		(250)		//左のサークルの位置
#define SPEEDCIRCLE_ONE_POS_X		(WINDOW_WIDTH - 130)	//右のサークルの位置
#define SPEEDCIRCLE_ONE_POS_Y		(250)		//右のサークルの位置

#define SPEEDMETER_ZERO_POS_X		(130)					//左のメーターの位置
#define SPEEDMETER_ZERO_POS_Y		(250)					//左のメーターの位置
#define SPEEDMETER_ONE_POS_X		(WINDOW_WIDTH - 130)	//右のメーターの位置
#define PROGRESMETER_POS_BOTTOM		(D3DXToRadian(-220.0f))						//メーターの回転初期位置
#define PROGRESMETER_POS_TOP		(D3DXToRadian(220.0f))						//メーターの回転の限界値

#define SPEEDMETER_ANGLE_VALUE		(0.05f)

#define SPEEDMETER_ANGLE_MIN		(0.0f)
#define SPEEDMETER_ANGLE_MAX		(4.5f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSpeedGUI(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		D3DTextureSpeedCircle[2] = {};					// テクスチャへのポインタ
static LPDIRECT3DTEXTURE9		D3DTextureSpeedMeter = NULL;					// テクスチャへのポインタ

static VERTEX_2D				vertexWkSpeedCircle[CIRCLE_MAX][NUM_VERTEX];	// 頂点情報格納ワーク
static METER					meterWk[METER_MAX];								// メーター構造体

static float currentSpeed[TARGETPLAYER_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSpeedGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	METER *meter = meterWk;

	meter->pos = D3DXVECTOR3(SPEEDMETER_ZERO_POS_X, SPEEDMETER_ZERO_POS_Y, 0.0f);
	meter->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	meter->texture = D3DTextureSpeedMeter;
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_METER_SIZE_X / 2, TEXTURE_METER_SIZE_Y / 2);
	meter->radius = D3DXVec2Length(&temp);									// エネミーの半径を初期化
	meter->baseAngle = atan2f(TEXTURE_METER_SIZE_Y, TEXTURE_METER_SIZE_X);	// エネミーの角度を初期化

// スピードサークルの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_SPEED_CIRCLE,			// ファイルの名前
		&D3DTextureSpeedCircle[0]);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_SPEED_CIRCLE,			// ファイルの名前
		&D3DTextureSpeedCircle[1]);		// 読み込むメモリー

	//スピードメーターの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_SPEED_METER,			// ファイルの名前
		&D3DTextureSpeedMeter);			// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexSpeedGUI();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSpeedGUI(void)
{
	//スピードサークル
	if (D3DTextureSpeedCircle[0] != NULL)
	{// テクスチャの開放
		D3DTextureSpeedCircle[0]->Release();
		D3DTextureSpeedCircle[0] = NULL;
	}

	if (D3DTextureSpeedCircle[1] != NULL)
	{// テクスチャの開放
		D3DTextureSpeedCircle[1]->Release();
		D3DTextureSpeedCircle[1] = NULL;
	}

	//スピードメーター
	if (D3DTextureSpeedMeter != NULL)
	{// テクスチャの開放
		D3DTextureSpeedMeter->Release();
		D3DTextureSpeedMeter = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSpeedGUI(void)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		float diff = GetGameParameterAdr(i)->playerSpeed - currentSpeed[i];
		currentSpeed[i] += diff * SPEEDMETER_ANGLE_VALUE;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSpeedGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	METER *meter = meterWk;
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//スピードメーター
	// テクスチャの設定
	pDevice->SetTexture(0, D3DTextureSpeedMeter);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, meter->vertexWkSpeedMeter, sizeof(VERTEX_2D));

	//スピードサークル
	for (int i = 0; i < CIRCLE_MAX; i++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, D3DTextureSpeedCircle[i]);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkSpeedCircle[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSpeedGUI(void)
{
	METER *meter = meterWk;

	// サークル頂点座標の設定
	vertexWkSpeedCircle[0][0].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[0][1].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[0][2].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[0][3].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);

	vertexWkSpeedCircle[1][0].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[1][1].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[1][2].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[1][3].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);

	//スピードサークルの設定
	for (int i = 0; i < CIRCLE_MAX; i++)
	{
		// テクスチャのパースペクティブコレクト用
		vertexWkSpeedCircle[i][0].rhw =
			vertexWkSpeedCircle[i][1].rhw =
			vertexWkSpeedCircle[i][2].rhw =
			vertexWkSpeedCircle[i][3].rhw = 1.0f;

		// 反射光の設定
		vertexWkSpeedCircle[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkSpeedCircle[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkSpeedCircle[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkSpeedCircle[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		vertexWkSpeedCircle[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexWkSpeedCircle[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexWkSpeedCircle[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexWkSpeedCircle[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//スピードメーターの設定
	// テクスチャのパースペクティブコレクト用
	meter->vertexWkSpeedMeter[0].rhw =
		meter->vertexWkSpeedMeter[1].rhw =
		meter->vertexWkSpeedMeter[2].rhw =
		meter->vertexWkSpeedMeter[3].rhw = 1.0f;

	// 反射光の設定
	meter->vertexWkSpeedMeter[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	meter->vertexWkSpeedMeter[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	meter->vertexWkSpeedMeter[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	meter->vertexWkSpeedMeter[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	return S_OK;
}

//=============================================================================
// メーターの頂点の設定
//=============================================================================
void SetVertexMeter(int meterID, float percent)
{
	METER *meter = meterWk;

	//連番になってる画像の分割
	////UV座標設定
	//float sizeX = 1.0f / PROGRESMETER_TEXTURE_DIV_X;
	//float sizeY = 1.0f / PROGRESMETER_TEXTURE_DIV_X;
	//int x = meterID % PROGRESMETER_TEXTURE_DIV_X;
	//int y = meterID / PROGRESMETER_TEXTURE_DIV_Y;

	//UV座標設定
	meter->pos.x = (meterID == 0) ? SPEEDMETER_ZERO_POS_X : SPEEDMETER_ONE_POS_X;
	float t = currentSpeed[meterID] / 5.0f;
	meter->rot.z = EaseLinear(t, SPEEDMETER_ANGLE_MIN, SPEEDMETER_ANGLE_MAX);
	meter->rot.z += D3DXToRadian(-180.0f);

	meter->vertexWkSpeedMeter[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	meter->vertexWkSpeedMeter[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	meter->vertexWkSpeedMeter[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	meter->vertexWkSpeedMeter[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//メーター頂点座標の設定
	meter->vertexWkSpeedMeter[0].vtx.x = meter->pos.x - cosf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[0].vtx.y = meter->pos.y - sinf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[0].vtx.z = 0.0f;

	meter->vertexWkSpeedMeter[1].vtx.x = meter->pos.x + cosf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[1].vtx.y = meter->pos.y - sinf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[1].vtx.z = 0.0f;

	meter->vertexWkSpeedMeter[2].vtx.x = meter->pos.x - cosf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[2].vtx.y = meter->pos.y + sinf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[2].vtx.z = 0.0f;

	meter->vertexWkSpeedMeter[3].vtx.x = meter->pos.x + cosf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[3].vtx.y = meter->pos.y + sinf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[3].vtx.z = 0.0f;
}
