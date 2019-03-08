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
#include "slashBullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER			"data/MODEL/airplane000.x"	// �ǂݍ��ރ��f����
#define MODEL_PLAYER_RELEASE	"data/MODEL/player001.x"	// �ǂݍ��ރ��f�����i�����[�X�Łj
#define	PLAYER_RADIUS			(10.0f)						// ���a
#define	VALUE_MOVE_PLAYER		(8.0f)						// �ړ����x
#define	RATE_MOVE_PLAYER		(0.15f)						// �ړ������W��
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.025f)			// ��]���x
#define	RATE_ROTATE_PLAYER		(0.10f)						// ��]�����W��
#define	VALUE_MOVE_BULLET		(7.5f)						// �e�̈ړ����x
#define PLAYER_MOVE_DURATION	 (20)						// ���[���̈ړ��ɂ����鎞��
#define LANE_LEFT				(0)							// �����[��
#define LANE_CENTER				(1)							// �������[��
#define LANE_RIGHT				(2)							// �E���[��
#define PLAYER_DEFAULT_POS_Y	(10.0f)
#define PLAYER_DEFAULT_POS_Z	(100.0f)
#define PLAYER_ACCEL_DIF		(50.0f)						// �ړ�����
#define PLAYER_ACCEL_DURATION	(30)						// �������ɂ����鎞��
#define PLAYER_TEXTURE_MAX		(9)
#define PLAYER_DEFAULTROT_Y		(D3DXToRadian(180.0f))
#define PLAYER_SHOT_INTERBAL	(30)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPD3DXMESH			mesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER			matBuff;		// ���b�V���̃}�e���A�������i�[
static DWORD				numMat;			// �������̑���

static D3DXMATRIX			mtxWorld;		// ���[���h�}�g���b�N�X
static PLAYER				player[TARGETPLAYER_MAX];			// �v���C���[���[�N

//�e�N�X�`����
static const char* textureName[PLAYER_TEXTURE_MAX] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"data/TEXTURE/PLAYER/vj2c.jpg",
	"data/TEXTURE/PLAYER/door_mtl1_diffcol.jpg",
	NULL,
	"data/TEXTURE/PLAYER/door_mtl2_diffcol.jpg"
};

//�e�N�X�`��
static LPDIRECT3DTEXTURE9 textures[PLAYER_TEXTURE_MAX];

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerAttack(int i);

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	mesh = NULL;
	matBuff = NULL;

	// X�t�@�C���̓ǂݍ���
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
	for (int i = 0; i < PLAYER_TEXTURE_MAX; i++)
	{
		textures[i] = CreateTextureFromFile((LPSTR)textureName[i], device);
	}
#endif

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		player[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player[i].radius = PLAYER_RADIUS;

		//�����蔻��̏�����
		player[i].collider.pos = &player[i].pos;
		player[i].collider.length = D3DXVECTOR3(PLAYER_RADIUS, PLAYER_RADIUS, PLAYER_RADIUS);
		player[i].collider.offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,				// �t�@�C���̖��O
			&texture);						// �ǂݍ��ރ������[
#endif
		//�v���C���[�̃p�����[�^��������
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
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PLAYER_TEXTURE_MAX; i++)
	{
		SAFE_RELEASE(textures[i]);
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
			int input = GetHorizontalInputTrigger(i); // �e�p�b�h�̓��͏���
			switch (player[i].currentLane)
			{
			case LANE_LEFT: // �����[���ɂ���Ƃ�
				if (input == 1)
				{// �E�����͂��ꂽ��
					player[i].prevLane = LANE_LEFT;
					player[i].currentLane = LANE_CENTER;
					player[i].moveFlag = true;
				}
				break;

			case LANE_CENTER: // �������[���ɂ���Ƃ�
				if (input == -1)
				{// �������͂��ꂽ��
					player[i].prevLane = LANE_CENTER;
					player[i].currentLane = LANE_LEFT;
					player[i].moveFlag = true;
				}
				else if (input == 1)
				{// �E�����͂��ꂽ��
					player[i].prevLane = LANE_CENTER;
					player[i].currentLane = LANE_RIGHT;
					player[i].moveFlag = true;
				}
				break;

			case LANE_RIGHT: // �E���[���ɂ���Ƃ�
				if (input == -1)
				{// �������͂��ꂽ��
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
			D3DXVECTOR3 currentLanePos = GetLanePos(player[i].currentLane) + GetLaneNormal(player[i].currentLane) * PLAYER_DEFAULT_POS_Y;
			D3DXVECTOR3 prevLaneRot = GetLaneRot(player[i].prevLane);
			D3DXVECTOR3 currentLaneRot = GetLaneRot(player[i].currentLane);

			// �A�j���[�V����
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


		if (player[i].accelerationFlag == true) // �������t���O����������
		{
			// �A�j���[�V����
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

		//�V���b�g�C���^�[�o���J�E���g
		player[i].shotInterbal++;

		//�U������
		PlayerAttack(i);
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
		D3DXMatrixRotationYawPitchRoll(&mtxRot, PLAYER_DEFAULTROT_Y, player[i].rot.x, -player[i].rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, player[i].pos.x, player[i].pos.y, player[i].pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		device->SetTransform(D3DTS_WORLD, &mtxWorld);

		// �}�e���A�����ɑ΂���|�C���^���擾
		mat = (D3DXMATERIAL*)matBuff->GetBufferPointer();

		for (int j = 0; j < (int)numMat; j++)
		{
			// �}�e���A���̐ݒ�
			device->SetMaterial(&mat[j].MatD3D);

			// �e�N�X�`���̐ݒ�
			device->SetTexture(0, textures[j]);

			// �`��
			mesh->DrawSubset(j);
		}

		{// �}�e���A�����f�t�H���g�ɖ߂�
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

//=============================================================================
// �v���C���[�̃A�N�Z�����[�V������Set�֐�
//=============================================================================
void SetPlayerAcceleration(int playerId, bool isAccelerator)
{
	if (isAccelerator == true)
	{
		//���W�̎擾
		D3DXVECTOR3 playerPos = GetPositionPlayer(playerId);
		player[playerId].prevPosZ = playerPos.z;
		player[playerId].currentPosZ = playerPos.z + PLAYER_ACCEL_DIF;

		// �t���O�̃Z�b�g
		player[playerId].accelerationFlag = true;
	}
	else if (isAccelerator == false)
	{
		//���W�̎擾
		D3DXVECTOR3 playerPos = GetPositionPlayer(playerId);
		player[playerId].prevPosZ = playerPos.z;
		player[playerId].currentPosZ = playerPos.z - PLAYER_ACCEL_DIF;

		// �t���O�̃Z�b�g
		player[playerId].accelerationFlag = true;
	}
}

//=============================================================================
// �v���C���[�̍U������
//=============================================================================
void PlayerAttack(int i)
{
	PLAYER* ptr = &player[i];

	//�U���{�^���̃g���K�[���m
	if (GetAttackButtonTrigger(i) && ptr->shotInterbal > PLAYER_SHOT_INTERBAL)
	{
		ptr->shotInterbal = 0;
		SetSlashBullet(ptr->pos, i);
	}
}