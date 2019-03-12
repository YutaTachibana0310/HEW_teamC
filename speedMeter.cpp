//=============================================================================
//
// �^�C�g����ʏ��� [speedMeter.cpp]
// Author : GP11A341 32 �x���a��
//
//=============================================================================
#include "speedMeter.h"
#include "Easing.h"
#include "gameParameter.h"

//*******************************************************************************************************
//�}�N����`
//*******************************************************************************************************
#define TEXTURE_SPEED_CIRCLE		"data/TEXTURE/EFFECT/speedGauge_circle.png"
#define TEXTURE_SPEED_METER			"data/TEXTURE/EFFECT/speedGauge_meter.png"

#define CIRCLE_MAX					(2)					//�T�[�N���̐�
#define METER_MAX					(2)					//���[�^�[�̐�
#define TEXTURE_CIRCLE_SIZE_X		(250.0f)			//�T�[�N���̉����T�C�Y
#define TEXTURE_CIRCLE_SIZE_Y		(250.0f)			//�T�[�N���̏c���T�C�Y
#define TEXTURE_METER_SIZE_X		(250.0f)			//���[�^�[�̉����T�C�Y
#define TEXTURE_METER_SIZE_Y		(250.0f)			//���[�^�[�̏c���T�C�Y

#define SPEEDCIRCLE_ZERO_POS_X		(130)						//���̃T�[�N���̈ʒu							
#define SPEEDCIRCLE_ZERO_POS_Y		(250)		//���̃T�[�N���̈ʒu
#define SPEEDCIRCLE_ONE_POS_X		(WINDOW_WIDTH - 130)	//�E�̃T�[�N���̈ʒu
#define SPEEDCIRCLE_ONE_POS_Y		(250)		//�E�̃T�[�N���̈ʒu

#define SPEEDMETER_ZERO_POS_X		(130)					//���̃��[�^�[�̈ʒu
#define SPEEDMETER_ZERO_POS_Y		(250)					//���̃��[�^�[�̈ʒu
#define SPEEDMETER_ONE_POS_X		(WINDOW_WIDTH - 130)	//�E�̃��[�^�[�̈ʒu
#define PROGRESMETER_POS_BOTTOM		(D3DXToRadian(-220.0f))						//���[�^�[�̉�]�����ʒu
#define PROGRESMETER_POS_TOP		(D3DXToRadian(220.0f))						//���[�^�[�̉�]�̌��E�l

#define SPEEDMETER_ANGLE_VALUE		(0.05f)

#define SPEEDMETER_ANGLE_MIN		(0.0f)
#define SPEEDMETER_ANGLE_MAX		(4.5f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSpeedGUI(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		D3DTextureSpeedCircle[2] = {};					// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DTEXTURE9		D3DTextureSpeedMeter = NULL;					// �e�N�X�`���ւ̃|�C���^

static VERTEX_2D				vertexWkSpeedCircle[CIRCLE_MAX][NUM_VERTEX];	// ���_���i�[���[�N
static METER					meterWk[METER_MAX];								// ���[�^�[�\����

static float currentSpeed[TARGETPLAYER_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSpeedGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	METER *meter = meterWk;

	meter->pos = D3DXVECTOR3(SPEEDMETER_ZERO_POS_X, SPEEDMETER_ZERO_POS_Y, 0.0f);
	meter->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	meter->texture = D3DTextureSpeedMeter;
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_METER_SIZE_X / 2, TEXTURE_METER_SIZE_Y / 2);
	meter->radius = D3DXVec2Length(&temp);									// �G�l�~�[�̔��a��������
	meter->baseAngle = atan2f(TEXTURE_METER_SIZE_Y, TEXTURE_METER_SIZE_X);	// �G�l�~�[�̊p�x��������

