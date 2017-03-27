//------------------------------------------------------------------------------
//	�^�C�g���F		input�̃w�b�_�[
//	�t�@�C�����F	input.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/10
//------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CKeyboard;
class CMouse;

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------
const int nKeyMax = 256;				//  �L�[�̍ő吔
const int nRepeatCnt = 20;				//  ���s�[�g�J�n�܂ł̑҂�����

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  DirectInput�N���X
class CInput
{
public:
	CInput();
	~CInput();
	HRESULT			Init(HINSTANCE hInstance, HWND hWnd);
	void			Uninit(void);
	void			Update(void);

	//  �擾�֐�
	CKeyboard		*GetKeyboard(void);
	CMouse			*GetMouse(void);

private:
	LPDIRECTINPUT8	m_Input;		//  IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
	CKeyboard		*m_Keyboard;
	CMouse			*m_Mouse;
};
#endif