//------------------------------------------------------------------------------
//	�^�C�g���F		�v���C���[�̊֐�
//	�t�@�C�����F	player.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/12/13
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "model.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include <typeinfo.h>
#include "meshField.h"
#include "title.h"
#include "tutorial.h"
#include "stencilShadow.h"
#include "ObbTest.h"
#include "UI.h"
#include "bullet.h"
#include "openAL.h"
#include "Func.h"
#include "enemy.h"
#include "missile.h"
#include "sprayBehide.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define POSY_ADJUST (18.0f)
#define SPEED_MAX	(40)

#define MISSILE_REPAIR_TIME (12)
#define BULLET_SHOT_COUNT (20)

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//  �eObb���Έʒu
const D3DXVECTOR3 g_ObbRelativePos[] =
{
	D3DXVECTOR3(0.0f, -23.0f, 0.0f),
	D3DXVECTOR3(0.0f, 12.0f, 38.0f),
	D3DXVECTOR3(0.0f, 44.0f, -26.0f),
	D3DXVECTOR3(0.0f, 28.0f, 170.0f)
};

//  �eObb�O���̒���
const D3DXVECTOR3 g_ObbLength[] =
{
	D3DXVECTOR3(36.0f, 25.0f, 235.0f),
	D3DXVECTOR3(36.0f, 10.0f, 120.0f),
	D3DXVECTOR3(16.0f, 22.0f, 16.0f),
	D3DXVECTOR3(12.0f, 28.0f, 12.0f)
};

//  �~�T�C���̕Έڗ�
const D3DXVECTOR3 g_MissileDeviationPos[] =
{
	D3DXVECTOR3(5.5f, 34.0f, 164.2f),
	D3DXVECTOR3(-5.5f, 34.0f, 164.2f),
	D3DXVECTOR3(5.5f, 34.0f, 176.0f),
	D3DXVECTOR3(-5.5f, 34.0f, 176.0f)
};

//  ���򖗁i�O�j�̕ψʗ�
const D3DXVECTOR3 g_SprayBeforeDeviationPos[] =
{
	D3DXVECTOR3(-2.0f, -40.0f, -192.0f),
	D3DXVECTOR3(2.0f, -40.0f, -192.0f)
};

//  ���򖗁i�O�j�̃T�C�Y
const D3DXVECTOR3 g_SprayBeforeSize = D3DXVECTOR3(150.0f, 50.0f, 0.0f);

//  ���򖗁i���j�̕ψʗ�
const D3DXVECTOR3 g_SprayBehideDeviationPos = D3DXVECTOR3(0.0f, -30.0f, 170.0f);

//  ���򖗁i���j�̃T�C�Y
const D3DXVECTOR3 g_SprayBehideSize = D3DXVECTOR3(100.0f, 0.0f, 300.0f);

//------------------------------------------------------------------------------
//	�֐���:	CPlayer::CPlayer
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CPlayer::CPlayer(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		m_Model[i] = NULL;
	}

	m_Weapon = WEAPON_NONE;
	m_WeaponID = WEAPON_NONE;	
	m_PowerNum =
	m_SpeedNum =
	m_BulletCnt =
	m_MissileCnt = 0;
	m_OverHitRate = 0.0f;
	m_bFire = false;
	m_BatteryRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCollision = false;
	m_HeatCol = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	m_bMoveFlag =
	m_bRotFlag =
	m_WeaponFlag = false;
}

//------------------------------------------------------------------------------
//	�֐���:	CPlayer::~CPlayer
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�f�X�g���N�^
//------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CPlayer *CPlayer::Create
//	����:	MODEL_TYPE	Model_Type
//			D3DXVECTOR3 pos
//			D3DXVECTOR3 rot
//	�߂�l:	pPlayer
//	����:	�v���C���[�̐���
//------------------------------------------------------------------------------
CPlayer *CPlayer::Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer	*pPlayer;
	pPlayer = new CPlayer();

	pPlayer->m_CharData.Pos = pos;
	pPlayer->m_CharData.Rot = rot;
	pPlayer->m_Type = Model_Type;
	pPlayer->m_CharData.bFlag = true;
	pPlayer->Init();
	return pPlayer;
}

