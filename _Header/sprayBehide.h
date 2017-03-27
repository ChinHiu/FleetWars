//------------------------------------------------------------------------------
//	�^�C�g���F		�����Ԃ��̃w�b�_�[
//	�t�@�C�����F	sprayBehide.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/02
//------------------------------------------------------------------------------
#ifndef _SPRAYBEHIDE_H_
#define _SPRAYBEHIDE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------
const int nSprayMax = 9;

class CSprayBehide_Data
{
public:
	D3DXVECTOR3 *Pos,			//  ���݂̈ʒu
				*Rot,			//  ��]
				*Size,			//  �T�C�Y
				Scl;			//  �g��k��
	CMatrix		Matrix;			//  �}�g���b�N�X
	CAnimation	Anim;			//  �A�j���[�V����
	bool		Flag,			//  true�͎g�p����
				AnimLoop,		//  true�̓��[�v����
				AlphaTest,		//  true�̓A���t�@�e�X�g����
				AlphaBlend;		//  true�̓A���t�@�u�����h����

	CSprayBehide_Data()
		: Pos(NULL)
		, Rot(NULL)
		, Size(NULL)
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
	{}
};

//  �G�t�F�N�g�N���X
class CSprayBehide : public CScene
{
private:
	CSprayBehide_Data		m_SprayBehide[nSprayMax];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;				//  ���_�o�b�t�@�ւ̃|�C���^
	CAnimation				m_Anim;

public:
	CSprayBehide(int nPriority = 1, OBJECT_TYPE Object_Type = OBJTYPE_PLAYER);
	~CSprayBehide();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CSprayBehide *Create(void);
	void	Set(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, bool bAnimLoop);
};

#endif