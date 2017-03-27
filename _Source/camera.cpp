//------------------------------------------------------------------------------
//	�^�C�g���F		�J�����֐�
//	�t�@�C�����F	camera.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/26
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "camera.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	�}�N����`��Const��`
//------------------------------------------------------------------------------
const int			nNear_Z			= 5;										//  NearZ�l
const int			nFar_Z			= 50000;									//  FarZ�l
const float			fView_Angle		= 45.0f;									//  ����p
const float			fDistance		= 650.0f;									//  �����_�Ǝ��_�̋���
const float			fCamera_Move	= 0.005f;									//  �f�o�b�O��ԃJ�����̈ړ���
const D3DXVECTOR3	View_Pos		= D3DXVECTOR3(291.00f, 107.0f, -400.0f);	//  ���_���W�����l
const D3DXVECTOR3	Look_Pos		= D3DXVECTOR3(0.0f, 40.0f, 0.0f);			//  �����_���W�����l
const D3DXVECTOR3	Gun_Pos			= D3DXVECTOR3(32.0f, 64.0f, 32.0f);			//  �e�̑��Έʒu

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CCamera::CCamera()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CCamera::CCamera()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CCamera::~CCamera()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CCamera::~CCamera()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CCamera::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CCamera::Init(D3DXVECTOR3 rot, bool bLookAt)
{
	//  �J�����̎��_
	m_CameraData.posV = View_Pos;

	//  �J�����̒����_
	m_CameraData.posR = Look_Pos;

	//  �J�����̏����
	m_CameraData.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//  �J�����̌���
	m_CameraData.rot = rot;

	//�J�����̈ړ���
	m_CameraData.fMove = fCamera_Move;

	//  ���_�ƒ����_�̋���
	m_CameraData.fDistance = fDistance;

	//  ���񒆐S�𒍎��_�ɐݒ�
	m_CameraData.bLookAt = bLookAt;
}	

