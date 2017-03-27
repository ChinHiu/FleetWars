//------------------------------------------------------------------------------
//	�^�C�g���F		Hamina�G�̊֐�
//	�t�@�C�����F	enemy_Hamina.cpp
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
#include "enemy.h"
#include "game.h"
#include "manager.h"
#include "title.h"
#include "game.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include <typeinfo.h>
#include "meshField.h"
#include "missile.h"
#include "obbTest.h"
#include "bullet.h"
#include "stencilShadow.h"
#include "effect.h"
#include "openAL.h"
#include "time.h"
#include "Func.h"
#include "userMap.h"
#include "sprayBehide.h"

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------
const float fHamina_PosY_Adjust = 25.0f;
const float fHamina_Speed_Max = 3.0f;

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define POSY_ADJUST (25.0f)
#define SPEED_MAX	(2.5f)
#define HAMINA_BATTERY_ROT_ZONE (0.5f)

#define HAMINA_SHIP_GUN_NUM				(50)
#define HAMINA_MISSILE_NUM				(1)

#define HAMINA_SHIP_GUN_REPAIRTIME		(15)
#define HAMINA_MISSILE_REPAIRTIME		(60)

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------
//  �eObb���Έʒu
const D3DXVECTOR3 g_ObbRelativePos[] =
{
	D3DXVECTOR3(0.0f, -38.0f, 0.0f),
	D3DXVECTOR3(0.0f, -10.0f, 36.0f),
	D3DXVECTOR3(0.0f, 10.0f, 20.0f),
	D3DXVECTOR3(0.0f, 40.0f, 20.0f),
	D3DXVECTOR3(0.0f, 0.0f, 192.0f)
};

//  �eObb�O���̒���
const D3DXVECTOR3 g_ObbLength[] =
{
	D3DXVECTOR3(34.0f, 18.0f, 220.0f),
	D3DXVECTOR3(32.0f, 10.0f, 114.0f),
	D3DXVECTOR3(26.0f, 10.0f, 63.0f),
	D3DXVECTOR3(20.0f, 20.0f, 20.0f),
	D3DXVECTOR3(7.0f, 18.0f, 7.0f)
};

const int nHamina_Life = 30;

//  ���򖗁i�O�j�̕ψʗ�
const D3DXVECTOR3 g_SprayBeforeDeviationPos[] =
{
	D3DXVECTOR3(-4.0f, -40.0f, -210.0f),
	D3DXVECTOR3(4.0f, -40.0f, -210.0f)
};

//  ���򖗁i�O�j�̃T�C�Y
const D3DXVECTOR3 g_SprayBeforeSize = D3DXVECTOR3(150.0f, 50.0f, 0.0f);

//  ���򖗁i���j�̕ψʗ�
const D3DXVECTOR3 g_SprayBehideDeviationPos = D3DXVECTOR3(0.0f, -30.0f, 170.0f);

//  ���򖗁i���j�̃T�C�Y
const D3DXVECTOR3 g_SprayBehideSize = D3DXVECTOR3(100.0f, 0.0f, 300.0f);

//------------------------------------------------------------------------------
//	�֐���:	CEnemy_Hamina::CEnemy_Hamina
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CEnemy_Hamina::CEnemy_Hamina(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_Type = MODEL_HAMINA;
}

//------------------------------------------------------------------------------
//	�֐���:	CEnemy_Hamina::~CEnemy_Hamina
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CEnemy_Hamina::~CEnemy_Hamina()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CEnemy_Hamina *CEnemy_Hamina::Create
//	����:	�Ȃ�
//	�߂�l:	pHamina
//	����:	Hamina�G�̐���
//------------------------------------------------------------------------------
CEnemy_Hamina *CEnemy_Hamina::Create(void)
{
	CEnemy_Hamina *pHamina;
	pHamina = new CEnemy_Hamina;

	pHamina->Init();

	return pHamina;
}

