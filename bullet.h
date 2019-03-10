//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : �����~�� 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	TEXTURE_BULLET		_T("data/TEXTURE/bg000.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
//#define	TEXTURE_BULLET_LOGO	_T("data/TEXTURE/title_logo.png")		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_BULLET			_T("data/TEXTURE/shadow000.jpg")	// �ǂݍ��ރe�N�X�`���t�@�C����



#define	BULLET_POS_X			(SCREEN_CENTER_X)							// �^�C�g���̕\���ʒu
#define	BULLET_POS_Y			(SCREEN_CENTER_Y)								// �^�C�g���̕\���ʒu
#define	BULLET_SIZE_X			(50)								// �^�C�g���̕�
#define	BULLET_SIZE_Y			(50)								// �^�C�g���̍���
#define BULLET_SIZE				(25.0f)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	PLANE	range;
	float	length;
	bool	use;
}BULLET;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UpdateBullet(void);

#endif
