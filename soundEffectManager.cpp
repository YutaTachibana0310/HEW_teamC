//=====================================
//
//�T�E���h�G�t�F�N�g�}�l�[�W������[soundEffectManager.cpp]
//Author:GP11A341 21 ���ԗY��
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
�}�N����`
***************************************/
#define SOUND_POS_FAR_END			(10000.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static const TCHAR* soundFileName[SOUND_MAX] =
{
	_T("data/SOUND/lockon.wav"),
};

static SOUNDEFFECT container[SOUND_MAX];

/**************************************
�v���g�^�C�v�錾
***************************************/
bool SaveSettingsSoundEffect(void);
bool LoadSettingsSoundEffect(void);
void DrawDebugWindowSoundEffect(void);

/**************************************
����������
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
�I������
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
�X�V����
***************************************/
void UpdateSoundEffectManager(void)
{
	DrawDebugWindowSoundEffect();
}

/**************************************
�Đ�����
***************************************/
void PlaySE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
�Đ�����(3D��)
***************************************/
void PlaySE_3D(DefineSE sound, float posZ)
{
	float decay = 1.0f - posZ / SOUND_POS_FAR_END;

	SetSoundVolume(container[sound].clip, container[sound].volume * decay);
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, true);
}

/**************************************
��~����
***************************************/
void StopSE(DefineSE sound)
{
	StopSoundBuffer(container[sound].clip);
}

/**************************************
�ĊJ����
***************************************/
void ResumeSE(DefineSE sound)
{
	PlaySoundBuffer(container[sound].clip, E_DS8_FLAG_NONE, false);
}

/**************************************
�Đ�������
***************************************/
bool IsPlayingSE(DefineSE sound)
{
	return IsPlaying(container[sound].clip);
}

/**************************************
���ʐݒ�
***************************************/
void SetSEVolume(DefineSE sound, float volume)
{
	SetSoundVolume(container[sound].clip, volume);
}

/**************************************
�f�o�b�O�E�B���h�E
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
�ݒ�ۑ�����
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
�ݒ�ǂݍ��ݏ���
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