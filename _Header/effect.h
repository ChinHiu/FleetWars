//------------------------------------------------------------------------------
//	�^�C�g���F		�G�t�F�N�g�̃w�b�_�[
//	�t�@�C�����F	effect.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/12/15
//------------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------

const int nEffect_Anim_Max = 50;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �G�t�F�N�g�f�[�^�N���X
class CEffect_Data
{
public:
	D3DXVECTOR3 Pos;			//  ���݂̈ʒu
	D3DXVECTOR3	Rot;			//  ��]
	D3DXVECTOR3 Size;			//  �T�C�Y
	D3DXVECTOR3 Scl;			//  �g��k��
	EFFECT_TYPE	EffectType;		//  �o���b�g�^�C�v
	CMatrix		Matrix;			//  �}�g���b�N�X
	D3DXMATRIX	ViewMatrix;		//  �r���[�}�g���b�N�X
	CAnimation	Anim;			//  �A�j���[�V����
	bool		Flag;			//  true�͎g�p����
	bool		AnimLoop;		//  true�̓��[�v����
	bool		AlphaTest;		//  true�̓A���t�@�e�X�g����
	bool		AlphaBlend;		//  true�̓A���t�@�u�����h����
	bool		ZBuffer;

	CEffect_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, EffectType(EFFECT_NONE)
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
		, ZBuffer(false)
	{
		D3DXMatrixIdentity(&ViewMatrix);
	}
};

//  �G�t�F�N�g�N���X
class CEffect : public CScene
{
public:
	CEffect(int nPriority = 3, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CEffect();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CEffect *Create(void);
	void	SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, EFFECT_TYPE EffectType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend, bool ZBuffer);

private:
	CEffect_Data			m_Effect[nEffect_Anim_Max];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;											//  ���_�o�b�t�@�ւ̃|�C���^
	CAnimation				m_Anim[EFFECT_EXPLOSION_001 - EFFECT_WATER_IMPACT];
};

#endif