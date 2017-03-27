//------------------------------------------------------------------------------
//	�^�C�g���F		�e�̊֐�
//	�t�@�C�����F	bullet.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/11/29
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "bullet.h"
#include "manager.h"
#include "Func.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "tutorial.h"
#include "player.h"
#include "meshField.h"
#include "openAL.h"
#include "time.h"
#include <typeinfo.h>
#include "water.h"
#include "effect.h"
#include "enemy.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------

const float fCheck_Sea = -15.0f;		//  �e�ƊC�̓����蔻��𒲐�����W��
const int	nBullet_Life = 120;			//  �e�̔�s����
const float	fBullet_Y_Max = 50.0f;		//  �e��Y���W�ő�l
const D3DXVECTOR2 Bullet_Size_Player = D3DXVECTOR2(2.0f, 2.0f);
const D3DXVECTOR2 Bullet_Size_Enemy = D3DXVECTOR2(4.0f, 4.0f);
const float fBullet_Effective_Fire = 6000.0f;
const float fBullet_Check = 5.0f;
const D3DXVECTOR3 Water_Impact_Size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CBullet::CBullet
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CBullet::CBullet(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;			//  ���_�o�b�t�@�ւ̃|�C���g
	m_TextureBuffer	= NULL;			//  �e�N�X�`���o�b�t�@�ւ̃|�C���g
	m_TextureFile	= NULL;			//  �e�N�X�`���t�@�C��
	m_ShotFrame	= 0;				//  �V���[�g�t���C��
	m_Gravity =						//  �d��
	m_Distance = 0.0f;				//  ����
	m_Player = NULL;
}

//------------------------------------------------------------------------------
//	�֐���:	CBullet::~CBullet
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CBullet::~CBullet()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CBullet *CBullet::Create
//	����:	�Ȃ�
//	�߂�l:	pBullet
//	����:	�K�g�����O�̐���
//------------------------------------------------------------------------------
CBullet *CBullet::Create(void)
{
	CBullet *pBullet;

	//  �C���X�^���X����
	pBullet = new CBullet;

	pBullet->m_TextureFile = PLAYER_SHOT_TEXTURE_FILE;

	//  �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		pBullet->m_TextureFile,				//  �e�N�X�`���t�@�C���ʒu
		&pBullet->m_TextureBuffer				//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	//  ������
	pBullet->Init();

	return pBullet;
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CBullet::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_���̍쐬
	MakeVertex(pDevice);

	m_Player = CManager::GetPlayer();
	m_Water = CManager::GetWater();
	m_Effect = CManager::GetEffect();
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	//�e�N�X�`���o�b�t�@�̊J��
	SAFE_RELEASE(m_TextureBuffer);

	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);

	m_TextureFile = NULL;

	m_Player = NULL;
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CBullet::Update(void)
{
	for (int i = 0; i < nBullet_Max; i++)
	{
		if (m_Bullet[i].Flag)
		{
			switch (m_Bullet[i].UserType)
			{
			//  �v���C���[�g�p��
			case USER_PLAYER:
				PlayerBulletUpdate(i);
				break;
			//  �G�g�p��
			case USER_ENEMY:
				EnemyBulletUpdate(i);
				break;
			}
		}
	}

	SetVertex();
}

void CBullet::PlayerBulletUpdate(int nID)
{
	float fHeight;
	float fDistance;
	CMode			*pMode = CManager::GetMode();
	CHamina_Data *pHaminaData = CManager::GetHamina()->GetHaminaData();

	if (m_Bullet[nID].Life > 0)
	{
		m_Bullet[nID].Pos += m_Bullet[nID].Vector * m_Bullet[nID].Speed;

		if (typeid(*pMode).name() == typeid(CGame).name())
		{
			//  �D�ɓ�����������
			for (int i = 0; i < nHamina_Max; i++)
			{
				for (int j = 0; j < nHamina_Obb_Max; j++)
				{
					fDistance = CManager::GetFunc()->LenOBBToPoint((pHaminaData + i)->Obb[j], m_Bullet[nID].Pos);
					if (fDistance <= 5.0f)
					{
						m_Bullet[i].Flag = false;

						//  �����G�t�F�N�g�Ɖ����̏���
						ExplosionUpdate(nID);

						(pHaminaData + i)->AddLife((int)(-12 * j * 0.3f));
						break;
					}
				}
			}
		}
		//  ��������
		if (m_Bullet[nID].Flag)
		{
			fHeight = CManager::GetSea()->GetHeight(m_Bullet[nID].Pos);

			if (m_Bullet[nID].Pos.y <= fHeight - fBullet_Check)
			{
				m_Bullet[nID].Pos.y = fHeight;
				m_Bullet[nID].Flag = false;

				//  �����G�t�F�N�g�Ɖ����̏���
				WaterImpactUpdate(nID);
			}
		}
		m_Bullet[nID].Life--;
	}
	else
	{
		m_Bullet[nID].Flag = false;
	}
}

