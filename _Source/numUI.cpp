//------------------------------------------------------------------------------
//	�^�C�g���F		�����nUI�̊֐�
//	�t�@�C�����F	numUI.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/01/08
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "game.h"
#include "tutorial.h"
#include "manager.h"
#include <typeinfo.h>
#include "numUI.h"
#include "number.h"
#include "player.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CNumUI::CNumUI
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CNumUI::CNumUI()
{
	m_MissileNum = NULL;
	m_MissileRepairTime = NULL;
	m_MissileFlag = NULL;
	m_JammingNum = NULL;
	m_JammingBulletTime = NULL;
	m_JammingFlag = NULL;
	m_RepairNum = NULL;
	m_Time = NULL;
	m_SpeedRate = NULL;
}

//------------------------------------------------------------------------------
//	�֐���:	CNumUI::~CNumUI
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CNumUI::~CNumUI()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CNumUI *CNumUI::Create
//	����:	�Ȃ�
//	�߂�l:	pNumUI
//	����:	�����nUI�̐���
//------------------------------------------------------------------------------
CNumUI *CNumUI::Create(void)
{
	CNumUI		*pNumUI;
	pNumUI = new CNumUI;
	pNumUI->Init();
	return pNumUI;
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumUI::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CNumUI::Init(void)
{
	CMode *pMode = CManager::GetMode();

	if ((typeid(*pMode).name() == typeid(CTutorial).name()) || (typeid(*pMode).name() == typeid(CGame).name()))
	{
		CPlayer *pPlayer = CManager::GetPlayer();

		//  ��ʃT�C�Y���擾
		D3DXVECTOR2 *pScreenSize = GetScreenSize();

		//  ��ʊ������擾
		float *pScreenRate = GetScreenRate();

		m_MissileFlag = &pPlayer->GetWeaponData(WEAPON_MISSILE)->bFlag;

		if ((typeid(*pMode).name() == typeid(CGame).name()))
		{
			CGame *pGame = ((CGame*)CManager::GetMode());
			m_Time = CNumber::Create(
				pGame->GetTime(),
				NULL,
				D3DXVECTOR3(pScreenSize->x - 205.0f * *pScreenRate, 55.0f * *pScreenRate, 0.0f),
				D3DXVECTOR3(40.0f * *pScreenRate, 60.0f * *pScreenRate, 0.0f),
				D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
				NUMBER_TYPE_TIME,
				true
			);
		}

		m_MissileRepairTime = CNumber::Create(
			&pPlayer->GetWeaponData(WEAPON_MISSILE)->nCoolDown,
			NULL,
			D3DXVECTOR3(111.84f * *pScreenRate, pScreenSize->y - 150.0f * *pScreenRate, 0.0f),
			D3DXVECTOR3(20.0f * *pScreenRate, 30.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			NUMBER_TYPE_TIME,
			true
		);

		m_MissileNum = CNumber::Create(
			&pPlayer->GetWeaponData(WEAPON_MISSILE)->nNum,
			1,
			D3DXVECTOR3(144.84f * *pScreenRate, pScreenSize->y - 150.0f * *pScreenRate, 0.0f),
			D3DXVECTOR3(24.0f * *pScreenRate, 36.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			NUMBER_TYPE_VALUE,
			true
		);

		m_RepairNum = CNumber::Create(
			&pPlayer->GetWeaponData(WEAPON_REPAIR)->nNum,
			1,
			D3DXVECTOR3(144.84f * *pScreenRate, pScreenSize->y - 65.0f * *pScreenRate, 0.0f),
			D3DXVECTOR3(24.0f * *pScreenRate, 36.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			NUMBER_TYPE_VALUE,
			true
		);

		m_PowerRate = CNumber::Create(
			pPlayer->GetPowerNum(),
			NULL,
			D3DXVECTOR3(167.5f * *pScreenRate, 103.0f * *pScreenRate, 0.0f),
			D3DXVECTOR3(20.0f * *pScreenRate, 30.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f),
			NUMBER_TYPE_POWER,
			true
		);

		m_SpeedRate = CNumber::Create(
			pPlayer->GetSpeedNum(),
			NULL,
			D3DXVECTOR3(157.5f * *pScreenRate, 135.5f * *pScreenRate, 0.0f),
			D3DXVECTOR3(20.0f * *pScreenRate, 30.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f),
			NUMBER_TYPE_SPEED,
			true
		);
	}

	if ((typeid(*pMode).name() == typeid(CResult).name()))
	{
		//  ��ʃT�C�Y���擾
		D3DXVECTOR2 *pScreenSize = GetScreenSize();

		//  ��ʊ������擾
		float *pScreenRate = GetScreenRate();

		CNumber::Create(
			CManager::GetKillsNum(),
			*CManager::GetKillsNum() > 9 ? 2 : 1,
			D3DXVECTOR3(750.0f * *pScreenRate, 359.5f * *pScreenRate, 0.0f),
			D3DXVECTOR3(40.0f * *pScreenRate, 60.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(0.94f, 0.74f, 0.17f, 1.0f),
			NUMBER_TYPE_VALUE,
			true
		);

		if (!*CManager::GetMissionResult())
		{
			CNumber::Create(
				CManager::GetClearTime(),
				NULL,
				D3DXVECTOR3(750.0f * *pScreenRate, 538.0f * *pScreenRate, 0.0f),
				D3DXVECTOR3(40.0f * *pScreenRate, 60.0f * *pScreenRate, 0.0f),
				D3DXCOLOR(0.94f, 0.74f, 0.17f, 1.0f),
				NUMBER_TYPE_TIME,
				true
			);
		}

		CNumber::Create(
			CManager::GetPlayerDamage(),
			NULL,
			D3DXVECTOR3(750.0f * *pScreenRate, 716.5f * *pScreenRate, 0.0f),
			D3DXVECTOR3(40.0f * *pScreenRate, 60.0f * *pScreenRate, 0.0f),
			D3DXCOLOR(0.94f, 0.74f, 0.17f, 1.0f),
			NUMBER_TYPE_DAMAGE,
			true
		);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumUI::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CNumUI::Uninit(void)
{
	m_MissileNum = NULL;
	m_MissileRepairTime = NULL;
	m_MissileFlag = NULL;
	m_JammingNum = NULL;
	m_JammingBulletTime = NULL;
	m_JammingFlag = NULL;
	m_RepairNum = NULL;
	m_Time = NULL;
	m_SpeedRate = NULL;
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumUI::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CNumUI::Update(void)
{
	/*CMode *pMode = CManager::GetMode();*/

	//  �Q�[�����[�h�̍X�V����
	/*if (typeid(*pMode).name() == typeid(CGame).name())
	{*/
		if (*m_MissileFlag) {
			m_MissileNum->SetNumberFlag(true);
			m_MissileRepairTime->SetNumberFlag(false);
		}
		else{
			m_MissileNum->SetNumberFlag(false);
			m_MissileRepairTime->SetNumberFlag(true);
		}
	/*}*/
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumUI::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CNumUI::Draw(void)
{
}