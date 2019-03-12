//=====================================
//
//ゲームパラメータ処理[gameParameter.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "gameParameter.h"
#include "goalTelop.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static GAMEPARAMETER param[TARGETPLAYER_MAX];
static SYSTEMPARAMETER sysParam;

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
初期化処理
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
終了処理
***************************************/
void UninitGameParameter(int num)
{

}

/**************************************
更新処理
***************************************/
void UpdateGameParameter(void)
{

}

/**************************************
描画処理
***************************************/
void DrawGameParameter(void)
{

}

/**************************************
ゲームパラメータアドレス取得処理
***************************************/
GAMEPARAMETER *GetGameParameterAdr(int n)
{
	return &param[n];
}

/**************************************
進行関連のパラメータセット処理
***************************************/
void SetSpeedGameParameter(int id, float speed)
{
	param[id].playerSpeed = speed;
}

/**************************************
ゴール到達判定処理
***************************************/
bool CheckPlayerGoaled(int id)
{
	//ゴール済みであればreturn true
	if (param[id].isPlayerGoaled)
		return true;

	//移動距離をチェックし、ゴールを超えていればテロップをセットしreturn true
	if (param[id].playerMoveDist >= GAMEPARAMETER_MOVEDIST_MAX)
	{
		param[id].isPlayerGoaled = true;
		SetGoalTelop(id);
		return true;
	}

	//未ゴール判定
	return false;
}

/**************************************
システムパラメータ取得処理
***************************************/
SYSTEMPARAMETER *GetSystemParameterAdr(void)
{
	return &sysParam;
}