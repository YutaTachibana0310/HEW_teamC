//=====================================
//
//�Փ˔��菈��[collisionManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "player.h"
#include "slashBullet.h"
#include "scrollSpeedController.h"
#include "gameParameter.h"

#include "bulletParticle.h"
#include "soundEffectManager.h"

#include "bullet.h"
#include "goalTape.h"
#include "goalTelop.h"
/**************************************
�}�N����`
***************************************/
#define BULLRTPARTICLE_SETNUM		(30)
#define	HITBULLET_ADDSCORE			(500)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void CollisionBulletAndPlayer(void);
void CollisionGoalAndPlayer(void);

/**************************************
�X�V����
***************************************/
void UpdateCollisionManager(void)
{
	CollisionBulletAndPlayer();
	CollisionGoalAndPlayer();
}

/**************************************
�o���b�g�ƃv���C���[�̏Փ˔���
***************************************/
void CollisionBulletAndPlayer(void)
{
	//�v���C���[�ƃX���b�V���o���b�g���Փ˔���
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < TARGETPLAYER_MAX; i++, player++)
	{
		int opponent = WrapAround(0, TARGETPLAYER_MAX, i + 1);
		BULLET *bullet = GetBulletAdr(opponent, 0);
		for (int j = 0; j < SLASHBULLET_NUM_MAX / 2; j++, bullet++)
		{
			//��A�N�e�B�u�̃o���b�g�Ƃ͔��肵�Ȃ�
			if (!bullet->use)
				continue;

			//�o�E���f�B���O�{�b�N�X�̔���
			if (ChechHitBoundingCube(&player->collider, &bullet->collider))
			{
				//���������v���C���[������
				SetPlayerAcceleration(i, false);

				//���Ă��v���C���[������
				SetPlayerAcceleration(opponent, true);

				//�X�R�A���Z
				GetGameParameterAdr(i)->score += HITBULLET_ADDSCORE;

				bullet->use = false;

				//�p�[�e�B�N���Z�b�g
				for (int cntParticle = 0; cntParticle < BULLRTPARTICLE_SETNUM; cntParticle++)
					SetBulletParticle(*bullet->collider.pos);

				//SE�Đ�
				PlaySE(SOUND_SLASH);

				//�Ή����Ă���X���b�V���o���b�g���A�N�e�B�u��
				GetSlashBulletAdr(bullet->idxSlashBullet)->active = false;
			}
		}
	}
}

/**************************************
�S�[���ƃv���C���[�̏Փ˔���
***************************************/
void CollisionGoalAndPlayer(void)
{
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < TARGETPLAYER_MAX; i++, player++)
	{
		GAMEPARAMETER *param = GetGameParameterAdr(i);
		if (param->isPlayerGoaled)
			continue;

		GOALTAPE *tape = GetGoalTapeAdr();
		if (ChechHitBoundingCube(&player->collider, &tape->collider))
		{
			SetGoalTelop(i);
			param->isPlayerGoaled = true;
		}
	}
}