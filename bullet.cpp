//=============================================================================
//
// タイトル画面処理 [bullet.cpp]
// Author : 李尚ミン 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "star.h"
#include "slashBullet.h"
#include "player.h"
#include "bullet.h"
#include "bulletParticle.h"
#include "gameParameter.h"

#define MOVE_SPEED_BULLET	(5.0f)
#define ATK_RANGE_WIDTH		(SCREEN_WIDTH * 2.0f)
#define ATK_RANGE_HEIGHT	(SCREEN_HEIGHT * 3.0f)
#define DEADZONE_STICK		(0.45f)
#define RANGE_ATK_WIDTH		(80.0f)
#define BULLET_SPEED		(16.0f)
#define BULLET_MAX			((int)(SLASHBULLET_NUM_MAX/2))

#define INTERVAL_EFFECT_POS	(0.0f)

#define BULLET_COLLIDER_LENGTH	(D3DXVECTOR3(10.0f, 10.0f, 5.0f))

#define BULLET_PARTICLE_EMMITT_NUM	(30)

#define BULLET_FORWORD_OFFSET	(0.0f)

#define BULLET_HIT_ADDSCORE		(500)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetBullet(BULLET* bulletData, int playerNo, float x, float y);
void SetMoveBullet(BULLET* bulletData, int playerNo);


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//PLANE					atkRange[TARGETPLAYER_MAX];
static BULLET			bulletData[TARGETPLAYER_MAX][BULLET_MAX];

bool					hitCheck;