//------------------------------------------------------------------------------
//	�֐���:	void CSceneX::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CPlayer::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();
	CMode	*pMode	= CManager::GetMode();
	CUI		*pUI	= CManager::GetUI();

	//  ���f���̐ݒ�
	m_Model[PLAYER_BODY] = CModel::Create(
		m_Type,
		MODEL_PARTS_GORSHKOV_BODY,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	m_Model[PLAYER_BATTERY] = CModel::Create(
		m_Type,
		MODEL_PARTS_GORSHKOV_BATTERY,
		D3DXVECTOR3(0.0f, 60.5f, -26.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	m_Model[PLAYER_GUN] = CModel::Create(
		m_Type,
		MODEL_PARTS_GORSHKOV_GUN,
		D3DXVECTOR3(0.0f, 3.5f, -3.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	//  ���f���e�̐ݒ�
	m_Model[PLAYER_BODY]->SetParent(NULL);
	m_Model[PLAYER_BATTERY]->SetParent(m_Model[PLAYER_BODY]);
	m_Model[PLAYER_GUN]->SetParent(m_Model[PLAYER_BATTERY]);

	//  �^�C�g�����[�h�̏���������
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		//  �V���h�E��ݒ�
		m_Shadow = CStencilShadow::Create(m_Type, D3DXVECTOR3(173.0f, -30.0f, 100.0f) );

		//  �}�g���N�X�̍X�V
		MatrixUpdate();

		//  �~�T�C����ݒ�
		for (int i = 0; i < nMissileMax_P; i++)
		{
			m_MissileID[i] = CManager::GetMissile()->Reset(&m_Matrix.World, USER_PLAYER, &m_CharData.Pos, &m_CharData.Rot, &m_CharData.bFlag, g_MissileDeviationPos[i]);
		}
	}

	//  �^�C�g�����[�h�ȊO�̏����������i�`���[�g���A���A�Q�[���j
	else
	{
		D3DXVECTOR3	ObbPos;

		if (typeid(*pMode).name() == typeid(CGame).name())
		{
			m_bMoveFlag =
			m_bRotFlag =
			m_WeaponFlag = true;
		}

		//  ����f�[�^��������
		m_WeaponData[WEAPON_BULLET].nNum = 0;
		m_WeaponData[WEAPON_BULLET].fCoolDown = 0.0f;
		m_WeaponData[WEAPON_BULLET].bFlag = true;

		m_WeaponData[WEAPON_MISSILE].nNum = 4;
		m_WeaponData[WEAPON_MISSILE].nCoolDown = MISSILE_REPAIR_TIME;
		m_WeaponData[WEAPON_MISSILE].bFlag = true;

		m_WeaponData[WEAPON_REPAIR].nNum = 1;
		m_WeaponData[WEAPON_REPAIR].nCoolDown = 0;
		m_WeaponData[WEAPON_REPAIR].bFlag = true;

		//  �}�g���N�X�̍X�V
		MatrixUpdate();

		//  �~�T�C����ݒ�
		for (int i = 0; i < nMissileMax_P; i++)
		{
			m_MissileID[i] = CManager::GetMissile()->Reset(&m_Matrix.World, USER_PLAYER, &m_CharData.Pos, &m_CharData.Rot, &m_CharData.bFlag, g_MissileDeviationPos[i]);
		}

		//  Obb�̐ݒ�
		for (int i = 0; i < nObbMax_P; i++)
		{
			D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[i], &m_Matrix.World);							//  Obb�ʒu���Z�o
			m_Obb[i].SetPos(ObbPos);																		//  Obb�ʒu��ݒ�
			m_Obb[i].SetLength(g_ObbLength[i]);																//  Obb�e��������ݒ�
			m_Obb[i].SetDirect(X_AXIS, D3DXVECTOR3(m_Matrix.Rot._11, m_Matrix.Rot._12, m_Matrix.Rot._13));	//  Obb��X�������x�N�g����ݒ�
			m_Obb[i].SetDirect(Y_AXIS, D3DXVECTOR3(m_Matrix.Rot._21, m_Matrix.Rot._22, m_Matrix.Rot._23));	//  Obb��Y�������x�N�g����ݒ�
			m_Obb[i].SetDirect(Z_AXIS, D3DXVECTOR3(m_Matrix.Rot._31, m_Matrix.Rot._32, m_Matrix.Rot._33));	//  Obb��Z�������x�N�g����ݒ�
			m_ObbTest[i] = CObbTest::Create(m_Obb[i].GetPos(), m_CharData.Rot, g_ObbLength[i]);				//  Obb�e�X�g�����̂̐ݒ�
		}

		//  �V���h�E��ݒ�
		m_Shadow = CStencilShadow::Create(m_Type, m_CharData.Pos);

		//  ���򖗂̐ݒ�i�O�j
		m_SprayBefore = CSpray::Create();

		for (int i = 0; i < SPRAY_TYPE_MAX; i++)
		{
			//  �����Ԃ�
			m_SprayBefore->Set(
				MODEL_GORSHKOV,
				&m_SprayBeforePos[i],
				&m_CharData.Rot,
				&m_SprayBeforeSize,
				(SPRAY_TYPE)i,
				true
			);
		}

		//  ���򖗂̐ݒ�i���j
		CManager::GetSprayBehide()->Set(
			&m_SprayBehidePos,
			&m_CharData.Rot,
			&m_SprayBehideSize,
			true
		);

		m_PowerNum = 50;
		m_SpeedNum = 2500;
		m_OldLife = 
		m_CharData.nLife = 100;


		//  UI�̐ݒ�
		//  ����}�[�N��ݒ�
		for (int i = UI_WEAPON_GATLING, j = 0; i <= UI_WEAPON_REPAIR; i++, j++)
		{
			m_WeaponMarkID[j] = pUI->Set(
				(UI_LABLE)i,
				UI_TYPE_NONE,
				D3DXVECTOR2(65.0f * *pScreenRate, pScreenSize->y - 85.0f * *pScreenRate * (UI_WEAPON_REPAIR - i) - 65.0f * *pScreenRate),
				D3DXVECTOR2(80.0f * *pScreenRate, 80.0f * *pScreenRate),
				D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f)
			);
		}

		//  HP�g
		pUI->Set(
			UI_LIFE_FRAME,
			UI_TYPE_NONE,
			D3DXVECTOR2((25.0f + 460.0f * 0.5f) * *pScreenRate, 50.0f * *pScreenRate),
			D3DXVECTOR2(460.0f * *pScreenRate, 50.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		//  HP
		m_LifeMarkID = pUI->Set(
			UI_LIFE,
			UI_WIDTH_SCROLL,
			D3DXVECTOR2(112.0f * *pScreenRate, 50.0f * *pScreenRate),
			D3DXVECTOR2(358.0f * *pScreenRate, 28.5f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		pUI->SetTexRate(m_LifeMarkID, 1.0f);

		//  �X�R�[�v
		m_ScopeMarkID = pUI->Set(
			UI_SCOPE,
			UI_TYPE_NONE,
			D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
			D3DXVECTOR2(1920.0f * *pScreenRate, 1080.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		//  ��͖C�M���
		m_HeatMarkID = pUI->Set(
			UI_HEAT,
			UI_HEIGHT_SCROLL,
			D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
			D3DXVECTOR2(450.0f * *pScreenRate, 441.6f * *pScreenRate),
			m_HeatCol
		);

		//  �ߔM�}�[�N
		m_OverHeatMarkID = pUI->Set(
			UI_OVERHEAT,
			UI_TYPE_NONE,
			D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
			D3DXVECTOR2(200.0f * *pScreenRate, 109.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
		);

		//  �����}�[�N
		pUI->Set(
			UI_INFINITY,
			UI_TYPE_NONE,
			D3DXVECTOR2(156.84f * *pScreenRate, pScreenSize->y - 85.0f * *pScreenRate * 2 - 65.0f * *pScreenRate),
			D3DXVECTOR2(73.68f * *pScreenRate, 40.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		//  �p���[�}�[�N
		pUI->Set(
			UI_POWER_MARK,
			UI_TYPE_NONE,
			D3DXVECTOR2(75.0f * *pScreenRate, 103.0f * *pScreenRate),
			D3DXVECTOR2(100 * *pScreenRate, 30 * *pScreenRate),
			D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f)
		);

		//  �X�s�[�h�}�[�N
		pUI->Set(
			UI_SPEED_MARK,
			UI_TYPE_NONE,
			D3DXVECTOR2(75.0f * *pScreenRate, 135.5f * *pScreenRate),
			D3DXVECTOR2(100 * *pScreenRate, 30 * *pScreenRate),
			D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f)
		);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	CMode *pMode = CManager::GetMode();

	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		m_Model[i]->Uninit();
	}

	m_Shadow->Uninit();
	m_Shadow = NULL;

	for (int i = 0; i < nObbMax_P; i++)
	{
		m_ObbTest[i] = NULL;
	}

	//	�^�C�g���ȊO
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		m_SprayBefore->Uninit();
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	CMode			*pMode			= CManager::GetMode();
	CKeyboard		*pKeyboard		= CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse			= CManager::GetInput()->GetMouse();
	CCamera_Data	*pCameraData	= CManager::GetCameraData();
	CMeshField		*pSea			= CManager::GetSea();
	CUI				*pUI			= CManager::GetUI();
	CMissile		*pMissile		= CManager::GetMissile();

//  �^�C�g���̍X�V
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		m_CharData.Pos.y = pSea->GetHeight(m_CharData.Pos) - 10.0f;

		MatrixUpdate();
	}
	else
	{
		if (typeid(*pMode).name() == typeid(CTutorial).name())
		{
			CTutorial	*pTutorial = ((CTutorial*)CManager::GetMode());
		}

		CHamina_Data *pHaminaData = CManager::GetHamina()->GetHaminaData();
		D3DXVECTOR3	ObbPos;

		if (m_WeaponFlag)
		{
			//  ���폈��
					//  ���폸���I��
			if (pKeyboard->GetTrigger(DIK_Q))
			{
				m_WeaponID--;
				m_WeaponID = m_WeaponID <= WEAPON_NONE - 1 ? WEAPON_REPAIR : m_WeaponID;
			}
			//  ����~���I��
			else if (pKeyboard->GetTrigger(DIK_E))
			{
				m_WeaponID++;
				m_WeaponID = m_WeaponID >= WEAPON_REPAIR + 1 ? WEAPON_NONE : m_WeaponID;
			}

			//  ���풼�ڑI��
			if (pKeyboard->GetTrigger(DIK_1)) m_WeaponID = WEAPON_BULLET;
			if (pKeyboard->GetTrigger(DIK_2)) m_WeaponID = WEAPON_MISSILE;
			if (pKeyboard->GetTrigger(DIK_3)) m_WeaponID = WEAPON_REPAIR;

		}

		//  �I�����������ݒ�
		m_Weapon = (WEAPON_TYPE)m_WeaponID;

		//  �I����������}�[�N�̐F��ݒ�
		for (int i = 0; i < WEAPON_TYPE_MAX; i++)
		{
			if (m_Weapon == i)	pUI->SetColor(m_WeaponMarkID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			else				pUI->SetColor(m_WeaponMarkID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.5f);
		}

		//  ��͖C��coolDown�^�C�����J�E���g�i�ߔM��ԁj
		if (!m_WeaponData[WEAPON_BULLET].bFlag)
		{
			m_WeaponData[WEAPON_BULLET].fCoolDown -= 0.005f;

			//  CD���I���΁A���ˉ\
			if (m_WeaponData[WEAPON_BULLET].fCoolDown <= 0.0f)
			{
				m_WeaponData[WEAPON_BULLET].bFlag = TRUE;
				m_WeaponData[WEAPON_BULLET].fCoolDown = 0.0f;
			}
		}
		else
		{	//  �A�˂ł͂Ȃ���΁A��������
			if (!m_bFire)
			{
				if (m_WeaponData[WEAPON_BULLET].fCoolDown > 0.0f)
				{
					m_WeaponData[WEAPON_BULLET].fCoolDown -= 0.0075f;

					//  CD���Ԃ̃`�F�b�N
					m_WeaponData[WEAPON_BULLET].fCoolDown = m_WeaponData[WEAPON_BULLET].fCoolDown <= 0.0f ? 0.0f : m_WeaponData[WEAPON_BULLET].fCoolDown;
				}
			}

			m_bFire = false;
		}

		//  �~�T�C���N�[���_�E��
		if (!m_WeaponData[WEAPON_MISSILE].bFlag)
		{
			//  �~�T�C��CoolDown�^�C���͕b�P�ʂŌv�Z
			m_MissileCnt--;

			if (m_MissileCnt <= 0)
			{
				m_WeaponData[WEAPON_MISSILE].nCoolDown--;
				m_MissileCnt = 60;
			}

			if (m_WeaponData[WEAPON_MISSILE].nCoolDown <= 0)
			{
				for (int i = 0; i < nMissileMax_P; i++)
				{
					//  �~�T�C�����Z�b�g
					m_MissileID[i] = pMissile->Reset(&m_Matrix.World, USER_PLAYER, &m_CharData.Pos, &m_CharData.Rot, &m_CharData.bFlag, g_MissileDeviationPos[i]);
				}
				m_WeaponData[WEAPON_MISSILE].bFlag = true;
				m_WeaponData[WEAPON_MISSILE].nCoolDown = MISSILE_REPAIR_TIME;
				m_WeaponData[WEAPON_MISSILE].nNum = nMissileMax_P;
			}
		}

		switch (m_Weapon)
		{
		case WEAPON_BULLET:		//  ��͖C
			WeaponBulletUpdate();

			if (typeid(*pMode).name() == typeid(CTutorial).name())
			{
				CTutorial	*pTutorial = ((CTutorial*)CManager::GetMode());

				if (*pTutorial->GetTutorialState() == TUTORIAL_7)
				{
					if(m_bFire)	pTutorial->AppTutorialPoint(15);
				}
			}
			break;
		case WEAPON_MISSILE:	//  �~�T�C��
			if (typeid(*pMode).name() == typeid(CGame).name())
			{
				WeaponMissileUpdate();
			}
			break;
		case WEAPON_REPAIR:		//  �ً}�C��
			if (typeid(*pMode).name() == typeid(CGame).name())
			{
				WeaponRepairUpdate();
			}
			break;
		default:
			break;
		}

		if (m_Weapon == WEAPON_BULLET)
		{
			CManager::GetUI()->SetFlag(m_ScopeMarkID, true);
			//  �ߔM�}�[�N
			CManager::GetUI()->SetFlag(m_OverHeatMarkID, !m_WeaponData[m_Weapon].bFlag);

			//  �M
			CManager::GetUI()->SetFlag(m_HeatMarkID, true);
			m_HeatCol.g = 1.0f - m_WeaponData[WEAPON_BULLET].fCoolDown;
			CManager::GetUI()->SetColor(m_HeatMarkID, m_HeatCol);
			CManager::GetUI()->SetTexRate(m_HeatMarkID, m_WeaponData[WEAPON_BULLET].fCoolDown);
		}
		else
		{
			CManager::GetUI()->SetFlag(m_ScopeMarkID, false);
			CManager::GetUI()->SetFlag(m_OverHeatMarkID, false);
			CManager::GetUI()->SetFlag(m_HeatMarkID, false);
		}

		if (m_OldLife > m_CharData.nLife) m_OldLife--;
		if (m_OldLife < m_CharData.nLife) m_OldLife++;

		m_fLifeRate = (float)(m_OldLife / 100.0f);

		pUI->SetTexRate(m_LifeMarkID, m_fLifeRate);

//  ���폈���͂����܂�

//  ��]����
		//  �C��͏�ɃJ�����Ɠ�������
		m_BatteryRot.y = pCameraData->rot.y - D3DX_PI;

		//  �C��̌����`�F�b�N
		SAFE_ROTCHECK(m_BatteryRot.y);

		//  �C��̌������X�V
		m_Model[PLAYER_BATTERY]->SetRot(m_BatteryRot);

		if (m_bRotFlag)
		{
			if (pKeyboard->GetPress(DIK_A))			m_CharData.Rot.y -= 0.005f;
			else if (pKeyboard->GetPress(DIK_D))	m_CharData.Rot.y += 0.005f;

			SAFE_ROTCHECK(m_CharData.Rot.y);

			if (typeid(*pMode).name() == typeid(CTutorial).name())
			{
				CTutorial	*pTutorial = ((CTutorial*)CManager::GetMode());

				if (*pTutorial->GetTutorialState() == TUTORIAL_4)
				{
					if (pKeyboard->GetPress(DIK_A) || pKeyboard->GetPress(DIK_D))	pTutorial->AppTutorialPoint(1);
				}
			}
		}
//  ��]�����͂����܂�

//  �ړ�����
		if (m_bMoveFlag)
		{
			//  �G���W���p���[�̉����A���������
			if (pKeyboard->GetPress(DIK_W))			m_PowerNum += 1;
			else if (pKeyboard->GetPress(DIK_S))	m_PowerNum -= 1;

			//  �p���[�l�̃`�F�b�N
			if (m_PowerNum > 100)					m_PowerNum = 100;
			else if (m_PowerNum < 0)				m_PowerNum = 0;
		}
		//  �ڕW�X�s�[�h�i���o�[���Z�o�iSpeed�̐�{�j
		m_AimSpeedNum = SPEED_MAX * m_PowerNum;

		//  ���݃X�s�[�h�i���o�[���X�V�iSpeed�̐�{�j
		if (m_SpeedNum > m_AimSpeedNum)			m_SpeedNum -= 4;
		else if (m_SpeedNum < m_AimSpeedNum)	m_SpeedNum += 3;

		//  �X�s�[�h���Z�o
		m_CharData.fSpeed = (float)m_SpeedNum * 0.001f;

		//  �ʒu�X�V
		m_CharData.Pos.x -= m_Obb[0].GetDirect(2).x * m_CharData.fSpeed;
		m_CharData.Pos.z -= m_Obb[0].GetDirect(2).z * m_CharData.fSpeed;
		m_CharData.Pos.y = pSea->GetHeight(m_CharData.Pos) + 20.0f;

//  �ړ������͂����܂�

		if (typeid(*pMode).name() == typeid(CGame).name())
		{
			//  �����蔻��
			m_bCollision = false;

			for (int i = 0; i < nHamina_Max; i++, pHaminaData++)
			{
				if (pHaminaData->CharData.bFlag)
				{
					if (pHaminaData->fDistance > 0.0f && pHaminaData->fDistance < 700.0f)
					{
						m_bCollision = CManager::GetFunc()->OBBs(pHaminaData->Obb[0], m_Obb[0]);
						break;
					}
				}
			}

			if (m_bCollision)
			{
				m_CharData.Pos.x = m_CharData.OldPos.x;
				m_CharData.Pos.z = m_CharData.OldPos.z;
				m_CharData.Rot = m_CharData.OldRot;
				m_SpeedNum -= m_SpeedNum <= 0 ? 0 : 5;
			}
		}

		//  ���򖗁i�O�j�̍X�V
		for (int i = 0; i < SPRAY_TYPE_MAX; i++)
		{
			D3DXVec3TransformCoord(&m_SprayBeforePos[i], &g_SprayBeforeDeviationPos[i], &m_Matrix.World);
			m_SprayBeforePos[i].y = pSea->GetHeight(m_SprayBeforePos[i]) - 20.0f;
		}
		m_SprayBeforeSize = g_SprayBeforeSize * (m_CharData.fSpeed / 4.0f);
		m_SprayBefore->Update();

		//  ���򖗁i���j�̍X�V
		D3DXVec3TransformCoord(&m_SprayBehidePos, &g_SprayBehideDeviationPos, &m_Matrix.World);
		m_SprayBehideSize = g_SprayBehideSize * (m_CharData.fSpeed / 4.0f);

		//  �}�g���N�X�̍X�V
		MatrixUpdate();

		//  Obb���̍X�V
		ObbUpdate();

		//  �V���h�E�ʒu�A��]�̍X�V
		m_Shadow->SetRot(m_CharData.Rot);
		m_Shadow->SetPos(m_CharData.Pos);

		//  ���W�Ɖ�]��ۑ�
		m_CharData.OldPos = m_CharData.Pos;
		m_CharData.OldRot = m_CharData.Rot;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	CMode *pMode = CManager::GetMode();

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �V���h�E�̕`��
	m_Shadow->Draw();

	//  ���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//  �p�[�c�̕`��
	if (m_Weapon == WEAPON_BULLET)
	{
		m_Model[PLAYER_BODY]->Draw();
	}
	else
	{
		for (int i = 0; i < PLAYER_PARTS_MAX; i++)
		{
			m_Model[i]->Draw();
		}
	}

	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		//  �D�O�̐��򖗂�`��
		for (int i = 0; i < SPRAY_TYPE_MAX; i++)
		{
			m_SprayBefore->Draw(i);
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::MatrixUpdate
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���[���h�}�g���b�N�X�̍X�V
//------------------------------------------------------------------------------
void CPlayer::MatrixUpdate(void)
{
	//  ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Matrix.World);

	//  �X�P�[���𔽉f
	D3DXMatrixScaling(&m_Matrix.Scl, m_CharData.Scl.x, m_CharData.Scl.y, m_CharData.Scl.z);
	D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl);

	//  ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_Matrix.Rot, m_CharData.Rot.y, m_CharData.Rot.x, m_CharData.Rot.z);
	D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot);

	//  �ʒu�𔽉f
	D3DXMatrixTranslation(&m_Matrix.Trans, m_CharData.Pos.x, m_CharData.Pos.y, m_CharData.Pos.z);
	D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans);
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::ObbUpdate(void)
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	OBB���̍X�V
//------------------------------------------------------------------------------
void CPlayer::ObbUpdate(void)
{
	D3DXVECTOR3 ObbPos;

	for (int i = 0; i < nObbMax_P; i++)
	{
		D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[i], &m_Matrix.World);							//  Obb�ʒu���Z�o
		m_Obb[i].SetPos(ObbPos);																		//  Obb�ʒu��ݒ�
		m_Obb[i].SetDirect(X_AXIS, D3DXVECTOR3(m_Matrix.Rot._11, m_Matrix.Rot._12, m_Matrix.Rot._13));	//  Obb��X�������x�N�g����ݒ�
		m_Obb[i].SetDirect(Y_AXIS, D3DXVECTOR3(m_Matrix.Rot._21, m_Matrix.Rot._22, m_Matrix.Rot._23));	//  Obb��Y�������x�N�g����ݒ�
		m_Obb[i].SetDirect(Z_AXIS, D3DXVECTOR3(m_Matrix.Rot._31, m_Matrix.Rot._32, m_Matrix.Rot._33));	//  Obb��Z�������x�N�g����ݒ�
		m_ObbTest[i]->SetPos(m_Obb[i].GetPos());														//  Obb�e�X�g�����̂̈ʒu��ݒ�
		m_ObbTest[i]->SetRot(m_CharData.Rot);															//  Obb�e�X�g�����̂̉�]��ݒ�
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::WeaponBulletUpdate(void)
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	��͖C�̍X�V
//------------------------------------------------------------------------------
void CPlayer::WeaponBulletUpdate(void)
{
	CKeyboard		*pKeyboard = CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse = CManager::GetInput()->GetMouse();
	CBullet			*pBullet = CManager::GetBullet();
	CCamera_Data	*pCameraData = CManager::GetCameraData();

	if (m_WeaponData[m_Weapon].bFlag)
	{
		//  ��͖C���ˏ���
		if (pMouse->GetPress(DIM_LEFT))
		{
			m_BulletCnt--;

			if (m_BulletCnt <= 0)
			{
				//  �e�̐ݒ�
				pBullet->Set(
					USER_PLAYER,
					pCameraData->posV,
					*pMouse->GetWorldPos()
				);

				//  �����̐ݒ�
				CManager::GetOpenAL()->Play(SOUND_LABEL_SE_CANNON, 1.0f, m_CharData.Pos.x, m_CharData.Pos.y, m_CharData.Pos.z);

				//  �e���˃J�E���g�����Z�b�g
				m_BulletCnt = BULLET_SHOT_COUNT;
			}

			//  �A�˒�
			m_bFire = true;

			m_WeaponData[m_Weapon].fCoolDown += 0.0015f;

			//  �I�[�o�[�q�b�g����΁A���˕s��
			if (m_WeaponData[m_Weapon].fCoolDown > 1.0f)
			{
				m_WeaponData[m_Weapon].fCoolDown = 1.0f;
				m_WeaponData[m_Weapon].bFlag = FALSE;
			}
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::WeaponMissileUpdate(void)
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�~�T�C���̍X�V
//------------------------------------------------------------------------------
void CPlayer::WeaponMissileUpdate(void)
{
	CKeyboard		*pKeyboard = CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse = CManager::GetInput()->GetMouse();
	CMissile		*pMissile = CManager::GetMissile();
	CHamina_Data	*pHaminaData = CManager::GetHamina()->GetHaminaData();
	CMissile_Data	*pMissileData = CManager::GetMissile()->GetMissileData();

	float			fDistance[nHamina_Max];
	int				nEnemyNum = 0;
	int				nEnemyID[nHamina_Max];

	if (m_WeaponData[m_Weapon].bFlag)
	{
		if (pMouse->GetRelease(DIM_LEFT))
		{
			//  �~�T�C�����ˏ���
			//  �˒��͈͓��̓G��􂢏o��
			for (int i = 0; i < nHamina_Max; i++)
			{
				if ((pHaminaData + i)->CharData.bFlag)
				{
					if ((pHaminaData + i)->AIType != HAMINA_DEAD)
					{
						if ((pHaminaData + i)->fDistance >= 2000.0f && (pHaminaData + i)->fDistance <= 7500.0f)
						{
							fDistance[nEnemyNum] = (pHaminaData + i)->fDistance;
							nEnemyID[nEnemyNum] = i;
							nEnemyNum++;
						}
					}
				}
			}

			if (nEnemyNum > 0)
			{
				//  ��ԉ����G��􂢏o��
				for (int i = 0; i < nEnemyNum - 1; i++)
				{
					if (fDistance[i] > fDistance[i + 1])
					{
						float tmp = fDistance[i + 1];
						int tmpID = nEnemyID[i + 1];

						fDistance[i + 1] = fDistance[i];
						fDistance[i] = tmp;

						nEnemyID[i + 1] = nEnemyID[i];
						nEnemyID[i] = tmpID;
					}
				}

			//  ��ԉ����G�͂����b�N
				pMissile->Set(&(pHaminaData + nEnemyID[nEnemyNum - 1])->CharData.Pos, m_MissileID[4 - m_WeaponData[WEAPON_MISSILE].nNum]);
				(pMissile->GetMissileData() + m_MissileID[4 - m_WeaponData[WEAPON_MISSILE].nNum])->SetLockShipID(nEnemyID[nEnemyNum - 1]);
				CManager::GetOpenAL()->Play(SOUND_LABEL_SE_MISSILE, 1.0f, m_CharData.Pos.x, m_CharData.Pos.y, m_CharData.Pos.z);

				m_WeaponData[m_Weapon].nNum -= 1;
			}

			//  �~�T�C���c�e0�Ȃ�΁A�g�p�s�\
			m_WeaponData[m_Weapon].bFlag = m_WeaponData[m_Weapon].nNum == 0 ? false : true;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CPlayer::WeaponRepairUpdate(void)
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�ً}�C���̍X�V
//------------------------------------------------------------------------------
void CPlayer::WeaponRepairUpdate(void)
{
	CKeyboard		*pKeyboard = CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse = CManager::GetInput()->GetMouse();

	if (m_WeaponData[WEAPON_REPAIR].bFlag)
	{
		if (pMouse->GetTrigger(DIM_LEFT))
		{
			m_WeaponData[WEAPON_REPAIR].nNum--;
			m_WeaponData[WEAPON_REPAIR].bFlag = false;

			//  ���C�t50��
			m_CharData.nLife += 50;
			m_CharData.nLife = m_CharData.nLife > 100 ? 100 : m_CharData.nLife;
		}
	}
}