//------------------------------------------------------------------------------
//	�^�C�g���F		���G�t�F�N�g�̊֐�
//	�t�@�C�����F	water.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/09/27
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "water.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "title.h"
#include "player.h"
#include <typeinfo.h>

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
//	�֐���:	CWater::CWater
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CWater::CWater(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  ���_�o�b�t�@�ւ̃|�C���g
}

//------------------------------------------------------------------------------
//	�֐���:	CWater::~CWater
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CWater::~CWater()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CWater *CWater::Create
//	����:	�Ȃ�
//	�߂�l:	pEffect
//	����:	�G�t�F�N�g�̐���
//------------------------------------------------------------------------------
CWater *CWater::Create(void)
{
	CWater *pWater;

	//  �C���X�^���X����
	pWater = new CWater;

	for (int i = 0; i <= EFFECT_WATER_IMPACT; i++)
	{
		switch (i)
		{
		case EFFECT_WATER_FALL_000:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		case EFFECT_WATER_FALL_001:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		case EFFECT_WATER_FALL_002:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		case EFFECT_WATER_IMPACT:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		default:
			break;
		}
	}

	//  ������
	pWater->Init();

	return pWater;
}

//------------------------------------------------------------------------------
//	�֐���:	void CWater::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CWater::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_���̍쐬
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	�֐���:	void CWater::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CWater::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CWater::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CWater::Update(void)
{
	for (int i = 0; i < nWater_Anim_Max; i++)
	{
		if (m_Water[i].Flag)
		{
			if (m_Water[i].Anim.PatternX != 1 && m_Water[i].Anim.PatternY != 1)
			{//  ���p�^�[���Əc�p�^�[�����P�ł͂Ȃ���΁A�e�N�X�`���A�j���[�V�����������s��
				//  �e�N�X�`�����W�̐ݒ�
				SetTexture(m_Water[i].Anim.Pattern, m_Water[i].Anim.PatternX, m_Water[i].Anim.PatternY, i);

				//  �J�E���g
				m_Water[i].Anim.Cnt++;

				if (m_Water[i].Anim.Cnt == m_Water[i].Anim.Frame)
				{//  ���t���[�����ƂɍX�V
					m_Water[i].Anim.Cnt = 0;						//  �A�j���[�V�����J�E���g�̏�����
					m_Water[i].Anim.Pattern++;						//  �A�j���[�V�������݃p�^�[�����X�V

					if (m_Water[i].Anim.Pattern == m_Water[i].Anim.PatternX * m_Water[i].Anim.PatternY)
					{//  �S�p�^�[�����񂵂��Ȃ��
						m_Water[i].Anim.Pattern = 0;				//  �A�j���[�V�����p�^�[�����̏�����
						if (!m_Water[i].AnimLoop)
						{//  ���[�v�ł͂Ȃ����
							m_Water[i].Flag = false;
						}
					}
				}
			}

			//  ���_���̐ݒ�
			SetVertex(i);
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CWater::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CWater::Draw(void)
{
	CMode *pMode = CManager::GetMode();

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//  ���e�X�g���s��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  ���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  ���e�X�g���i�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  ���Q�ƒl

	//  �Q�[�����[�h�̍X�V����
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		//  ���Z�����i�A���t�@�u�����h�j
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//  SRC(���ꂩ��`�悷�鑤)�{DEST(���ɕ`�悳��Ă鑤)
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//  SRC�𔼓�����������
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//  DEST�����̂܂ܕ`�悷��
	}
	////  �y�o�b�t�@�֎~
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int i = 0; i < nWater_Anim_Max; i++)
	{
		if (m_Water[i].Flag)
		{
			//  ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_Water[i].Matrix.World);

			//  �X�P�[���𔽉f
			D3DXMatrixScaling( &m_Water[i].Matrix.Scl, m_Water[i].Scl.x, m_Water[i].Scl.y, m_Water[i].Scl.z );
			D3DXMatrixMultiply( &m_Water[i].Matrix.World, &m_Water[i].Matrix.World, &m_Water[i].Matrix.Scl );

			//  ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &m_Water[i].Matrix.Rot, m_Water[i].Rot.y, m_Water[i].Rot.x, m_Water[i].Rot.z );
			D3DXMatrixMultiply( &m_Water[i].Matrix.World, &m_Water[i].Matrix.World, &m_Water[i].Matrix.Rot );

			//  �ʒu�𔽉f
			D3DXMatrixTranslation( &m_Water[i].Matrix.Trans, m_Water[i].Pos.x, m_Water[i].Pos.y, m_Water[i].Pos.z );
			D3DXMatrixMultiply( &m_Water[i].Matrix.World, &m_Water[i].Matrix.World, &m_Water[i].Matrix.Trans );

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_Water[i].Matrix.World);

			//  �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(m_Water[i].WaterType));

			if (m_Water[i].Size.z == 0.0f)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}

			//  �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);

			if (m_Water[i].Size.z == 0.0f)	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
	}

	//  ���e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//  �^�C�g�����[�h�̍X�V����
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		//  �ʏ�u�����h
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���f�X�e�B�l�[�V�����J���[�̎w��
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CWater::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CWater::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nWater_Anim_Max,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,					//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,					//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL							//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nWater_Anim_Max; i++, pVtx+=nNumVertex)
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_Water[i].Size.x * 0.5f, m_Water[i].Size.y * 0.5f, m_Water[i].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Water[i].Size.x * 0.5f, m_Water[i].Size.y * 0.5f, m_Water[i].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Water[i].Size.x * 0.5f, -m_Water[i].Size.y * 0.5f, -m_Water[i].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Water[i].Size.x * 0.5f, -m_Water[i].Size.y * 0.5f, -m_Water[i].Size.z * 0.5f);

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
//	�֐���:	void CEffect::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CWater::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, EFFECT_TYPE WaterType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend)
{
	int nCnt = 3;
	float fRot = D3DX_PI / 3.0f;

	for (int i = 0; i < nWater_Anim_Max; i++)
	{
		if (!m_Water[i].Flag)
		{
			m_Water[i].Pos = pos;
			m_Water[i].Rot = rot;
			m_Water[i].Size = size;
			m_Water[i].WaterType = WaterType;
			m_Water[i].AnimLoop = bAnimLoop;
			m_Water[i].Anim.PatternX = m_InitAnim[m_Water[i].WaterType].PatternX;
			m_Water[i].Anim.PatternY = m_InitAnim[m_Water[i].WaterType].PatternY;
			m_Water[i].Anim.Frame = m_InitAnim[m_Water[i].WaterType].Frame;
			m_Water[i].Flag = true;
			m_Water[i].AlphaTest = AlphaTest;
			m_Water[i].AlphaBlend = AlphaBlend;

			if (WaterType != EFFECT_WATER_IMPACT)
			{
				break;
			}
			else
			{
				nCnt--;
				m_Water[i].Rot.y += fRot * (float)nCnt;
				if (nCnt <= 0)
				{
					break;
				}
			}
			
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CWater::SetVertex
//	����:	int nID
//	�߂�l:	�Ȃ�
//	����:	���_���̐ݒ�
//------------------------------------------------------------------------------
void CWater::SetVertex(int nID)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	if (m_Water[nID].WaterType == EFFECT_WATER_IMPACT)
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.7f, m_Water[nID].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.7f, m_Water[nID].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.3f, -m_Water[nID].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.3f, -m_Water[nID].Size.z * 0.5f);
	}
	else
	{
		//  ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.5f, m_Water[nID].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.5f, m_Water[nID].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.5f, -m_Water[nID].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.5f, -m_Water[nID].Size.z * 0.5f);
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CWater::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CWater::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
{
	D3DXVECTOR2 TexAdjust;				//  �e�N�X�`�������W��
	int nPatternAnimX, nPatternAnimY;	//  �A�j���[�V�����p�^�[�����i�[����

	TexAdjust.x = 1.0f / float(nPatternX);
	TexAdjust.y = 1.0f / float(nPatternY);

	if (nPatternX == 1)
	{//  ���������p�^�[�����P�Ȃ�΁A�e�N�X�`��X���W�ς�炸�̐ݒ�
		nPatternAnimX = 1;
	}
	else
	{
		nPatternAnimX = nPatternAnim;
	}

	if (nPatternY == 1)
	{//  �����c���p�^�[�����P�Ȃ�΁A�e�N�X�`��Y���W�ς�炸�̐ݒ�
		nPatternAnimY = 0;
	}
	else
	{
		nPatternAnimY = nPatternAnim;
	}
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[1].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[2].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));
	pVtx[3].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}