bool					useSet;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{

	for (int cntPlayer = 0; cntPlayer < TARGETPLAYER_MAX; cntPlayer++)
	{
		for (int cntBullet = 0; cntBullet < SLASHBULLET_NUM_MAX; cntBullet++)
		{
			bulletData[cntPlayer][cntBullet].range.vtx[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bulletData[cntPlayer][cntBullet].range.vtx[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bulletData[cntPlayer][cntBullet].range.vtx[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bulletData[cntPlayer][cntBullet].range.vtx[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bulletData[cntPlayer][cntBullet].range.nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			bulletData[cntPlayer][cntBullet].idxSlashBullet = -1;

			bulletData[cntPlayer][cntBullet].use = false;
			bulletData[cntPlayer][cntBullet].collider.length = BULLET_COLLIDER_LENGTH;
			bulletData[cntPlayer][cntBullet].collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//stickAxis = D3DXVECTOR2(0.0f, 0.0f);

	hitCheck = false;

	useSet = true;

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	D3DXVECTOR2	stickAxis;

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_Z))
	{
		SetBullet(&bulletData[0][0], 0, 0.0f, 0.5f);
	}
#endif

	//for (int cntPad = 0; cntPad < TARGETPLAYER_MAX; cntPad++)
	//{
	//	stickAxis.x = GetStickAxisX(cntPad);
	//	stickAxis.y = GetStickAxisY(cntPad);

	//	if (fabsf(stickAxis.x) + fabsf(stickAxis.y) > DEADZONE_STICK && useSet)
	//	{
	//		for (int cntBullet = 0; cntBullet < SLASHBULLET_NUM_MAX; cntBullet++)
	//		{
	//			if (bulletData[cntPad][cntBullet].use)
	//			{
	//				continue;
	//			}

	//			SetBullet(&bulletData[cntPad][cntBullet], cntPad, stickAxis.x, stickAxis.y);

	//			break;
	//		}

	//	
	//		useSet = false;
	//	}
	//	else if (fabsf(stickAxis.x) + fabsf(stickAxis.y) < DEADZONE_STICK)
	//	{
	//		useSet = true;
	//	}

	//}

	for (int cntPlayer = 0; cntPlayer < TARGETPLAYER_MAX; cntPlayer++)
	{
		for (int cntBullet = 0; cntBullet < BULLET_MAX; cntBullet++)
		{
			if (bulletData[cntPlayer][cntBullet].use)
			{
				SetMoveBullet(&bulletData[cntPlayer][cntBullet], cntPlayer);
			}

		}
	}


}
//=============================================================================
// バレットの移動処理
//=============================================================================
bool GetAttackTrigger(int playerNo)
{
	D3DXVECTOR2	stickAxis;

	stickAxis.x = GetStickAxisX(playerNo);
	stickAxis.y = GetStickAxisY(playerNo);

	if (fabsf(stickAxis.x) + fabsf(stickAxis.y) > DEADZONE_STICK)// && useSet)
	{
		for (int cntBullet = 0; cntBullet < BULLET_MAX; cntBullet++)
		{
			if (bulletData[playerNo][cntBullet].use)
			{
				continue;
			}

			SetBullet(&bulletData[playerNo][cntBullet], playerNo, stickAxis.x, stickAxis.y);

			return true;
			//break;
		}


		//useSet = false;
	}
	//else if (fabsf(stickAxis.x) + fabsf(stickAxis.y) < DEADZONE_STICK)
	//{
	//	useSet = true;
	//}

	return false;

}


//=============================================================================
// バレットの移動処理
//=============================================================================
void SetMoveBullet(BULLET* bulletData, int playerNo)
{
	//float		depthPlayerPos;
	//D3DXVECTOR3 posSlash;
	D3DXVECTOR3	posPlayer = GetPositionPlayer(playerNo);

	bulletData->length += BULLET_SPEED;
	//depthPlayerPos = GetPositionPlayer(playerNo).z;

	bulletData->range.vtx[0].z = posPlayer.z;
	bulletData->range.vtx[2].z = posPlayer.z;

	bulletData->range.vtx[1].z = posPlayer.z + bulletData->length;
	bulletData->range.vtx[3].z = posPlayer.z + bulletData->length;

	D3DXVECTOR3 posEffect, wkPos;

	wkPos = bulletData->range.vtx[1] - bulletData->range.vtx[3];

	wkPos /= 2.0f;

	wkPos += bulletData->range.vtx[3];

	wkPos.z -= INTERVAL_EFFECT_POS;

	SetSlashBulletPos(wkPos, bulletData->idxSlashBullet);

	if (ClippingStar(bulletData->range))
	{
		bulletData->use = false;
		FreeSlashBullet(bulletData->idxSlashBullet);
		bulletData->idxSlashBullet = -1;
		SetPlayerAcceleration(playerNo, true);

		//スコア加算
		GetGameParameterAdr(playerNo)->score += BULLET_HIT_ADDSCORE;

		//パーティクルセット
		for (int cntParticle = 0; cntParticle < BULLET_PARTICLE_EMMITT_NUM; cntParticle++)
			SetBulletParticle(wkPos);
	}
	else if (wkPos.z > SLASHBULLET_MOVE_BORDER_Z + posPlayer.z)
	{
		bulletData->use = false;
		FreeSlashBullet(bulletData->idxSlashBullet);
		bulletData->idxSlashBullet = -1;
	}

}


//=============================================================================
// バレットのセット処理
//=============================================================================
void SetBullet(BULLET* bulletData, int playerNo, float x, float y)
{
	D3DXVECTOR3 vec1, vec2, cross, nor;

	D3DXVECTOR3 posPlayer = GetPositionPlayer(playerNo);

	float tmp = 0.0f;
	while (tmp == 0.0f)
	{
		tmp = (float)(rand() % 200) - 100.0f;
	}
	tmp /= 100.0f;

	// 切断平面の４頂点の座標を設定
	bulletData->range.vtx[0].x = posPlayer.x + x * RANGE_ATK_WIDTH + tmp;
	bulletData->range.vtx[0].y = posPlayer.y - y * RANGE_ATK_WIDTH - tmp;
	bulletData->range.vtx[0].z = posPlayer.z;

	bulletData->range.vtx[1].x = posPlayer.x + x * RANGE_ATK_WIDTH;
	bulletData->range.vtx[1].y = posPlayer.y - y * RANGE_ATK_WIDTH;
	bulletData->range.vtx[1].z = posPlayer.z + RANGE_ATK_WIDTH;

	bulletData->range.vtx[2].x = posPlayer.x - x * RANGE_ATK_WIDTH + tmp;
	bulletData->range.vtx[2].y = posPlayer.y + y * RANGE_ATK_WIDTH - tmp;
	bulletData->range.vtx[2].z = posPlayer.z;

	bulletData->range.vtx[3].x = posPlayer.x - x * RANGE_ATK_WIDTH;
	bulletData->range.vtx[3].y = posPlayer.y + y * RANGE_ATK_WIDTH;
	bulletData->range.vtx[3].z = posPlayer.z + RANGE_ATK_WIDTH;

	bulletData->length = BULLET_FORWORD_OFFSET;

	// 切断平面の法線を設定
	vec1 = bulletData->range.vtx[1] - bulletData->range.vtx[0];

	vec2 = bulletData->range.vtx[2] - bulletData->range.vtx[0];

	D3DXVec3Cross(&cross, &vec1, &vec2);
	D3DXVec3Normalize(&nor, &cross);

	bulletData->range.nor = nor;

	// バレットを使用状態にする
	bulletData->use = true;

	D3DXVECTOR3 posEffect, wkPos;

	wkPos = bulletData->range.vtx[1] - bulletData->range.vtx[3];

	wkPos /= 2.0f;

	wkPos += bulletData->range.vtx[3];

	wkPos.z -= INTERVAL_EFFECT_POS;

	bulletData->idxSlashBullet = SetSlashBullet(wkPos, playerNo, x, -y);
	bulletData->collider.pos = &(GetSlashBulletAdr(bulletData->idxSlashBullet)->pos);
}

//=============================================================================
// バレットのゲット処理
//=============================================================================
void GetBulletPos(int playerNo, float x, float y)
{

}

//=============================================================================
// バレットのアドレス取得処理
//=============================================================================
BULLET *GetBulletAdr(int playerNo, int id)
{
	return &bulletData[playerNo][id];
}
