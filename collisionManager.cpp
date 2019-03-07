//=====================================
//
//�Փ˔��菈��[collisionManager.cpp]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#include "collisionManager.h"
#include "player.h"
#include "slashBullet.h"

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
			if (!bullet->active)
				continue;

			if (ChechHitBoundingCube(&player->collider, &bullet->collider))
			{
				SetPlayerAcceleration(i, false);
			}
		}
	}
}