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

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
更新処理
***************************************/
void UpdateCollisionManager(void)
{
	//プレイヤーとスラッシュバレットを衝突判定
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < TARGETPLAYER_MAX; i++, player++)
	{
		SLASHBULLET *bullet = GetSlashBulletAdr(0);
		for (int j = 0; j < SLASHBULLET_NUM_MAX; j++, bullet++)
		{
			//非アクティブのバレットとは判定しない
			if (!bullet->active)
				continue;

			//プレイヤー自身が発射したバレットとは判定しない
			if (bullet->parentPlayerID == i)
				continue;

			//バウンディングボックスの判定
			if (ChechHitBoundingCube(&player->collider, &bullet->collider))
			{
				//バレットが当たったら減速
				SetPlayerAcceleration(i, false);
				bullet->active = false;
			}
		}
	}
}