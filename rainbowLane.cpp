//=====================================
//
//レインボーレーン処理[rainbowLane.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "rainbowLane.h"
#include "gameParameter.h"

/**************************************
マクロ定義
***************************************/
#define RAINBOWLANE_TEXTURE_NAME	"data/TEXTURE/BG/rainbowLane.jpg"	//テクスチャのパス
#define RAINBOWLANE_BACK_END		(-1000.0f)							//レーンの後ろの端
#define RAINBOWLANE_FRONT_END		(20000.0f)							//レーンの前の端
#define RAINBOWLANE_WIDTH			(5.0f)								//レーンの幅
#define RAINBOWLANE_TEXTURELOOP		(200.0f)							//テクスチャループ回数
#define RAINBOWLANE_SCROLLSPEED		(-0.05f)							//スクロール速度
#define RAINBOWLANE_NUM_MAX			(3)									//レーン最大数
#define RAINBOWLANE_BASEPOS_Y		(-50.0f)							//レーンの基準位置(Y)
#define RAINBOWLANE_OFFSET_X		(50.0f)								//レーンのオフセット(X)
#define RAINBOWLANE_OFFSET_Y		(30.0f)								//レーンのオフセット(Y)
#define RAINBOWLANE_ROT_VALUE		(D3DXToRadian(40.0f))				//レーンの回転量

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 vtxBuff;				//頂点バッファ
static LPDIRECT3DTEXTURE9 texture;					//テクスチャ
static int cntFrame;								//カウントフレーム



//各レーンの座標
static D3DXVECTOR3 lanePos[RAINBOWLANE_NUM_MAX] = {
	D3DXVECTOR3(-RAINBOWLANE_OFFSET_X, RAINBOWLANE_BASEPOS_Y + RAINBOWLANE_OFFSET_Y, 0.0f),
	D3DXVECTOR3(0.0f, RAINBOWLANE_BASEPOS_Y, 0.0f),
	D3DXVECTOR3(RAINBOWLANE_OFFSET_X, RAINBOWLANE_BASEPOS_Y + RAINBOWLANE_OFFSET_Y, 0.0f),
};	



//各レーンの回転量
static D3DXVECTOR3 laneRot[RAINBOWLANE_NUM_MAX] = {
	D3DXVECTOR3(0.0f, 0.0f, -RAINBOWLANE_ROT_VALUE),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, RAINBOWLANE_ROT_VALUE),
};

/**************************************
プロトタイプ宣言
***************************************/
void SetVertexRainbowLane(void);			//頂点設定処理
void ScrollRainbowLane(int n);				//スクロール処理

/**************************************
lanePos.yのGet関数
***************************************/
D3DXVECTOR3 GetLanePos(int num)
{
	return lanePos[num];
}

/**************************************
lレーンの回転のGet関数
***************************************/
D3DXVECTOR3 GetLaneRot(int num)
{
	return laneRot[num];
}

/**************************************
初期化処理
***************************************/
void InitRainbowLane(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&vtxBuff,
		NULL);

	//テクスチャを読み込み
	texture = CreateTextureFromFile((LPSTR)RAINBOWLANE_TEXTURE_NAME, pDevice);

	SetVertexRainbowLane();
}

/**************************************
終了処理
***************************************/
void UninitRainbowLane(int num)
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);
}

/**************************************
更新処理
***************************************/
void UpdateRainbowLane(void)
{
	cntFrame++;
}

/**************************************
描画処理
***************************************/
void DrawRainbowLane(int n)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld, mtxTranslate, mtxRot;

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//テクスチャをスクロール
	ScrollRainbowLane(n);

	//回転でレーンの明るさが変わらないようにライティングはオフに
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	for (int i = 0; i < RAINBOWLANE_NUM_MAX; i++)
	{
		D3DXMatrixIdentity(&mtxWorld);

		//回転
		D3DXMatrixRotationYawPitchRoll(&mtxRot, laneRot[i].y, laneRot[i].x, laneRot[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//移動
		D3DXMatrixTranslation(&mtxTranslate, lanePos[i].x, lanePos[i].y, lanePos[i].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
		
		//ワールド変換行列をセット
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	//ライティングをもとに戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
頂点設定処理
***************************************/
void SetVertexRainbowLane(void)
{
	VERTEX_3D *pVtx;

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	pVtx[0].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[1].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_FRONT_END);
	pVtx[2].vtx = D3DXVECTOR3(-RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);
	pVtx[3].vtx = D3DXVECTOR3( RAINBOWLANE_WIDTH / 2.0f, 0.0f, RAINBOWLANE_BACK_END);

	//UV座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, RAINBOWLANE_TEXTURELOOP);

	//法線設定
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//ディフューズ設定
	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	vtxBuff->Unlock();
}

/**************************************
スクロール処理
***************************************/
void ScrollRainbowLane(int n)
{
	VERTEX_3D *pVtx;
	GAMEPARAMETER *param = GetGameParameterAdr(n);

	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//UV座標のオフセットを計算
	float offset = cntFrame * RAINBOWLANE_SCROLLSPEED * param->playerSpeed;

	pVtx[0].tex = D3DXVECTOR2(0.0f, offset);
	pVtx[1].tex = D3DXVECTOR2(1.0f, offset);
	pVtx[2].tex = D3DXVECTOR2(0.0f, offset + RAINBOWLANE_TEXTURELOOP);
	pVtx[3].tex = D3DXVECTOR2(1.0f, offset + RAINBOWLANE_TEXTURELOOP);

	vtxBuff->Unlock();
}