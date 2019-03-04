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
#define PLAYER_MOVE_BORDER	(80.0f)						// �ő�ړ��͈�
#define PLAYER_MOVE_DURATION (20)						// ���[���̈ړ��ɂ����鎞��
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9	texture;		// �e�N�X�`���ǂݍ��ݏꏊ
static LPD3DXMESH			mesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER			matBuff;		// ���b�V���̃}�e���A�������i�[
static DWORD				numMat;			// �������̑���

static D3DXMATRIX			mtxWorld;		// ���[���h�}�g���b�N�X
static PLAYER				player;			// �v���C���[���[�N

static int					laneCnt;		// ���[������J�E���^�[

//=============================================================================
// ����������
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

	laneCnt = 0;

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
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *mat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player.rot.y, player.rot.x, player.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, player.pos.x, player.pos.y, player.pos.z);
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

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &player;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return player.pos;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return player.rot;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return player.rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return player.move;
}
