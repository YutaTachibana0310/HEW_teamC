//=======================================================================================================
//�G�t�F�N�g�̏���
//=======================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*******************************************************************************************************
//�}�N����`
//*******************************************************************************************************
#define TEXTURE_EFFECT		 "data/TEXTURE/EFFECT/effect000.jpg"		//�e�N�X�`���t�@�C���̓ǂݍ���
#define EFFECT_MAX			 (525)										//�G�t�F�N�g�̍ő吔
#define EFFECT_SIZE_X		 (20.0f)									//�e�N�X�`����X�T�C�Y
#define EFFECT_SIZE_Y		 (20.0f)									//�e�N�X�`����Y�T�C�Y

#define VALUE_MOVE_EFFECT    (2.0f)										//�ړ����x

#define MOVE_SPEED			 (0.75f)									//�ړ�

#define EFFECT_RADIUS		 (0.015f)									//���a
#define EFFECT_LIFE			 (80)										//�G�t�F�N�g�̃��C�t
//*******************************************************************************************************
//�\���̒�`
//*******************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//�G�t�F�N�g�̈ʒu
	D3DXVECTOR3 rot;			//�G�t�F�N�g�̉�]
	D3DXVECTOR3	scl;			//�G�t�F�N�g�̑傫��
	D3DXVECTOR3 move;			//�G�t�F�N�g�̈ړ�

	D3DXCOLOR col;				//�G�t�F�N�g�̐F

	float sizeX;				//�G�t�F�N�g��X���̑傫��
	float sizeY;				//�G�t�F�N�g��Y���̑傫��

	int life;					//���C�t
	int timer;					//����
	bool use;					//�g�p���Ă��邩
}EFFECT;

//*******************************************************************************************************
//�v���g�^�C�v�錾
//*******************************************************************************************************
HRESULT InitEffect(void);										//�G�t�F�N�g�̏���������
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 Device);				//�G�t�F�N�g�̒��_���W
	
void DrawEffect(void);											//�G�t�F�N�g�̕`�揈��
void UpdateEffect(void);										//�G�t�F�N�g�̍X�V����
void UninitEffect(void);										//�G�t�F�N�g�̏I������

void SetVertexEffect(int IdxEffect, float sizeX, float sizeY);  //�G�t�F�N�g�̒��_�̃Z�b�g
void SetColorEffect(int IdxEffect, D3DXCOLOR col);				//�G�t�F�N�g�̃J���[�Z�b�g

static int SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float sizeX, float sizeY, int timer);
#endif