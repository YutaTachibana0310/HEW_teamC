//=============================================================================
//
// �v���C���[���� [player.h]
// Author : GP11A341 12 ����P��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ���݂̌���
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	float radius;			// ���a

	int prevLane;			// �O�ɂ������[���̔ԍ�
	int currentLane;		// �����郌�[���̔ԍ�
	int moveCntFrame;		// �t���[���J�E���g
	bool moveFlag;			// �ړ��t���O
} PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

D3DXVECTOR3 GetPositionPlayer(void);
D3DXVECTOR3 GetRotationPlayer(void);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);

#endif
