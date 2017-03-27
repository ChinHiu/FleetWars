//------------------------------------------------------------------------------
//	�^�C�g���F		Obb�e�X�g�̊֐�
//	�t�@�C�����F	ObbTest.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/01
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "ObbTest.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
//#include "game.h"
#include "player.h"

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------
const int nCubeFaceNum = 6;

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CObbTest::CObbTest
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CObbTest::CObbTest(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  ���_�o�b�t�@�ւ̃|�C���g
#ifdef _DEBUG
	m_bObbTest = true;
#else
	m_bObbTest = false;
#endif
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
}

//------------------------------------------------------------------------------
//	�֐���:	CObbTest::~CObbTest
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CObbTest::~CObbTest()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CObbTest *CObbTest::Create
//	����:	�Ȃ�
//	�߂�l:	pEffect
//	����:	�G�t�F�N�g�̐���
//------------------------------------------------------------------------------
CObbTest *CObbTest::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CObbTest *pObbTest;

	//  �C���X�^���X����
	pObbTest = new CObbTest;

	//  �l����
	pObbTest->m_ObbTest.Pos = pos;
	pObbTest->m_ObbTest.Rot = rot;
	pObbTest->m_ObbTest.Size = size;
	pObbTest->m_ObbTest.Flag = true;

	//  ������
	pObbTest->Init();

	return pObbTest;
}

//------------------------------------------------------------------------------
//	�֐���:	void CObbTest::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CObbTest::Init(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_���̍쐬
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	�֐���:	void CObbTest::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CObbTest::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CObbTest::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CObbTest::Update(void)
{
#ifdef _DEBUG

	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F4))	m_bObbTest = m_bObbTest ? false : true;

	SetVertex();
#endif
}

//------------------------------------------------------------------------------
//	�֐���:	void CObbTest::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CObbTest::Draw(void)
{
	if (m_bObbTest)
	{
		//  �f�o�C�X���擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
		pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

		//  ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//  �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//  ���C�g������
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//  �t�H�O������
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

		if (m_bObbTest)
		{
			//  ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_ObbTest.Matrix.World);

			//  �X�P�[���𔽉f
			D3DXMatrixScaling(&m_ObbTest.Matrix.Scl, m_ObbTest.Scl.x, m_ObbTest.Scl.y, m_ObbTest.Scl.z);
			D3DXMatrixMultiply(&m_ObbTest.Matrix.World, &m_ObbTest.Matrix.World, &m_ObbTest.Matrix.Scl);

			//  ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&m_ObbTest.Matrix.Rot, m_ObbTest.Rot.y, m_ObbTest.Rot.x, m_ObbTest.Rot.z);
			D3DXMatrixMultiply(&m_ObbTest.Matrix.World, &m_ObbTest.Matrix.World, &m_ObbTest.Matrix.Rot);

			//  �ʒu�𔽉f
			D3DXMatrixTranslation(&m_ObbTest.Matrix.Trans, m_ObbTest.Pos.x, m_ObbTest.Pos.y, m_ObbTest.Pos.z);
			D3DXMatrixMultiply(&m_ObbTest.Matrix.World, &m_ObbTest.Matrix.World, &m_ObbTest.Matrix.Trans);

			//  ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_ObbTest.Matrix.World);

			for (int i = 0; i < nCubeFaceNum; i++)
			{
				//  �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
			}

		}

		//  ���C�g�L����
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		//  �t�H�O�L����
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CObbTest::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CObbTest::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nCubeFaceNum,		//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,									//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,										//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,									//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,									//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL												//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);

	pVtx[4].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[5].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[6].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[7].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);

	pVtx[8].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[9].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[10].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[11].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);

	pVtx[12].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[13].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[14].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[15].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);

	pVtx[16].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[17].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[18].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[19].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);

	pVtx[20].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[21].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[22].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[23].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);

	for (int i = 0; i < nNumVertex * nCubeFaceNum; i += nNumVertex, pVtx += nNumVertex)
	{
		//�@���̐ݒ�
		pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

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

void CObbTest::SetVertex(void)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nNumVertex * nCubeFaceNum; i += nNumVertex, pVtx += nNumVertex)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_Col;
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

void CObbTest::SetCol(D3DXCOLOR col)
{
	m_Col = col;
};

void CObbTest::SetPos(D3DXVECTOR3 pos)
{
	m_ObbTest.Pos = pos;
};

void CObbTest::SetRot(D3DXVECTOR3 rot)
{
	m_ObbTest.Rot = rot;
};