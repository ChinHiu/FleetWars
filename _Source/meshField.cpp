//------------------------------------------------------------------------------
//	�^�C�g���F		���b�V���t�B�[���h�̊֐�
//	�t�@�C�����F	meshField.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/24
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "meshField.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------
const int nNum_Null_Vertex = 2;		//  �k�ރ|���S���̒��_��

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CMeshField::CMeshField
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CMeshField::CMeshField(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_TextureBuffer = NULL;
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;
	m_PositionBuffer = NULL;

	m_VertexPos = NULL;
	m_Nor = NULL;

	m_Pos =
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//------------------------------------------------------------------------------
//	�֐���:	CMeshField::~CMeshField
//	����:	�Ȃ�
//	�߂�l:	CMeshField
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CMeshField::~CMeshField()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CMeshField *CMeshField::LoadMap
//	����:	int nPriority, OBJECT_TYPE Object_Type		//  �v���C�I���e�B�ԍ��A�I�u�W�F�N�g�^�C�v
//			MESH_TYPE Mesh_Type							//  ���b�V���^�C�v
//			LPCSTR MAP_FILE, LPCSTR TEXTURE_FILE		//	�}�b�v�t�@�C���p�X�A�e�N�X�`���t�@�C���p�X
//			bool SeamlessTex, float SeamlessScl			//  �V�����[�X�e�N�X�`���g�p���ǂ����A�V�����[�X�K��
//	�߂�l:	pField
//	����:	�t�B�[���h�̐���
//------------------------------------------------------------------------------
CMeshField *CMeshField::LoadMap(MESH_TYPE Mesh_Type, LPCSTR MAP_FILE, LPCSTR TEXTURE_FILE, bool SeamlessTex, float SeamlessScl)
{
	CMeshField	*pField;
	FILE		*fp;

	char		str[256];
	int			nCntPos;

	pField = new CMeshField();

	nCntPos = 0;

	//  �f�[�^�̃G�N�X�|�[�g
	fp = fopen(MAP_FILE, "r");

	while (true)
	{
		fscanf(fp, "%s", str);
		if (feof(fp) != 0)	break;

		//  ���_��
		if (strcmp(str, "VtxNum") == 0)
		{
			fscanf(
				fp,
				"%d %d %d",
				&pField->m_Mesh.WidthNum,
				&pField->m_Mesh.HeightNum,
				&pField->m_Mesh.VertexNum
			);
		}

		if (strcmp(str, "Size") == 0)
		{
			fscanf(
				fp,
				"%f %f",
				&pField->m_Size.x,
				&pField->m_Size.z
			);
		}
	}

	pField->m_VertexPos = new D3DXVECTOR3[pField->m_Mesh.VertexNum];
	pField->m_Nor		= new D3DXVECTOR3[pField->m_Mesh.VertexNum];
	pField->m_NorType	= new NORMAL_TYPE[pField->m_Mesh.VertexNum];

	fseek(fp, 0, SEEK_SET);

	while (true)
	{
		fscanf(fp, "%s", str);
		if (feof(fp) != 0)	break;

		if (strcmp(str, "Pos") == 0)
		{
			fscanf(
				fp,
				"%f %f %f",
				&pField->m_VertexPos[nCntPos].x,
				&pField->m_VertexPos[nCntPos].y,
				&pField->m_VertexPos[nCntPos].z
			);
			nCntPos++;
		}
	}

	//  Mesh���
	pField->m_Mesh.IndexNum = pField->m_Mesh.VertexNum + (pField->m_Mesh.WidthNum + 2) * (pField->m_Mesh.HeightNum - 2);
	pField->m_Mesh.SeamlessTex = SeamlessTex;
	pField->m_Mesh.SeamlessScl = SeamlessScl;
	pField->m_Mesh.Type = Mesh_Type;

	//  �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		TEXTURE_FILE,										//  �e�N�X�`���t�@�C���ʒu
		&pField->m_TextureBuffer							//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	//  ���b�V���̏�����
	pField->Init();

	return pField;

	fclose(fp);
}

//------------------------------------------------------------------------------
//	�֐���:	CMeshField *CMeshField::Create
//	����:	int nPriority, OBJECT_TYPE Object_Type		//  �v���C�I���e�B�ԍ��A�I�u�W�F�N�g�^�C�v
//			MESH_TYPE Mesh_Type, LPCSTR TEXTURE_FILE	//  ���b�V���^�C�v�A�e�N�X�`���t�@�C���p�X
//			D3DXVECTOR3 pos, D3DXVECTOR3 size			//  �ʒu�A�T�C�Y
//			int WidthNum, int HeightNum					//  ���̒��_���A�c�̒��_��
//			bool SeamlessTex, float SeamlessScl			//  �V�����[�X�e�N�X�`���g�p���ǂ����A�V�����[�X�K��
//	�߂�l:	pField
//	����:	�t�B�[���h�̐���
//------------------------------------------------------------------------------
CMeshField *CMeshField::Create(MESH_TYPE Mesh_Type, LPCSTR TEXTURE_FILE, D3DXVECTOR3 pos, D3DXVECTOR3 size, int WidthNum, int HeightNum, bool SeamlessTex, float SeamlessScl)
{
	int nVertexNum = WidthNum * HeightNum;

	CMeshField	*pField;

	pField = new CMeshField();

	pField->m_VertexPos = new D3DXVECTOR3[nVertexNum];
	pField->m_Nor		= new D3DXVECTOR3[nVertexNum];
	pField->m_NorType	= new NORMAL_TYPE[nVertexNum];

	//  Mesh���
	pField->m_Mesh.WidthNum		= WidthNum;
	pField->m_Mesh.HeightNum	= HeightNum;
	pField->m_Mesh.VertexNum	= nVertexNum;
	pField->m_Mesh.IndexNum		= nVertexNum + (WidthNum + 2) * (HeightNum - 2);
	pField->m_Mesh.SeamlessTex	= SeamlessTex;
	pField->m_Mesh.SeamlessScl	= SeamlessScl;
	pField->m_Mesh.Type			= Mesh_Type;

	pField->m_Pos	= pos;
	pField->m_Size	= size;

	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		TEXTURE_FILE,								//  �e�N�X�`���t�@�C���ʒu
		&pField->m_TextureBuffer					//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	//  ���_���W���Z�o
	pField->CalculateVertex();

	//  ���b�V���̏�����
	pField->Init();

	return pField;
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CMeshField::Init(void)
{
	//  �f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �@���^�C�v���Z�o
	CalculateNormalType();

	//  �@�������Z�o
	CalculateNormal();

	//  ���_���̍쐬
	MakeVertex(pDevice);

	//  �C���f�b�N�X���̍쐬
	MakeIndex(pDevice);

	//  �g�Q�̏�����
	if (m_Mesh.Type == MESH_SEA)	WaveInit();
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CMeshField::Uninit(void)
{
	//  �e�N�X�`���o�b�t�@���J��
	SAFE_RELEASE(m_TextureBuffer);

	//  ���̒��_�o�b�t�@�ւ��J��
	SAFE_RELEASE(m_PositionBuffer);

	//  ���_�o�b�t�@���J��
	SAFE_RELEASE(m_VertexBuffer);

	//  �C���f�b�N�X�o�b�t�@���J��
	SAFE_RELEASE(m_IndexBuffer);

	delete[] m_VertexPos;
	delete[] m_NorType;
	delete[] m_Nor;
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CMeshField::Update(void)
{
	//  �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �L�[�{�[�h�̎擾
	CKeyboard	*pKeyboard = CManager::GetInput()->GetKeyboard();

	//  �}�E�X�̎擾
	CMouse		*pMouse = CManager::GetInput()->GetMouse();

	if (m_Mesh.Type == MESH_SEA)	WaveUpdate();
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CMeshField::Draw(void)
{
	//  �f�o�C�X�̃Q�b�^�[
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

	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);				//  ���[���h�}�g���b�N�X��ݒ�
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetIndices(m_IndexBuffer);									//  �C���f�b�N�X�o�b�t�@���o�C���h����
	pDevice->SetFVF(FVF_VERTEX_3D);										//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, m_TextureBuffer);							//  �e�N�X�`���̐ݒ�

	//  �`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_Mesh.VertexNum,		//  �����_��
		0,
		m_Mesh.IndexNum - 2		//  �v���~�e�B�u��
	);
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::CalculateVertex
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���_���W���v�Z
//------------------------------------------------------------------------------
void CMeshField::CalculateVertex(void)
{
	int		nHeightNumHalf;					//  �c���_���̔���
	float	fAdjustX, fAdjustZ;				//  ���S���WX�A���S���WZ�𒲐��̌W��

	nHeightNumHalf = m_Mesh.HeightNum / 2;

	//  �t�B�[���h���S�����_���W�ɂ���W���̐ݒ�
	fAdjustX = m_Mesh.WidthNum % 2 == 0 ? 0.5f : 0.0f;	//  �����_���������Ȃ�0.5f�A���0.0f
	fAdjustZ = m_Mesh.HeightNum % 2 == 0 ? 0.5f : 0.0f; //  �c���_���������Ȃ�0.5f�A���0.0f

	//  �t�B�[���h�̍��W���v�Z
	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		int nCntVertex = i % m_Mesh.WidthNum;

		//  ���_���W�̐ݒ�
		m_VertexPos[i].x = (nCntVertex - m_Mesh.WidthNum / 2 + fAdjustX) * m_Size.x;
		m_VertexPos[i].y = 0.0f;
		m_VertexPos[i].z = (nHeightNumHalf - fAdjustZ) * m_Size.z;

		if (nCntVertex == m_Mesh.WidthNum - 1)
		{
			nHeightNumHalf--;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::CalculateNormalType
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�@���^�C�v���̍쐬
//------------------------------------------------------------------------------
void CMeshField::CalculateNormalType(void)
{
	int nNumLeftTop, nNumRightTop, nNumLeftDown, nNumRightDown;

	nNumLeftTop = 0;
	nNumRightTop = m_Mesh.WidthNum - 1;
	nNumLeftDown = m_Mesh.VertexNum - m_Mesh.WidthNum;
	nNumRightDown = m_Mesh.VertexNum - 1;

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		m_NorType[i] = NONE;		//  �@���^�C�v�̏�����
	}

	m_NorType[nNumLeftTop] = LEFT_TOP;
	m_NorType[nNumRightTop] = RIGHT_TOP;
	m_NorType[nNumLeftDown] = LEFT_DOWN;
	m_NorType[nNumRightDown] = RIGHT_DOWN;

	if (m_Mesh.WidthNum > 2)
	{//  �����_���Q�ȏ�̏ꍇ
	 //  �@���^�C�v����Ӄ^�C�v�ɐݒ�
		for (int i = 1; i < nNumRightTop; i++)
		{
			m_NorType[i] = TOP_SIDE;
		}

		//  �@���^�C�v�����Ӄ^�C�v�ɐݒ�
		for (int i = nNumLeftDown + 1; i < nNumRightDown; i++)
		{
			m_NorType[i] = DOWN_SIDE;
		}

		if (m_Mesh.HeightNum > 2)
		{//  ���Əc���_���Q�ȏ�̏ꍇ
		 //  �@���^�C�v���ݒ�̂𒆉��^�C�v�ɐݒ�
			for (int i = 0; i < m_Mesh.VertexNum; i++)
			{
				m_NorType[i] = m_NorType[i] == NONE ? MIDDLE : m_NorType[i];
			}
		}
	}

	if (m_Mesh.HeightNum > 2)
	{//  �c���_���Q�ȏ�̏ꍇ
	 //  �@���^�C�v�����Ӄ^�C�v�ɐݒ�
		for (int i = m_Mesh.WidthNum; i < nNumLeftDown; i += m_Mesh.WidthNum)
		{
			m_NorType[i] = LEFT_SIDE;
		}

		//  �@���^�C�v���E�Ӄ^�C�v�ɐݒ�
		for (int i = m_Mesh.WidthNum * 2 - 1; i < nNumRightDown; i += m_Mesh.WidthNum)
		{
			m_NorType[i] = RIGHT_SIDE;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CMeshField::MakeNormal
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	�@�����̍쐬
//------------------------------------------------------------------------------
void CMeshField::CalculateNormal(void)
{
	D3DXVECTOR3	Vector[6], Normal[6];

	//  �@�������߂�
	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		switch (m_NorType[i])
		{
		case LEFT_TOP:
			Vector[0] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];

			//  �Q�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1]));
			break;

		case RIGHT_TOP:
			Vector[0] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - 1] - m_VertexPos[i];

			//  �P�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &Normal[0]);
			break;

		case LEFT_DOWN:
			Vector[0] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + 1] - m_VertexPos[i];

			//  �P�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &Normal[0]);
			break;

		case RIGHT_DOWN:
			Vector[0] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];

			//  �Q�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1]));
			break;

		case TOP_SIDE:
			Vector[0] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i - 1] - m_VertexPos[i];

			//  �R�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;

		case DOWN_SIDE:
			Vector[0] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i + 1] - m_VertexPos[i];

			//  �R�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case LEFT_SIDE:
			Vector[0] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];

			//  �R�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case RIGHT_SIDE:
			Vector[0] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];

			//  �R�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  �@�������߂�
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case MIDDLE:
			Vector[0] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[4] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[5] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];

			//  �U�ʂ̖@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);
			D3DXVec3Cross(&Normal[3], &Vector[3], &Vector[4]);
			D3DXVec3Cross(&Normal[4], &Vector[4], &Vector[5]);
			D3DXVec3Cross(&Normal[5], &Vector[5], &Vector[0]);

			//  �@�������߂�
			D3DXVec3Normalize(
				&m_Nor[i],
				&(Normal[0] + Normal[1] + Normal[2] + Normal[3] + Normal[4] + Normal[5])
			);
			break;
		default:
			break;
		}

		//  ���K��
		D3DXVec3Normalize(&m_Nor[i], &m_Nor[i]);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CMeshField::MakeIndex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	�C���f�b�N�X���̍쐬
