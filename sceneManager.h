//=====================================
//
//シーンマネージャヘッダ[sceneManager.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
enum DefineScene
{
	GameScene,
	TitleScene,
	DefineSceneMax
};

enum SceneResult
{
	SceneRunning,
	SceneFinished,
	SceneResultMax
};

/**************************************
プロトタイプ宣言
***************************************/
void InitSceneManager(int* ptr);
void UninitSceneManager(int num);
void UninitScene(int num);
void UpdateSceneManager(void);
void DrawSceneManager(int n);
void SetScene(DefineScene sceneId);
int GetNextScene(void);
#endif