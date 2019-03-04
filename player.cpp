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
#define PLAYER_DEFAULT_POS_Z	(100.0f)
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9	texture;		// テクスチャ読み込み場所
static LPD3DXMESH			mesh;			// ID3DXMeshインターフェイスへのポインタ
static LPD3DXBUFFER			matBuff;		// メッシュのマテリアル情報を格納
static DWORD				numMat;			// 属性情報の総数

static D3DXMATRIX			mtxWorld;		// ワールドマトリックス
static PLAYER				player;			// プレイヤーワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	texture = NULL;
	mesh = NULL;
	matBuff = NULL;

	player.pos = D3DXVECTOR3(0.0f, -10.0f, 100.0f);
	player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player.radius = PLAYER_RADIUS;

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

	player.pos = GetLanePos(1);
	player.pos.z = PLAYER_DEFAULT_POS_Z;
	player.prevLane = player.currentLane = LANE_CENTER;
	//player.moveFlag = false;

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
	if (player.moveFlag == false)
	{
		switch (player.currentLane)
		{
		case LANE_LEFT:
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				player.prevLane = LANE_LEFT;
				player.currentLane = LANE_CENTER;
				player.moveFlag = true;
			}
			break;

		case LANE_CENTER:
			if (GetKeyboardTrigger(DIK_LEFT))
			{
				player.prevLane = LANE_CENTER;
				player.currentLane = LANE_LEFT;
				player.moveFlag = true;
			}
			if (GetKeyboardTrigger(DIK_RIGHT))
			{
				player.prevLane = LANE_CENTER;
				player.currentLane = LANE_RIGHT;
				player.moveFlag = true;
			}
			break;

		case LANE_RIGHT:
			if (GetKeyboardTrigger(DIK_LEFT))
			{
				player.prevLane = LANE_RIGHT;
				player.currentLane = LANE_CENTER;
				player.moveFlag = true;
			}
			break;
		}
	}
	else if (player.moveFlag == true)
	{
		//座標の取得
		D3DXVECTOR3 prevLanePos = GetLanePos(player.prevLane);
		D3DXVECTOR3 currentLanePos = GetLanePos(player.currentLane);
		
		player.moveCntFrame++;
		float t = (float)player.moveCntFrame / PLAYER_MOVE_DURATION;
		float posX = EaseInOutCubic(t, prevLanePos.x, currentLanePos.x);
		float posY = EaseInOutCubic(t, prevLanePos.y, currentLanePos.y);

		player.pos.x = posX;
		player.pos.y = posY + 10.0f;

		if (player.moveCntFrame == PLAYER_MOVE_DURATION)
		{
			player.moveCntFrame = 0;
			player.moveFlag = false;
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

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player.rot.y, player.rot.x, player.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, player.pos.x, player.pos.y, player.pos.z);
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

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &player;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return player.pos;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return player.rot;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return player.rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return player.move;
}
