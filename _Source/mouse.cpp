//------------------------------------------------------------------------------
//	�^�C�g���F		�}�E�X�֘A�̊֐�
//	�t�@�C�����F	mouse.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/31
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "input.h"
#include "mouse.h"
#include "camera.h"
#include "cursor.h"
//#include "game.h"
#include "title.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CMouse::CMouse
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CMouse::CMouse()
{
	m_Dev			= NULL;
	//m_Cursor		= NULL;
	m_MouseState.lX =
	m_MouseState.lY =
	m_MouseState.lZ = 0;
	ZeroMemory(m_StateTrigger, sizeof(m_StateTrigger));		//  �g���K�[��Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateRelease, sizeof(m_StateRelease));		//  �����X��Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateRepeat, sizeof(m_StateRepeat));		//  ���s�[�g��Ԃ��󂯎�郏�[�N
	ZeroMemory(m_StateRepeatCnt, sizeof(m_StateRepeatCnt));	//  ���s�[�g�J�E���^���󂯎�郏�[�N
}

//------------------------------------------------------------------------------
//	�֐���:	CScene::~CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CMouse::~CMouse()
{
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CMouse::Init
//	����:	HINSTANCE hInstance, HWND hWnd
//	�߂�l:	E_FAIL���Ə��������s�AS_OK���Ə���������
//	����:	����������
//------------------------------------------------------------------------------
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  �C���X�^���X����
	m_Cursor = new CCursor;

	//  IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^���擾
	LPDIRECTINPUT8 pInput = Input;
	

	if (FAILED(pInput->CreateDevice(GUID_SysMouse, &m_Dev, NULL)))
	{//  �f�o�C�X�I�u�W�F�N�g���쐬
		MessageBox(hWnd, "�}�E�X������܂���I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	if (m_Dev != NULL)
	{
		if (FAILED(m_Dev->SetDataFormat(&c_dfDIMouse)))											//  �f�[�^�t�H�[�}�b�g�̐ݒ�
		{//  �f�[�^�t�H�[�}�b�g��ݒ�
			MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//  (DISCL_EXCLUSIVE | DISCL_FOREGROUND�i�t�H�A�O���E���h����r�����[�h
		//  (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
		//  �������[�h��ݒ�j
		if (FAILED(m_Dev->SetCooperativeLevel(hWnd, (DISCL_EXCLUSIVE | DISCL_FOREGROUND))))		//  �������[�h�̐ݒ�
		{
			MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//  �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_REL;															//  ���Βl���[�h�Őݒ�i��΃��[�h��DIPROPAXISMODE_ABS�j

		if (FAILED(m_Dev->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			MessageBox(hWnd, "�����[�h�̐ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//  �}�E�X�\���̂̏�����
		SetRect(&m_Mouse.moveRect, 0, 0, (int)pScreenSize->x, (int)pScreenSize->y);	//  �}�E�X�J�[�\���̓����͈�
		m_Mouse.x		= (int)(pScreenSize->x * 0.5f);									//  �}�E�X�J�[�\���̂w���W��������
		m_Mouse.y		= (int)(pScreenSize->y * 0.5f);									//  �}�E�X�J�[�\���̂x���W��������
		m_Mouse.moveAdd	= 2;															//  �}�E�X�J�[�\���̈ړ��ʂ�ݒ�

		//���͐���J�n
		m_Dev->Acquire();

		//�J�[�\���̏���������
		m_Cursor->Init();
	}

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CMouse::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CMouse::Uninit(void)
{
	if (m_Dev != NULL)
	{//  �A�N�Z�X�����J��
		m_Dev->Unacquire();
		m_Dev->Release();
		m_Dev = NULL;
	}

	//  �J�[�\���̏I������
	m_Cursor->Uninit();
}

//------------------------------------------------------------------------------
//	�֐���:	void CMouse::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CMouse::Update(void)
{
	HWND hWnd = GetWnd();
	POINT tempPos;
	GetCursorPos(&tempPos);
	ScreenToClient(hWnd, &tempPos);

	CMode *pMode = CManager::GetMode();
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		CTitle *pTitle = ((CTitle*)CManager::GetMode());
		m_Mouse.x = (int)tempPos.x;
		m_Mouse.y = (int)tempPos.y;

		MouseUpdate();
	}
	else
	{
		CGame *pGame = ((CGame*)CManager::GetMode());
		CCamera_Data *pCameraData = CManager::GetCameraData();
/*
		D3DXVECTOR3 *pScopePos = CGame::GetScope()->GetPosition();*/

		m_Mouse.x = (int)(pScreenSize->x * 0.5f);
		m_Mouse.y = (int)(pScreenSize->y * 0.5f);

	/*	m_Mouse.x = (int)tempPos.x;
		m_Mouse.y = (int)tempPos.y;*/

		MouseUpdate();

		//  ���[���h���W�֕ϊ�
		CalcScreenToXZ(
			&m_Pos,
			m_Mouse.x,
			m_Mouse.y,
			pScreenSize->x,
			pScreenSize->y,
			&pCameraData->mtxView,
			&pCameraData->mtxProjection
		);

		m_Cursor->Update();

		//  �J�[�\���̐ݒ�
		m_Cursor->SetPosition(m_Pos);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	bool CMouse::GetPress
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�}�E�X�̃v���X��Ԃ��擾
//------------------------------------------------------------------------------
bool CMouse::GetPress(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CMouse::GetTrigger
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�}�E�X�̃g���K�[��Ԃ��擾
//------------------------------------------------------------------------------
bool CMouse::GetTrigger(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CKeyboard::GetRelease
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�}�E�X�̃����[�X��Ԃ��擾
//------------------------------------------------------------------------------
bool CMouse::GetRelease(int nKey)
{
	return (m_StateTrigger[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CMouse::GetRepeat
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�}�E�X�̃��s�[�g��Ԃ��擾
//------------------------------------------------------------------------------
bool CMouse::GetRepeat(int nKey)
{
	return (m_StateRepeat[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CMouse::GetRepeat
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�}�E�X�̃��s�[�g��Ԃ��擾
//------------------------------------------------------------------------------
MSTATE *CMouse::GetMousePoint(void)
{
	return &m_Mouse;
}

//------------------------------------------------------------------------------
//	�֐���:	bool CMouse::GetRepeat
//	����:	int nKey
//	�߂�l:	true���Ɖ����Ă���, false���Ɖ����Ă��Ȃ�
//	����:	�}�E�X�̃��s�[�g��Ԃ��擾
//------------------------------------------------------------------------------
DIMOUSESTATE *CMouse::GetMouseState(void)
{
	return &m_MouseState;
}

//------------------------------------------------------------------------------
//	�֐���:	D3DXVECTOR3 *CMouse::GetWorldPos
//	����:	�Ȃ�
//	�߂�l:	m_Pos
//	����:	�}�E�X�̃��[���h���W���擾
//------------------------------------------------------------------------------
D3DXVECTOR3 *CMouse::GetWorldPos(void)
{
	return &m_Pos;
}

////------------------------------------------------------------------------------
////	�֐���:	PRIMITIVE_TYPE *CMouse::GetPrimitiveType
////	����:	�Ȃ�
////	�߂�l:	m_Type
////	����:	�I�������v���~�e�B�u�^�C�v���擾
////------------------------------------------------------------------------------
//PRIMITIVE_TYPE *CMouse::GetPrimitiveType(void)
//{
//	return &m_Type;
//}

//------------------------------------------------------------------------------
//	�֐���:	int	*CMouse::GetInBlockNum
//	����:	�Ȃ�
//	�߂�l:	m_nInBlockNum
//	����:	�}�E�X�̂���u���b�N���擾
//------------------------------------------------------------------------------
int	*CMouse::GetInBlockNum(void)
{
	return &m_nInBlockNum;
}

//------------------------------------------------------------------------------
//	�֐���:	CCursor *CMouse::GetCursor
//	����:	�Ȃ�
//	�߂�l:	m_Cursor
//	����:	�J�[�\�����擾
//------------------------------------------------------------------------------
CCursor *CMouse::GetCursor(void)
{
	return m_Cursor;
}

//------------------------------------------------------------------------------
//	�֐���:	D3DXVECTOR3 *CMouse::CalcScreenToWorld
//	����:	D3DXVECTOR3* pout,
//			int Sx,							//  �X�N���[��X���W
//			int Sy,							//  �X�N���[��Y���W
//			float fZ,						//  �ˉe��Ԃł�Z�l�i0�`1�j
//			int Screen_w,
//			int Screen_h,
//			D3DXMATRIX* View,
//			D3DXMATRIX* Prj
//	�߂�l:	m_Cursor
//	����:	�X�N���[�����W�����[���h���W�ɕϊ�
//------------------------------------------------------------------------------
D3DXVECTOR3 *CMouse::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,							//  �X�N���[��X���W
	int Sy,							//  �X�N���[��Y���W
	float fZ,						//  �ˉe��Ԃł�Z�l�i0�`1�j
	float Screen_w,
	float Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	//  �e�s��̋t�s����Z�o
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w * 0.5f;
	VP._22 = -Screen_h * 0.5f;
	VP._41 = Screen_w * 0.5f;
	VP._42 = Screen_h * 0.5f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	//  �t�ϊ�
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(
		pout,
		&D3DXVECTOR3((float)Sx, (float)Sy, fZ),
		&tmp
	);

	return pout;
}

//------------------------------------------------------------------------------
//	�֐���:	D3DXVECTOR3 *CMouse::CalcScreenToXZ
//	����:	D3DXVECTOR3* pout,
//			int Sx,
//			int Sy,
//			int Screen_w,
//			int Screen_h,
//			D3DXMATRIX* View,
//			D3DXMATRIX* Prj		
//	�߂�l:	m_Cursor
//	����:	XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
//------------------------------------------------------------------------------
D3DXVECTOR3 *CMouse::CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	float Screen_w,
	float Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);

	//  ���Ƃ̌������N���Ă���ꍇ�͌�_���o��
	//  �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if (ray.y <= 0) {
		//  ����_
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}

void CMouse::MouseUpdate(void)
{
	if (m_Dev != NULL)
	{
		BYTE MouseStateOld[nKeyMax];

		//  �O��̃f�[�^��ۑ�
		memcpy(MouseStateOld, m_MouseState.rgbButtons, nKeyMax);

		if (SUCCEEDED(m_Dev->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
		{//  �f�o�C�X����f�[�^���擾
		 //  ��ʊO�`�F�b�N
			if (m_Mouse.x < m_Mouse.moveRect.left)
			{
				m_Mouse.x = m_Mouse.moveRect.left;
			}
			if (m_Mouse.x > m_Mouse.moveRect.right)
			{
				m_Mouse.x = m_Mouse.moveRect.right;
			}
			if (m_Mouse.y < m_Mouse.moveRect.top)
			{
				m_Mouse.y = m_Mouse.moveRect.top;
			}
			if (m_Mouse.y > m_Mouse.moveRect.bottom)
			{
				m_Mouse.y = m_Mouse.moveRect.bottom;
			}

			for (int i = 0; i < nKeyMax; i++)
			{//  �f�o�C�X����f�[�^���擾
				m_StateTrigger[i] = (MouseStateOld[i] ^ m_MouseState.rgbButtons[i]) & m_MouseState.rgbButtons[i];
				m_StateRelease[i] = (MouseStateOld[i] ^ m_MouseState.rgbButtons[i]) & ~m_MouseState.rgbButtons[i];
				m_StateRepeat[i] = m_StateTrigger[i];

				if (m_MouseState.rgbButtons[i])
				{
					m_StateRepeatCnt[i]++;
					if (m_StateRepeatCnt[i] >= nRepeatCnt)
					{
						m_StateRepeat[i] = m_MouseState.rgbButtons[i];
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
			//  �}�E�X�ւ̃A�N�Z�X�����擾
			m_Dev->Acquire();
		}
	}
}