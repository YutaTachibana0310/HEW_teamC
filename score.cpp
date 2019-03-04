//=============================================================================
//
// スコア処理 [score.cpp]
// Author :堀内和希
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/SCORE/number002.png"		//読み込むテクスチャファイル名
#define	TEXTURE_FRAME_SCORE	"data/TEXTURE/SCORE/frame_score.png"    //読み込むテクスチャファイル名
#define	SCORE_SIZE_X		(35.0f)									//スコアの数字の幅
#define	SCORE_SIZE_Y		(50.0f)									//スコアの数字の高さ
#define	SCORE_INTERVAL_X	(0.0f)									//スコアの数字の表示間隔

#define	NUM_PLACE			(6)										//スコアの桁数

#define SCORE_POS			(D3DXVECTOR3(WINDOW_CENTER_X, WINDOW_HEIGHT - 200.0f, 0.0f))
#define	SCORE_POS_X			(SCREEN_WIDTH - (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 600.0f)	//スコアの表示基準位置Ｘ座標
#define	SCORE_POS_Y			(25.0f)																	//スコアの表示基準位置Ｙ座標
#define SCORE_POW			(10.0f)									//スコアのパウ？
#define SCORE_VERTEX		(4)										//スコアの頂点数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureScore(int score, int number);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		pD3DTextureScore[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffScore = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				posScore;					// 位置
D3DXVECTOR3				rotScore;					// 向き

int						score;						// スコア

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// スコアの初期化
	score = 0;

	// 頂点情報の作成
	MakeVertexScore(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_SCORE,			// ファイルの名前
		&pD3DTextureScore[0]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FRAME_SCORE,		// ファイルの名前
		&pD3DTextureScore[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if (pD3DTextureScore[0] != NULL)
	{// テクスチャの開放
		pD3DTextureScore[0]->Release();
		pD3DTextureScore[0] = NULL;
	}
	if (pD3DTextureScore[1] != NULL)
	{// テクスチャの開放
		pD3DTextureScore[1]->Release();
		pD3DTextureScore[1] = NULL;
	}

	if (pD3DVtxBuffScore != NULL)
	{// 頂点バッファの開放
		pD3DVtxBuffScore->Release();
		pD3DVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (score % (int)(powf(SCORE_POW, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(SCORE_POW, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureScore(nCntPlace, number);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, pD3DVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, pD3DTextureScore[0]);

	// ポリゴンの描画
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * SCORE_VERTEX), NUM_POLYGON);
	}

	// テクスチャの設定
	pDevice->SetTexture(0, pD3DTextureScore[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * SCORE_VERTEX), NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + SCORE_VERTEX),	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
		FVF_VERTEX_2D,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
		&pD3DVtxBuffScore,								// 頂点バッファインターフェースへのポインタ
		NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += SCORE_VERTEX)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y - 30, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 20, SCORE_POS_Y - 30, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 20, SCORE_POS_Y + 55, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		pD3DVtxBuffScore->Unlock();
	}

	return S_OK;
}

////=============================================================================
//// テクスチャ座標の設定
////=============================================================================
//void SetTextureScore(int idx, int number)
//{
//	VERTEX_2D *pVtx;
//
//	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
//	pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	pVtx += (idx * SCORE_VERTEX);
//
//	// 頂点座標の設定
//	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.14f, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.14f, 1.0f);
//
//	// 頂点データをアンロックする
//	pD3DVtxBuffScore->Unlock();
//}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureScore(int score, int number)
{
	VERTEX_2D *Vtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pD3DVtxBuffScore->Lock(0, 0, (void**)&Vtx, 0);

	Vtx += (score * SCORE_VERTEX);

	// 頂点座標の設定
	Vtx[0].tex = D3DXVECTOR2( 0.1f, 0.0f);
	Vtx[1].tex = D3DXVECTOR2( 0.1f + 0.14f, 0.0f);
	Vtx[2].tex = D3DXVECTOR2( 0.1f, 1.0f);
	Vtx[3].tex = D3DXVECTOR2( 0.1f + 0.14f, 1.0f);


	////頂点座標設定
	//float offsetX = number == 0 ? -SCORE_SIZE_X : SCORE_SIZE_X;
	//D3DXVECTOR3 pos = SCORE_POS;
	//pos.x += offsetX;

	//Vtx[0].vtx = pos + D3DXVECTOR3(-SCORE_SIZE_X / 2.0f, -SCORE_SIZE_Y / 2.0f, 0.0f);
	//Vtx[1].vtx = pos + D3DXVECTOR3(	SCORE_SIZE_X / 2.0f, -SCORE_SIZE_Y / 2.0f, 0.0f);
	//Vtx[2].vtx = pos + D3DXVECTOR3(-SCORE_SIZE_X / 2.0f,  SCORE_SIZE_Y / 2.0f, 0.0f);
	//Vtx[3].vtx = pos + D3DXVECTOR3(	SCORE_SIZE_X / 2.0f,  SCORE_SIZE_Y / 2.0f, 0.0f);
}

//=============================================================================
// スコアの変更
//=============================================================================
void ChangeScore(int value)
{
	score += value;
	if (score < 0)
	{
		score = 0;
	}
	else if (score >= (int)(powf(SCORE_POW, (float)(NUM_PLACE + 1))))
	{
		score = (int)(powf(SCORE_POW, (float)(NUM_PLACE + 1))) - 1;
	}
}