void CBullet::EnemyBulletUpdate(int nID)
{
	float fDistance;
	float fHeight;

	m_Bullet[nID].FlyTime--;

	//  �ړ�����
	m_Bullet[nID].Pos.x += m_Bullet[nID].Vector.x * m_Bullet[nID].Speed;
	m_Bullet[nID].Pos.z += m_Bullet[nID].Vector.z * m_Bullet[nID].Speed;
	m_Bullet[nID].Pos.y += m_Bullet[nID].Gravity;

	//  �d�͔��]�̏���
	if (!m_Bullet[nID].bGravityInvert)
	{
		//  �e���ō��_�ɓ��B����΁i����s���Ԉȉ��ł���΁j�A�d�͔��]
		m_Bullet[nID].Gravity = m_Bullet[nID].FlyTime <= m_Bullet[nID].FlyTimeHalf ? -m_Bullet[nID].Gravity : m_Bullet[nID].Gravity;
		m_Bullet[nID].bGravityInvert = true;
	}

	//  �D�ɓ�����������
	for (int i = 0; i < nObbMax_P; i++)
	{
		//  �e�ƃv���C���[�eOBB�̋������Z�o
		fDistance = CManager::GetFunc()->LenOBBToPoint(*m_Player->GetObb(i), m_Bullet[nID].Pos);
		if (fDistance <= fBullet_Check)
		{
			m_Bullet[nID].Flag = false;

			//  �����G�t�F�N�g�Ɖ�������
			ExplosionUpdate(nID);

			//  �v���C���[�Ƀ_���[�W��ݒ�
			m_Player->AddLife(-1);
			break;
		}
	}

	//  ��������
	if (m_Bullet[nID].Flag)
	{
		//  �C�Ƃ̋����iY�j���Z�o
		fHeight = CManager::GetSea()->GetHeight(m_Bullet[nID].Pos);

		if (m_Bullet[nID].Pos.y <= fHeight - fBullet_Check)
		{
			m_Bullet[nID].Pos.y = fHeight;
			m_Bullet[nID].Flag = false;

			//  �����G�t�F�N�g�Ɖ�������
			WaterImpactUpdate(nID);
		}
	}
}

void CBullet::WaterImpactUpdate(int nID)
{
	float fVoiceDistance;
	float fVoiceRate;

	//  �����G�t�F�N�g
	m_Water->Set(
		m_Bullet[nID].Pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		Water_Impact_Size,
		EFFECT_WATER_IMPACT,
		false,
		true,
		true
	);

	//  ����������v���C���[�܂ł̋������Z�o
	fVoiceDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Bullet[nID].Pos);

	//  �����������Z�o�i��������������͈͓��ł���΁A�����ɂ��Z�o�@��:0.0f�ɐݒ�j
	fVoiceRate = fVoiceDistance <= fVoice_Water_Distance ? 1.0f - fVoiceDistance / fVoice_Water_Distance : 0.0f;

	if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WATER_EXPLOSION, fVoiceRate, m_Bullet[nID].Pos.x, m_Bullet[nID].Pos.y, m_Bullet[nID].Pos.z);
}

