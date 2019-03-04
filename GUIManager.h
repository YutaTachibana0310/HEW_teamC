//=====================================
//
//GUIマネージャヘッダ[GUIManager.h]
//Author:GP11A341 21 立花雄太
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/
enum GUI_NUMTEXTURE
{
	GUI_NUMSCORE,
	GUI_NUMLOCKON,
	GUI_NUMBONUSTIME,
	GUI_NUMRANKING,
	GUI_NUMTEX_MAX
};
/**************************************
プロトタイプ宣言
***************************************/
void InitGUIManager(int num);
void UninitGUIManager(int num);
void UpdateGUIManager(int currentScene);
void DrawGUIManager(int currentScene);

//各シーンGU初期化処理
void InitGameSceneGUI(void);
void InitTitleSceneGUI(void);
void InitResultSceneGUI(void);

//各シーンGUI終了処理
void UninitGameSceneGUI(void);
void UninitTitleSceneGUI(void);
void UninitResultSceneGUI(void);

//各シーンGUI更新処理
void UpdateGameSceneGUI(void);
void UpdateTitleSceneGUI(void);
void UpdateResultSceneGUI(void);

//各シーンGUI描画処理
void DrawGameSceneGUI(void);
void DrawTitleSceneGUI(void);
void DrawResultSceneGUI(void);

#endif