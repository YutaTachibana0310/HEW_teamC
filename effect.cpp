#include "effect.h"
#include "camera.h"

//*******************************************************************************************************
//�O���[�o���ϐ�
//*******************************************************************************************************
static EFFECT				     Effect[EFFECT_MAX];

static D3DXMATRIX				 MtxWorldEffect;	//���[���h�}�g���b�N�X
static D3DXVECTOR3				 PosBase;			//�G�t�F�N�g�̔����ʒu

static float					 WidthBase = 1.0f;	//��̕�
static float					 HeightBase = 1.0f;	//��̍���


static LPDIRECT3DTEXTURE9		 D3DTextureEffect = NULL;		//�G�t�F�N�g�e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9	 D3DVtxBufferEffect = NULL;		//�G�t�F�N�g�e�N�X�`���ւ̒��_�o�b�t�@�̃|�C���^

static bool Pause = false;

//=======================================================================================================
//�G�t�F�N�g�̏���������
//=======================================================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//���_���W�̍쐬
	MakeVertexEffect(Device);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,
								TEXTURE_EFFECT, 
								&D3DTextureEffect);


	for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
	{
		Effect[CntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Effect[CntEffect].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Effect[CntEffect].sizeX = EFFECT_SIZE_X;
		Effect[CntEffect].sizeY = EFFECT_SIZE_Y;
		Effect[CntEffect].timer = 0;
		Effect[CntEffect].use = false;
	}

	PosBase = D3DXVECTOR3(0.0f,0.0f,0.0f);
	return S_OK;
}

//=======================================================================================================
//�G�t�F�N�g�̏I����������
//=======================================================================================================
void UninitEffect(void)
{
	if (D3DTextureEffect != NULL)
	{//�e�N�X�`���̊J��
		D3DTextureEffect->Release();
		D3DTextureEffect = NULL;
	}
	if (D3DVtxBufferEffect != NULL)
	{//���_�o�b�t�@�̊J��
		D3DVtxBufferEffect->Release();
		D3DVtxBufferEffect = NULL;
	}
}

//=======================================================================================================
//�G�t�F�N�g�̍X�V����
//=======================================================================================================
void UpdateEffect(void)
{
	if(Pause==false)
	{ 
		for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
		{
			if (Effect[CntEffect].use)
			{//�g�p��
				Effect[CntEffect].pos.z += Effect[CntEffect].move.z;
				Effect[CntEffect].pos.y += Effect[CntEffect].move.y;

				if (Effect[CntEffect].pos.y <= Effect[CntEffect].sizeY / 2)
				{// ���n����
					Effect[CntEffect].pos.y = Effect[CntEffect].sizeY / 2;
					Effect[CntEffect].move.z = -Effect[CntEffect].move.z * MOVE_SPEED;
				}
			/*	Effect[CntEffect].move.y -= 0.25f;
				Effect[CntEffect].move.z += (0.0f - Effect[CntEffect].move.z) * EFFECT_RADIUS;
*/
				Effect[CntEffect].life--;
				if (Effect[CntEffect].life <= 0)
				{
					Effect[CntEffect].use = false;
					/*ReleaseShadow(Effect[CntEffect].nIdxShadow);
					Effect[CntEffect].nIdxShadow = -1;*/
				}
				else
				{
					Effect[CntEffect].col.a -= 0.03f;
					if (Effect[CntEffect].col.a < 0.0f)
					{
						Effect[CntEffect].col.a = 0.0f;
					}


					if (Effect[CntEffect].life <= EFFECT_LIFE)
					{
						Effect[CntEffect].col.r = 0.99f - (float)(40 - Effect[CntEffect].life) / 8.0f * 0.06f + 0.2f;
						Effect[CntEffect].col.g = 0.40f - (float)(40 - Effect[CntEffect].life) / 8.0f * 0.07f;
						Effect[CntEffect].col.b = 0.40f;
					}

					if (Effect[CntEffect].life <= 5)
					{
						// ���l�ݒ�
						Effect[CntEffect].col.a -= 0.001f;
						if (Effect[CntEffect].col.a < 0.0f)
						{
							Effect[CntEffect].col.a = 0.0f;
						}
					}

					// �F�̐ݒ�
					SetColorEffect(CntEffect, Effect[CntEffect].col);
				}
			}
		}

		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 move;
			float Angle, Length;
			float size;
			int life;
			pos = PosBase;
			Angle = (float)(rand() % 620 - 300) / 50.0f;
			Length = rand() % (int)(WidthBase) / 50.0f - WidthBase;

			move.z = 1.0f;

			life = rand() % 30 + 5;

			size = 15.0f;

			pos.y = size / 2;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(pos);

		}
	}
}

