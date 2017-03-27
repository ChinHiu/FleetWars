/*------------------------------------------------------------------------------
|	�^�C�g���F		�J�[�\���̏���
|	�t�@�C�����F	cursor.cpp
|	�쐬�ҁF		AT12A244 33 CHIN HIU
|	�쐬���F		2015/11/21
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�X�V����:
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "input.h"
#include "cursor.h"

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CCursor::CCursor
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CCursor::CCursor()
{
	m_VertexBuffer = NULL;			//  ���_�o�b�t�@�ւ̃|�C�� 
	m_TextureBuffer = NULL;					//  �e�N�X�`���ւ̃|�C���^
}

//------------------------------------------------------------------------------
//	�֐���:	CScene::~CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CCursor::~CCursor()
{
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CCursor::Init
//	����:	�Ȃ�
//	�߂�l:	E_FAIL���Ə��������s�AS_OK���Ə���������
//	����:	����������
//------------------------------------------------------------------------------
void CCursor::Init( void )
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �J�[�\�����g�p�ݒ�
	m_Flag = true;
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(30.0f, 0.0f, 30.0f);
	/*m_Anim.PatternX = 8;
	m_Anim.PatternY = 4;
	m_Anim.Pattern = 0;
	m_Anim.Frame = 2;
	m_Anim.Cnt = 0;*/

	//  �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
								pDevice,
								CURSOR3D_TEXTURE_FILE,	//  �e�N�X�`���t�@�C���ʒu
								&m_TextureBuffer				//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	//  ���_���̍쐬
	MakeVertex( pDevice );
}

//------------------------------------------------------------------------------
//	�֐���:	void CCursor::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CCursor::Uninit(void)
{
	//  �e�N�X�`���o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);

	//  ���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_TextureBuffer);
}

void CCursor::Update(void)
{
	//if (m_Flag == true)
	//{
	//	if (m_Anim.PatternX != 1 && m_Anim.PatternY != 1)
	//	{//  ���p�^�[���Əc�p�^�[�����P�ł͂Ȃ���΁A�e�N�X�`���A�j���[�V�����������s��
	//		m_Anim.Cnt++;									//  �A�j���[�V�����J�E���g

	//		if (m_Anim.Cnt == m_Anim.Frame)
	//		{//  ���t���[�����ƂɍX�V
	//			m_Anim.Cnt = 0;									//  �A�j���[�V�����J�E���g�̏�����
	//			m_Anim.Pattern++;								//  �A�j���[�V�������݃p�^�[�����X�V

	//			//  �e�N�X�`�����W�̐ݒ�
	//			SetTexture(m_Anim.Pattern, m_Anim.PatternX, m_Anim.PatternY);

	//			if (m_Anim.Pattern == m_Anim.PatternX * m_Anim.PatternY)
	//			{//  �S�p�^�[�����񂵂��Ȃ��
	//				m_Anim.Pattern = 0;							//  �A�j���[�V�����p�^�[�����̏�����
	//			}
	//		}
	//	}
	//}
}

//------------------------------------------------------------------------------
//	�֐���:	void CCursor::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CCursor::Draw(void)
{
	//if (m_Flag == true)
	//{

	//	//  �f�o�C�X���擾
	//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	//	pDevice->SetStreamSource(0, m_VtxBuffer, 0, sizeof(VERTEX_3D));

	//	//  ���_�t�H�[�}�b�g�̐ݒ�
	//	pDevice->SetFVF(FVF_VERTEX_3D);

	//	//���[���h�}�g���b�N�X�̏�����
	//	D3DXMatrixIdentity(&m_Matrix.World);

	//	//�X�P�[���𔽉f
	//	D3DXMatrixScaling
	//	(
	//		&m_Matrix.Scl,
	//		m_Scl.x,
	//		m_Scl.y,
	//		m_Scl.z
	//	);
	//	D3DXMatrixMultiply
	//	(
	//		&m_Matrix.World,
	//		&m_Matrix.World,
	//		&m_Matrix.Scl
	//	);

	//	//��]�𔽉f
	//	D3DXMatrixRotationYawPitchRoll
	//	(
	//		&m_Matrix.Rot,
	//		m_Rot.y,
	//		m_Rot.x,
	//		m_Rot.z
	//	);
	//	D3DXMatrixMultiply
	//	(
	//		&m_Matrix.World,
	//		&m_Matrix.World,
	//		&m_Matrix.Rot
	//	);

	//	//�ʒu�𔽉f
	//	D3DXMatrixTranslation
	//	(
	//		&m_Matrix.Trans,
	//		m_Pos.x,
	//		m_Pos.y,
	//		m_Pos.z
	//	);
	//	D3DXMatrixMultiply
	//	(
	//		&m_Matrix.World,
	//		&m_Matrix.World,
	//		&m_Matrix.Trans
	//	);

	//	//���[���h�}�g���b�N�X��ݒ�
	//	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	//	pDevice->SetStreamSource(0, m_VtxBuffer, 0, sizeof(VERTEX_3D));

	//	//���_�t�H�[�}�b�g�̐ݒ�
	//	pDevice->SetFVF(FVF_VERTEX_3D);

	//	//�e�N�X�`���̐ݒ�
	//	pDevice->SetTexture(0, m_TexBuffer);

	//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	////  ���Z�����i�A���t�@�u�����h�j
	//	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//  SRC(���ꂩ��`�悷�鑤)�{DEST(���ɕ`�悳��Ă鑤)
	//	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//  SRC�𔼓�����������
	//	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//  DEST�����̂܂ܕ`�悷��

	//	//  ���e�X�g���s��
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  ���e�X�g�̗L����
	//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  ���e�X�g���i�
	//	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  ���Q�ƒl

	//	//  �y�o�b�t�@�֎~
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	//	//  �|���S���̕`��
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4, 2);

	//	
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	//	//  �ʏ�u�����h
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//���\�[�X�J���[�̎w��
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���f�X�e�B�l�[�V�����J���[�̎w��

	//	//  ���e�X�g���s��Ȃ�
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  ���e�X�g������

	//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//}
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CCursor::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���̍쐬
//------------------------------------------------------------------------------
HRESULT CCursor::MakeVertex( LPDIRECT3DDEVICE9 pDevice )
{
	//���_�o�b�t�@���m��
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,						//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,						//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL								//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);

	//  �@���̐ݒ�
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//  ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CCursor::SetVertex
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���_���W�ݒ�
//------------------------------------------------------------------------------/
void CCursor::SetVertex(void)
{
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CCursor::Set
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�J�[�\���̐ݒ�
//------------------------------------------------------------------------------/
void CCursor::SetPosition(D3DXVECTOR3 pos)
{
	if( m_Flag == true )
	{
		//  �ʒu��ݒ�
		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Pos.z = pos.z;
	}
}

D3DXVECTOR3 *CCursor::GetPosition(void)
{
	return &m_Pos;
}


//------------------------------------------------------------------------------
//	�֐���:	void CScene3D::SetTexture
//	����:	int nPatternAnim, int nPatternX, int nPatternY 
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CCursor::SetTexture(int nPatternAnim, int nPatternX, int nPatternY)
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

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[1].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[2].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));
	pVtx[3].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}