//------------------------------------------------------------------------------
//	�֐���:	void CEnemy_Hamina::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CEnemy_Hamina::Init(void)
{
	CMode *pMode = CManager::GetMode();

	//  �D���S�_����~�T�C���̕Έڗʂ̏�����
	m_MissileDeviationPos = D3DXVECTOR3(0.0f, 6.0f, 192.8f);

	for (int i = 0; i < nHamina_Max; i++)
	{
		m_Hamina[i].Model[HAMINA_BODY] = CModel::Create(
			MODEL_HAMINA,
			MODEL_PARTS_HAMINA_BODY,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		);

		m_Hamina[i].Model[HAMINA_BATTERY] = CModel::Create(
			MODEL_HAMINA,
			MODEL_PARTS_HAMINA_BATTERY,
			D3DXVECTOR3(0.0f, -10.0f, -125.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		);

		m_Hamina[i].Model[HAMINA_GUN] = CModel::Create(
			MODEL_HAMINA,
			MODEL_PARTS_HAMINA_GUN,
			D3DXVECTOR3(0.0f, 3.5f, -3.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		);

		//  ���f���e�̐ݒ�
		m_Hamina[i].Model[HAMINA_BODY]->SetParent(NULL);
		m_Hamina[i].Model[HAMINA_BATTERY]->SetParent(m_Hamina[i].Model[HAMINA_BODY]);
		m_Hamina[i].Model[HAMINA_GUN]->SetParent(m_Hamina[i].Model[HAMINA_BATTERY]);
	}

	//CMissile *pMissile = CManager::GetMissile();

	for (int i = 0; i < nHamina_Max; i++)
	{
		D3DXVECTOR3	ObbPos;

		//  �}�g���N�X�̍X�V
		MatrixUpdate(i);

		//  Obb�̐ݒ�
		for (int j = 0; j < nHamina_Obb_Max; j++)
		{
			D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[j], &m_Hamina[i].Matrix.World);														//  Obb�ʒu���Z�o
			m_Hamina[i].Obb[j].SetPos(ObbPos);																										//  Obb�ʒu��ݒ�
			m_Hamina[i].Obb[j].SetLength(g_ObbLength[j]);																							//  Obb�e��������ݒ�
			m_Hamina[i].Obb[j].SetDirect(X_AXIS, D3DXVECTOR3(m_Hamina[i].Matrix.Rot._11, m_Hamina[i].Matrix.Rot._12, m_Hamina[i].Matrix.Rot._13));	//  Obb��X�������x�N�g����ݒ�
			m_Hamina[i].Obb[j].SetDirect(Y_AXIS, D3DXVECTOR3(m_Hamina[i].Matrix.Rot._21, m_Hamina[i].Matrix.Rot._22, m_Hamina[i].Matrix.Rot._23));	//  Obb��Y�������x�N�g����ݒ�
			m_Hamina[i].Obb[j].SetDirect(Z_AXIS, D3DXVECTOR3(m_Hamina[i].Matrix.Rot._31, m_Hamina[i].Matrix.Rot._32, m_Hamina[i].Matrix.Rot._33));	//  Obb��Z�������x�N�g����ݒ�
			m_Hamina[i].ObbTest[j] = CObbTest::Create(m_Hamina[i].Obb[j].GetPos(), m_Hamina[i].CharData.Rot, g_ObbLength[j]);						//  Obb�e�X�g�����̂̐ݒ�
		}

		//  �V���h�E��ݒ�
		m_Hamina[i].Shadow = CStencilShadow::Create(MODEL_HAMINA, m_Hamina[i].CharData.Pos);

		//  ���򖗂̐ݒ�i�O�j
		m_Hamina[i].SprayBefore = CSpray::Create();

		for (int k = 0; k < SPRAY_TYPE_MAX; k++)
		{
			//  �����Ԃ�
			m_Hamina[i].SprayBefore->Set(
				MODEL_GORSHKOV,
				&m_Hamina[i].SprayBeforePos[k],
				&m_Hamina[i].CharData.Rot,
				&m_Hamina[i].SprayBeforeSize,
				(SPRAY_TYPE)k,
				true
			);
		}

		//  ���򖗂̐ݒ�i���j
		CManager::GetSprayBehide()->Set(
			&m_Hamina[i].SprayBehidePos,
			&m_Hamina[i].CharData.Rot,
			&m_Hamina[i].SprayBehideSize,
			true
		);

		//m_Hamina[i].GunPos.SetDeviation(&m_Hamina[i].Pos, &m_Hamina[i].Rot, D3DXVECTOR3(0.0f, -6.5f, -125.0f));
	}

	m_Player = CManager::GetPlayer();
}

//------------------------------------------------------------------------------
//	�֐���:	void CEnemy_Hamina::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CEnemy_Hamina::Uninit(void)
{
	for (int i = 0; i < nHamina_Max; i++)
	{
		for (int j = 0; j < HAMINA_PARTS_MAX; j++)
		{
			m_Hamina[i].Model[j]->Uninit();
		}

		m_Hamina[i].Shadow->Uninit();

		m_Hamina[i].SprayBefore->Uninit();
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CEnemy_Hamina::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CEnemy_Hamina::Update(void)
{
	CMeshField		*pSea = CManager::GetSea();

	for (int i = 0; i < nHamina_Max; i++)
	{
		if (m_Hamina[i].CharData.bFlag)
		{
			float fAimDistance;
			float fAimTime;
			float RotY;

			//  ���[�U�[�}�b�v
			CManager::GetUserMap()->SensorCheck(&m_Hamina[i].bUserMap, m_Hamina[i].CharData.Pos, ENEMY);

			if (m_Hamina[i].CharData.nLife > 0)
			{
				//  �~�T�C�������Z�b�g
				if (m_Hamina[i].WeaponData[HAMINA_MISSILE].nCoolDown == 0)
				{
					m_Hamina[i].MissileID = CManager::GetMissile()->Reset(&m_Hamina[i].Matrix.World, USER_ENEMY, &m_Hamina[i].CharData.Pos, &m_Hamina[i].CharData.Rot, &m_Hamina[i].CharData.bFlag, m_MissileDeviationPos);
					m_Hamina[i].WeaponData[HAMINA_MISSILE].bFlag = true;
					m_Hamina[i].WeaponData[HAMINA_MISSILE].nNum = HAMINA_MISSILE_NUM;
					m_Hamina[i].WeaponData[HAMINA_MISSILE].nCoolDown = HAMINA_MISSILE_REPAIRTIME * 60;
				}
				//  �~�T�C������
				if (!m_Hamina[i].WeaponData[HAMINA_MISSILE].bFlag)
				{
					m_Hamina[i].WeaponData[HAMINA_MISSILE].nCoolDown--;
				}
				else
				{
					switch ((rand() % 10))
					{
					case 0:
						if (m_Hamina[i].fDistance >= 3000.0f)
						{
							CManager::GetMissile()->Set(m_Player->GetPosition(), m_Hamina[i].MissileID);
							m_Hamina[i].WeaponData[HAMINA_MISSILE].nNum--;
						}
						break;
					default:
						break;
					}

					if (m_Hamina[i].WeaponData[HAMINA_MISSILE].nNum == 0)	m_Hamina[i].WeaponData[HAMINA_MISSILE].bFlag = false;
				}


				//  ��͖C�����Z�b�g
				if (m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nCoolDown == 0)
				{
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].bFlag = true;
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nNum = HAMINA_SHIP_GUN_NUM;
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nCoolDown = HAMINA_SHIP_GUN_REPAIRTIME * 60;
				}

				if (!m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].bFlag) {
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nCoolDown--;
				}
				else
				{
					if (m_Hamina[i].BatteryRot.y > 0.0f && m_Hamina[i].BatteryRot.y <= 0.55f || m_Hamina[i].BatteryRot.y < 0.0f && m_Hamina[i].BatteryRot.y >= -0.55f)
					{
						if (m_Hamina[i].GunCnt == 0)
						{
							CManager::GetBullet()->Set(
								USER_ENEMY,
								//m_Hamina[i].GunPos.GetPos(),
								m_Hamina[i].AimPos,
								*m_Player->GetPosition()
							);
							m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nNum--;
							m_Hamina[i].GunCnt = 240;
						}
						else
						{
							m_Hamina[i].GunCnt--;
						}

						if (m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nNum == 0)	m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].bFlag = false;
					}
				}

				//  ��͖C�𔭎�

				//  �C��͏�Ƀv���C���[�̐i�ޕ����̂�����x�����Ɍ����Ă�
				fAimDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Hamina[i].CharData.Pos);
				fAimTime = fAimDistance / fBullet_Speed_Enemy;
				m_Hamina[i].AimPos.x = m_Player->GetPosition()->x - fAimTime * *m_Player->GetSpeed() * m_Player->GetObb(0)->GetDirect(2).x;
				m_Hamina[i].AimPos.z = m_Player->GetPosition()->z - fAimTime * *m_Player->GetSpeed() * m_Player->GetObb(0)->GetDirect(2).z;
				m_Hamina[i].AimPos.y = m_Player->GetPosition()->y;
				RotY = CManager::GetFunc()->GetXZRot(m_Hamina[i].AimPos, m_Hamina[i].CharData.Pos);

				//  �C��̌������X�V
				m_Hamina[i].BatteryRot.y = RotY + D3DX_PI - m_Hamina[i].CharData.Rot.y;

				//  �C��̌������`�F�b�N
				SAFE_ROTCHECK(m_Hamina[i].BatteryRot.y);

				//  �C��������X�V
				m_Hamina[i].Model[HAMINA_BATTERY]->SetRot(m_Hamina[i].BatteryRot);

				m_Hamina[i].VectorToPlayer = *m_Player->GetPosition() - m_Hamina[i].CharData.Pos;

				m_Hamina[i].fDistance = D3DXVec3Length(&m_Hamina[i].VectorToPlayer);

				//  AI����
				switch (m_Hamina[i].AIType)
				{
				case HAMINA_LEFT_LEADER:
					//  �v���C���[�Ƃ̋������߂��Ȃ�΁A����]����
					if (m_Hamina[i].fDistance < 3000.0f && m_Hamina[i].State != HAMINA_TURN_LEFT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z) - D3DX_PI);
						m_Hamina[i].State = HAMINA_TURN_LEFT;
					}
					else if (m_Hamina[i].fDistance > 5000.0f && m_Hamina[i].State != HAMINA_TURN_LEFT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z) - D3DX_PI);
						m_Hamina[i].State = HAMINA_TURN_LEFT;
					}

					if (m_Hamina[i].fMoveRot <= 0.0f)	m_Hamina[i].State = HAMINA_MOVE;

					m_LeftLeaderState = m_Hamina[i].State;
					break;
				case HAMINA_LEFT_NORMAL1:
					//  ���ʈȊO�̍s���̓��[�_�[�ƈꏏ
					if (m_LeftLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_LeftLeaderState;
					break;
				case HAMINA_LEFT_NORMAL2:
					//  ���ʈȊO�̍s���̓��[�_�[�ƈꏏ
					if (m_LeftLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_LeftLeaderState;
					break;
				case HAMINA_RIGHT_LEADER:
					//  �v���C���[�Ƃ̋������߂��Ȃ�΁A�E��]����
					if (m_Hamina[i].fDistance < 1500.0f && m_Hamina[i].State != HAMINA_TURN_RIGHT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(D3DX_PI - atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z));
						m_Hamina[i].State = HAMINA_TURN_RIGHT;
					}
					else if (m_Hamina[i].fDistance > 4500.0f && m_Hamina[i].State != HAMINA_TURN_RIGHT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(D3DX_PI - atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z));
						m_Hamina[i].State = HAMINA_TURN_RIGHT;
					}

					if (m_Hamina[i].fMoveRot <= 0.0f)	m_Hamina[i].State = HAMINA_MOVE;
					m_RightLeaderState = m_Hamina[i].State;
					break;
				case HAMINA_RIGHT_NORMAL1:
					//  ���ʈȊO�̍s���̓��[�_�[�ƈꏏ
					if (m_RightLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_RightLeaderState;
					break;
				case HAMINA_RIGHT_NORMAL2:
					//  ���ʈȊO�̍s���̓��[�_�[�ƈꏏ
					if (m_RightLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_RightLeaderState;
					break;
				case HAMINA_RAND:
					//  �C��̎ˌ��s�\�p�x�̏ꍇ�A�v���C���[�̕����ɂ���āA��]����
					if (m_Hamina[i].BatteryRot.y > -D3DX_PI && m_Hamina[i].BatteryRot.y <= -D3DX_PI * HAMINA_BATTERY_ROT_ZONE)
					{
						m_Hamina[i].State = HAMINA_TURN_LEFT;
					}

					if (m_Hamina[i].BatteryRot.y >= D3DX_PI * HAMINA_BATTERY_ROT_ZONE && m_Hamina[i].BatteryRot.y <= D3DX_PI)
					{
						m_Hamina[i].State = HAMINA_TURN_RIGHT;
					}

					//  ���͒����ړ�
					if (m_Hamina[i].BatteryRot.y > 0.0f && m_Hamina[i].BatteryRot.y <= 0.55f || m_Hamina[i].BatteryRot.y < 0.0f && m_Hamina[i].BatteryRot.y >= -0.55f)
					{
						m_Hamina[i].State = HAMINA_MOVE;
					}
					break;
				default:
					break;
				}
			}
			else if(m_Hamina[i].CharData.nLife <= 0 && m_Hamina[i].State != HAMINA_DEAD)
			{
				float fVoiceDistance;
				float fVoiceRate;

				for (int j = 0; j < HAMINA_PARTS_MAX; j++)
				{
					m_Hamina[i].Model[j]->SetBroken(true);
				}

				CManager::GetEffect()->SetEffect(
					m_Hamina[i].CharData.Pos,
					D3DXVECTOR3(250.0f, 250.0f, 0.0f),
					EFFECT_EXPLOSION_001,
					false,
					true,
					true,
					true
				);

				//  ����������v���C���[�܂ł̋������Z�o
				fVoiceDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Hamina[i].CharData.Pos);

				//  �����������Z�o�i��������������͈͓��ł���΁A�����ɂ��Z�o�@��:0.0f�ɐݒ�j
				fVoiceRate = fVoiceDistance <= fVoice_Distance ? 1.0f - fVoiceDistance / fVoice_Distance : 0.0f;

				if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_SHIP_EXPLOSION, fVoiceRate, m_Hamina[i].CharData.Pos.x, m_Hamina[i].CharData.Pos.y, m_Hamina[i].CharData.Pos.z);

				m_Hamina[i].State = HAMINA_DEAD;

				CManager::AddKillsNum(1);
			}

			//  ��Ԃ��Ƃ̏���
			switch (m_Hamina[i].State)
			{
			case HAMINA_MOVE:
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			case HAMINA_TURN_LEFT:
				m_Hamina[i].CharData.Rot.y -= 0.002f;
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			case HAMINA_TURN_RIGHT:
				m_Hamina[i].CharData.Rot.y += 0.002f;
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			case HAMINA_DEAD:
				m_Hamina[i].CharData.fSpeed -= m_Hamina[i].CharData.fSpeed > 0.0f ? 0.01f : 0.0f;
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			default:
				break;
			}

			SAFE_ROTCHECK(m_Hamina[i].CharData.Rot.y);

			//  Y���W�̏���
			if (m_Hamina[i].State != HAMINA_DEAD)
			{
				m_Hamina[i].CharData.Pos.y = pSea->GetHeight(m_Hamina[i].CharData.Pos) + fHamina_PosY_Adjust;
			}
			else
			{
				m_Hamina[i].CharData.Pos.y -= m_Hamina[i].CharData.Pos.y > -50.0f ? 0.2f : 0.0f;
				m_Hamina[i].CharData.bFlag = m_Hamina[i].CharData.Pos.y <= -50.0f ? false : true;
			}

			//  �����蔻��
			//  �����蔻��
			m_Hamina[i].bCollision = false;

			if (m_Hamina[i].fDistance > 0.0f && m_Hamina[i].fDistance < 700.0f)
			{
				m_Hamina[i].bCollision = CManager::GetFunc()->OBBs(*m_Player->GetObb(0), m_Hamina[i].Obb[0]);
			}

			if (m_Hamina[i].bCollision)
			{
				m_Hamina[i].CharData.Pos.x = m_Hamina[i].CharData.OldPos.x;
				m_Hamina[i].CharData.Pos.z = m_Hamina[i].CharData.OldPos.z;
				m_Hamina[i].CharData.Rot = m_Hamina[i].CharData.OldRot;
				m_Hamina[i].CharData.fSpeed -= m_Hamina[i].CharData.fSpeed <= 0.0f ? 0.0f : 0.005f;
			}

			//  ���򖗂̍X�V
			//  ���򖗁i�O�j�̍X�V
			for (int k = 0; k < SPRAY_TYPE_MAX; k++)
			{
				D3DXVec3TransformCoord(&m_Hamina[i].SprayBeforePos[k], &g_SprayBeforeDeviationPos[k], &m_Hamina[i].Matrix.World);
				m_Hamina[i].SprayBeforePos[k].y = pSea->GetHeight(m_Hamina[i].SprayBeforePos[k]) - 25.0f;
			}
			m_Hamina[i].SprayBeforeSize = g_SprayBeforeSize * (m_Hamina[i].CharData.fSpeed / fHamina_Speed_Max);
			m_Hamina[i].SprayBefore->Update();

			//  ���򖗁i���j�̍X�V
			D3DXVec3TransformCoord(&m_Hamina[i].SprayBehidePos, &g_SprayBehideDeviationPos, &m_Hamina[i].Matrix.World);
			m_Hamina[i].SprayBehideSize = g_SprayBehideSize * (m_Hamina[i].CharData.fSpeed / fHamina_Speed_Max);

			//  �}�g���N�X�̍X�V
			MatrixUpdate(i);

			//  Obb���̍X�V
			ObbUpdate(i);

			//  �V���h�E�ʒu�A��]�̍X�V
			m_Hamina[i].Shadow->SetRot(m_Hamina[i].CharData.Rot);
			m_Hamina[i].Shadow->SetPos(m_Hamina[i].CharData.Pos);

			//  ���W�Ɖ�]��ۑ�
			m_Hamina[i].CharData.OldPos = m_Hamina[i].CharData.Pos;
			m_Hamina[i].CharData.OldRot = m_Hamina[i].CharData.Rot;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CEnemy_Hamina::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CEnemy_Hamina::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < nHamina_Max; i++)
	{
		if (m_Hamina[i].CharData.bFlag)
		{
			
			m_Hamina[i].Shadow->Draw();

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_Hamina[i].Matrix.World);

			for (int j = 0; j < HAMINA_PARTS_MAX; j++)
			{
				//  �p�[�c�̕`��
				m_Hamina[i].Model[j]->Draw();
			}

			//  �D�O�̐��򖗂�`��
			for (int k = 0; k < SPRAY_TYPE_MAX; k++)
			{
				m_Hamina[i].SprayBefore->Draw(k);
			}
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CEneny_Hamina::MatrixUpdate
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���[���h�}�g���b�N�X�̍X�V
//------------------------------------------------------------------------------
void CEnemy_Hamina::MatrixUpdate(int nID)
{
	//  ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Hamina[nID].Matrix.World);

	//  �X�P�[���𔽉f
	D3DXMatrixScaling(&m_Hamina[nID].Matrix.Scl, m_Hamina[nID].CharData.Scl.x, m_Hamina[nID].CharData.Scl.y, m_Hamina[nID].CharData.Scl.z);
	D3DXMatrixMultiply(&m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.Scl);

	//  ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&m_Hamina[nID].Matrix.Rot, m_Hamina[nID].CharData.Rot.y, m_Hamina[nID].CharData.Rot.x, m_Hamina[nID].CharData.Rot.z);
	D3DXMatrixMultiply(&m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.Rot);

	//  �ʒu�𔽉f
	D3DXMatrixTranslation(&m_Hamina[nID].Matrix.Trans, m_Hamina[nID].CharData.Pos.x, m_Hamina[nID].CharData.Pos.y, m_Hamina[nID].CharData.Pos.z);
	D3DXMatrixMultiply(&m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.Trans);

}

//------------------------------------------------------------------------------
//	�֐���:	void CEnemy_Hamina::ObbUpdate
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	OBB���̍X�V
//------------------------------------------------------------------------------
void CEnemy_Hamina::ObbUpdate(int nID)
{
	D3DXVECTOR3 ObbPos;

	for (int i = 0; i < nHamina_Obb_Max; i++)
	{
		D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[i], &m_Hamina[nID].Matrix.World);																//  Obb�ʒu���Z�o
		m_Hamina[nID].Obb[i].SetPos(ObbPos);																											//  Obb�ʒu��ݒ�
		m_Hamina[nID].Obb[i].SetDirect(X_AXIS, D3DXVECTOR3(m_Hamina[nID].Matrix.Rot._11,m_Hamina[nID].Matrix.Rot._12, m_Hamina[nID].Matrix.Rot._13));	//  Obb��X�������x�N�g����ݒ�
		m_Hamina[nID].Obb[i].SetDirect(Y_AXIS, D3DXVECTOR3(m_Hamina[nID].Matrix.Rot._21,m_Hamina[nID].Matrix.Rot._22, m_Hamina[nID].Matrix.Rot._23));	//  Obb��Y�������x�N�g����ݒ�
		m_Hamina[nID].Obb[i].SetDirect(Z_AXIS, D3DXVECTOR3(m_Hamina[nID].Matrix.Rot._31,m_Hamina[nID].Matrix.Rot._32, m_Hamina[nID].Matrix.Rot._33));	//  Obb��Z�������x�N�g����ݒ�
		m_Hamina[nID].ObbTest[i]->SetPos(m_Hamina[nID].Obb[i].GetPos());																				//  Obb�e�X�g�����̂̈ʒu��ݒ�
		m_Hamina[nID].ObbTest[i]->SetRot(m_Hamina[nID].CharData.Rot);																					//  Obb�e�X�g�����̂̉�]��ݒ�
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CEnemy_Hamina::Set
//	����:	D3DXVECTOR3 pos, D3DXVECTOR3 rot
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CEnemy_Hamina::Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, HAMINA_AI_TYPE AI_Type)
{
	for (int i = 0; i < nHamina_Max; i++)
	{
		if (!m_Hamina[i].CharData.bFlag)
		{
			m_Hamina[i].CharData.Pos = Pos;
			m_Hamina[i].CharData.OldPos = Pos;
			m_Hamina[i].CharData.Rot = Rot;
			m_Hamina[i].CharData.OldRot = Rot;
			m_Hamina[i].BatteryRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Hamina[i].CharData.fSpeed = SPEED_MAX;
			m_Hamina[i].CharData.nLife = nHamina_Life;
			m_Hamina[i].AIType = AI_Type;
			m_Hamina[i].CharData.bFlag = true;
			break;
		}
	}
}

CHamina_Data *CEnemy_Hamina::GetHaminaData(void)
{
	return &m_Hamina[0];
}

//void CEnemy_Hamina::SetMissileLock(bool bMissileLock, int nID)
//{ 
//	m_Hamina[nID].SetMissileLockFlag(bMissileLock);
//}