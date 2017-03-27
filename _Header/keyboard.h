//------------------------------------------------------------------------------
//	�^�C�g���F		�L�[�{�[�h�̃w�b�_�[
//	�t�@�C�����F	keyboard.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/10
//------------------------------------------------------------------------------
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �L�[�{�[�h�N���X
class CKeyboard
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT	Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input);
	void	Uninit(void);
	void	Update(void);

	//  �擾�֐�
	bool	GetPress(int key);
	bool	GetTrigger(int key);
	bool	GetRelease(int key);
	bool	GetRepeat(int key);

private:
	LPDIRECTINPUTDEVICE8	m_Dev;									//  IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
	BYTE					m_KeyboardState[nKeyMax];			//  �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE					m_StateTrigger[nKeyMax];				//  �g���K�[��Ԃ��󂯎�郏�[�N
	BYTE					m_StateRelease[nKeyMax];				//  �����X��Ԃ��󂯎�郏�[�N
	BYTE					m_StateRepeat[nKeyMax];				//  ���s�[�g��Ԃ��󂯎�郏�[�N
	int						m_StateRepeatCnt[nKeyMax];			//  ���s�[�g�J�E���^���󂯎�郏�[�N
};

#endif