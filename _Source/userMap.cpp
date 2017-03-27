//------------------------------------------------------------------------------
//	�^�C�g���F		���[�U�[�}�b�v�̊֐�
//	�t�@�C�����F	userMap.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/01/06
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "userMap.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "tutorial.h"
#include "enemy.h"
#include "camera.h"
#include <typeinfo.h>
#include "enemy.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

// �}�b�v�f�ނ̃p�����[�^
const LPCSTR g_UserMap[USERMAP_TYPE_MAX] =
{
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Background.png" },	
	{ "./data/TEXTURE/UI/GAME/Radar/Bullet_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Missile_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Jamming_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Sensor.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Ship_Mark.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Target.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Target.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Frame.png" }
};

//------------------------------------------------------------------------------
//	�֐���:	CUserMap::CUserMap
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CUserMap::CUserMap(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer	= NULL;		//  ���_�o�b�t�@�ւ̃|�C��
	for (int i = 0; i < USERMAP_TYPE_MAX; i++)
	{
		m_TextureBuffer[i] = NULL;		//  �e�N�X�`���ւ̃|�C���^
	}
}

//------------------------------------------------------------------------------
//	�֐���:	CUserMap::~CUserMap
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CUserMap::~CUserMap()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CUserMap *CUserMap::Create
//	����:	�Ȃ�
//	�߂�l:	pUserMap
//	����:	���[�U�[�}�b�v�̐���
//------------------------------------------------------------------------------
CUserMap *CUserMap::Create(void)
{
	CUserMap *pUserMap;
	pUserMap = new CUserMap;

	for (int i = 0; i < USERMAP_TYPE_MAX; i++)
	{
		//  �e�N�X�`���̐ݒ�
		D3DXCreateTextureFromFile
		(
			CManager::GetRenderer()->GetDevice(),
			g_UserMap[i],										//  �e�N�X�`���t�@�C���ʒu
			&pUserMap->m_TextureBuffer[i]						//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
		);
	}

	pUserMap->Init();

	return pUserMap;
}