void CBullet::ExplosionUpdate(int nID)
{
	float fVoiceDistance;
	float fVoiceRate;
	float fExplosionRate;

	srand((unsigned)time(NULL));

	//  �����_���ɔ��j�K�͂����߂�
	switch ((rand() % 5))
	{
	case 0:
		fExplosionRate = 0.9f;
		break;
	case 1:
		fExplosionRate = 1.0f;
		break;
	case 2:
		fExplosionRate = 0.75f;
		break;
	case 3:
		fExplosionRate = 1.2f;
		break;
	case 4:
		fExplosionRate = 0.6f;
		break;
	}

	//  �����G�t�F�N�g
	m_Effect->SetEffect(
		m_Bullet[nID].Pos,
		D3DXVECTOR3(60.0f * fExplosionRate, 60.0f * fExplosionRate, 0.0f),
		EFFECT_EXPLOSION_000,
		false,
		true,
		true,
		true
	);

	//  ����������v���C���[�܂ł̋������Z�o
	fVoiceDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Bullet[nID].Pos);

	//  �����������Z�o�i��������������͈͓��ł���΁A�����ɂ��Z�o�@��:0.0f�ɐݒ�j
	fVoiceRate = fVoiceDistance <= fVoice_Distance ? 1.0f - fVoiceDistance / fVoice_Distance : 0.0f;

	if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_CANNON_EXPLOSION, fVoiceRate, m_Bullet[nID].Pos.x, m_Bullet[nID].Pos.y, m_Bullet[nID].Pos.z);
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CBullet::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//  ���C�g�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  ���e�X�g���s��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  ���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  ���e�X�g���i�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  ���Q�ƒl

	for (int i = 0; i < nBullet_Max; i++)
	{
		if (m_Bullet[i].Flag)
		{
			//  ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_Bullet[i].Matrix.World);

			//  �r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &m_Bullet[i].ViewMatrix);

			//  �t�s������߂�
			D3DXMatrixInverse(&m_Bullet[i].Matrix.World, NULL, &m_Bullet[i].ViewMatrix);

			m_Bullet[i].Matrix.World._41 = 0.0f;
			m_Bullet[i].Matrix.World._42 = 0.0f;
			m_Bullet[i].Matrix.World._43 = 0.0f;

			//  �X�P�[���𔽉f
			D3DXMatrixScaling( &m_Bullet[i].Matrix.Scl, m_Bullet[i].Scl.x, m_Bullet[i].Scl.y, m_Bullet[i].Scl.z );
			D3DXMatrixMultiply( &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.Scl );

			//  ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &m_Bullet[i].Matrix.Rot, m_Bullet[i].Rot.y, m_Bullet[i].Rot.x, m_Bullet[i].Rot.z );
			D3DXMatrixMultiply( &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.Rot );

			//  �ʒu�𔽉f
			D3DXMatrixTranslation( &m_Bullet[i].Matrix.Trans, m_Bullet[i].Pos.x, m_Bullet[i].Pos.y, m_Bullet[i].Pos.z );
			D3DXMatrixMultiply( &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.Trans );

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_Bullet[i].Matrix.World);

			//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
			pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

			//  ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//  �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_TextureBuffer);

			//  �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  ���C�g��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  ���e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CBullet::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CBullet::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nBullet_Max,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,									//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,								//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL											//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nBullet_Max; i++, pVtx += nNumVertex )
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos = 
		pVtx[1].pos = 
		pVtx[2].pos = 
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}
	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::Set
//	����:	USER_TYPE User_Type, D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos
//	�߂�l:	�Ȃ�
//	����:	�e�̐ݒ�
//------------------------------------------------------------------------------
void CBullet::Set(USER_TYPE User_Type, D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	for (int i = 0; i < nBullet_Max; i++)
	{
		if (!m_Bullet[i].Flag)
		{
			m_Bullet[i].UserType = User_Type;
			m_Bullet[i].Pos = pos;
			m_Bullet[i].TargetPos = TargetPos;
			m_Bullet[i].Vector = TargetPos - pos;
			D3DXVec3Normalize(&m_Bullet[i].Vector, &m_Bullet[i].Vector);
			m_Bullet[i].CheckSea = false;
			m_Bullet[i].Flag = true;
			m_Bullet[i].Speed = User_Type == USER_PLAYER ? fBullet_Speed_Player : fBullet_Speed_Enemy;
			m_Bullet[i].Size = User_Type == USER_PLAYER ? Bullet_Size_Player : Bullet_Size_Enemy;
			m_Bullet[i].Life = nBullet_Life;

			if (User_Type == USER_ENEMY)
			{
				//  �v���C���[�Ƃ̋������Z�o
				m_Bullet[i].Distance = CManager::GetFunc()->GetDistance(TargetPos, pos);
				m_Bullet[i].Distance = m_Bullet[i].Distance > fBullet_Effective_Fire ? fBullet_Effective_Fire : m_Bullet[i].Distance;

				//  ��s���Ԃ��Z�o
				m_Bullet[i].FlyTime = (int)(m_Bullet[i].Distance / m_Bullet[i].Speed);
				m_Bullet[i].FlyTimeHalf = m_Bullet[i].FlyTime / 2;
				m_Bullet[i].bGravityInvert = false;

				//  ���d�͂��Z�o
				m_Bullet[i].Gravity = (pos.y + fBullet_Y_Max * m_Bullet[i].Distance / fBullet_Effective_Fire) / m_Bullet[i].FlyTime;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::SetVertex
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���_���̍X�V
//------------------------------------------------------------------------------
void CBullet::SetVertex(void)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nBullet_Max; i++, pVtx += nNumVertex)
	{
		if (m_Bullet[i].Flag)
		{
			//  ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-m_Bullet[i].Size.x * 0.5f, m_Bullet[i].Size.y * 0.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Bullet[i].Size.x * 0.5f, m_Bullet[i].Size.y * 0.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_Bullet[i].Size.x * 0.5f, -m_Bullet[i].Size.y * 0.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Bullet[i].Size.x * 0.5f, -m_Bullet[i].Size.y * 0.5f, 0.0f);
		}
	}
	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}