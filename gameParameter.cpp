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
		param[i].score = 0;
		param[i].deltaTime = 0.0f;
		param[i].isPlayerGoaled = false;
		param[i].posOffset = 0;
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
	return param[id].isPlayerGoaled;
}

/**************************************
�V�X�e���p�����[�^�擾����
***************************************/
SYSTEMPARAMETER *GetSystemParameterAdr(void)
{
	return &sysParam;
}

/**************************************
�I�t�Z�b�g�J�E���g��������
***************************************/
void AddOffsetCount(int playerID, bool isInclement)
{
	int addValue = isInclement ? 1 : -1;

	param[playerID].posOffset = Clamp(GAMEPARAMETER_POSOFFSET_MIN, GAMEPARAMETER_SPEED_MAX, param[playerID].posOffset + addValue);

}

/**************************************
���s���菈��
***************************************/
int CheckWinnerPlayer(void)
{
	if (param[0].deltaTime > param[1].deltaTime)
		return 1;

	if (param[0].deltaTime < param[1].deltaTime)
		return 0;

	//�����Ȃ̂ŃX�R�A�Ŕ���
	if (param[0].score > param[1].score)
		return 0;

	return 1;
}