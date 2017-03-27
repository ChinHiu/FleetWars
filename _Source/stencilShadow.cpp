//------------------------------------------------------------------------------
//	�^�C�g���F		�X�e���V���V���h�E�̊֐�
//	�t�@�C�����F	stencil.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/10
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "stencilShadow.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "camera.h"
#include "meshField.h"
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
//	�֐���:	CStencilShadow::CStencilShadow
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CStencilShadow::CStencilShadow()
{
	m_Pos =
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_bFlag = false;
}

//------------------------------------------------------------------------------
//	�֐���:	CStencilShadow::~CStencilShadow
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CStencilShadow::~CStencilShadow()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CStencilShadow *CStencilShadow::Create
//	����:	�Ȃ�
//	�߂�l:	sceneX
//	����:	X�̐���
//------------------------------------------------------------------------------
CStencilShadow *CStencilShadow::Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos)
{
	CStencilShadow *pStencilShadow;

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pStencilShadow = new CStencilShadow;
	pStencilShadow->m_Pos = pos;	//  �ʒu���
	pStencilShadow->m_ModelType = Model_Type;

	pStencilShadow->Init();
	return pStencilShadow;
}

//------------------------------------------------------------------------------
//	�֐���:	void CStencilShadow::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CStencilShadow::Init(void)
{
	CMode *pMode = CManager::GetMode();

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �^�C�g�����[�h�̍X�V����
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		switch (m_ModelType)
		{
		case MODEL_GORSHKOV:
			m_ModelFile = TITLE_GORSHKOV_SHADOW_FILE;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_ModelType)
		{
		case MODEL_GORSHKOV:
			m_ModelFile = GORSHKOV_SHADOW_FILE;
			break;
		case MODEL_HAMINA:
			m_ModelFile = HAMINA_SHADOW_FILE;
		default:
			break;
		}
	}

	//  X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		m_ModelFile,		//  �ǂݍ��ރt�@�C���ʒu
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMat,			//  �}�e���A�����
		NULL,
		&m_NumMat,			//  �}�e���A���̐�
		&m_Mesh				//  ���b�V�����
	);

	Make2DVertex(pDevice);

	m_bFlag = true;
}

//------------------------------------------------------------------------------
//	�֐���:	void CStencilShadow::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CStencilShadow::Uninit(void)
{
	//  ���b�V�����̊J��
	SAFE_RELEASE(m_Mesh);

	//  �}�b�g�o�b�t�@�̊J��
	SAFE_RELEASE(m_BuffMat);

	//  ���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	�֐���:	void CStencilShadow::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CStencilShadow::Update(void)
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CStencilShadow::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CStencilShadow::Draw(void)
{
	if (m_bFlag)
	{
		D3DXMATERIAL	*pMat;
		D3DMATERIAL9	matDef;

		//  �f�o�C�X���擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//  ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_Matrix.World);

		//  �X�P�[���𔽉f
		D3DXMatrixScaling( &m_Matrix.Scl, m_Scl.x, m_Scl.y, m_Scl.z );
		D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl );

		//  ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &m_Matrix.Rot, m_Rot.y, m_Rot.x, m_Rot.z );
		D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot );

		//  �ʒu�𔽉f
		D3DXMatrixTranslation( &m_Matrix.Trans, m_Pos.x, m_Pos.y, m_Pos.z );
		D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans );

		//  ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

		//  ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);
		pMat = (D3DXMATERIAL *)m_BuffMat->GetBufferPointer();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{
			pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//  ���b�V���̕`��
			m_Mesh->DrawSubset(nCntMat);

			pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

			//  ���b�V���̕`��
			m_Mesh->DrawSubset(nCntMat);
		}

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
		pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

		//  ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//  �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//  �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * nNumVertex, nNumPolygon);

		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		//  �}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

HRESULT CStencilShadow::Make2DVertex(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * nNumVertex,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,				//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL							//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pScreenSize->x, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, pScreenSize->y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pScreenSize->x, pScreenSize->y, 0.0f);

	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	//  ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f);

	//  �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();

	return S_OK;
}