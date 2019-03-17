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
		param[i].score = 0;
		param[i].deltaTime = 0.0f;
		param[i].isPlayerGoaled = false;
		param[i].posOffset = 0;
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
	return param[id].isPlayerGoaled;
}

/**************************************
システムパラメータ取得処理
***************************************/
SYSTEMPARAMETER *GetSystemParameterAdr(void)
{
	return &sysParam;
}

/**************************************
オフセットカウント増減処理
***************************************/
void AddOffsetCount(int playerID, bool isInclement)
{
	int addValue = isInclement ? 1 : -1;

	param[playerID].posOffset = Clamp(GAMEPARAMETER_POSOFFSET_MIN, GAMEPARAMETER_SPEED_MAX, param[playerID].posOffset + addValue);

}

/**************************************
勝敗判定処理
***************************************/
int CheckWinnerPlayer(void)
{
	if (param[0].deltaTime > param[1].deltaTime)
		return 1;

	if (param[0].deltaTime < param[1].deltaTime)
		return 0;

	//同着なのでスコアで判定
	if (param[0].score > param[1].score)
		return 0;

	return 1;
}