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

#define MOVE_SPEED_BULLET	(5.0f)
#define ATK_RANGE_WIDTH		(SCREEN_WIDTH * 2.0f)
#define ATK_RANGE_HEIGHT	(SCREEN_HEIGHT * 3.0f)
#define DEADZONE_STICK		(0.4f)
#define RANGE_ATK_WIDTH		(300.0f)
#define BULLET_SPEED		(3.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetBullet(int playerNo, float x, float y);


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//PLANE					atkRange[TARGETPLAYER_MAX];
static BULLET			bulletData[TARGETPLAYER_MAX];

bool					hitCheck;

bool					useSet;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{

	for (int cntPlayer = 0; cntPlayer < TARGETPLAYER_MAX; cntPlayer++)
	{
		bulletData[cntPlayer].range.vtx[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bulletData[cntPlayer].range.vtx[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bulletData[cntPlayer].range.vtx[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bulletData[cntPlayer].range.vtx[3] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bulletData[cntPlayer].range.nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		bulletData[cntPlayer].use = false;

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
	float		depthPlayerPos;

	for (int cntPad = 0; cntPad < TARGETPLAYER_MAX; cntPad++)
	{
		stickAxis.x = GetStickAxisX(cntPad);
		stickAxis.y = GetStickAxisY(cntPad);

		if (fabsf(stickAxis.x) + fabsf(stickAxis.y) > DEADZONE_STICK && useSet)
		{
			SetBullet(cntPad, stickAxis.x, stickAxis.y);
		
			useSet = false;
		}
		else if (fabsf(stickAxis.x) + fabsf(stickAxis.y) < DEADZONE_STICK)
		{
			useSet = true;
		}

	}

	for (int cntPlayer = 0; cntPlayer < TARGETPLAYER_MAX; cntPlayer++)
	{
		if (bulletData[cntPlayer].use)
		{
			bulletData[cntPlayer].length += BULLET_SPEED;
			depthPlayerPos = GetPositionPlayer(cntPlayer).z;
			

			bulletData[cntPlayer].range.vtx[0].z = depthPlayerPos;
			bulletData[cntPlayer].range.vtx[2].z = depthPlayerPos;

			bulletData[cntPlayer].range.vtx[1].z += depthPlayerPos + bulletData[cntPlayer].length;
			bulletData[cntPlayer].range.vtx[3].z += depthPlayerPos + bulletData[cntPlayer].length;

			ClippingStar(bulletData[cntPlayer].range);

		}
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void SetBullet(int playerNo, float x, float y)
{
	D3DXVECTOR3 vec1, vec2, cross, nor;
	D3DXVECTOR3 posPlayer = GetPositionPlayer(playerNo);

	// 切断平面の４頂点の座標を設定
	bulletData[playerNo].range.vtx[0].x = posPlayer.x + x * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[0].y = posPlayer.y + y * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[0].z = posPlayer.z;

	bulletData[playerNo].range.vtx[1].x = posPlayer.x + x * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[1].y = posPlayer.y + y * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[1].z = posPlayer.z + RANGE_ATK_WIDTH;

	bulletData[playerNo].range.vtx[2].x = posPlayer.x - x * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[2].y = posPlayer.y - y * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[2].z = posPlayer.z;

	bulletData[playerNo].range.vtx[3].x = posPlayer.x - x * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[3].y = posPlayer.y - y * RANGE_ATK_WIDTH;
	bulletData[playerNo].range.vtx[3].z = posPlayer.z + RANGE_ATK_WIDTH;

	bulletData[playerNo].length = RANGE_ATK_WIDTH;

	// 切断平面の法線を設定
	vec1 = bulletData[playerNo].range.vtx[1] - bulletData[playerNo].range.vtx[0];

	vec2 = bulletData[playerNo].range.vtx[2] - bulletData[playerNo].range.vtx[0];

	D3DXVec3Cross(&cross, &vec1, &vec2);
	D3DXVec3Normalize(&nor, &cross);

	bulletData[playerNo].range.nor = nor;

	// バレットを使用状態にする
	bulletData[playerNo].use = true;
}

