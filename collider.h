//=============================================================================
//
// �R���C�_�[�w�b�_ [collider.h]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

/*
�l�p�`�|���S����\���\����
*/
typedef struct
{
	D3DXVECTOR3 topL;		//���㒸�_
	D3DXVECTOR3 bottomL;	//�������_
	D3DXVECTOR3 bottomR;	//�E�����_
	D3DXVECTOR3 topR;		//�E�㒸�_
	D3DXVECTOR3 nor;		//�@���x�N�g��
}PLANE;

/*
�O�p�`�|���S����\���\����
*/
typedef struct
{
	D3DXVECTOR3 a;			//���_1
	D3DXVECTOR3 b;			//���_2
	D3DXVECTOR3 c;			//���_3
	D3DXVECTOR3 nor;		//�@���x�N�g��
}TRIANGLE;

//�X�t�B�A�R���C�_�[
typedef struct
{
	D3DXVECTOR3 *pos;		//��������I�u�W�F�N�g�̍��W�|�C���^
	D3DXVECTOR3 offset;		//�ΏۃI�u�W�F�N�g����̃I�t�Z�b�g
	float radius;			//���a
	bool active;			//�A�N�e�B�u����
}COLLIDER_SPHERE;

//�L���[�u�R���C�_�[
typedef struct
{	
	D3DXVECTOR3 *pos;		//��������I�u�W�F�N�g�̍��W�|�C���^
	D3DXVECTOR3 offset;		//�ΏۃI�u�W�F�N�g����̃I�t�Z�b�g
	D3DXVECTOR3 length;		//�[�_�ւ̋���
	bool active;			//�A�N�e�B�u����
}COLLIDER_CUBE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCollider(int num);
void UninitCollider(int num);

bool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, TRIANGLE tri, D3DXVECTOR3 *out);
bool CheckHitPlaneAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, PLANE plane, D3DXVECTOR3 *out);
bool CheckHitBoundingSphere(const COLLIDER_SPHERE *s1, const COLLIDER_SPHERE *s2);
bool ChechHitBoundingCube(const COLLIDER_CUBE *c1, const COLLIDER_CUBE *c2);

void DrawBoundingSphere(const COLLIDER_SPHERE *s);
void DrawBoundingCube(const COLLIDER_CUBE *cube);

#endif