//=====================================
//
//�Q�[���R���g���[���w�b�_[gameController.h]
//Author:GP11A341 21 ���ԗY��
//
//=====================================
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/
//�Q�[���R���g���[���\����
typedef struct {
	int cntFrame;

	int currentState;
	int prevState;
}GAMECONTROLLER;

//�Q�[���R���g���[���̊e�X�e�[�g
enum GAMECONTROLLER_STATE {
	GAMECONTROLLER_START,
	GAMECONTROLLER_STATEMAX
};
/**************************************
�v���g�^�C�v�錾
***************************************/
void InitGameController(int num);
void UninitGameController(int num);
void UpdateGameController(void);
void DrawGameController(void);

//��ԑJ�ڏ���
void ChangeStateGameController(int next);

//�e���ꏈ��
void EnterGameControllerStart(GAMECONTROLLER *entity);

//�e�X�V����
void UpdateGameControllerStart(GAMECONTROLLER *entity);

#endif