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
#include "slashBullet.h"
#include "gameParameter.h"
#include "effect.h"
#include "soundEffectManager.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER			"data/MODEL/airplane000.x"	// 読み込むモデル名
#define MODEL_PLAYER_RELEASE	"data/MODEL/player001.x"	// 読み込むモデル名（リリース版）
#define	PLAYER_RADIUS			(10.0f)						// 半径
#define	VALUE_MOVE_PLAYER		(8.0f)						// 移動速度
#define	RATE_MOVE_PLAYER		(0.15f)						// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.025f)			// 回転速度
#define	RATE_ROTATE_PLAYER		(0.10f)						// 回転慣性係数
#define	VALUE_MOVE_BULLET		(7.5f)						// 弾の移動速度
#define PLAYER_MOVE_DURATION	(20)						// レーンの移動にかける時間
#define LANE_LEFT				(0)							// 左レーン
#define LANE_CENTER				(1)							// 中央レーン
#define LANE_RIGHT				(2)							// 右レーン
#define PLAYER_DEFAULT_POS_Y	(10.0f)
#define PLAYER_DEFAULT_POS_Z	(100.0f)
#define PLAYER_ACCEL_DIF		(50.0f)						// 移動距離
#define PLAYER_ACCEL_DURATION	(30)						// 加減速にかける時間
#define PLAYER_ACCEL_RANDOMRANGE	(10.0f)
#define PLAYER_TEXTURE_MAX		(9)
#define PLAYER_DEFAULTROT_Y		(D3DXToRadian(180.0f))
#define PLAYER_SHOT_INTERBAL	(20)
#define PLAYER_BODYTEX_INDEX	(5)
#define PLAYER_SCALE			(2.0f)
#define PLAYER_EFFECTPOS_L		(D3DXVECTOR3(-3.0f, 2.0f, 10.0f))
#define PLAYER_EFFECTPOS_R		(D3DXVECTOR3( 3.0f, 2.0f, 10.0f))
#define PLAYER_EFFECTSCALE_ACCEL	(2.0f)
#define PLAYER_EFFECTSCALE_NORMAL	(1.0f)
#define PLAYER_DECCEL_DIF		(80.0f)						//減速距離

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPD3DXMESH			mesh;			// ID3DXMeshインターフェイスへのポインタ
static LPD3DXBUFFER			matBuff;		// メッシュのマテリアル情報を格納
static DWORD				numMat;			// 属性情報の総数

static D3DXMATRIX			mtxWorld;		// ワールドマトリックス
static PLAYER				player[TARGETPLAYER_MAX];			// プレイヤーワーク

//テクスチャ名
static const char* textureName[PLAYER_TEXTURE_MAX] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"data/TEXTURE/PLAYER/vj2c_1.jpg",
	"data/TEXTURE/PLAYER/door_mtl1_diffcol.jpg",
	NULL,
	"data/TEXTURE/PLAYER/door_mtl2_diffcol.jpg"
};

//ボディ用のテクスチャ名
static const char* BodyTextureName[TARGETPLAYER_MAX] = {
	"data/TEXTURE/PLAYER/vj2c_1.jpg",
	"data/TEXTURE/PLAYER/vj2c_2.jpg",
};

//テクスチャ
static LPDIRECT3DTEXTURE9 textures[PLAYER_TEXTURE_MAX];
static LPDIRECT3DTEXTURE9 bodyTexture[TARGETPLAYER_MAX];

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerAttack(int i);

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	mesh = NULL;
	matBuff = NULL;

	// Xファイルの読み込み
