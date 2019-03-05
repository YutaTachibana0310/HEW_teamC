//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : GP11A341 12 ����P��
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "rainbowLane.h"
#include "Easing.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/airplane000.x"	// �ǂݍ��ރ��f����
#define	PLAYER_RADIUS		(10.0f)						// ���a
#define	VALUE_MOVE_PLAYER	(8.0f)						// �ړ����x
#define	RATE_MOVE_PLAYER	(0.15f)						// �ړ������W��
#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// ��]���x
#define	RATE_ROTATE_PLAYER	(0.10f)						// ��]�����W��
#define	VALUE_MOVE_BULLET	(7.5f)						// �e�̈ړ����x
#define PLAYER_MOVE_DURATION (20)						// ���[���̈ړ��ɂ����鎞��
#define LANE_LEFT			(0)							// ���t�g���[��
#define LANE_CENTER			(1)							// �Z���^�[���[��
#define LANE_RIGHT			(2)							// ���C�g���[��
#define PLAYER_DEFAULT_POS_Y	(10.0f)
#define PLAYER_DEFAULT_POS_Z	(100.0f)
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9	texture;		// �e�N�X�`���ǂݍ��ݏꏊ
static LPD3DXMESH			mesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER			matBuff;		// ���b�V���̃}�e���A�������i�[
static DWORD				numMat;			// �������̑���

static D3DXMATRIX			mtxWorld;		// ���[���h�}�g���b�N�X
static PLAYER				player[TARGETPLAYER_MAX];			// �v���C���[���[�N

//=============================================================================
// ����������
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

		// X�t�@�C���̓ǂݍ���
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
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,		// �t�@�C���̖��O
			&texture);	// �ǂݍ��ރ������[
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
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (texture != NULL)
	{// �e�N�X�`���̊J��
		texture->Release();
		texture = NULL;
	}

	if (mesh != NULL)
	{// ���b�V���̊J��
		mesh->Release();
		mesh = NULL;
	}

	if (matBuff != NULL)
	{// �}�e���A���̊J��
		matBuff->Release();
		matBuff = NULL;
	}
}

//=============================================================================
// �X�V����
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
			//���W�Ɖ�]�̎擾
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
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *mat;

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, player[i].rot.y, player[i].rot.x, player[i].rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, player[i].pos.x, player[i].pos.y, player[i].pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		device->SetTransform(D3DTS_WORLD, &mtxWorld);

		// �}�e���A�����ɑ΂���|�C���^���擾
		mat = (D3DXMATERIAL*)matBuff->GetBufferPointer();

		for (int i = 0; i < (int)numMat; i++)
		{
			// �}�e���A���̐ݒ�
			device->SetMaterial(&mat[i].MatD3D);

			// �e�N�X�`���̐ݒ�
			device->SetTexture(0, texture);

			// �`��
			mesh->DrawSubset(i);
		}

		{// �}�e���A�����f�t�H���g�ɖ߂�
			D3DXMATERIAL mat;

			mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			device->SetMaterial(&mat.MatD3D);
		}
	}
}

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(int num)
{
	return &player[num];
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(int playerID)
{
	return player[playerID].pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(int playerID)
{
	return player[playerID].rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return player[0].rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return player[0].move;
}
