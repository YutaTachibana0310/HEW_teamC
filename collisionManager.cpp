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

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
�X�V����
***************************************/
void UpdateCollisionManager(void)
{
	//�v���C���[�ƃX���b�V���o���b�g���Փ˔���
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < TARGETPLAYER_MAX; i++, player++)
	{
		SLASHBULLET *bullet = GetSlashBulletAdr(0);
		for (int j = 0; j < SLASHBULLET_NUM_MAX; j++, bullet++)
		{
			//��A�N�e�B�u�̃o���b�g�Ƃ͔��肵�Ȃ�
			if (!bullet->active)
				continue;

			//�v���C���[���g�����˂����o���b�g�Ƃ͔��肵�Ȃ�
			if (bullet->parentPlayerID == i)
				continue;

			//�o�E���f�B���O�{�b�N�X�̔���
			if (ChechHitBoundingCube(&player->collider, &bullet->collider))
			{
				//�o���b�g�����������猸��
				SetPlayerAcceleration(i, false);
				bullet->active = false;
			}
		}
	}
}