//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);
D3DXMATRIX GetMtxProjection(void);
void GetInvCameraRotMtx(D3DXMATRIX *mtx, const D3DXVECTOR3* objPos);
D3DXVECTOR3 GetCameraPos(void);
#endif
