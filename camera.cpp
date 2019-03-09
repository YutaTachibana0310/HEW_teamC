//=============================================================================
//
// �J�������� [camera.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "camera.h"
#include "input.h"

#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE					(D3DXToRadian(60.0f))	// ����p
#define	VIEW_ASPECT					((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z					(50.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z					(20000.0f)				// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA			(20.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA			(D3DX_PI * 0.01f)		// �J�����̉�]��

#define CAMERA_POSITION_OFFSET		(D3DXVECTOR3(0.0f, 30.0f, -150.0f))	//���_�̈ʒu
#define CAMERA_TARGET_OFFSET		(D3DXVECTOR3(0.0f, 10.0f, 50.0f))	//�����_�̈ʒu
#define CAMERA_OFFSET_MAGNI			(0.2f)								//�J�����̈ړ��{��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA camera;

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitCamera(void)
{
	camera.pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	camera.target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera.destPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camera.destTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetCamera(0);

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(int targetPlayerID)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���C���[����ɒ����_��ݒ�
	D3DXVECTOR3 playerPos = GetPositionPlayer(targetPlayerID);
	camera.target = playerPos + CAMERA_TARGET_OFFSET;
	camera.target.x *= CAMERA_OFFSET_MAGNI;
	camera.target.y *= CAMERA_OFFSET_MAGNI;

	//�v���C���[����ɃJ�����̎��_�����肷��
	camera.pos = playerPos + CAMERA_POSITION_OFFSET;
	camera.pos.x *= CAMERA_OFFSET_MAGNI;
	camera.pos.y *= CAMERA_OFFSET_MAGNI;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera.view);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&camera.view, 
						&camera.pos,		// �J�����̎��_
						&camera.target,		// �J�����̒����_
						&camera.up);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera.view);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera.projection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&camera.projection,
								VIEW_ANGLE,			// ����p
								VIEW_ASPECT,		// �A�X�y�N�g��
								VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &camera.projection);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return camera.rot;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	D3DXMATRIX view;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->GetTransform(D3DTS_VIEW, &view);
	return view;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxProjection(void)
{
	D3DXMATRIX projection;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	return projection;
}

//=============================================================================
// �J������������]�s��̎擾
//=============================================================================
void GetInvCameraRotMtx(D3DXMATRIX *mtx, const D3DXVECTOR3* objPos)
{
	if (objPos != NULL)
	{
		D3DXMATRIX inv;
		D3DXMatrixIdentity(&inv);
		D3DXMatrixLookAtLH(&inv, &camera.pos, objPos, &camera.up);
		D3DXMatrixInverse(&inv, NULL, &inv);
		inv._41 = 0.0f;
		inv._42 = 0.0f;
		inv._43 = 0.0f;
	}
	else
	{
		mtx->_11 = camera.view._11;
		mtx->_12 = camera.view._21;
		mtx->_13 = camera.view._31;

		mtx->_21 = camera.view._12;
		mtx->_22 = camera.view._22;
		mtx->_23 = camera.view._32;

		mtx->_31 = camera.view._13;
		mtx->_32 = camera.view._23;
		mtx->_33 = camera.view._33;

		mtx->_41 = 0.0f;
		mtx->_42 = 0.0f;
		mtx->_43 = 0.0f;
	}

}

//=============================================================================
// �J�������W�̎擾
//=============================================================================
D3DXVECTOR3 GetCameraPos(void)
{
	return camera.pos;
}

//=============================================================================
// �J�����A�h���X�擾����
//=============================================================================
CAMERA *GetCameraAdr(void)
{
	return &camera;
}