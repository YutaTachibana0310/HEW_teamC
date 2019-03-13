//=====================================
//
//衝突判定処理[collisionManager.cpp]
//Author:GP11A341 21 立花雄太
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
マクロ定義
***************************************/
#define BULLRTPARTICLE_SETNUM		(30)
#define	HITBULLET_ADDSCORE			(500)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void CollisionBulletAndPlayer(void);
void CollisionGoalAndPlayer(void);

/**************************************
更新処理
***************************************/
void UpdateCollisionManager(void)
{
	CollisionBulletAndPlayer();
	CollisionGoalAndPlayer();
}

/**************************************
バレットとプレイヤーの衝突判定
***************************************/
void CollisionBulletAndPlayer(void)
{
	//プレイヤーとスラッシュバレットを衝突判定
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < TARGETPLAYER_MAX; i++, player++)
	{
		int opponent = WrapAround(0, TARGETPLAYER_MAX, i + 1);
		BULLET *bullet = GetBulletAdr(opponent, 0);
		for (int j = 0; j < SLASHBULLET_NUM_MAX / 2; j++, bullet++)
		{
			//非アクティブのバレットとは判定しない
			if (!bullet->use)
				continue;

			//バウンディングボックスの判定
			if (ChechHitBoundingCube(&player->collider, &bullet->collider))
			{
				//当たったプレイヤーを減速
				SetPlayerAcceleration(i, false);

				//当てたプレイヤーを加速
				SetPlayerAcceleration(opponent, true);

				//スコア加算
				GetGameParameterAdr(i)->score += HITBULLET_ADDSCORE;

				bullet->use = false;

				//パーティクルセット
				for (int cntParticle = 0; cntParticle < BULLRTPARTICLE_SETNUM; cntParticle++)
					SetBulletParticle(*bullet->collider.pos);

				//SE再生
				PlaySE(SOUND_SLASH);

				//対応しているスラッシュバレットを非アクティブに
				GetSlashBulletAdr(bullet->idxSlashBullet)->active = false;
			}
		}
	}
}

/**************************************
ゴールとプレイヤーの衝突判定
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