// �X�s�[�h�T�[�N���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SPEED_CIRCLE,			// �t�@�C���̖��O
		&D3DTextureSpeedCircle[0]);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SPEED_CIRCLE,			// �t�@�C���̖��O
		&D3DTextureSpeedCircle[1]);		// �ǂݍ��ރ������[

	//�X�s�[�h���[�^�[�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SPEED_METER,			// �t�@�C���̖��O
		&D3DTextureSpeedMeter);			// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexSpeedGUI();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSpeedGUI(void)
{
	//�X�s�[�h�T�[�N��
	if (D3DTextureSpeedCircle[0] != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureSpeedCircle[0]->Release();
		D3DTextureSpeedCircle[0] = NULL;
	}

	if (D3DTextureSpeedCircle[1] != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureSpeedCircle[1]->Release();
		D3DTextureSpeedCircle[1] = NULL;
	}

	//�X�s�[�h���[�^�[
	if (D3DTextureSpeedMeter != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureSpeedMeter->Release();
		D3DTextureSpeedMeter = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSpeedGUI(void)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		float diff = GetGameParameterAdr(i)->playerSpeed - currentSpeed[i];
		currentSpeed[i] += diff * SPEEDMETER_ANGLE_VALUE;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSpeedGUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	METER *meter = meterWk;
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�X�s�[�h���[�^�[
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTextureSpeedMeter);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, meter->vertexWkSpeedMeter, sizeof(VERTEX_2D));

	//�X�s�[�h�T�[�N��
	for (int i = 0; i < CIRCLE_MAX; i++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTextureSpeedCircle[i]);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWkSpeedCircle[i], sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexSpeedGUI(void)
{
	METER *meter = meterWk;

	// �T�[�N�����_���W�̐ݒ�
	vertexWkSpeedCircle[0][0].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[0][1].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[0][2].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[0][3].vtx = D3DXVECTOR3(SPEEDCIRCLE_ZERO_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ZERO_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);

	vertexWkSpeedCircle[1][0].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[1][1].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y - TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[1][2].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X - TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);
	vertexWkSpeedCircle[1][3].vtx = D3DXVECTOR3(SPEEDCIRCLE_ONE_POS_X + TEXTURE_CIRCLE_SIZE_X / 2.0f, SPEEDCIRCLE_ONE_POS_Y + TEXTURE_CIRCLE_SIZE_Y / 2.0f, 0.0f);

	//�X�s�[�h�T�[�N���̐ݒ�
	for (int i = 0; i < CIRCLE_MAX; i++)
	{
		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		vertexWkSpeedCircle[i][0].rhw =
			vertexWkSpeedCircle[i][1].rhw =
			vertexWkSpeedCircle[i][2].rhw =
			vertexWkSpeedCircle[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		vertexWkSpeedCircle[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkSpeedCircle[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkSpeedCircle[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexWkSpeedCircle[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		vertexWkSpeedCircle[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexWkSpeedCircle[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexWkSpeedCircle[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexWkSpeedCircle[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//�X�s�[�h���[�^�[�̐ݒ�
	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	meter->vertexWkSpeedMeter[0].rhw =
		meter->vertexWkSpeedMeter[1].rhw =
		meter->vertexWkSpeedMeter[2].rhw =
		meter->vertexWkSpeedMeter[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	meter->vertexWkSpeedMeter[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	meter->vertexWkSpeedMeter[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	meter->vertexWkSpeedMeter[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	meter->vertexWkSpeedMeter[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	return S_OK;
}

//=============================================================================
// ���[�^�[�̒��_�̐ݒ�
//=============================================================================
void SetVertexMeter(int meterID, float percent)
{
	METER *meter = meterWk;

	//�A�ԂɂȂ��Ă�摜�̕���
	////UV���W�ݒ�
	//float sizeX = 1.0f / PROGRESMETER_TEXTURE_DIV_X;
	//float sizeY = 1.0f / PROGRESMETER_TEXTURE_DIV_X;
	//int x = meterID % PROGRESMETER_TEXTURE_DIV_X;
	//int y = meterID / PROGRESMETER_TEXTURE_DIV_Y;

	//UV���W�ݒ�
	meter->pos.x = (meterID == 0) ? SPEEDMETER_ZERO_POS_X : SPEEDMETER_ONE_POS_X;
	float t = currentSpeed[meterID] / 5.0f;
	meter->rot.z = EaseLinear(t, SPEEDMETER_ANGLE_MIN, SPEEDMETER_ANGLE_MAX);
	meter->rot.z += D3DXToRadian(-180.0f);

	meter->vertexWkSpeedMeter[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	meter->vertexWkSpeedMeter[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	meter->vertexWkSpeedMeter[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	meter->vertexWkSpeedMeter[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���[�^�[���_���W�̐ݒ�
	meter->vertexWkSpeedMeter[0].vtx.x = meter->pos.x - cosf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[0].vtx.y = meter->pos.y - sinf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[0].vtx.z = 0.0f;

	meter->vertexWkSpeedMeter[1].vtx.x = meter->pos.x + cosf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[1].vtx.y = meter->pos.y - sinf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[1].vtx.z = 0.0f;

	meter->vertexWkSpeedMeter[2].vtx.x = meter->pos.x - cosf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[2].vtx.y = meter->pos.y + sinf(meter->baseAngle - meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[2].vtx.z = 0.0f;

	meter->vertexWkSpeedMeter[3].vtx.x = meter->pos.x + cosf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[3].vtx.y = meter->pos.y + sinf(meter->baseAngle + meter->rot.z) * meter->radius;
	meter->vertexWkSpeedMeter[3].vtx.z = 0.0f;
}