//------------------------------------------------------------------------------
HRESULT CMeshField::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	int nAdjust = 2;						//  �C���f�b�N�X�o�b�t�@�p�W��
	int nDegTriNum = 0;						//  �k�ގO�p�`���_�̐�
	int	nIdxEvenNum = 0;					//  �C���f�b�N�X���_�ԍ��������̐�(�k�ގO�p�`���_������)

	//  �C���f�b�N�X�o�b�t�@���m��
	if (FAILED(pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * m_Mesh.IndexNum,		//  �C���f�b�N�X�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(���[�h�P��)
		D3DUSAGE_WRITEONLY,					//  �C���f�b�N�X�o�b�t�@�̎g�p�@
		D3DFMT_INDEX16,						//  �g�p����C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED,					//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_IndexBuffer,						//  �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL								//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  �C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	WORD *pIdx;

	//  �C���f�b�N�X�f�[�^�͈̔͂����b�N���A�C���f�b�N�X�o�b�t�@�ւ̃|�C���^���擾
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//  ���_�ԍ����擾(N�^�`��p)
	for (int i = 0; i < m_Mesh.IndexNum; i++)
	{
		//  �k�ރ|���S�����_�ԍ���ݒ�(���s2��)
		if (i == m_Mesh.WidthNum * nAdjust + nDegTriNum)
		{
			if (i % 2 == 0)
			{//  1��
				pIdx[i] = pIdx[i - 1];
				nDegTriNum++;
			}
			else
			{//  2��
				pIdx[i] = m_Mesh.WidthNum + nIdxEvenNum;
				nAdjust += 2;				//  ���̍s�̏k�ރ|���S�����_�ԍ��̌v�Z�p�W����ݒ�
				nDegTriNum++;				//  �k�ރ|���S�����_����1�����Z����
			}
		}

		else if (i % 2 == 0)
		{//  ���_�ԍ��������Ȃ�
			pIdx[i] = m_Mesh.WidthNum + nIdxEvenNum;
			nIdxEvenNum++;
		}

		else
		{//  ���_�ԍ�����Ȃ�
			pIdx[i] = i - nIdxEvenNum - nDegTriNum;
		}
	}

	//  �C���f�b�N�X�f�[�^���A�����b�N����
	m_IndexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CMeshField::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_���̍쐬
//------------------------------------------------------------------------------
HRESULT CMeshField::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	float fAdjustTexY = 0.0f;					//  �e�N�X�`��Y���W���炷�W��									

	//  ���_�o�b�t�@���m��
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_Mesh.VertexNum,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						//  ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,						//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL									//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�o�b�t�@���m��
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(D3DXVECTOR3) * m_Mesh.VertexNum,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						//  ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_PositionBuffer,						//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL									//  NULL�ɐݒ�
	)))
	{
		return E_FAIL;
	}

	D3DXVECTOR3 *pPos;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);
	m_PositionBuffer->Lock(0, 0, (void**)&pPos, 0);

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		int nCntVertex = i % m_Mesh.HeightNum;

		//  ���_���W�̐ݒ�
		pVtx[i].pos =
		pPos[i] = m_VertexPos[i];

		//  �@���̐ݒ�
		pVtx[i].nor = m_Nor[i];

		//  ���F	D3DXCOLOR(0.94f, 0.9f, 0.55f, 1.0f)
		//  ���F	D3DXCOLOR(0.345f, 0.75f, 0.25f, 1.0f)
		//  ��ΐF	D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		//  ���_�J���[�̐ݒ�
		if (m_Mesh.Type == MESH_ISLAND)	pVtx[i].col = D3DXCOLOR(0.345f, 0.75f, 0.25f, 1.0f);
		else							pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//  �e�N�X�`�����W�̐ݒ�
		if (m_Mesh.SeamlessTex)	pVtx[i].tex = D3DXVECTOR2(m_Mesh.SeamlessScl / m_Mesh.WidthNum * (float)nCntVertex, m_Mesh.SeamlessScl / m_Mesh.WidthNum * fAdjustTexY);
		else					pVtx[i].tex = D3DXVECTOR2((float)nCntVertex, fAdjustTexY);

		//  ���͖��s�Ō�̒��_�̏ꍇ
		if (nCntVertex == m_Mesh.WidthNum - 1)	fAdjustTexY++;
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
	m_PositionBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::SetVertex(void)
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���_���̍X�V
//------------------------------------------------------------------------------
void CMeshField::SetVertex(void)
{
	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		//  ���_���W�̐ݒ�
		pVtx[i].pos = m_VertexPos[i];
		pVtx[i].nor = m_Nor[i];
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::WaveInit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�g�̏���������
//------------------------------------------------------------------------------
void CMeshField::WaveInit(void)
{
	CMode *pMode = CManager::GetMode();

#ifdef _DEBUG
	m_WaveID = 0;
#endif

	//  �^�C�g�����[�h�̔g�ݒ�
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		int i = 0;
		m_Wave[i].K = D3DXVECTOR2(1.0f, 1.0f);
		m_Wave[i].A = 3.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.1f;
		m_Wave[i].WaveLength = 1300.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(1.0f, 0.5f);
		m_Wave[i].A = -4.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 1200.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(0.5f, 1.0f);
		m_Wave[i].A = -1.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.3f;
		m_Wave[i].WaveLength = 800.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(0.2f, 1.0f);
		m_Wave[i].A = -0.6f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 600.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;
	}

	//  �Q�[�����[�h�̔g�ݒ�
	else
	{
		int i = 0;
		m_Wave[i].K = D3DXVECTOR2(1.0f, 1.0f);
		m_Wave[i].A = -3.5f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.1f;
		m_Wave[i].WaveLength = 1200.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(-1.0f, 0.5f);
		m_Wave[i].A = 8.5f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.1f;
		m_Wave[i].WaveLength = 1500.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(0.2f, 0.8f);
		m_Wave[i].A = -5.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 2000.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(-0.2f, 1.0f);
		m_Wave[i].A = -0.6f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 500.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::SeaUpdate
//	����:	MESH_TYPE MeshType
//	�߂�l:	�Ȃ�
//	����:	�g�̍X�V
//------------------------------------------------------------------------------
void CMeshField::WaveUpdate(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	D3DXVECTOR2 posXZ = D3DXVECTOR2(0, 0);
	float posY = 0;
	D3DXVECTOR2 posXZDif = D3DXVECTOR2(0, 0);
	float posYDif = 0;
	float temp = 0;

	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 *pVec;
	m_PositionBuffer->Lock(0, 0, (void **)&pVec, 0);

#ifdef _DEBUG
//	if (pKeyboard->GetTrigger(DIK_TAB))
//	{
//		m_WaveID++;
//		if (m_WaveID >= nWaveMax)
//		{
//			m_WaveID = 0;
//		}
//	}
//
//	if (pKeyboard->GetTrigger(DIK_LSHIFT))
//	{ 
//		if (pKeyboard->GetTrigger(DIK_1))		m_Wave[m_WaveID].K.x += 0.01f;
//		if (pKeyboard->GetTrigger(DIK_2))		m_Wave[m_WaveID].K.y += 0.01f;
//		if (pKeyboard->GetTrigger(DIK_3))		m_Wave[m_WaveID].Omega += 0.1f;
//		if (pKeyboard->GetTrigger(DIK_4))		m_Wave[m_WaveID].OmegaT += 0.1f;
//	}
//	else 
//	{ 
//		if (pKeyboard->GetTrigger(DIK_1))		m_Wave[m_WaveID].K.x -= 0.01f;  
//		if (pKeyboard->GetTrigger(DIK_2))		m_Wave[m_WaveID].K.y -= 0.01f;  
//		if (pKeyboard->GetTrigger(DIK_3))		m_Wave[m_WaveID].Omega -= 0.1f;  
//		if (pKeyboard->GetTrigger(DIK_4))		m_Wave[m_WaveID].OmegaT -= 0.1f;
//	}   
//
//	if (pKeyboard->GetTrigger(DIK_5))			m_Wave[m_WaveID].A += 0.1f; 
//	if (pKeyboard->GetTrigger(DIK_6))			m_Wave[m_WaveID].A -= 0.1f;
//
//	if (pKeyboard->GetTrigger(DIK_7))			m_Wave[m_WaveID].t = 0.0f;
//
//	if (pKeyboard->GetTrigger(DIK_8))
//	{ 
//		m_Wave[m_WaveID].WaveLength += 1.0f;
//		m_Wave[m_WaveID].k = 2.0f * D3DX_PI / m_Wave[m_WaveID].WaveLength;
//		D3DXVec2Normalize(&m_Wave[m_WaveID].K, &m_Wave[m_WaveID].K);
//		m_Wave[m_WaveID].K *= m_Wave[m_WaveID].k;
//		m_Wave[m_WaveID].testAk = m_Wave[m_WaveID].A * m_Wave[m_WaveID].k;
//	}  
//	if (pKeyboard->GetTrigger(DIK_9))
//	{ 
//		m_Wave[m_WaveID].WaveLength -= 1.0f;
//		m_Wave[m_WaveID].k = 2.0f * D3DX_PI / m_Wave[m_WaveID].WaveLength;
//		D3DXVec2Normalize(&m_Wave[m_WaveID].K, &m_Wave[m_WaveID].K);
//		m_Wave[m_WaveID].K *= m_Wave[m_WaveID].k;
//		m_Wave[m_WaveID].testAk = m_Wave[m_WaveID].A * m_Wave[m_WaveID].k;
//	} 
//	if (pKeyboard->GetTrigger(DIK_0))
//	{ 
//		m_Wave[m_WaveID].k = 2.0f * D3DX_PI / m_Wave[m_WaveID].WaveLength;
//		D3DXVec2Normalize(&m_Wave[m_WaveID].K, &m_Wave[m_WaveID].K);
//		m_Wave[m_WaveID].K *= m_Wave[m_WaveID].k;
//		m_Wave[m_WaveID].testAk = m_Wave[m_WaveID].A * m_Wave[m_WaveID].k;
//	}
#endif

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		posXZ = D3DXVECTOR2(pVec[i].x, pVec[i].z);
		posY = pVec[i].y;

		for (int j = 0; j < nWaveMax; j++)
		{
			// x = x0 - (K / k)*Asin(K*x0 - ��t)
			// y = Acos(K*x0 - ��t)
			temp = D3DXVec2Dot(&m_Wave[j].K, &posXZ) - m_Wave[j].Omega * m_Wave[j].t;

			//  �ψʗʂ��Z�o
			posXZDif += (m_Wave[j].K / m_Wave[j].k) * m_Wave[j].A * sinf(temp);
			posYDif += m_Wave[j].A * cosf(temp);
		}

		//  ���W���X�V
		m_VertexPos[i].x = posXZ.x - posXZDif.x;
		m_VertexPos[i].z = posXZ.y - posXZDif.y;
		m_VertexPos[i].y = posY - posYDif;
	}

	for (int k = 0; k < nWaveMax; k++)
	{
		m_Wave[k].t += m_Wave[k].OmegaT;
	}

	m_PositionBuffer->Unlock();

	//  �@�������Z�o
	CalculateNormal();

	SetVertex();
}

//------------------------------------------------------------------------------
//	�֐���:	void CMeshField::CheckVertex
//	����:	D3DXVECTOR3 pos
//	�߂�l:	�Ȃ�
//	����:	���݂��钸�_�ԍ��̃`�F�b�N
//------------------------------------------------------------------------------
int CMeshField::CheckVertex(D3DXVECTOR3 pos)
{
	int		nWidthID;		//  �����_�ԍ�
	int		nHeightID;		//  �c���_�ԍ�
	float	fWidthID;		//  �����_�ԍ��ifloat�^�j
	float	fHeightID;		//  �c���_�ԍ��ifloat�^�j
	int		nInVertexID;	//  ���݂��钸�_�ԍ�

	//  �t�B�[���h�͈͓��ł����
	if ( pos.x >= m_VertexPos[0].x && pos.x <= m_VertexPos[m_Mesh.HeightNum - 1].x
		&&
		pos.z <= m_VertexPos[0].z && pos.z >= m_VertexPos[m_Mesh.VertexNum - 1].z )
	{
		//  ���݂��钸�_�ԍ� = �t�B�[���h���S���_ + �Ώۂ̍��W / �t�B�[���h�̒���
		fWidthID = m_Mesh.WidthNum * 0.5f + pos.x / m_Size.x;
		fHeightID = m_Mesh.HeightNum * 0.5f - pos.z / m_Size.z;

		nWidthID = (int)fWidthID;
		nHeightID = (int)fHeightID;

		// ���݂��钸�_�ԍ����Z�o
		nInVertexID = nHeightID * m_Mesh.WidthNum + nWidthID;
	}
	else
	{
		nInVertexID = -1;
	}

	return nInVertexID;
}

//------------------------------------------------------------------------------
//	�֐���:	float CMeshField::GetHeight
//	����:	D3DXVECTOR3 pos
//	�߂�l:	float fHeight
//	����:	�Ώۂƃv���~�e�B�u�̌����_�����߂�i�����j
//			�|���S���`�F�b�N�F���͂P�A�C�͂R���R
//------------------------------------------------------------------------------
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3	VectorVtx[6], VectorObject[6], VectorResult[6];
	D3DXVECTOR3	Vector[4], Normal[2];
	int			nNum[4];
	float		fHeight;
	int			nCheckMax;
	int			nInVertexID;
	int			nCheckVertexID[9];

	//  �Q�ƕ��̂��钸�_�ԍ����`�F�b�N
	nInVertexID = CheckVertex(pos);

	//  ���b�V���^�C�v���ƂɃu���b�N�v�Z�����킯��
	switch (m_Mesh.Type)
	{
	case MESH_ISLAND:
		nCheckVertexID[0] = nInVertexID;
		nCheckMax = 1;
		break;
	case MESH_SEA:
		for (int i = 0; i < 3; i++)
		{
			nCheckVertexID[0 + i * 3] = nInVertexID + i - 1 - m_Mesh.WidthNum;
			nCheckVertexID[1 + i * 3] = nInVertexID + i - 1;
			nCheckVertexID[2 + i * 3] = nInVertexID + i - 1 + m_Mesh.WidthNum;
		}
		nCheckMax = 9;
		break;
	}

	for (int i = 0; i < nCheckMax; i++)
	{
		if (nInVertexID != -1)
		{
			//  �u���b�N���_�ԍ����Z�o
			nNum[0] = nCheckVertexID[i];
			nNum[1] = nNum[0] + 1;
			nNum[2] = nNum[0] + m_Mesh.WidthNum;
			nNum[3] = nNum[0] + m_Mesh.WidthNum + 1;

			//  �v���~�e�B�u�̃x�N�g�����v�Z
			VectorVtx[0] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[2]];
			VectorVtx[1] = m_VertexPos[nNum[3]] - m_VertexPos[nNum[0]];
			VectorVtx[2] = m_VertexPos[nNum[2]] - m_VertexPos[nNum[3]];

			VectorVtx[3] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[1]];
			VectorVtx[4] = m_VertexPos[nNum[1]] - m_VertexPos[nNum[3]];
			VectorVtx[5] = VectorVtx[1];

			//  �Ώۂ̃x�N�g�����v�Z
			VectorObject[0] = pos - m_VertexPos[nNum[2]];
			VectorObject[1] = pos - m_VertexPos[nNum[0]];
			VectorObject[2] = pos - m_VertexPos[nNum[3]];

			VectorObject[3] = pos - m_VertexPos[nNum[1]];
			VectorObject[4] = pos - m_VertexPos[nNum[3]];
			VectorObject[5] = pos - m_VertexPos[nNum[0]];

			for (int nCnt = 0; nCnt < 6; nCnt++)
			{
				//  �x�N�g���x���W���O�ɐݒ�
				VectorVtx[nCnt].y =
				VectorObject[nCnt].y = 0.0f;

				//  �Ώۂ��v���~�e�B�u�e�ӂ̍��E�ǂ��炩�ɂ���̌v�Z�i�O�ρj
				D3DXVec3Cross(&VectorResult[nCnt], &VectorObject[nCnt], &VectorVtx[nCnt]);
			}

			//  ���E�v���~�e�B�u�Q�ӂ̃x�N�g�����v�Z
			Vector[0] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[2]];
			Vector[1] = m_VertexPos[nNum[3]] - m_VertexPos[nNum[2]];
			Vector[2] = m_VertexPos[nNum[3]] - m_VertexPos[nNum[1]];
			Vector[3] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[1]];

			//  �v���~�e�B�u�@�������߂�(���v���)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[2], &Vector[3]);

			//  �v���~�e�B�u�@���̐��K��
			D3DXVec3Normalize(&Normal[0], &Normal[0]);
			D3DXVec3Normalize(&Normal[1], &Normal[1]);

			//  ���E�v���~�e�B�u�ǂ���ɂ���`�F�b�N
			if (VectorResult[0].y <= 0)		//  ��
			{
				if (VectorResult[1].y <= 0)
				{
					if (VectorResult[2].y <= 0)
					{
						//  ���������߂�
						fHeight = m_VertexPos[nNum[2]].y - ((Normal[0].x * (pos.x - m_VertexPos[nNum[2]].x)) + Normal[0].z * (pos.z - m_VertexPos[nNum[2]].z)) / Normal[0].y;
					}
				}
			}

			if (VectorResult[3].y > 0)		//  �E
			{
				if (VectorResult[4].y > 0)
				{
					if (VectorResult[5].y > 0)
					{
						//  ���������߂�
						fHeight = m_VertexPos[nNum[1]].y - ((Normal[1].x * (pos.x - m_VertexPos[nNum[1]].x)) + Normal[1].z * (pos.z - m_VertexPos[nNum[1]].z)) / Normal[1].y;
					}
				}
			}
		}
	}

	return fHeight;
}
