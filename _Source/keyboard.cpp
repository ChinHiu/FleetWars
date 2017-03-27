//------------------------------------------------------------------------------
//	�^�C�g���F		ditectInput�֘A�̊֐�
//	�t�@�C�����F	directInput.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/10
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "input.h"
#include "keyboard.h"

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CKeyboard::CKeyboard
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CKeyboard::CKeyboard()
{
	m_Dev = NULL;

	ZeroMemory(m_KeyboardState,sizeof(m_KeyboardState));		//  �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateTrigger, sizeof(m_StateTrigger));			//  �g���K�[��Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateRelease, sizeof(m_StateRelease));			//  �����X��Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateRepeat, sizeof(m_StateRepeat));			//  ���s�[�g��Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateRepeatCnt, sizeof(m_StateRepeatCnt));		//  ���s�[�g�J�E���^���󂯎�郏�[�N
}

//------------------------------------------------------------------------------
//	�֐���:	CScene::~CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CKeyboard::~CKeyboard()
{
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CKeyboard::Init
//	����:	HINSTANCE hInstance, HWND hWnd
//	�߂�l:	E_FAIL���Ə��������s�AS_OK���Ə���������
//	����:	����������
//------------------------------------------------------------------------------
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input)
{
	//  IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^���擾
	LPDIRECTINPUT8 pInput = Input;

	if (FAILED(pInput->CreateDevice(GUID_SysKeyboard, &m_Dev, NULL)))
	{//  �f�o�C�X�I�u�W�F�N�g���쐬
		MessageBox(hWnd, "�L�[�{�[�h������܂���I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	if (m_Dev != NULL)
	{
		if (FAILED(m_Dev->SetDataFormat(&c_dfDIKeyboard)))											//�f�[�^�t�H�[�}�b�g�̐ݒ�
		{//  �f�[�^�t�H�[�}�b�g��ݒ�
			MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//  �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		if (FAILED(m_Dev->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))	//�������[�h�̐ݒ�
		{
			MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//  ���͐���J�n
		m_Dev->Acquire();
	}

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CKeyboard::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CKeyboard::Uninit(void)
{
	if (m_Dev != NULL)
	{//  �A�N�Z�X�����J��
		m_Dev->Unacquire();
		m_Dev->Release();
		m_Dev = NULL;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CKeyboard::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CKeyboard::Update(void)
{
	if (m_Dev != NULL)
	{
		BYTE KeyStateOld[nKeyMax];

		//  �O��̃f�[�^��ۑ�
		memcpy(KeyStateOld, m_KeyboardState, nKeyMax);

		if (SUCCEEDED(m_Dev->GetDeviceState(sizeof(m_KeyboardState), m_KeyboardState)))
		{//  �f�o�C�X����f�[�^���擾
			for (int i = 0; i < nKeyMax; i++)
			{
				m_StateTrigger[i]	= (KeyStateOld[i] ^ m_KeyboardState[i]) & m_KeyboardState[i];
				m_StateRelease[i]	= (KeyStateOld[i] ^ m_KeyboardState[i]) & ~m_KeyboardState[i];
				m_StateRepeat[i]	= m_StateTrigger[i];

				if (m_KeyboardState[i])
				{
					m_StateRepeatCnt[i]++;
					if (m_StateRepeatCnt[i] >= nRepeatCnt)
					{
						m_StateRepeat[i] = m_KeyboardState[i];
					}
				}
				else
				{
					m_StateRepeatCnt[i] = 0;
					m_StateRepeat[i] = 0;
				}
			}
		}
		else
		{
			//  �L�[�{�[�h�ւ̃A�N�Z�X�����擾
			m_Dev->Acquire();
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	bool CKeyboard::GetPress
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�L�[�{�[�h�̃v���X��Ԃ��擾
//------------------------------------------------------------------------------
bool CKeyboard::GetPress(int nKey)
{
	return (m_KeyboardState[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CKeyboard::GetTrigger
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�L�[�{�[�h�̃g���K�[��Ԃ��擾
//------------------------------------------------------------------------------
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_StateTrigger[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CKeyboard::GetRelease
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�L�[�{�[�h�̃����[�X��Ԃ��擾
//------------------------------------------------------------------------------
bool CKeyboard::GetRelease (int nKey)
{
	return (m_StateRelease[nKey] & 0x80) ? true : false;
}


//------------------------------------------------------------------------------
//	�֐���:	bool CKeyboard::GetRepeat
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�L�[�{�[�h�̃��s�[�g��Ԃ��擾
//------------------------------------------------------------------------------
bool CKeyboard::GetRepeat(int nKey)
{
	return (m_StateRepeat[nKey] & 0x80) ? true : false;
}
