#include "effect.h"
#include "camera.h"

//*******************************************************************************************************
//グローバル変数
//*******************************************************************************************************
static EFFECT				     Effect[EFFECT_MAX];

static D3DXMATRIX				 MtxWorldEffect;	//ワールドマトリックス
static D3DXVECTOR3				 PosBase;			//エフェクトの発生位置

static float					 WidthBase = 1.0f;	//基準の幅
static float					 HeightBase = 1.0f;	//基準の高さ


static LPDIRECT3DTEXTURE9		 D3DTextureEffect = NULL;		//エフェクトテクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9	 D3DVtxBufferEffect = NULL;		//エフェクトテクスチャへの頂点バッファのポインタ

static bool Pause = false;

//=======================================================================================================
//エフェクトの初期化処理
//=======================================================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//頂点座標の作成
	MakeVertexEffect(Device);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,
								TEXTURE_EFFECT, 
								&D3DTextureEffect);


	for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
	{
		Effect[CntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Effect[CntEffect].sizeX = EFFECT_SIZE_X;
		Effect[CntEffect].sizeY = EFFECT_SIZE_Y;
		Effect[CntEffect].timer = 0;
		Effect[CntEffect].use = false;
	}

	PosBase = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}

//=======================================================================================================
//エフェクトの終了処理処理
//=======================================================================================================
void UninitEffect(void)
{
	if (D3DTextureEffect != NULL)
	{//テクスチャの開放
		D3DTextureEffect->Release();
		D3DTextureEffect = NULL;
	}
	if (D3DVtxBufferEffect != NULL)
	{//頂点バッファの開放
		D3DVtxBufferEffect->Release();
		D3DVtxBufferEffect = NULL;
	}
}

//=======================================================================================================
//エフェクトの更新処理
//=======================================================================================================
void UpdateEffect(void)
{
	if(Pause==false)
	{ 
		for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
		{
			if (Effect[CntEffect].use)
			{//使用中
				Effect[CntEffect].pos.z += Effect[CntEffect].move.z;
				Effect[CntEffect].pos.y += Effect[CntEffect].move.y;

				if (Effect[CntEffect].pos.y <= Effect[CntEffect].sizeY / 2)
				{// 着地した
					Effect[CntEffect].pos.y = Effect[CntEffect].sizeY / 2;
					Effect[CntEffect].move.z = -Effect[CntEffect].move.z * MOVE_SPEED;
				}
			/*	Effect[CntEffect].move.y -= 0.25f;
				Effect[CntEffect].move.z += (0.0f - Effect[CntEffect].move.z) * EFFECT_RADIUS;
*/
				Effect[CntEffect].life--;
				if (Effect[CntEffect].life <= 0)
				{
					Effect[CntEffect].use = false;
					/*ReleaseShadow(Effect[CntEffect].nIdxShadow);
					Effect[CntEffect].nIdxShadow = -1;*/
				}
				else
				{
					Effect[CntEffect].col.a -= 0.03f;
					if (Effect[CntEffect].col.a < 0.0f)
					{
						Effect[CntEffect].col.a = 0.0f;
					}


					if (Effect[CntEffect].life <= EFFECT_LIFE)
					{
						Effect[CntEffect].col.r = 0.99f - (float)(40 - Effect[CntEffect].life) / 8.0f * 0.06f + 0.2f;
						Effect[CntEffect].col.g = 0.40f - (float)(40 - Effect[CntEffect].life) / 8.0f * 0.07f;
						Effect[CntEffect].col.b = 0.40f;
					}

					if (Effect[CntEffect].life <= 5)
					{
						// α値設定
						Effect[CntEffect].col.a -= 0.001f;
						if (Effect[CntEffect].col.a < 0.0f)
						{
							Effect[CntEffect].col.a = 0.0f;
						}
					}

					// 色の設定
					SetColorEffect(CntEffect, Effect[CntEffect].col);
				}
			}
		}

		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			float Angle, Length;
			float size;
			int life;
			pos = PosBase;
			Angle = (float)(rand() % 620 - 300) / 50.0f;
			Length = rand() % (int)(WidthBase) / 50.0f - WidthBase;

			move.z = 1.0f;

			life = rand() % 30 + 5;

			size = 15.0f;

			pos.y = size / 2;

			// エフェクトの設定
			SetEffect(pos);

		}
	}
}

