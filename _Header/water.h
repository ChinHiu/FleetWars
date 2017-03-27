//------------------------------------------------------------------------------
//	�^�C�g���F		���G�t�F�N�g�̃w�b�_�[
//	�t�@�C�����F	water.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/09/27
//------------------------------------------------------------------------------
#ifndef _WATER_H_
#define _WATER_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"
#include "manager.h"

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------
const int nWater_Anim_Max = 50;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  ���f�[�^�N���X
class CWater_Data
{
public:
	D3DXVECTOR3 Pos;			//  ���݂̈ʒu
	D3DXVECTOR3	Rot;			//  ��]
	D3DXVECTOR3	Size;			//  �T�C�Y
	D3DXVECTOR3	Scl;			//  �g��k��
	EFFECT_TYPE	WaterType;		//  ���^�C�v
	CMatrix		Matrix;			//  �}�g���b�N�X
	CAnimation	Anim;			//  �A�j���[�V����
	bool		Flag;			//  true�͎g�p����
	bool		AnimLoop;		//  true�̓��[�v����
	bool		AlphaTest;		//  true�̓A���t�@�e�X�g����
	bool		AlphaBlend;		//  true�̓A���t�@�u�����h����

	CWater_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, WaterType(EFFECT_NONE)
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
	{}
};

//  �G�t�F�N�g�N���X
class CWater : public CScene
{
public:
	CWater(int nPriority = 3, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CWater();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CWater *Create(void);
	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, EFFECT_TYPE WaterType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend);

private:
	CWater_Data				m_Water[nWater_Anim_Max];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;					//  ���_�o�b�t�@�ւ̃|�C���^
	CAnimation				m_InitAnim[EFFECT_WATER_IMPACT + 1];
};

#endif