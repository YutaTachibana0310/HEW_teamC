//=============================================================================
//
// �R���C�_�[���� [collider.cpp]
// Author : GP11A341 21 ���ԗY��
//
//=============================================================================
#include "collider.h"

/*****************************************************************************
�}�N����`
*****************************************************************************/

/*****************************************************************************
�\���̒�`
*****************************************************************************/

/*****************************************************************************
�O���[�o���ϐ�
*****************************************************************************/
static LPD3DXMESH meshSphere;		//���̃��b�V��
static LPD3DXMESH meshCube;			//�L���[�u���b�V��
static D3DMATERIAL9 material;		//�����蔻��\���p�}�e���A��

/*****************************************************************************
����������
*****************************************************************************/
void InitCollider(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//���̃��b�V���쐬
		D3DXCreateSphere(pDevice,
			1.0f,
			8,
			8,
			&meshSphere,
			NULL);

		//�L���[�u���b�V���쐬
		D3DXCreateBox(pDevice,
			1.0f,
			1.0f,
			1.0f,
			&meshCube,
			NULL);

		//�}�e���A���쐬
		ZeroMemory(&material, sizeof(material));
		material.Diffuse.r = 1.0f;
		material.Diffuse.g = 0.0f;
		material.Diffuse.b = 0.0f;
		material.Diffuse.a = 1.0f;

		material.Ambient.r = 1.0f;
		material.Ambient.g = 0.0f;
		material.Ambient.b = 0.0f;
		material.Ambient.a = 1.0f;

		material.Specular.r = 1.0f;
		material.Specular.g = 0.0f;
		material.Specular.b = 0.0f;
		material.Specular.a = 1.0f;

		material.Emissive.r = 1.0f;
		material.Emissive.g = 0.0f;
		material.Emissive.b = 0.0f;
		material.Emissive.a = 1.0f;

		initialized = true;

	}
}

/*****************************************************************************
�I������
*****************************************************************************/
void UninitCollider(int num)
{
	if (num == 0)
	{
		SAFE_RELEASE(meshSphere);
		SAFE_RELEASE(meshCube);
	}
}


/*****************************************************************************
�o�E���f�B���O�X�t�B�A�`�揈��
*****************************************************************************/
void DrawBoundingSphere(const COLLIDER_SPHERE *s)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate, mtxScale, mtxWorld;
	D3DMATERIAL9 matDef;

	//get defaultMaterial
	pDevice->GetMaterial(&matDef);

	//set renderstate & material
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetMaterial(&material);
	pDevice->SetTexture(0, NULL);

	//identify
	D3DXMatrixIdentity(&mtxWorld);

	//scaling
	D3DXMatrixScaling(&mtxScale, s->radius, s->radius, s->radius);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//translate
	D3DXMatrixTranslation(&mtxTranslate, s->pos->x + s->offset.x, s->pos->y + s->offset.y, s->pos->z + s->offset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
	
	//set world
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//draw
	meshSphere->DrawSubset(0);

	//reset renderstate & material0
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetMaterial(&matDef);
}

/*****************************************************************************
�o�E���f�B���O�L���[�u�`�揈��
*****************************************************************************/
void DrawBoundingCube(const COLLIDER_CUBE *cube)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTranslate, mtxScale, mtxWorld;
	D3DMATERIAL9 matDef;

	//get defaultMaterial
	pDevice->GetMaterial(&matDef);

	//set renderstate & material
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetMaterial(&material);
	pDevice->SetTexture(0, NULL);

	//identify
	D3DXMatrixIdentity(&mtxWorld);

	//scaling
	D3DXMatrixScaling(&mtxScale, cube->length.x * 2, cube->length.y * 2, cube->length.z * 2);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	//translate
	D3DXMatrixTranslation(&mtxTranslate, cube->pos->x + cube->offset.x, cube->pos->y + cube->offset.y, cube->pos->z + cube->offset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
	
	//set world
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//draw
	meshCube->DrawSubset(0);

	//reset renderstate & material0
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetMaterial(&matDef);
}

