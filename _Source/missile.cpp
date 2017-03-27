//------------------------------------------------------------------------------
//	�^�C�g���F		�~�T�C���̊֐�
//	�t�@�C�����F	missile.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/01/03
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "model.h"
#include "missile.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "meshField.h"
#include <time.h>
#include "openAL.h"
#include "effect.h"
#include "Func.h"
#include "userMap.h"
#include "enemy.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
const D3DXVECTOR3 AxisYVectorUP = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CMissile::CMissile
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CMissile::CMissile(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_Model	= NULL;			//  ���f���ւ̃|�C���g
}

//------------------------------------------------------------------------------
//	�֐���:	CMissile::~CMissile
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CMissile::~CMissile()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CMissile *CMissile::Create
//	����:	�Ȃ�
//	�߂�l:	pBullet
//	����:	�K�g�����O�̐���
//------------------------------------------------------------------------------
CMissile *CMissile::Create(void)
{
	CMissile *pMissile;

	//  �C���X�^���X����
	pMissile = new CMissile;

	//  ������
	pMissile->Init();

	return pMissile;
}

//------------------------------------------------------------------------------
//	�֐���:	void CMissile::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CMissile::Init(void)
{
	m_Model = CModel::Create(
		MODEL_MISSILE,
		MODEL_PARTS_MISSILE,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	m_Model->SetParent(NULL);
}

//------------------------------------------------------------------------------
//	�֐���:	void CMissile::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CMissile::Uninit(void)
{
	m_Model->Uninit();
}

//------------------------------------------------------------------------------
//	�֐���:	void CMissile::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CMissile::Update(void)
{
	CEffect *pEffect = CManager::GetEffect();
	CPlayer *pPlayer = CManager::GetPlayer();

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (m_Missile[i].Flag)
		{
			if (m_Missile[i].UserType == USER_ENEMY && m_Missile[i].State != MISSILE_STATE_NONE)
			{
				CManager::GetUserMap()->SensorCheck(&m_Missile[i].bUserMap, m_Missile[i].Pos, USERMAP_MISSILE);
			}

			if (!m_Missile[i].ShipFlag)
			{
				m_Missile[i].Flag = false;
			}

			switch (m_Missile[i].State)
			{
			case MISSILE_READY:
				m_Missile[i].Speed += m_Missile[i].Speed <= 3.0f ? 0.1f : 0.5f;
				m_Missile[i].Pos.y += m_Missile[i].Speed;

				//  ���̏�Ԃ�
				if (m_Missile[i].Speed > 15.0f)	m_Missile[i].State = MISSILE_RISE;
				break;
			case MISSILE_RISE:
				m_Missile[i].Speed += 0.5f;
				m_Missile[i].Pos.y += m_Missile[i].Speed;

				//  ���̏�Ԃ�
				if (m_Missile[i].Pos.y > m_Missile[i].TargetPos->y + 2500.0f)
				{
					//  �e�}�g���b�N�X��؂�
					D3DXVec3TransformCoord(&m_Missile[i].Pos, &m_Missile[i].Pos, m_Missile[i].ShipMatrix);
					m_Missile[i].bParent = false;
					m_Missile[i].State = MISSILE_PURSUIT;
				}
				break;
			case MISSILE_PURSUIT:
				m_Missile[i].Speed = 3.0f;
				m_Missile[i].Vector = *m_Missile[i].TargetPos - m_Missile[i].Pos;
				D3DXVec3Normalize(&m_Missile[i].Vector, &m_Missile[i].Vector);
				m_Missile[i].Gravity += m_Missile[i].Gravity >= 15.0f ? 0.0f : 0.2f;

				m_Missile[i].Rot.y = atan2f(m_Missile[i].Vector.x, m_Missile[i].Vector.z) + D3DX_PI;
				m_Missile[i].Rot.x = D3DXVec3Dot(&AxisYVectorUP, &m_Missile[i].Vector);

				m_Missile[i].Pos += m_Missile[i].Vector * (m_Missile[i].Speed + m_Missile[i].Gravity);

				if (m_Missile[i].Pos.y <= m_Missile[i].TargetPos->y + 20.0f)	m_Missile[i].State = MISSILE_EXPLOSION;
				break;
			case MISSILE_EXPLOSION:
				float fVoiceDistance;
				float fVoiceRate;

				m_Missile[i].State = MISSILE_STATE_MAX;
				m_Missile[i].Flag = false;

				if (m_Missile[i].UserType == USER_PLAYER)
				{
					(CManager::GetHamina()->GetHaminaData() + m_Missile[i].LockShipID)->AddLife(-15);
					m_Missile[i].UserType = USER_NONE;
				}

				if (m_Missile[i].UserType == USER_ENEMY)
				{
					m_Missile[i].UserType = USER_NONE;
					pPlayer->AddLife(-5);
				}

				pEffect->SetEffect(
					m_Missile[i].Pos,
					D3DXVECTOR3(150.0f, 150.0f, 0.0f),
					EFFECT_EXPLOSION_001,
					false,
					true,
					true,
					true
				);

				//  ����������v���C���[�܂ł̋������Z�o
				fVoiceDistance = CManager::GetFunc()->GetDistance(*pPlayer->GetPosition(), m_Missile[i].Pos);
			
				//  �����������Z�o�i��������������͈͓��ł���΁A�����ɂ��Z�o�@��:0.0f�ɐݒ�j
				fVoiceRate = fVoiceDistance <= fVoice_Distance ? 1.0f - fVoiceDistance / fVoice_Distance : 0.0f;

				if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_MISSILE_EXPLOSION, fVoiceRate, m_Missile[i].Pos.x, m_Missile[i].Pos.y, m_Missile[i].Pos.z);
				break;
			default:
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CMissile::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CMissile::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (m_Missile[i].Flag)
		{
			D3DXMATRIX		pParentMatrix;

			//  ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_Missile[i].Matrix.World);

			//  �e�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pParentMatrix);

			//  �e�̐ݒ�
			if (m_Missile[i].bParent)	pParentMatrix = *m_Missile[i].ShipMatrix;

			//  �X�P�[���𔽉f
			D3DXMatrixScaling( &m_Missile[i].Matrix.Scl, m_Missile[i].Scl.x, m_Missile[i].Scl.y, m_Missile[i].Scl.z );
			D3DXMatrixMultiply( &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.Scl );

			//  ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &m_Missile[i].Matrix.Rot, m_Missile[i].Rot.y, m_Missile[i].Rot.x, m_Missile[i].Rot.z );
			D3DXMatrixMultiply( &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.Rot );

			//  �ʒu�𔽉f
			D3DXMatrixTranslation( &m_Missile[i].Matrix.Trans, m_Missile[i].Pos.x, m_Missile[i].Pos.y, m_Missile[i].Pos.z );
			D3DXMatrixMultiply( &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.Trans );

			//  �e�̃}�g���b�N�X�𔽉f
			if (m_Missile[i].bParent)	D3DXMatrixMultiply(&m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &pParentMatrix);

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_Missile[i].Matrix.World);

			m_Model->Draw();
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CMissile::Set
//	����:	D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CMissile::Set(D3DXVECTOR3 *TargetPos, int nID)
{
	m_Missile[nID].TargetPos = TargetPos;
	m_Missile[nID].State = MISSILE_READY;
	m_Missile[nID].Speed = 0.0f;
	m_Missile[nID].Gravity = 0.0f;
	m_Missile[nID].Life = 3;
	m_Missile[nID].bUserMap = false;
}

int	CMissile::Reset(D3DXMATRIX *ShipMatrix, USER_TYPE User_Type, D3DXVECTOR3 *ShipPos, D3DXVECTOR3 *ShipRot, bool *bShipFlag, D3DXVECTOR3 DeviationPos)
{
	int nID;

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (!m_Missile[i].Flag)
		{
			m_Missile[i].ShipMatrix = ShipMatrix;
			m_Missile[i].Rot = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);
			m_Missile[i].ShipPos = ShipPos;
			m_Missile[i].ShipRot = ShipRot;
			m_Missile[i].ShipFlag = bShipFlag;
			m_Missile[i].Pos = 
			m_Missile[i].DeviationPos = DeviationPos;
			m_Missile[i].DeviationRot = atan2f(DeviationPos.x, DeviationPos.z);
			m_Missile[i].Radius = sqrtf(DeviationPos.x * DeviationPos.x + DeviationPos.z * DeviationPos.z);
			m_Missile[i].UserType = User_Type;
			m_Missile[i].CheckSea = false;
			m_Missile[i].State = MISSILE_STATE_NONE;
			m_Missile[i].Flag = true;
			m_Missile[i].bParent = true;
			nID = i;
			break;
		}
	}

	return nID;
}

CMissile_Data *CMissile::GetMissileData(void)
{
	return &m_Missile[0];
}