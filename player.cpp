//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : GP11A341 12 境野輝実
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "rainbowLane.h"
#include "Easing.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/airplane000.x"	// 読み込むモデル名
#define	PLAYER_RADIUS		(10.0f)						// 半径
#define	VALUE_MOVE_PLAYER	(8.0f)						// 移動速度
#define	RATE_MOVE_PLAYER	(0.15f)						// 移動慣性係数
#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// 回転速度
#define	RATE_ROTATE_PLAYER	(0.10f)						// 回転慣性係数
#define	VALUE_MOVE_BULLET	(7.5f)						// 弾の移動速度
#define PLAYER_MOVE_DURATION (20)						// レーンの移動にかける時間
#define LANE_LEFT			(0)							// レフトレーン
#define LANE_CENTER			(1)							// センターレーン
#define LANE_RIGHT			(2)							// ライトレーン
#define PLAYER_DEFAULT_POS_Y	(10.0f)
#define PLAYER_DEFAULT_POS_Z	(100.0f)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9	texture;		// テクスチャ読み込み場所
static LPD3DXMESH			mesh;			// ID3DXMeshインターフェイスへのポインタ
static LPD3DXBUFFER			matBuff;		// メッシュのマテリアル情報を格納
static DWORD				numMat;			// 属性情報の総数

static D3DXMATRIX			mtxWorld;		// ワールドマトリックス
static PLAYER				player[TARGETPLAYER_MAX];			// プレイヤーワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		texture = NULL;
		mesh = NULL;
		matBuff = NULL;

		player[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].radius = PLAYER_RADIUS;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL_PLAYER,
			D3DXMESH_SYSTEMMEM,
			device,
			NULL,
			&matBuff,
			NULL,
			&numMat,
			&mesh)))
		{
			return E_FAIL;
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FILENAME,		// ファイルの名前
			&texture);	// 読み込むメモリー
#endif

		player[i].pos = GetLanePos(1);
		player[i].pos.y += PLAYER_DEFAULT_POS_Y;
		player[i].pos.z = (i + 1) * PLAYER_DEFAULT_POS_Z;
		player[i].prevLane = player[i].currentLane = LANE_CENTER;
		player[i].moveFlag = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (texture != NULL)
	{// テクスチャの開放
		texture->Release();
		texture = NULL;
	}

	if (mesh != NULL)
	{// メッシュの開放
		mesh->Release();
		mesh = NULL;
	}

	if (matBuff != NULL)
	{// マテリアルの開放
		matBuff->Release();
		matBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		if (player[i].moveFlag == false)
		{
			int input = GetHorizontalInputTrigger(i);
			switch (player[i].currentLane)
			{
			case LANE_LEFT:
				if (input == 1)
				{
					player[i].prevLane = LANE_LEFT;
					player[i].currentLane = LANE_CENTER;
					player[i].moveFlag = true;
				}
				break;

			case LANE_CENTER:
				if (input == -1)
				{
					player[i].prevLane = LANE_CENTER;
					player[i].currentLane = LANE_LEFT;
					player[i].moveFlag = true;
				}
				else if (input == 1)
				{
					player[i].prevLane = LANE_CENTER;
					player[i].currentLane = LANE_RIGHT;
					player[i].moveFlag = true;
				}
				break;

			case LANE_RIGHT:
				if (input == -1)
				{
					player[i].prevLane = LANE_RIGHT;
					player[i].currentLane = LANE_CENTER;
					player[i].moveFlag = true;
				}
				break;
			}
		}
		else if (player[i].moveFlag == true)
		{
			//座標と回転の取得
			D3DXVECTOR3 prevLanePos = GetLanePos(player[i].prevLane) + GetLaneNormal(player[i].prevLane) * PLAYER_DEFAULT_POS_Y;
			D3DXVECTOR3 currentLanePos = GetLanePos(player[i].currentLane) + GetLaneNormal(player[i].currentLane) * PLAYER_DEFAULT_POS_Y;;
			D3DXVECTOR3 prevLaneRot = GetLaneRot(player[i].prevLane);
			D3DXVECTOR3 currentLaneRot = GetLaneRot(player[i].currentLane);

			player[i].moveCntFrame++;
			float t = (float)player[i].moveCntFrame / PLAYER_MOVE_DURATION;
			float posX = EaseOutCubic(t, prevLanePos.x, currentLanePos.x);
			float posY = EaseOutCubic(t, prevLanePos.y, currentLanePos.y);
			float rotZ = EaseOutCubic(t, prevLaneRot.z, currentLaneRot.z);

			player[i].pos.x = posX;
			player[i].pos.y = posY + PLAYER_DEFAULT_POS_Y;
			player[i].rot.z = rotZ;

			if (player[i].moveCntFrame == PLAYER_MOVE_DURATION)
			{
				player[i].moveCntFrame = 0;
				player[i].moveFlag = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *mat;

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, player[i].rot.y, player[i].rot.x, player[i].rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, player[i].pos.x, player[i].pos.y, player[i].pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		device->SetTransform(D3DTS_WORLD, &mtxWorld);

		// マテリアル情報に対するポインタを取得
		mat = (D3DXMATERIAL*)matBuff->GetBufferPointer();

		for (int i = 0; i < (int)numMat; i++)
		{
			// マテリアルの設定
			device->SetMaterial(&mat[i].MatD3D);

			// テクスチャの設定
			device->SetTexture(0, texture);

			// 描画
			mesh->DrawSubset(i);
		}

		{// マテリアルをデフォルトに戻す
			D3DXMATERIAL mat;

			mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			device->SetMaterial(&mat.MatD3D);
		}
	}
}

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(int num)
{
	return &player[num];
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(int playerID)
{
	return player[playerID].pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(int playerID)
{
	return player[playerID].rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return player[0].rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return player[0].move;
}
