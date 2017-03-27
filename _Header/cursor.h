//------------------------------------------------------------------------------
//	�^�C�g���F		�}�E�X�̃w�b�_�[
//	�t�@�C�����F	keyboard.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/10
//------------------------------------------------------------------------------
#ifndef _CURSOR_H_
#define _CURSOR_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define	CURSOR_TEXTURE_FILE	"./data/TEXTURE/cursor000.png"				//  2D�J�[�\���̃e�N�X�`���t�@�C���p�X
#define CURSOR3D_TEXTURE_FILE "./data/TEXTURE/EffectAnim/Cursor3D.png"	//  3D�J�[�\���̃e�N�X�`���t�@�C���p�X

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �J�[�\���N���X
class CCursor
{
public:
	CCursor();
	~CCursor();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	//  �擾�֐�
	D3DXVECTOR3 *GetPosition(void);

	//  �Z�b�g�֐�
	void	SetVertex(void);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY);
	void	SetPosition(D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;		//  ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_TextureBuffer;	//  �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_Pos;
	D3DXVECTOR3				m_Rot;
	D3DXVECTOR3				m_Scl;
	bool					m_Flag;
	D3DXVECTOR3				m_Size;
	//CAnimation			m_Anim;
	CMatrix					m_Matrix;
};

#endif