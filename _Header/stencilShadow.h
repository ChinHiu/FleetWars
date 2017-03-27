//------------------------------------------------------------------------------
//	�^�C�g���F		�X�e���V���V���h�E�̃w�b�_�[
//	�t�@�C�����F	stencil.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/11/15
//------------------------------------------------------------------------------
#ifndef _STENCILSHADOW_H_
#define _STENCILSHADOW_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define TITLE_GORSHKOV_SHADOW_FILE	"./data/MODEL/SHADOW/Title_Gorshkov_Shadow.x"
#define GORSHKOV_SHADOW_FILE		"./data/MODEL/SHADOW/Gorshkov_Shadow.x"
#define HAMINA_SHADOW_FILE			"./data/MODEL/SHADOW/Hamina_Shadow.x"

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �X�e���V���V���h�E�N���X
class CStencilShadow
{
public:
	CStencilShadow();
	~CStencilShadow();

	static CStencilShadow *Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	HRESULT Make2DVertex(LPDIRECT3DDEVICE9 pDevice);

	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; };
	void SetFlag(bool bFlag) { m_bFlag = bFlag; };

private:
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;				//  ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH					m_Mesh;						//  ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER				m_BuffMat;					//  �}�e���A�����ւ̃|�C���^
	DWORD						m_NumMat;					//  �}�e���A����
	int							m_NumVertices;				//  ���_��
	DWORD						m_sizeFVF;					//  ���_�t�H�[�}�b�g
	CMatrix						m_Matrix;					//  �}�g���b�N�X
	LPCSTR						m_ModelFile;				//  ���f���t�@�C��
	MODEL_TYPE					m_ModelType;				//  ���f���^�C�v
	D3DXVECTOR3					m_Pos;						//  �ʒu
	D3DXVECTOR3					m_Rot;						//  ��]
	D3DXVECTOR3					m_Scl;						//  �g��k��
	bool						m_bFlag;					//  �g�p���邩�ǂ���
};

#endif