//=======================================================================================================
//�G�t�F�N�g�̕`�揈��
//=======================================================================================================
void DrawEffect(void) 
{
	LPDIRECT3DDEVICE9 Device = GetDevice();
	D3DXMATRIX MtxView, MtxScale, MtxTranslate;

	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	
	//���C�e�B���O�𖳌�
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
	{
		if (Effect[CntEffect].use)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&MtxWorldEffect);

			//�r���[�}�g���b�N�X���擾
			MtxView = GetMtxView();

			MtxWorldEffect._11 = MtxView._11;
			MtxWorldEffect._12 = MtxView._21;
			MtxWorldEffect._13 = MtxView._31;
			MtxWorldEffect._21 = MtxView._12;
			MtxWorldEffect._22 = MtxView._22;
			MtxWorldEffect._23 = MtxView._32;
			MtxWorldEffect._31 = MtxView._13;
			MtxWorldEffect._32 = MtxView._23;
			MtxWorldEffect._33 = MtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&MtxScale, Effect[CntEffect].scl.x, Effect[CntEffect].scl.y, Effect[CntEffect].scl.z);
			D3DXMatrixMultiply(&MtxWorldEffect, &MtxWorldEffect, &MtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&MtxTranslate, Effect[CntEffect].pos.x, Effect[CntEffect].pos.y, Effect[CntEffect].pos.z);
			D3DXMatrixMultiply(&MtxWorldEffect, &MtxWorldEffect, &MtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			Device->SetTransform(D3DTS_WORLD, &MtxWorldEffect);

			Device->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			Device->SetStreamSource(0, D3DVtxBufferEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			Device->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			Device->SetTexture(0, D3DTextureEffect);

			// �|���S���̕`��
			Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (CntEffect * 4), NUM_POLYGON);

		}
	}

	//���C�e�B���O��L��
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	Device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);

}

//=======================================================================================================
// ���_���̍쐬
//=======================================================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * EFFECT_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBufferEffect,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *Vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBufferEffect->Lock(0, 0, (void**)&Vtx, 0);

		for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++, Vtx += 4)
		{
			// ���_���W�̐ݒ�
			Vtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			Vtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X  / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			Vtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, EFFECT_SIZE_Y  / 2, 0.0f);
			Vtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X  / 2, EFFECT_SIZE_Y  / 2, 0.0f);

			// �@���̐ݒ�
			Vtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			Vtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			Vtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			Vtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			Vtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Vtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Vtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Vtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			Vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			Vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			Vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			Vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBufferEffect->Unlock();
	}

	return S_OK;
}

//=======================================================================================================
// ���_���̐ݒ�
//=======================================================================================================
void SetVertexEffect(int nIdxEffect, float sizeX, float sizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *Vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBufferEffect->Lock(0, 0, (void**)&Vtx,0);

		Vtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		Vtx[0].vtx = D3DXVECTOR3(-sizeX / 2, -sizeY / 2, 0.0f);
		Vtx[1].vtx = D3DXVECTOR3(-sizeX / 2, sizeY  / 2, 0.0f);
		Vtx[2].vtx = D3DXVECTOR3(sizeX  / 2, -sizeY / 2, 0.0f);
		Vtx[3].vtx = D3DXVECTOR3(sizeX  / 2, sizeY  / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBufferEffect->Unlock();
	}
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEffect(int nIdxEffect, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *Vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBufferEffect->Lock(0, 0, (void**)&Vtx, 0);

		Vtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		Vtx[0].diffuse =
		Vtx[1].diffuse =
		Vtx[2].diffuse =
		Vtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		D3DVtxBufferEffect->Unlock();
	}
}

//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
int SetEffect(D3DXVECTOR3 pos)
{
	int nIdxEffect = -1;

	for (int CntEffect = 0; CntEffect < EFFECT_MAX; CntEffect++)
	{
		if (!Effect[CntEffect].use)
		{
			Effect[CntEffect].pos = pos;
			Effect[CntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Effect[CntEffect].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Effect[CntEffect].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Effect[CntEffect].col =  EFFECT_COLOR;
			Effect[CntEffect].sizeX = EFFECT_SIZE_X;
			Effect[CntEffect].sizeY = EFFECT_SIZE_Y;
			Effect[CntEffect].life = EFFECT_LIFE;
			Effect[CntEffect].use = true;

			// ���_���W�̐ݒ�
			SetVertexEffect(CntEffect, EFFECT_SIZE_X, EFFECT_SIZE_Y);

			// ���_�J���[�̐ݒ�
			SetColorEffect(CntEffect,
				D3DXCOLOR(Effect[CntEffect].col.r, Effect[CntEffect].col.b,
					Effect[CntEffect].col.b, Effect[CntEffect].col.a));

			nIdxEffect = CntEffect;

			break;
		}
	}

	return nIdxEffect;
}
