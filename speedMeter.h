//=======================================================================================================
//�G�t�F�N�g�̏���
//=======================================================================================================
#ifndef _SPEEDMETER_H_
#define _SPEEDMETER_H_

#include "main.h"

#define CIRCLE_MAX					(2)
#define METER_MAX					(2)
//*******************************************************************************************************
//�\���̒�`
//*******************************************************************************************************
typedef struct	// ���[�^�[�\����
{
	D3DXVECTOR3			pos;										// �|���S���̈ړ���
	D3DXVECTOR3			rot;										// �|���S���̉�]��

	VERTEX_2D			vertexWk[NUM_VERTEX];						// ���_���i�[���[�N
	LPDIRECT3DTEXTURE9	texture;									// �e�N�X�`�����
	VERTEX_2D			vertexWkSpeedMeter[NUM_VERTEX];				// ���_���i�[���[�N	

	float				radius;										// ���a
	float				baseAngle;									// �p�x
} METER;	
//*******************************************************************************************************
//�v���g�^�C�v�錾
//*******************************************************************************************************
HRESULT InitSpeedGUI(void);
void UninitSpeedGUI(void);
void UpdateSpeedGUI(void);
void DrawSpeedGUI(void);

void SetVertexMeter(int meterID, float percent);
#endif