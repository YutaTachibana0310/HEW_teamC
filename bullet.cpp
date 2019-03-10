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
#include "player.h"
#include "bullet.h"
#include "slashBullet.h"

#define MOVE_SPEED_BULLET	(5.0f)
#define ATK_RANGE_WIDTH		(SCREEN_WIDTH * 2.0f)
#define ATK_RANGE_HEIGHT	(SCREEN_HEIGHT * 3.0f)
#define DEADZONE_STICK		(0.5f)
#define RANGE_ATK_WIDTH		(90.0f)
#define BULLET_SPEED		(6.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetBullet(BULLET* bulletData, D3DXVECTOR3 posPlayer, float x, float y);
void SetMoveBullet(BULLET* bulletData, D3DXVECTOR3 posPlayer);


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//PLANE					atkRange[TARGETPLAYER_MAX];
static BULLET			bulletData[TARGETPLAYER_MAX][SLASHBULLET_NUM_MAX];

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

			bulletData[cntPlayer][cntBullet].use = false;
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
		SetBullet(0, GetPositionPlayer(0), 0.0442587733f, 0.5f);
	}
#endif

	for (int cntPad = 0; cntPad < TARGETPLAYER_MAX; cntPad++)
	{
		stickAxis.x = GetStickAxisX(cntPad);
		stickAxis.y = GetStickAxisY(cntPad);

		if (fabsf(stickAxis.x) + fabsf(stickAxis.y) > DEADZONE_STICK && useSet)
		{
			for (int cntBullet = 0; cntBullet < SLASHBULLET_NUM_MAX; cntBullet++)
			{
				if (bulletData[cntPad][cntBullet].use)
				{
					continue;
				}

				//D3DXVECTOR3 posPlayer = GetPositionPlayer(cntPad);
				SetBullet(&bulletData[cntPad][cntBullet], GetPositionPlayer(cntPad), stickAxis.x, stickAxis.y);
				break;
			}

		
			useSet = false;
		}
		else if (fabsf(stickAxis.x) + fabsf(stickAxis.y) < DEADZONE_STICK)
		{
			useSet = true;
		}

	}

	for (int cntPlayer = 0; cntPlayer < TARGETPLAYER_MAX; cntPlayer++)
	{
		for (int cntBullet = 0; cntBullet < SLASHBULLET_NUM_MAX; cntBullet++)
		{
			if (bulletData[cntPlayer][cntBullet].use)
			{
				SetMoveBullet(&bulletData[cntPlayer][cntBullet], GetPositionPlayer(cntPlayer));
			}

		}
	}


}

//=============================================================================
// バレットの移動処理
//=============================================================================
void SetMoveBullet(BULLET* bulletData, D3DXVECTOR3 posPlayer)
{
	//float		depthPlayerPos;

	bulletData->length += BULLET_SPEED;
	//depthPlayerPos = GetPositionPlayer(playerNo).z;

	bulletData->range.vtx[0].z = posPlayer.z;
	bulletData->range.vtx[2].z = posPlayer.z;

	bulletData->range.vtx[1].z = posPlayer.z + bulletData->length;
	bulletData->range.vtx[3].z = posPlayer.z + bulletData->length;

	if (ClippingStar(bulletData->range))
	{
		bulletData->use = false;
	}

}


//=============================================================================
// バレットのセット処理
//=============================================================================
void SetBullet(BULLET* bulletData, D3DXVECTOR3 posPlayer, float x, float y)
{
	D3DXVECTOR3 vec1, vec2, cross, nor;

	
	float tmp = 0.0f;
	while (tmp == 0.0f)
	{
		tmp = (float)(rand() % 20) - 10.0f;
	}
	tmp /= 10.0f;

	// 切断平面の４頂点の座標を設定
	bulletData->range.vtx[0].x = posPlayer.x + x * RANGE_ATK_WIDTH - tmp;
	bulletData->range.vtx[0].y = posPlayer.y - y * RANGE_ATK_WIDTH + tmp;
	bulletData->range.vtx[0].z = posPlayer.z;

	bulletData->range.vtx[1].x = posPlayer.x + x * RANGE_ATK_WIDTH + tmp;
	bulletData->range.vtx[1].y = posPlayer.y - y * RANGE_ATK_WIDTH - tmp;
	bulletData->range.vtx[1].z = posPlayer.z + RANGE_ATK_WIDTH;

	bulletData->range.vtx[2].x = posPlayer.x - x * RANGE_ATK_WIDTH - tmp;
	bulletData->range.vtx[2].y = posPlayer.y + y * RANGE_ATK_WIDTH + tmp;
	bulletData->range.vtx[2].z = posPlayer.z;

	bulletData->range.vtx[3].x = posPlayer.x - x * RANGE_ATK_WIDTH + tmp;
	bulletData->range.vtx[3].y = posPlayer.y + y * RANGE_ATK_WIDTH - tmp;
	bulletData->range.vtx[3].z = posPlayer.z + RANGE_ATK_WIDTH;

	bulletData->length = RANGE_ATK_WIDTH;

	// 切断平面の法線を設定
	vec1 = bulletData->range.vtx[1] - bulletData->range.vtx[0];

	vec2 = bulletData->range.vtx[2] - bulletData->range.vtx[0];

	D3DXVec3Cross(&cross, &vec1, &vec2);
	D3DXVec3Normalize(&nor, &cross);

	bulletData->range.nor = nor;

	// バレットを使用状態にする
	bulletData->use = true;

}

//=============================================================================
// バレットのセット処理
//=============================================================================
void GetBulletPos(int playerNo, float x, float y)
{

}
