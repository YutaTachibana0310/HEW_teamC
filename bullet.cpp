//=============================================================================
//
// �^�C�g����ʏ��� [bullet.cpp]
// Author : �����~�� 
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
// �v���g�^�C�v�錾
//*****************************************************************************
void SetBullet(int playerNo, float x, float y);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//PLANE					atkRange[TARGETPLAYER_MAX];
static BULLET			bulletData[TARGETPLAYER_MAX];

bool					hitCheck;

bool					useSet;


//=============================================================================
// ����������
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
// �X�V����
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
// �X�V����
//=============================================================================
void SetBullet(int playerNo, float x, float y)
{
	D3DXVECTOR3 vec1, vec2, cross, nor;
	D3DXVECTOR3 posPlayer = GetPositionPlayer(playerNo);

	// �ؒf���ʂ̂S���_�̍��W��ݒ�
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

	// �ؒf���ʂ̖@����ݒ�
	vec1 = bulletData[playerNo].range.vtx[1] - bulletData[playerNo].range.vtx[0];

	vec2 = bulletData[playerNo].range.vtx[2] - bulletData[playerNo].range.vtx[0];

	D3DXVec3Cross(&cross, &vec1, &vec2);
	D3DXVec3Normalize(&nor, &cross);

	bulletData[playerNo].range.nor = nor;

	// �o���b�g���g�p��Ԃɂ���
	bulletData[playerNo].use = true;
}