//------------------------------------------------------------------------------
//	�֐���:	void CCamera::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CCamera::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CCamera::Update(void)
{
	CMode		*pMode		= CManager::GetMode();
	CKeyboard	*pKeyboard	= CManager::GetInput()->GetKeyboard();
	CMouse		*pMouse		= CManager::GetInput()->GetMouse();

	//  �^�C�g���ȊO�J�����̍X�V
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		CPlayer	*pPlayer = CManager::GetPlayer();				//  �v���C���[���擾
		WEAPON_TYPE *pPlayerWeapon = pPlayer->GetWeponType();	//  �v���C���[���݂̕�����擾
		D3DXVECTOR3 *pPlayerPos = pPlayer->GetPosition();		//  �v���C���[�ʒu���擾
		D3DXVECTOR3 *pPlayerRot = pPlayer->GetRotation();		//  �v���C���[��]���擾

		float RateRot;

		if (*pPlayerWeapon != m_OldWeapon)
		{
			if(*pPlayerWeapon == WEAPON_BULLET) m_CameraData.rot.x = D3DX_PI * 0.57f;
			else								m_CameraData.rot.x = D3DX_PI * 0.43f;
		}

		switch (*pPlayerWeapon)
		{
		case WEAPON_BULLET:
			if (pMouse->GetMouseState()->lX != 0)
			{
				m_CameraData.rot.y += pMouse->GetMouseState()->lX * fCamera_Move;
				SAFE_ROTCHECK(m_CameraData.rot.y);
			}

			RateRot = m_CameraData.rot.y + pPlayerRot->y;
			SAFE_ROTCHECK(RateRot);

			if (pMouse->GetMouseState()->lY != 0)
			{
				m_CameraData.rot.x += pMouse->GetMouseState()->lY * fCamera_Move;
				if (m_CameraData.rot.x >= D3DX_PI * 0.57f)
				{
					m_CameraData.rot.x = D3DX_PI * 0.57f;
				}
				else if (m_CameraData.rot.x <= D3DX_PI * 0.4f)
				{
					m_CameraData.rot.x = D3DX_PI * 0.4f;
				}
			}

			m_CameraData.posV.x = pPlayerPos->x + sinf(-pPlayerRot->y) * Gun_Pos.x;
			m_CameraData.posV.y = pPlayerPos->y + Gun_Pos.y;
			m_CameraData.posV.z = pPlayerPos->z - cosf(-pPlayerRot->y) * Gun_Pos.z;

			//  �v���C���[�J�����̒Ǐ]
			m_CameraData.posR.x = m_CameraData.posV.x - sinf(-RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			m_CameraData.posR.y = m_CameraData.posV.y + cosf(m_CameraData.rot.x) * m_CameraData.fDistance;
			m_CameraData.posR.z = m_CameraData.posV.z + cosf(-RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			break;
		default:
			if (pMouse->GetMouseState()->lX != 0)
			{
				m_CameraData.rot.y += pMouse->GetMouseState()->lX * fCamera_Move;
				SAFE_ROTCHECK(m_CameraData.rot.y);
			}

			RateRot = m_CameraData.rot.y + pPlayerRot->y;
			SAFE_ROTCHECK(RateRot);

			//  �����_���W�̍X�V
			m_CameraData.posR.x = pPlayerPos->x;
			m_CameraData.posR.y = Look_Pos.y;
			m_CameraData.posR.z = pPlayerPos->z;

			//  �����_���王�_�����߂�
			m_CameraData.posV.x = m_CameraData.posR.x - sinf(RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			m_CameraData.posV.z = m_CameraData.posR.z - cosf(RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			m_CameraData.posV.y = m_CameraData.posR.y + cosf(m_CameraData.rot.x) * m_CameraData.fDistance;
			break;
		}

		m_OldWeapon = *pPlayerWeapon;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CCamera::SetCamera
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�J�����̐ݒ�
//------------------------------------------------------------------------------
void CCamera::SetCamera(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_CameraData.mtxProjection);

	//  �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH
	(
		&m_CameraData.mtxProjection,
		D3DXToRadian(fView_Angle),					//  ����p
		(float)pScreenSize->x / pScreenSize->y,		//  �A�X�y�N�g��
		(float)nNear_Z,								//  NearZ�l
		(float)nFar_Z								//  FarZ�l
	);

	//  �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_CameraData.mtxProjection);

	//  �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH
	(
		&m_CameraData.mtxView,
		&m_CameraData.posV,
		&m_CameraData.posR,
		&m_CameraData.vecU
	);

	//  �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_CameraData.mtxView);
}

//------------------------------------------------------------------------------
//	�֐���:	CCamera_Data *CCamera::GetCamera
//	����:	�Ȃ�
//	�߂�l:	m_Camera
//	����:	�J�����f�[�^�̎擾
//------------------------------------------------------------------------------
CCamera_Data *CCamera::GetCameraData(void)
{
	return &m_CameraData;
}
//
////------------------------------------------------------------------------------
////	�֐���:	void CCamera::Move
////	����:	CKeyboard *keyboard
////			int UP_KEY					int DOWN_KEY
////			int LEFT_KEY				int RIGHT_KEY
////			int VIEW_LTURNING_KEY		int VIEW_RTURNING_KEY
////			int LOOKAT_LTURNING_KEY		int LOOKAT_RTURNING_KEY
////	�߂�l:	�Ȃ�
////	����:	�J�����̑���
////------------------------------------------------------------------------------
//void CCamera::Move(CKeyboard *keyboard, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY, int VIEW_LTURNING_KEY, int VIEW_RTURNING_KEY, int LOOKAT_LTURNING_KEY, int LOOKAT_RTURNING_KEY)
//{
//	//  ���_����
//	if (keyboard->GetPress(VIEW_LTURNING_KEY))			m_Camera.rot.y -= D3DX_PI * 0.01f;		//  ������
//	else if (keyboard->GetPress(VIEW_RTURNING_KEY))		m_Camera.rot.y += D3DX_PI * 0.01f;		//  �E����
//

//	m_Camera.bLookAt = false;
//	//  �����_����
//	if (keyboard->GetPress(LOOKAT_LTURNING_KEY))
//	{//  ������
//		m_Camera.rot.y += D3DX_PI * 0.01f;
//
//		//  ���񒆐S�𒍎��_�ɐݒ�
//		m_Camera.bLookAt = true;
//	}
//	else if (keyboard->GetPress(LOOKAT_RTURNING_KEY))
//	{//  �E����
//		m_Camera.rot.y -= D3DX_PI * 0.01f;
//
//		//  ���񒆐S�𒍎��_�ɐݒ�
//		m_Camera.bLookAt = true;
//	}
//
//	SAFE_ROTCHECK(m_Camera.rot.y);
//
//	if (keyboard->GetPress(UP_KEY))
//	{
//		if (keyboard->GetPress(LEFT_KEY))
//		{//  ����ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(RIGHT_KEY)))
//		{//  �E��ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else
//		{//  �O�ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI) * m_Camera.fMove;
//		}
//	}
//	else if (keyboard->GetPress(DOWN_KEY))
//	{
//		if (keyboard->GetPress(LEFT_KEY))
//		{//  �����ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(RIGHT_KEY)))
//		{//  �E���ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else
//		{//  ��ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y) * m_Camera.fMove;
//		}
//	}
//	else if (keyboard->GetPress(LEFT_KEY))
//	{
//		if (keyboard->GetPress(UP_KEY))
//		{//  ����ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(DOWN_KEY)))
//		{//  �����ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else
//		{//  ���ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.5f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.5f) * m_Camera.fMove;
//		}
//	}
//	else if (keyboard->GetPress(RIGHT_KEY))
//	{
//		if (keyboard->GetPress(UP_KEY))
//		{//  �E��ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(DOWN_KEY)))
//		{//  �E���ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else
//		{//  �E�ړ�
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.5f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.5f) * m_Camera.fMove;
//		}
//	}
//}