/*****************************************************************************
�֐���	�Fbool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, POLYGON_TRIANGLE tri, D3DXVECTOR3 *out)
����1	�FD3DXVECTOR3 start	�c�@�����̎n�_
����2	�FD3DXVECTOR3 end	�c�@�����̏I�_
����3	�FPOLYGON_TRIANGLE tri		�c�@�O�p�`�|���S��
����4	�FD3DXVECTOR3 *out	�c�@��_���i�[����|�C���^
����	�F�����ƎO�p�`�|���S���̓����蔻��
*****************************************************************************/
bool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, POLYGON_TRIANGLE tri, D3DXVECTOR3 *out)
{
	//�����̎n�_�A�I�_�ƃt�B�[���h�̖@���x�N�g���Ƃ̓��ς��v�Z
	D3DXVECTOR3 v1 = start - tri.a;
	D3DXVECTOR3 v2 = end - tri.a;

	float dotV1 = D3DXVec3Dot(&tri.nor, &v1);
	float dotV2 = D3DXVec3Dot(&tri.nor, &v2);

	//���ʂƐ������������Ă��Ȃ�(���ϓ��m�̐ς̕��������ł���)�ꍇ�Afalse�����^�[��
	if (dotV1 * dotV2 > 0)
	{
		return false;
	}

	//�����ƕ��ʂ̌�_���v�Z
	D3DXVECTOR3 line = end - start;	//������\���x�N�g��

	float ratio = fabsf(dotV1) / (fabsf(dotV1) + fabsf(dotV2));

	float x = start.x + (line.x * ratio);	//x���W
	float y = start.y + (line.y * ratio);	//y���W
	float z = start.z + (line.z * ratio);	//z���W
	D3DXVECTOR3 p = D3DXVECTOR3(x, y, z);	//��_

	//��_���|���S���̈�����`�F�b�N
	D3DXVECTOR3 n1, n2, n3;

	D3DXVec3Cross(&n1, &(tri.b - tri.a), &(p - tri.a));	//�t�B�[���h�̕ӂƁA���_����_�x�N�g���̖@���x�N�g�����v�Z
	D3DXVec3Cross(&n2, &(tri.c - tri.b), &(p - tri.b));
	D3DXVec3Cross(&n3, &(tri.a - tri.c), &(p - tri.c));

	float dot_n12 = D3DXVec3Dot(&n1, &n2);
	float dot_n23 = D3DXVec3Dot(&n2, &n3);

	//�S�Ă̖@���x�N�g�������������i���ς����ɂȂ�Ȃ��j�ł���Ό�_�̓t�B�[���h���ɂ���
	if (dot_n12 >= 0 && dot_n23 >= 0)
	{
		*out = p;
		return true;
	}

	return false;
}

