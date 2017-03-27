//------------------------------------------------------------------------------
//	�^�C�g���F		���f���̊֐�
//	�t�@�C�����F	model.cpp
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
#include "scene.h"
#include "model.h"
#include "manager.h"

//------------------------------------------------------------------------------
//	�֐���:	CModel::CModel
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CModel::CModel()
{
	m_ModelData	= NULL;
	m_Parent	= NULL;
	m_SizeFVF	=
	m_NumVertex = 0;
	m_Pos		=
	m_Rot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bBroken	= false;
}

//------------------------------------------------------------------------------
//	�֐���:	CModel::~CModel
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�f�X�g���N�^
//------------------------------------------------------------------------------
CModel::~CModel()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CModel *CModel::Create
//	����:	MODEL_TYPE	Model_Type	//  ���f���^�C�v
//			MODEL_PARTS Model_Parts	//  ���f���p�[�c
//			D3DXVECTOR3 pos			//  �ʒu
//			D3DXVECTOR3 rot			//  ��]
//	�߂�l:	*pModel
//	����:	���f���𐶐�
//------------------------------------------------------------------------------
CModel *CModel::Create(MODEL_TYPE Model_Type, MODEL_PARTS Model_Parts, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel;
	pModel = new CModel;

	pModel->m_Pos			= pos;					//  �ʒu���
	pModel->m_Rot			= rot;					//  ��]
	pModel->m_ModelType		= Model_Type;			//  ���f���^�C�v
	pModel->m_ModelParts	= Model_Parts;			//  ���f���p�[�c

	//  ������
	pModel->Init();

	return pModel;
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CModel::Init(void)
{
	//  �p�[�c���ƂɃ��f���f�[�^���擾
	m_ModelData = CManager::GetModeData(m_ModelParts);
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CModel::Uninit(void)
{
	m_ModelData = NULL;		//  ���f���f�[�^
	m_Parent	= NULL;		//  �e���
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CModel::Update(void)
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CModel::Draw(void)
{
	D3DXMATERIAL	*pMat;
	D3DMATERIAL9	matDef;
	D3DXMATRIX		pParentMatrix;

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Matrix.World);

	//  �e�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pParentMatrix);

	//  �e�̐ݒ�
	if (m_Parent != NULL)	pParentMatrix = m_Parent->GetWorldMatrix();
	else					pDevice->GetTransform(D3DTS_WORLD, &pParentMatrix);

	//  �X�P�[���𔽉f
	D3DXMatrixScaling( &m_Matrix.Scl, m_Scl.x, m_Scl.y, m_Scl.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl );

	//  ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll( &m_Matrix.Rot, m_Rot.y, m_Rot.x, m_Rot.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot );

	//  �ʒu�𔽉f
	D3DXMatrixTranslation( &m_Matrix.Trans, m_Pos.x, m_Pos.y, m_Pos.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans );

	//  �e�̃}�g���b�N�X�𔽉f
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &pParentMatrix );
	
	//  ���[���h�}�g���b�N�X��ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//  ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL *)m_ModelData->BufferMat->GetBufferPointer();

	for (int i = 0; i < (int)m_ModelData->NumMat; i++)
	{
		//  �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//  �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::GetModelTextureBuffer(m_ModelType, m_bBroken));

		//  ���b�V���̕`��
		m_ModelData->Mesh->DrawSubset(i);
	}

	//  �}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//------------------------------------------------------------------------------
//	�֐���:	D3DXMATRIX CModel::GetWorldMatrix(void)
//	����:	�Ȃ�
//	�߂�l:	m_Matrix.World
//	����:	���[���h�}�g���b�N�X���擾
//------------------------------------------------------------------------------
D3DXMATRIX CModel::GetWorldMatrix(void)
{
	return m_Matrix.World;
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::SetParent
//	����:	CModel *model
//	�߂�l:	�Ȃ�
//	����:	�e��ݒ�
//------------------------------------------------------------------------------
void CModel::SetParent(CModel *model)
{
	m_Parent = model;
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::SetPosition
//	����:	D3DXVECTOR3 m_Pos
//	�߂�l:	�Ȃ�
//	����:	�ʒu��ݒ�
//------------------------------------------------------------------------------
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//------------------------------------------------------------------------------
//	�֐���:	void CModel::SetRotation
//	����:	D3DXVECTOR3 m_Rot
//	�߂�l:	�Ȃ�
//	����:	��]��ݒ�
//------------------------------------------------------------------------------
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

void CModel::SetBroken(bool bFlag)
{
	m_bBroken = bFlag;
}