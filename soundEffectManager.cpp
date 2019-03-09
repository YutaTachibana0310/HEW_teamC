//=====================================
//
//サウンドエフェクトマネージャ処理[soundEffectManager.cpp]
//Author:GP11A341 21 立花雄太
//
//=====================================
#include "soundEffectManager.h"
#include "sound.h"
#include <tchar.h>
#include "debugWindow.h"
#include <stdio.h>

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

/**************************************
マクロ定義
***************************************/
#define SOUND_POS_FAR_END			(10000.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static const TCHAR* soundFileName[SOUND_MAX] =
{
	_T("data/SOUND/lockon.wav"),
};

static SOUNDEFFECT container[SOUND_MAX];

/**************************************
プロトタイプ宣言
***************************************/
bool SaveSettingsSoundEffect(void);
bool LoadSettingsSoundEffect(void);
void DrawDebugWindowSoundEffect(void);

/**************************************
初期化処理
***************************************/
void InitSoundEffectManager(int num)
{
	static bool initialized = false;

	if (!initialized)
	{
		bool res = LoadSettingsSoundEffect();

		for (int i = 0; i < SOUND_MAX; i++)
		{
			container[i].clip = LoadSound(&soundFileName[static_cast<unsigned int>(i)][0]);
			SetSoundVolume(container[i].clip, container[i].volume);
		}
		initialized = true;
	}

	return;
}

/**************************************
終了処理
***************************************/
void UninitSoundEffectManager(int num)
{
	if (num == 0)
	{
		for (int i = 0; i < SOUND_MAX; i++)
		{
			SAFE_RELEASE(container[i].clip);
		}
	}
}

/**************************************
更新処理
***************************************/
void UpdateSoundEffectManager(void)
{
	DrawDebugWindowSoundEffect();
}

/**************************************
再生処理
***************************************/
void PlaySE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
再生処理(3D版)
***************************************/
void PlaySE_3D(DefineSE sound, float posZ)
{
	float decay = 1.0f - posZ / SOUND_POS_FAR_END;

	SetSoundVolume(container[sound].clip, container[sound].volume * decay);
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
停止処理
***************************************/
void StopSE(DefineSE sound)
{
	StopSoundBuffer(container[sound].clip);
}

/**************************************
再開処理
***************************************/
void ResumeSE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, false);
}

/**************************************
再生中判定
***************************************/
bool IsPlayingSE(DefineSE sound)
{
	return IsPlaying(container[sound].clip);
}

/**************************************
音量設定
***************************************/
void SetSEVolume(DefineSE sound, float volume)
{
	SetSoundVolume(container[sound].clip, volume);
}

/**************************************
デバッグウィンドウ
***************************************/
void DrawDebugWindowSoundEffect(void)
{
	BeginDebugWindow("SoundEffect");

	for (int i = 0; i < SOUND_MAX; i++)
	{
		DebugText("%d", i);
		DebugSameLine();
		if (DebugSliderFloat("", &container[i].volume, SOUND_VOLUME_MIN, SOUND_VOLUME_MAX))
		{
			SetSoundVolume(container[i].clip, container[i].volume);
		}
	}

	if (DebugButton("Save Settings"))
	{
		SaveSettingsSoundEffect();
		for (int i = 0; i < SOUND_MAX; i++)
		{
			SetSoundVolume(container[i].clip, container[i].volume);
		}
	}

	EndDebugWindow("SoundEffect");

	BeginDebugWindow("PlaySound");

	for (int i = 0; i < SOUND_MAX; i++)
	{
		char str[8];
		sprintf(str, "%d", i);
		if (DebugButton(str)) { PlaySE((DefineSE)i); }
	}

	EndDebugWindow("PlaySound");
}

/**************************************
設定保存処理
***************************************/
bool SaveSettingsSoundEffect(void)
{
	FILE *fp = NULL;
	fp = fopen("data/SETTINGS/sound.ini", "wb");

	if (fp == NULL)
	{
		return false;
	}

	for (int i = 0; i < SOUND_MAX; i++)
	{
		fwrite(&container[i].volume, sizeof(float), 1, fp);
	}

	fclose(fp);

	return true;
}

/**************************************
設定読み込み処理
***************************************/
bool LoadSettingsSoundEffect(void)
{
	FILE *fp = NULL;
	fp = fopen("data/SETTINGS/sound.ini", "rb");

	if (fp == NULL)
	{
		for (int i = 0; i < SOUND_MAX; i++)
		{
			container[i].volume = SOUND_VOLUME_INIT;
		}

		return false;
	}

	for (int i = 0; i < SOUND_MAX; i++)
	{
		int res = fread(&container[i].volume, sizeof(float), 1, fp);
		if (res == EOF)
			container[i].volume = SOUND_VOLUME_INIT;
	}

	fclose(fp);

	return true;
}