//------------------------------------------------------------------------------
//	�֐���:	void CUserMap::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CUserMap::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ��ʃT�C�Y���擾
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  ��ʊ������擾
	float *pScreenRate = GetScreenRate();

	CMode *pMode = CManager::GetMode();

	//  ���C�_�[���̏�����
	m_UserMap[RADAR_BACKGROUNG].Pos =
	m_UserMap[BULLET_LIMITS].Pos =
	m_UserMap[MISSILE_LIMITS].Pos =
	m_UserMap[JAMMING_LIMITS].Pos =
	m_UserMap[RADAR_SENSOR].Pos =
	m_UserMap[RADAR_LIMITS].Pos =
	m_UserMap[PLAYER].Pos =
	m_UserMap[nUserMapMax - 1].Pos = D3DXVECTOR2(pScreenSize->x - 200.0f * *pScreenRate, pScreenSize->y - 200.0f * *pScreenRate);

	m_UserMap[RADAR_BACKGROUNG].Size =
	m_UserMap[BULLET_LIMITS].Size =
	m_UserMap[MISSILE_LIMITS].Size =
	m_UserMap[JAMMING_LIMITS].Size =
	m_UserMap[RADAR_SENSOR].Size =
	m_UserMap[RADAR_LIMITS].Size =
	m_UserMap[PLAYER].Size =
	m_UserMap[nUserMapMax - 1].Size = D3DXVECTOR2(350.0f * *pScreenRate, 350.0f * *pScreenRate);

	m_UserMap[RADAR_BACKGROUNG].Flag =
	m_UserMap[BULLET_LIMITS].Flag =
	m_UserMap[RADAR_SENSOR].Flag =
	m_UserMap[RADAR_LIMITS].Flag =
	m_UserMap[PLAYER].Flag =
	m_UserMap[nUserMapMax - 1].Flag = true;

	m_UserMap[RADAR_BACKGROUNG].Type = RADAR_BACKGROUNG;
	m_UserMap[BULLET_LIMITS].Type = BULLET_LIMITS;
	m_UserMap[MISSILE_LIMITS].Type = MISSILE_LIMITS;
	m_UserMap[JAMMING_LIMITS].Type = JAMMING_LIMITS;
	m_UserMap[RADAR_SENSOR].Type = RADAR_SENSOR;
	m_UserMap[RADAR_LIMITS].Type = RADAR_LIMITS;
	m_UserMap[PLAYER].Type = PLAYER;
	m_UserMap[nUserMapMax - 1].Type = RADAR_FRAME;

	m_TexSensorLength = sqrtf((m_UserMap[RADAR_SENSOR].Size.x * 0.5f ) * (m_UserMap[RADAR_SENSOR].Size.x * 0.5f) + (m_UserMap[RADAR_SENSOR].Size.y * 0.5f) * (m_UserMap[RADAR_SENSOR].Size.y * 0.5f));
	m_TexSensorAngle = atan2f(m_UserMap[RADAR_SENSOR].Size.x * 0.5f, m_UserMap[RADAR_SENSOR].Size.y * 0.5f);

	m_Sensor.Pos[0] = D3DXVECTOR2(pScreenSize->x - 200.0f * *pScreenRate, pScreenSize->y - 200.0f * *pScreenRate);
	m_Sensor.Size = D3DXVECTOR2(20.0f * *pScreenRate, 155.0f * *pScreenRate);
	m_Sensor.Angle = atan2f(m_Sensor.Size.x * 0.5f, m_Sensor.Size.y * 0.5f);

	m_WeaponLimitsAngle = atan2f(m_UserMap[BULLET_LIMITS].Size.x * 0.5f, (m_UserMap[BULLET_LIMITS].Size.y * 0.5f));

	m_CameraRotY = &CManager::GetCameraData()->rot.y;
	m_PlayerRotY = &CManager::GetPlayer()->GetRotation()->y;
	m_WeaponType = CManager::GetPlayer()->GetWeponType();

	//  ���_���̍쐬
	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	�֐���:	void CUI::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CUserMap::Uninit(void)
{
	//  ���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);

	//  �e�N�X�`���o�b�t�@�̊J��
	for (int i = 0; i < USERMAP_TYPE_MAX; i++)
	{
		SAFE_RELEASE(m_TextureBuffer[i]);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CUserMap::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CUserMap::Update(void)
{
	float *pScreenRate = GetScreenRate();

	m_Sensor.Rot -= D3DX_PI / 90.0f;

	SAFE_ROTCHECK(m_Sensor.Rot);

	m_Sensor.Pos[1].x = m_Sensor.Pos[0].x + sinf(m_Sensor.Angle + m_Sensor.Rot) * m_Sensor.Size.y;
	m_Sensor.Pos[1].y = m_Sensor.Pos[0].y + cosf(m_Sensor.Angle + m_Sensor.Rot) * m_Sensor.Size.y;

	m_Sensor.Pos[2].x = m_Sensor.Pos[0].x + sinf(m_Sensor.Rot) * m_Sensor.Size.y;
	m_Sensor.Pos[2].y = m_Sensor.Pos[0].y + cosf(m_Sensor.Rot) * m_Sensor.Size.y;

	for (int i = 0; i < nUserMapMax; i++)
	{
		if (m_UserMap[i].Col.a <= 0.0f)
		{
			m_UserMap[i].Flag = false;
		}

		switch (*m_WeaponType) {
		case WEAPON_BULLET:
			m_UserMap[BULLET_LIMITS].Flag = true;
			m_UserMap[MISSILE_LIMITS].Flag = false;
			m_UserMap[JAMMING_LIMITS].Flag = false;
			break;
		case WEAPON_MISSILE:
			m_UserMap[BULLET_LIMITS].Flag = false;
			m_UserMap[MISSILE_LIMITS].Flag = true;
			m_UserMap[JAMMING_LIMITS].Flag = false;
			break;
		default:
			m_UserMap[BULLET_LIMITS].Flag = false;
			m_UserMap[MISSILE_LIMITS].Flag = false;
			m_UserMap[JAMMING_LIMITS].Flag = false;
			break;
		}

		if (m_UserMap[i].Flag)
		{
			if ( m_UserMap[i].Type == ENEMY || m_UserMap[i].Type == USERMAP_MISSILE)
			{
				m_UserMap[i].Col.a -= 0.01f;
				m_UserMap[i].Size.x += 0.05f * *pScreenRate;
				m_UserMap[i].Size.y += 0.05f * *pScreenRate;
			}

			SetVertex(i);
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CUserMap::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CUserMap::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  ���C�g������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////  �t�H�O������
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	////  ���e�X�g���s��
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  ���e�X�g�̗L����
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  ���e�X�g���i�
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  ���Q�ƒl

	for (int i = 0; i < nUserMapMax; i++)
	{
		if (m_UserMap[i].Flag)
		{
			//  �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_TextureBuffer[m_UserMap[i].Type]);

			////  �y�e�X�g���s��
			//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//  �y�e�X�g�L����
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					//  �y�l�̍X�V���s��Ȃ����A�y�e�X�g��L��������
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				//  �y�e�X�g���i�

			//if (m_UserMap[i].Type == ENEMY || m_UserMap[i].Type] == FRIENDLY)
			//{

			//  �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);

			////  �y�e�X�g���s��Ȃ�
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				//  �y�e�X�g���i�
		}
	}

	//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////  �t�H�O�L����
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	////  ���e�X�g���s��Ȃ�
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  ���e�X�g������
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CUserMap::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice, POLYGON *pPOLYGON
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CUserMap::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * nNumVertex * nUserMapMax,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,									//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,								//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL											//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nUserMapMax; i++, pVtx += nNumVertex)
	{
		pVtx[0].pos = D3DXVECTOR3(m_UserMap[i].Pos.x - m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y - m_UserMap[i].Size.y * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_UserMap[i].Pos.x + m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y - m_UserMap[i].Size.y * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_UserMap[i].Pos.x - m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y + m_UserMap[i].Size.y * 0.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_UserMap[i].Pos.x + m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y + m_UserMap[i].Size.y * 0.5f, 0.0f);

		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		//  ���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_UserMap[i].Col;

		//  �e�N�X�`�����W�̐ݒ�
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
//	�֐���:	void CUserMap::SetVertex
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���_���̍X�V
//------------------------------------------------------------------------------
void CUserMap::SetVertex(int nID)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//if (nID == RADAR_SENSOR)
	//{
		switch (nID)
		{
		case RADAR_SENSOR:
			pVtx[0].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			pVtx[1].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			pVtx[2].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			pVtx[3].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			break;
		case BULLET_LIMITS:
			pVtx[0].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			pVtx[1].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			pVtx[2].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			pVtx[3].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			break;
		case PLAYER:
			pVtx[0].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			pVtx[1].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			pVtx[2].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			pVtx[3].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			break;
		default:
			pVtx[0].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x - m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y - m_UserMap[nID].Size.y * 0.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x + m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y - m_UserMap[nID].Size.y * 0.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x - m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y + m_UserMap[nID].Size.y * 0.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x + m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y + m_UserMap[nID].Size.y * 0.5f, 0.0f);
			break;
		}
	/*}*/

	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	//  ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_UserMap[nID].Col;

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CBullet::SetBullet
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CUserMap::Set(int *nID, D3DXVECTOR2 pos, USERMAP_TYPE type)
{
	//  ��ʊ������擾
	float *pScreenRate = GetScreenRate();
	//int j = 0;

	//if (type == USERMAP_MISSILE)
	//{
	//	j = HAMINA_MAX;
	//}

	for (int i = 7; i < nUserMapMax -1; i++)
	{
		if (!m_UserMap[i].Flag)
		{
			m_UserMap[i].Pos = pos;
			m_UserMap[i].Type = type;
			m_UserMap[i].Flag = true;
			m_UserMap[i].Size = D3DXVECTOR2(10.0f * *pScreenRate, 10.0f * *pScreenRate);
			switch (type)
			{
			case ENEMY:
				m_UserMap[i].Col = D3DXCOLOR(1.0f, 0.0f, 0.25f, 1.0f);
				m_UserMap[i].Size = D3DXVECTOR2(12.0f * *pScreenRate, 12.0f * *pScreenRate);
				break;
			case USERMAP_MISSILE:
				m_UserMap[i].Col = D3DXCOLOR(0.0f, 1.0f, 1.00f, 1.0f);
				m_UserMap[i].Size = D3DXVECTOR2(6.5f * *pScreenRate, 6.5f * *pScreenRate);
				break;
			}
			*nID = i;
			break;
		}
	}
}

int CUserMap::SensorCheck(bool *check, D3DXVECTOR3 pos, USERMAP_TYPE type)
{
	int nID;
	float length, angle, rot;
	D3DXVECTOR3	VectorVertex[3], VectorTarget[3], VectorResult[3], SensorPos[3], EnemyPos;
	D3DXVECTOR2 EnemyVector, EnenyMapPos, EnemyRotPos;
	CPlayer *pPlayer = CManager::GetPlayer();
	D3DXVECTOR3 *PlayerPos = pPlayer->GetPosition();
	D3DXVECTOR3 *PlayerRot = pPlayer->GetRotation();
	float *fScreenRate = GetScreenRate();

	//  �v���C���[����G�܂ł̃x�N�g�����Z�o
	EnemyVector.x = -(pos.x - PlayerPos->x) / (75.0f / *fScreenRate);
	EnemyVector.y = (pos.z - PlayerPos->z ) / (75.0f / *fScreenRate);

	length = sqrtf((EnemyVector.x * EnemyVector.x ) + ( EnemyVector.y * EnemyVector.y));
	angle = atan2f(EnemyVector.x, EnemyVector.y);

	rot = -angle - D3DX_PI * 0.5f;

	SAFE_ROTCHECK(rot);

	EnemyRotPos.x = -cosf(rot) * length;
	EnemyRotPos.y = -sinf(rot) * length;

	//  �}�b�v�̍��W����芄���ŎZ�o
	EnenyMapPos = m_UserMap[nUserMapMax - 1].Pos - EnemyRotPos;

	//  �����蔻��p�G���W�̕ϊ�
	EnemyPos.x = EnenyMapPos.x;
	EnemyPos.y = 0.0f;
	EnemyPos.z = EnenyMapPos.y;

	for (int i = 0; i < 3; i++)
	{
		SensorPos[i].x = m_Sensor.Pos[i].x;
		SensorPos[i].y = 0.0f;
		SensorPos[i].z = m_Sensor.Pos[i].y;
	}

	//  �v���~�e�B�u�̃x�N�g�����v�Z
	VectorVertex[0] = SensorPos[1] - SensorPos[0];
	VectorVertex[1] = SensorPos[2] - SensorPos[1];
	VectorVertex[2] = SensorPos[0] - SensorPos[2];

	//  �Ώۂ̃x�N�g�����v�Z
	VectorTarget[0] = EnemyPos - SensorPos[0];
	VectorTarget[1] = EnemyPos - SensorPos[1];
	VectorTarget[2] = EnemyPos - SensorPos[2];

	for (int i = 0; i < 3; i++)
	{
		//  �x�N�g���x���W���O�ɐݒ�
		VectorVertex[i].y =
		VectorTarget[i].y = 0.0f;

		//  �Ώۂ��v���~�e�B�u�e�ӂ̍��E�ǂ��炩�ɂ���̌v�Z�i�O�ρj
		D3DXVec3Cross(&VectorResult[i], &VectorTarget[i], &VectorVertex[i]);
	}

	//  ���E�v���~�e�B�u�ǂ���ɂ���`�F�b�N
	if (VectorResult[0].y >= 0)
	{//  ���v���~�e�B�u�ɂ���ꍇ
		if (VectorResult[1].y >= 0)
		{
			if (VectorResult[2].y >= 0)
			{
				*check = true;
				Set(&nID, EnenyMapPos, type);
			}
		}
		else
		{
			*check = false;
		}
		
	}
	else
	{
		*check = false;
	}
	return nID;
}

bool CUserMap::GetUserMapFlag(int nID)
{
	return m_UserMap[nID].Flag;
}

D3DXVECTOR2 *CUserMap::GetUserMapPos(void)
{
	return &m_UserMap[7].Pos;
}