#ifdef _DEBUG
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
#else
	if (FAILED(D3DXLoadMeshFromX(MODEL_PLAYER_RELEASE,
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
	//テクスチャロード
	for (int i = 0; i < PLAYER_TEXTURE_MAX; i++)
	{
		textures[i] = CreateTextureFromFile((LPSTR)textureName[i], device);
	}
	//ボディ用テクスチャロード
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		bodyTexture[i] = CreateTextureFromFile((LPSTR)BodyTextureName[i], device);
	}
#endif

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		player[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].radius = PLAYER_RADIUS;

		//当たり判定の初期化
		player[i].collider.pos = &player[i].pos;
		player[i].collider.length = D3DXVECTOR3(PLAYER_RADIUS, PLAYER_RADIUS, PLAYER_RADIUS);
		player[i].collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//プレイヤーのパラメータを初期化
		int laneIndex = i == 0 ? LANE_LEFT : LANE_RIGHT;
		player[i].pos = GetLanePos(laneIndex);
		player[i].pos.z = 0.0f;
		player[i].rot = GetLaneRot(laneIndex);
		player[i].prevLane = player[i].currentLane = laneIndex;
		player[i].moveFlag = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PLAYER_TEXTURE_MAX; i++)
	{
		SAFE_RELEASE(textures[i]);
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
			int input = GetHorizontalInputTrigger(i); // 各パッドの入力処理
			switch (player[i].currentLane)
			{
			case LANE_LEFT: // 左レーンにいるとき
				if (input == 1)
				{// 右が入力されたら
					player[i].prevLane = LANE_LEFT;
					player[i].currentLane = LANE_CENTER;
					player[i].moveFlag = true;
					PlaySE(SOUND_LANEMOVE);
				}
				break;

			case LANE_CENTER: // 中央レーンにいるとき
				if (input == -1)
				{// 左が入力されたら
					player[i].prevLane = LANE_CENTER;
					player[i].currentLane = LANE_LEFT;
					player[i].moveFlag = true;
					PlaySE(SOUND_LANEMOVE);
				}
				else if (input == 1)
				{// 右が入力されたら
					player[i].prevLane = LANE_CENTER;
					player[i].currentLane = LANE_RIGHT;
					player[i].moveFlag = true;
					PlaySE(SOUND_LANEMOVE);
				}
				break;

			case LANE_RIGHT: // 右レーンにいるとき
				if (input == -1)
				{// 左が入力されたら
					player[i].prevLane = LANE_RIGHT;
					player[i].currentLane = LANE_CENTER;
					player[i].moveFlag = true;
					PlaySE(SOUND_LANEMOVE);
				}
				break;
			}
		}
		else if (player[i].moveFlag == true)
		{
			//座標と回転の取得
			D3DXVECTOR3 prevLanePos = GetLanePos(player[i].prevLane) + GetLaneNormal(player[i].prevLane);// *PLAYER_DEFAULT_POS_Y;
			D3DXVECTOR3 currentLanePos = GetLanePos(player[i].currentLane) + GetLaneNormal(player[i].currentLane);// *PLAYER_DEFAULT_POS_Y;
			D3DXVECTOR3 prevLaneRot = GetLaneRot(player[i].prevLane);
			D3DXVECTOR3 currentLaneRot = GetLaneRot(player[i].currentLane);

			// アニメーション
			player[i].moveCntFrame++;
			float t = (float)player[i].moveCntFrame / PLAYER_MOVE_DURATION;
			float posX = EaseOutCubic(t, prevLanePos.x, currentLanePos.x);
			float posY = EaseOutCubic(t, prevLanePos.y, currentLanePos.y);
			float rotZ = EaseOutCubic(t, prevLaneRot.z, currentLaneRot.z);

			player[i].pos.x = posX;
			player[i].pos.y = posY;
			player[i].rot.z = rotZ;

			if (player[i].moveCntFrame == PLAYER_MOVE_DURATION)
			{
				player[i].moveCntFrame = 0;
				player[i].moveFlag = false;
			}
		}


		if (player[i].accelerationFlag == true) // 加減速フラグが立ったら
		{
			// アニメーション
			player[i].accelCntFrame++;
			float t = (float)player[i].accelCntFrame / PLAYER_ACCEL_DURATION;
			float posZ = EaseOutCubic(t, player[i].prevPosZ, player[i].currentPosZ);

			player[i].pos.z = posZ;

			if (player[i].accelCntFrame == PLAYER_ACCEL_DURATION)
			{
				player[i].accelCntFrame = 0;
				player[i].accelerationFlag = false;
			}
		}

		//ショットインターバルカウント
		player[i].shotInterbal++;

		//攻撃処理
		PlayerAttack(i);

		//エフェクトセット処理(加速中はエフェクトが大きくなる)
		float effectScale = player[i].accelerationFlag ? PLAYER_EFFECTSCALE_ACCEL : PLAYER_EFFECTSCALE_NORMAL;
		SetEffect(player[i].effectPosL, effectScale);
		SetEffect(player[i].effectPosR, effectScale);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *mat;

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		//スケーリング
		D3DXMatrixScaling(&mtxScale, PLAYER_SCALE, PLAYER_SCALE, PLAYER_SCALE);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, PLAYER_DEFAULTROT_Y, player[i].rot.x, -player[i].rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, player[i].pos.x, player[i].pos.y, player[i].pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		device->SetTransform(D3DTS_WORLD, &mtxWorld);

		//エフェクトセット位置をワールド変換
		D3DXVec3TransformCoord(&player[i].effectPosL, &PLAYER_EFFECTPOS_L, &mtxWorld);
		D3DXVec3TransformCoord(&player[i].effectPosR, &PLAYER_EFFECTPOS_R, &mtxWorld);

		// マテリアル情報に対するポインタを取得
		mat = (D3DXMATERIAL*)matBuff->GetBufferPointer();

		for (int j = 0; j < (int)numMat; j++)
		{
			// マテリアルの設定
			device->SetMaterial(&mat[j].MatD3D);

			// テクスチャの設定
			if(j != PLAYER_BODYTEX_INDEX)
				device->SetTexture(0, textures[j]);
			else
				device->SetTexture(0, bodyTexture[i]);

			// 描画
			mesh->DrawSubset(j);
		}

		{// マテリアルをデフォルトに戻す
			D3DXMATERIAL mat;

			mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			device->SetMaterial(&mat.MatD3D);
		}
#ifdef _DEBUG
		DrawBoundingCube(&player[i].collider);
#endif
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

//=============================================================================
// プレイヤーのアクセラレーションのSet関数
//=============================================================================
void SetPlayerAcceleration(int playerId, bool isAccelerator)
{
	//加減速中は再加減速できない
	if (player[playerId].accelerationFlag)
		return;

	if (isAccelerator == true)
	{
		//座標の取得
		D3DXVECTOR3 playerPos = GetPositionPlayer(playerId);
		player[playerId].prevPosZ = playerPos.z;
		player[playerId].currentPosZ = playerPos.z + PLAYER_ACCEL_DIF + RandomRangef(-PLAYER_ACCEL_RANDOMRANGE, PLAYER_ACCEL_RANDOMRANGE);

		// フラグのセット
		player[playerId].accelerationFlag = true;

		//ゲームパラメータも加速
		float setSpeed = GetGameParameterAdr(playerId)->playerSpeed + GAMEPARAMETER_SPEED_ADDVALUE;
		GetGameParameterAdr(playerId)->playerSpeed = Clampf(GAMEPARAMETER_SPEED_MIN, GAMEPARAMETER_SPEED_MAX, setSpeed);

		//SE再生
		PlaySE(SOUND_ACCEL);

		//前進カウント
		AddOffsetCount(playerId, true);
	}
	else if (isAccelerator == false)
	{
		//座標の取得
		D3DXVECTOR3 playerPos = GetPositionPlayer(playerId);
		player[playerId].prevPosZ = playerPos.z;
		player[playerId].currentPosZ = playerPos.z - PLAYER_DECCEL_DIF + RandomRangef(-PLAYER_ACCEL_RANDOMRANGE, PLAYER_ACCEL_RANDOMRANGE);;

		// フラグのセット
		player[playerId].accelerationFlag = true;

		//ゲームパラメータも減速
		float setSpeed = GetGameParameterAdr(playerId)->playerSpeed + GAMEPARAMETER_SPEED_DECLVALUE;
		GetGameParameterAdr(playerId)->playerSpeed = Clampf(GAMEPARAMETER_SPEED_MIN, GAMEPARAMETER_SPEED_MAX, setSpeed);

		//後退カウント
		AddOffsetCount(playerId, false);
	}
}

//=============================================================================
// プレイヤーの攻撃処理
//=============================================================================
void PlayerAttack(int i)
{
	PLAYER* ptr = &player[i];

	//移動中は攻撃できない
	if (ptr->moveFlag || ptr->shotInterbal < PLAYER_SHOT_INTERBAL)
		return;


	//攻撃ボタンのトリガー検知
	if (GetAttackTrigger(i))
	{
		ptr->shotInterbal = 0;
		PlaySE(SOUIND_BULLET);
	}
}