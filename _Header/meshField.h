//------------------------------------------------------------------------------
//	�^�C�g���F		���b�V���t�B�[���h�����̃w�b�_�[
//	�t�@�C�����F	meshField.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/24
//------------------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------

const int nWaveMax = 4;			//  �g�̍ő吔

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
//  �e�N�X�`���t�@�C���p�X
#define SEAMLESSMESHFIELD_TEXTURE_FILE	"./data/TEXTURE/Seamless_Field.jpg"	//  �V�����[�X�t�B�[���h
#define SEAMLESSSEA_TEXTURE_FILE		"./data/TEXTURE/Seamless_Sea.jpg"	//  �V�����[�X�C
#define FIELD_TEXTURE_FILE				"./data/TEXTURE/Field.jpg"			//  �t�B�[���h
#define SEA_TEXTURE_FILE				"./data/TEXTURE/Sea.jpg"			//  �C
#define ISLAND_MAP_FILE					"./data/MAP/MapData.txt"			//  �}�b�v�f�[�^

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  �@���^�C�v
typedef enum
{
	NONE = 0,
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_DOWN,
	RIGHT_DOWN,
	TOP_SIDE,
	DOWN_SIDE,
	LEFT_SIDE,
	RIGHT_SIDE,
	MIDDLE
}NORMAL_TYPE;

//  ���b�V���^�C�v
typedef enum
{
	MESH_NONE = -1,
	MESH_ISLAND,
	MESH_SEA,
	MESH_TYPE_MAX
}MESH_TYPE;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �g�f�[�^�N���X
class CWave_Data
{
public:
	D3DXVECTOR2 K;
	float		A;
	float		Omega;
	float		t;
	float		OmegaT;
	float		WaveLength;
	float		k;
	float		testAk;

	CWave_Data()
		: K(D3DXVECTOR2(0, 0))
		, A(0.0f)
		, Omega(0.0f)
		, t(0.0f)
		, OmegaT(0.0f)
		, WaveLength(0.0f)
		, k(0.0f)
		, testAk(0.0f)
	{}
};

//  ���b�V���f�[�^�N���X
class CMesh_Data
{
public:
	int			WidthNum;		//  ���̒��_��
	int			HeightNum;		//  �c�̒��_��
	int			VertexNum;		//  �����_��
	int			IndexNum;		//  �C���f�b�N�X��
	//int			PrimitiveNum;	//  �|���S����
	int			VertexId;		//  ���_�ԍ�
	float		SeamlessScl;	//  �V�[�����X�K��
	bool		SeamlessTex;	//  �V�[�����X�e�N�X�`�����g�p���邩�ǂ���
	MESH_TYPE	Type;			//  ���b�V���^�C�v

	CMesh_Data()
		: WidthNum(0)
		, HeightNum(0)
		, VertexNum(0)
		, IndexNum(0)
		//, PrimitiveNum(0)
		, VertexId(0)
		, SeamlessTex(false)
		, SeamlessScl(1.0f)
		, Type(MESH_NONE)
	{}
};

//  ���b�V���t�B�[���h�N���X
class CMeshField : public CScene
{
public:
	CMeshField(int nPriority = 0, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CMeshField();

	static			CMeshField *LoadMap(MESH_TYPE Mesh_Type, LPCSTR MAP_FILE, LPCSTR TEXTURE_FILE, bool SeamlessTex, float SeamlessScl);
	static			CMeshField *Create(MESH_TYPE Mesh_Type, LPCSTR TEXTURE_FILE, D3DXVECTOR3 pos, D3DXVECTOR3 size, int WidthNum, int HeightNum, bool SeamlessTex, float SeamlessScl);

	void			Init(void);
	void			Uninit(void);
	void			Update(void);
	void			Draw(void);

	void			CalculateVertex(void);
	void			CalculateNormal(void);
	void			CalculateNormalType(void);

	void			SetVertex(void);
	HRESULT			MakeIndex(LPDIRECT3DDEVICE9 pDevice);
	HRESULT			MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	int				CheckVertex(D3DXVECTOR3 pos);
	void			WaveInit(void);
	void			WaveUpdate(void);

	//  �擾�֐�
	float			GetHeight(D3DXVECTOR3 pos);

private:
	LPDIRECT3DTEXTURE9			m_TextureBuffer;		//  �e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;			//  ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_PositionBuffer;		//  ���̒��_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;			//  �C���f�b�N�X�o�b�t�@�ւ̃|�C���^�[

	D3DXVECTOR3					*m_VertexPos;			//  ���_���W
	D3DXVECTOR3					*m_Nor;					//  �@��
	NORMAL_TYPE					*m_NorType;				//  �@���̃^�C�v

#ifdef _DEBUG
	int							m_WaveID;				//  �g�ԍ�
#endif

	CWave_Data					m_Wave[nWaveMax];		//  �g�f�[�^
	CMesh_Data					m_Mesh;					//  ���b�V���f�[�^

	CMatrix						m_Matrix;				//  �}�g���N�X���
	D3DXVECTOR3					m_Pos;					//  �ʒu
	D3DXVECTOR3					m_Rot;					//  ��]
	D3DXVECTOR3					m_Scl;					//  �g��k��
	D3DXVECTOR3					m_Size;					//  �T�C�Y
};

#endif