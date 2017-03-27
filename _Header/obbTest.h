//------------------------------------------------------------------------------
//	�^�C�g���F		Obb�e�X�g�̃w�b�_�[
//	�t�@�C�����F	ObbTest.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/01
//------------------------------------------------------------------------------
#ifndef _ObbTEST_H_
#define _ObbTEST_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  Obb�e�X�g�f�[�^�N���X
class CObbTest_Data
{
public:
	D3DXVECTOR3 Pos;			//  ���݂̈ʒu
	D3DXVECTOR3	Rot;			//  ��]
	D3DXVECTOR3	Size;			//  �T�C�Y
	D3DXVECTOR3	Scl;			//  �g��k��
	CMatrix		Matrix;			//  �}�g���b�N�X
	bool		Flag;

	CObbTest_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Flag(false)
	{}
};

//  ObbTest�N���X
class CObbTest : public CScene
{
private:
	CObbTest_Data			m_ObbTest;
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;		//  ���_�o�b�t�@�ւ̃|�C���^
	bool					m_bObbTest;
	D3DXCOLOR				m_Col;

public:
	CObbTest(int nPriority = 2, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CObbTest();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(void);
	static	CObbTest *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void	SetCol(D3DXCOLOR col);
	void	SetPos(D3DXVECTOR3 pos);
	void	SetRot(D3DXVECTOR3 rot);
};

#endif