//=======================================================================================================
//エフェクトの描画処理
//=======================================================================================================
void DrawEffect(void) 
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX MtxView, MtxScale, MtxTranslate;

	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	
	//ライティングを無効
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
	{
		if (Effect[CntEffect].use)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&MtxWorldEffect);

			//ビューマトリックスを取得
			MtxView = GetMtxView();

			MtxWorldEffect._11 = MtxView._11;
			MtxWorldEffect._12 = MtxView._21;
			MtxWorldEffect._13 = MtxView._31;
			MtxWorldEffect._21 = MtxView._12;
			MtxWorldEffect._22 = MtxView._22;
			MtxWorldEffect._23 = MtxView._32;
			MtxWorldEffect._31 = MtxView._13;
			MtxWorldEffect._32 = MtxView._23;
			MtxWorldEffect._33 = MtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&MtxScale, Effect[CntEffect].scl.x, Effect[CntEffect].scl.y, Effect[CntEffect].scl.z);
			D3DXMatrixMultiply(&MtxWorldEffect, &MtxWorldEffect, &MtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&MtxTranslate, Effect[CntEffect].pos.x, Effect[CntEffect].pos.y, Effect[CntEffect].pos.z);
			D3DXMatrixMultiply(&MtxWorldEffect, &MtxWorldEffect, &MtxTranslate);

			// ワールドマトリックスの設定
			Device->SetTransform(D3DTS_WORLD, &MtxWorldEffect);

			Device->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 頂点バッファをデバイスのデータストリームにバインド
			Device->SetStreamSource(0, D3DVtxBufferEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			Device->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			Device->SetTexture(0, D3DTextureEffect);

			// ポリゴンの描画
			Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (CntEffect * 4), NUM_POLYGON);

		}
	}

	//ライティングを有効
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	Device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);

}

//=======================================================================================================
// 頂点情報の作成
//=======================================================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * EFFECT_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
		FVF_VERTEX_3D,								// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBufferEffect,						// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *Vtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBufferEffect->Lock(0, 0, (void**)&Vtx, 0);

		for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++, Vtx += 4)
		{
			// 頂点座標の設定
			Vtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			Vtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X  / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			Vtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, EFFECT_SIZE_Y  / 2, 0.0f);
			Vtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X  / 2, EFFECT_SIZE_Y  / 2, 0.0f);

			// 法線の設定
			Vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			Vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			Vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			Vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			Vtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Vtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Vtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Vtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			Vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			Vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			Vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			Vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		D3DVtxBufferEffect->Unlock();
	}

	return S_OK;
}

//=======================================================================================================
// 頂点情報の設定
//=======================================================================================================
void SetVertexEffect(int nIdxEffect, float sizeX, float sizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *Vtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBufferEffect->Lock(0, 0, (void**)&Vtx,0);

		Vtx += (nIdxEffect * 4);

		// 頂点座標の設定
		Vtx[0].vtx = D3DXVECTOR3(-sizeX / 2, -sizeY / 2, 0.0f);
		Vtx[1].vtx = D3DXVECTOR3(-sizeX / 2, sizeY  / 2, 0.0f);
		Vtx[2].vtx = D3DXVECTOR3(sizeX  / 2, -sizeY / 2, 0.0f);
		Vtx[3].vtx = D3DXVECTOR3(sizeX  / 2, sizeY  / 2, 0.0f);

		// 頂点データをアンロックする
		D3DVtxBufferEffect->Unlock();
	}
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEffect(int nIdxEffect, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *Vtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBufferEffect->Lock(0, 0, (void**)&Vtx, 0);

		Vtx += (nIdxEffect * 4);

		// 頂点座標の設定
		Vtx[0].diffuse =
		Vtx[1].diffuse =
		Vtx[2].diffuse =
		Vtx[3].diffuse = col;

		// 頂点データをアンロックする
		D3DVtxBufferEffect->Unlock();
	}
}

//=============================================================================
// エフェクトの設定
//=============================================================================
int SetEffect(D3DXVECTOR3 pos)
{
	int nIdxEffect = -1;

	for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
	{
		if (!Effect[CntEffect].use)
		{
			Effect[CntEffect].pos = pos;
			Effect[CntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Effect[CntEffect].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Effect[CntEffect].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Effect[CntEffect].col =  EFFECT_COLOR;
			Effect[CntEffect].sizeX = EFFECT_SIZE_X;
			Effect[CntEffect].sizeY = EFFECT_SIZE_Y;
			Effect[CntEffect].life = EFFECT_LIFE;
			Effect[CntEffect].use = true;

			// 頂点座標の設定
			SetVertexEffect(CntEffect, EFFECT_SIZE_X, EFFECT_SIZE_Y);

			// 頂点カラーの設定
			SetColorEffect(CntEffect,
				D3DXCOLOR(Effect[CntEffect].col.r, Effect[CntEffect].col.b,
					Effect[CntEffect].col.b, Effect[CntEffect].col.a));

			nIdxEffect = CntEffect;

			break;
		}
	}

	return nIdxEffect;
}