/*****************************************************************************
�֐���	�Fbool CheckHitTriangleAndLine(D3DXVECTOR3 start, D3DXVECTOR3 end, POLYGON_PLANE plane, D3DXVECTOR3 *out)
����1	�FD3DXVECTOR3 start	�c�@�����̎n�_
����2	�FD3DXVECTOR3 end	�c�@�����̏I�_
����3	�FPOLYGON_TRIANGLE tri		�c�@�l�p�`�|���S�����a
����4	�FD3DXVECTOR3 *out	�c�@��_���i�[����|�C���^
����	�F�O�p�`�|���S���Ɛ����̓����蔻��
*****************************************************************************/
bool CheckHitPlaneAndLine(D3DXVECTOR3 start, D3DXVECTOR3 goal, POLYGON_PLANE plane, D3DXVECTOR3 *out)
{
	//�����̎n�_�A�I�_�ƃt�B�[���h�̖@���x�N�g���Ƃ̓��ς��v�Z
	D3DXVECTOR3 v1 = start - plane.topL;
	D3DXVECTOR3 v2 = goal - plane.topL;

	float dotV1 = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &v1);
	float dotV2 = D3DXVec3Dot(&D3DXVECTOR3(0, 1, 0), &v2);

	//���ʂƐ������������Ă��Ȃ�(���ϓ��m�̐ς̕��������ł���)�ꍇ�Afalse�����^�[��
	if (dotV1 * dotV2 > 0)
	{
		return false;
	}

	//�����ƕ��ʂ̌�_���v�Z
	D3DXVECTOR3 line = goal - start;	//������\���x�N�g��

	float ratio = fabsf(dotV1) / (fabsf(dotV1) + fabsf(dotV2));

	float x = start.x + (line.x * ratio);	//x���W
	float y = start.y + (line.y * ratio);	//y���W
	float z = start.z + (line.z * ratio);	//z���W
	D3DXVECTOR3 p = D3DXVECTOR3(x, y, z);			//��_

											//��_���|���S���̈�����`�F�b�N
	D3DXVECTOR3 n1, n2, n3, n4;

	D3DXVec3Cross(&n1, &(plane.bottomL - plane.topL), &(p - plane.bottomL));	//�t�B�[���h�̕ӂƁA���_����_�x�N�g���̖@���x�N�g�����v�Z
	D3DXVec3Cross(&n2, &(plane.bottomR - plane.bottomL), &(p - plane.bottomR));
	D3DXVec3Cross(&n3, &(plane.topR - plane.bottomR), &(p - plane.topR));
	D3DXVec3Cross(&n4, &(plane.topL- plane.topR), &(p - plane.topL));

	float dot_n12 = D3DXVec3Dot(&n1, &n2);
	float dot_n23 = D3DXVec3Dot(&n2, &n3);
	float dot_n34 = D3DXVec3Dot(&n3, &n4);

	//�S�Ă̖@���x�N�g�������������i���ς����ɂȂ�Ȃ��j�ł���Ό�_�̓t�B�[���h���ɂ���
	if (dot_n12 >= 0 && dot_n23 >= 0 && dot_n34 >= 0)
	{
		*out = p;
		return true;
	}

	return false;
}

/*****************************************************************************
�֐���	�Fbool ChechHitBoundingSphere(SPHERE s1, SPHERE s2)
����1	�FSPHERE s1�@�c�@�o�E���f�B���O�X�t�B�A1
����2	�FSPHERE s2�@�c�@�o�E���f�B���O�X�t�B�A2
����	�F�o�E���f�B���O�X�t�B�A�̓����蔻��
*****************************************************************************/
bool CheckHitBoundingSphere(const COLLIDER_SPHERE *s1, const COLLIDER_SPHERE *s2)
{
	if (!s1->active || !s2->active)
	{
		//return false;
	}

	D3DXVECTOR3 d = (*s2->pos + s2->offset) -(*s1->pos + s1->offset);
	float lenghtSq = D3DXVec3LengthSq(&d);

	return (lenghtSq > (s1->radius + s2->radius) * (s1->radius + s2->radius)) ? false : true;
}

/*****************************************************************************
�֐���	�Fbool ChechHitBoundingCube(SPHERE s1, SPHERE s2)
����1	�FSPHERE s1�@�c�@�o�E���f�B���O�X�t�B�A1
����2	�FSPHERE s2�@�c�@�o�E���f�B���O�X�t�B�A2
����	�F�o�E���f�B���O�X�t�B�A�̓����蔻��
*****************************************************************************/
bool ChechHitBoundingCube(const COLLIDER_CUBE *c1, const COLLIDER_CUBE *c2)
{
	
	D3DXVECTOR3 pos1 = *(c1->pos) + c1->offset;
	D3DXVECTOR3 pos2 = *(c2->pos) + c2->offset;

	if (pos1.x + c1->length.x < pos2.x - c2->length.x || pos1.x - c1->length.x > pos2.x + c2->length.x)
		return false;

	if (pos1.y + c1->length.y < pos2.y - c2->length.y || pos1.y - c1->length.y > pos2.y + c2->length.y)
		return false;

	if (pos1.z + c1->length.z < pos2.z - c2->length.z || pos1.z - c1->length.z > pos2.z + c2->length.z)
		return false;

	return true;
}