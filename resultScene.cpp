//=====================================
//
//���U���g�V�[������[resulScene.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "resultScene.h"
#include "bgmManager.h"
#include "soundEffectManager.h"

#include "gameParameter.h"
#include "sceneFade.h"
#include "gameParameter.h"

#include "meshCylinder.h"
#include "rainbowLane.h"
#include "player.h"

/**************************************
�}�N����`
***************************************/
#define RESULTSCENE_DURATION			(300)
#define RESULTSCENE_SCROLL_SPEED		(1.0f)
#define RESULTSCENE_BGM_FADEDURATION	(60)
/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static int cntFrame;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
HRESULT InitResultScene(int num)
{
	cntFrame = 0;

	InitMeshCylinder(num);
	InitRainbowLane(num);
	InitPlayer();

	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		GetGameParameterAdr(i)->playerSpeed = RESULTSCENE_SCROLL_SPEED;
	}

	//BGM�Đ�
	FadeInBGM(BGM_RESULT, BGM_FADE_DURATION);

	//�����Đ�
	PlaySE(SOUND_CHEER);

	return S_OK;
}

/**************************************
�I������
***************************************/
void UninitResultScene(int num)
{
	UninitMeshCylinder(num);
	UninitRainbowLane(num);
	UninitPlayer();
}

/**************************************
�X�V����
***************************************/
void UpdateResultScene(void)
{
	UpdateGameParameter();

	UpdateMeshCylinder();
	UpdateRainbowLane();
	UpdatePlayer();

	cntFrame++;
	if (cntFrame == RESULTSCENE_DURATION)
	{
		FadeOutBGM(BGM_RESULT, RESULTSCENE_BGM_FADEDURATION);
		SetSceneFade(TitleScene);
	}
}

/**************************************
�`�揈��
***************************************/
void DrawResultScene(int n)
{
	DrawMeshCylinder(n);
	DrawRainbowLane(n);
	DrawPlayer();
}
