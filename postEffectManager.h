//=====================================
//
//�|�X�g�G�t�F�N�g�}�l�[�W���w�b�_[postEffectManager.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _POSTEFFECTMANAGER_H_
#define _POSTEFFECTMANAGER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
enum DEFINE_POSTEFFECT {
	EFFECT_SHOCKBLUR,
	EFFECT_MONOTONE,
	EFFECT_MAX,
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitPostEffectManager(int num);
void UninitPostEffectManager(int num);
void UpdatePostEffectManager(void);
void DrawPostEffectManager(LPDIRECT3DTEXTURE9 tex[2], LPDIRECT3DSURFACE9 suf[2], LPDIRECT3DSURFACE9 back, int targetID);

bool CheckActivePostEffect(char effect);
bool SetPostEffectUse(char effect, bool state);
#endif