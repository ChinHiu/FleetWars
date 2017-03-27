//------------------------------------------------------------------------------
//	�^�C�g���F		�f�o�b�O����
//	�t�@�C�����F	debugProc.cpp
//	�쐬�ҁF		AT13B284 33 CHIN HIU
//	�쐬���F		2015/12/03
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include <stdio.h>
#include <varargs.h>
#include <stdarg.h>
#include "debugProc.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "mouse.h"
#include "player.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CScene::CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CDebugProc::CDebugProc()
{
	m_pFont = NULL;				//  �t�H���g�ւ̃|�C���^
}

//------------------------------------------------------------------------------
//	�֐���:	CScene::~CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CDebugProc::~CDebugProc()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CDebugProc::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CDebugProc::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �f�o�b�O�v���V�[�W���\���p�t�H���g��ݒ�
	D3DXCreateFont
	(
		pDevice,									
		15,
		0,
		FW_NORMAL,
		NULL,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pFont
	);

	//  �[���N���A����
	memset(m_StrDebug, 0, sizeof m_StrDebug);
}

//------------------------------------------------------------------------------
//	�֐���:	void CDebugProc::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CDebugProc::Uninit(void)
{
	//  �f�o�b�O�v���V�[�W���\���p�t�H���g��ݒ�
	SAFE_RELEASE(m_pFont);
}

//------------------------------------------------------------------------------
//	�֐���:	void CDebugProc::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CDebugProc::Update(void)
{
//	CGame *Game = ((CGame*)CManager::GetMode());
//
//	//  �J�������擾
//	CCamera_Data *pCamera = Game->GetCamera()->GetCamera();
///*
//	D3DXVECTOR2 *pUserMap = CGame::GetUserMap()->GetUserMapPos();*/
//
//	/*CEnemy *pEnemy = CGame::GetEnemy();
//	CHamina_Data *pHamina = Game->GetEnemyHamina()->GetHaminaData();
//*/
//
	CCamera_Data *pCamera = CManager::GetCameraData();

	if (pCamera != NULL)
	{
		CPlayer *pPlayer = CManager::GetPlayer();
		//  �v���C���[���擾
		D3DXVECTOR3 *pPlayerPos = pPlayer->GetPosition();
		D3DXVECTOR3 *pPlayerRot = pPlayer->GetRotation();
		CMouse *pMouse = CManager::GetInput()->GetMouse();

		PrintDebugProc("*** �J������� ***\n");
		PrintDebugProc("[ ���_					( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
		PrintDebugProc("[ �����_				( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
		PrintDebugProc("[ ����					( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);
		PrintDebugProc("[ ���_�ƒ����_�̋���	( %.2f )]\n\n", pCamera->fDistance);

		PrintDebugProc("*** �v���C���[��� ***\n");
		PrintDebugProc("[ ���W					( X:%.2f Y:%.2f Z:%.2f )]\n", pPlayerPos->x, pPlayerPos->y, pPlayerPos->z);
		PrintDebugProc("[ ����					( X:%.2f Y:%.2f Z:%.2f )]\n\n", pPlayerRot->x, pPlayerRot->y, pPlayerRot->z);

		PrintDebugProc("*** �}�E�X��� ***\n");
		PrintDebugProc("[ IX:%d IY:%d IZ:%d ]\n", pMouse->GetMouseState()->lX, pMouse->GetMouseState()->lY, pMouse->GetMouseState()->lZ);
		PrintDebugProc("[ ��ʂ̈ʒu			(x:%d y:%d ) ]\n", pMouse->GetMousePoint()->x, pMouse->GetMousePoint()->y);
		PrintDebugProc("[ ���[���h���W			(x:%.2f y:%.2f z:%.2f ) ]\n", pMouse->GetWorldPos()->x, pMouse->GetWorldPos()->y, pMouse->GetWorldPos()->z);
	}
//		/*PrintDebugProc("*** HAMINA�C���]��� ***\n");
//		for (int i = 0; i < HAMINA_MAX; i++) {
//			if ((pHamina + i)->Flag) {
//				PrintDebugProc("[ �C�����        ( X:%.2f Y:%.2f Z:%.2f )]\n", (pHamina + i)->BatteryRot.x, (pHamina + i)->BatteryRot.y, (pHamina + i)->BatteryRot.z);
//			}
//		}
//		PrintDebugProc("*** �v���C���[ID��� ***\n");
//		PrintDebugProc("[ 1[%d] 2[%d] 3[%d] 4[%d] ]\n", pPlayer->GetLockShipID(0), pPlayer->GetLockShipID(1), pPlayer->GetLockShipID(2), pPlayer->GetLockShipID(3));*/
//	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CDebugProc::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CDebugProc::Draw(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	RECT rect = { 0, 0, (int)pScreenSize->x, (int)pScreenSize->y };

	//  �e�L�X�g�`��
	m_pFont->DrawText(NULL, &m_StrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(250, 0, 50, 255));

	//  �[���N���A����
	memset(m_StrDebug, 0, sizeof m_StrDebug);
}

//------------------------------------------------------------------------------
//	�֐���:	void CDebugProc::PrintDebugProc
//	����:	char *fmt, ...
//	�߂�l:	�Ȃ�
//	����:	�f�o�b�O�v���V�[�W���p�UPrintf
//------------------------------------------------------------------------------
void CDebugProc::PrintDebugProc(char *fmt, ...)
{
	int len;

	//  �������`�F�b�N
	len = strlen(m_StrDebug);

	va_list	list;
	va_start(list, fmt);
	vsprintf(&m_StrDebug[len], fmt, list);
	va_end(list);
}
