//------------------------------------------------------------------------------
//	�^�C�g���F		�����Ԃ��̃w�b�_�[
//	�t�@�C�����F	spray.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/02
//------------------------------------------------------------------------------
#ifndef _SPRAYBEFORE_H_
#define _SPRAYBEFORE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define SPRAY_BEFORE_TEXTURE_FILE		"./data/TEXTURE/EffectAnim/Spray_Before_4_8.png"
#define SPRAY_BEHIDE_TEXTURE_FILE		"./data/TEXTURE/EffectAnim/Spray_Behide_8_2.png"

//  �����Ԃ��^�C�v
typedef enum
{
	SPRAY_NONE = -1,
	SPRAY_BEFORE_LEFT,
	SPRAY_BEFORE_RIGHT,
	SPRAY_TYPE_MAX
}SPRAY_TYPE;

class CSpray_Data
{
public:
	D3DXVECTOR3 *Pos;			//  ���݂̈ʒu
	D3DXVECTOR3	*Rot;			//  ��]
	D3DXVECTOR3	*Size;			//  �T�C�Y
	D3DXVECTOR3	Scl;			//  �g��k��
	SPRAY_TYPE	SprayType;		//  �o���b�g�^�C�v
	CMatrix		Matrix;			//  �}�g���b�N�X
	CAnimation	Anim;			//  �A�j���[�V����
	bool		Flag;			//  true�͎g�p����
	bool		AnimLoop;		//  true�̓��[�v����
	bool		AlphaTest;		//  true�̓A���t�@�e�X�g����
	bool		AlphaBlend;		//  true�̓A���t�@�u�����h����
	D3DXVECTOR2 AdjustRot;

	CSpray_Data()
		: Pos(NULL)
		, Rot(NULL)
		, Size(NULL)
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, SprayType(SPRAY_NONE)
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
		, AdjustRot(D3DXVECTOR2(0.0f, 0.0f))
	{}
};

//  �G�t�F�N�g�N���X
class CSpray
{
private:
	CSpray_Data				m_Spray[SPRAY_TYPE_MAX];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;				//  ���_�o�b�t�@�ւ̃|�C���^
	CAnimation				m_Anim[SPRAY_TYPE_MAX];
	MODEL_TYPE				m_Type;

public:
	CSpray();
	~CSpray();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(int nID);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CSpray *Create(void);
	void	Set(MODEL_TYPE Model_Type, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, SPRAY_TYPE Spray_Type, bool bAnimLoop);
};

#endif