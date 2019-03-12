//=====================================
//
//�Q�[���p�����[�^����[gameParameter.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "gameParameter.h"
#include "goalTelop.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static GAMEPARAMETER param[TARGETPLAYER_MAX];
static SYSTEMPARAMETER sysParam;

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void InitGameParameter(int num)
{
	for (int i = 0; i < TARGETPLAYER_MAX; i++)
	{
		param[i].playerSpeed = 0.0f;
		param[i].playerMoveDist = 0.0f;
		param[i].isPlayerGoaled = false;
		param[1].score = 0;
		param[i].deltaTime = 0.0f;
		param[i].isPlayerGoaled = false;
	}

	sysParam.currentProgress = 0.0f;
	sysParam.winnerID = -1;
}

/**************************************
�I������
***************************************/
void UninitGameParameter(int num)
{

}

/**************************************
�X�V����
***************************************/
void UpdateGameParameter(void)
{

}

/**************************************
�`�揈��
***************************************/
void DrawGameParameter(void)
{

}

/**************************************
�Q�[���p�����[�^�A�h���X�擾����
***************************************/
GAMEPARAMETER *GetGameParameterAdr(int n)
{
	return &param[n];
}

/**************************************
�i�s�֘A�̃p�����[�^�Z�b�g����
***************************************/
void SetSpeedGameParameter(int id, float speed)
{
	param[id].playerSpeed = speed;
}

/**************************************
�S�[�����B���菈��
***************************************/
bool CheckPlayerGoaled(int id)
{
	//�S�[���ς݂ł����return true
	if (param[id].isPlayerGoaled)
		return true;

	//�ړ��������`�F�b�N���A�S�[���𒴂��Ă���΃e���b�v���Z�b�g��return true
	if (param[id].playerMoveDist >= GAMEPARAMETER_MOVEDIST_MAX)
	{
		param[id].isPlayerGoaled = true;
		SetGoalTelop(id);
		return true;
	}

	//���S�[������
	return false;
}

/**************************************
�V�X�e���p�����[�^�擾����
***************************************/
SYSTEMPARAMETER *GetSystemParameterAdr(void)
{
	return &sysParam;
}