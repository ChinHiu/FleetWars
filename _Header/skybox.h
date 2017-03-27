//------------------------------------------------------------------------------
//	�^�C�g���F		�X�J�C�{�b�N�X�̃w�b�_�[
//	�t�@�C�����F	skybox.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/06/20
//------------------------------------------------------------------------------
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  �X�J�C�e�N�X�`���^�C�v
typedef enum
{
	UP_TEXTURE = 0,
	LEFT_TEXTURE,
	FRONE_TEXTURE,
	RIGHT_TEXTURE,
	BACK_TEXTURE,
	DOWN_TEXTURE,
	SKY_TEXTURE_MAX
}SKY_TEXTURE;

//  �X�J�C�^�C�v
typedef enum
{
	TROPICALSUNNYDAY = 0,
	SKY_TYPE_MAX
}SKY_TYPE;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �X�J�C�{�b�N�X�N���X
class CSkybox : public CScene
{
public:
	CSkybox(int nPriority = 0, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CSkybox();

	static	CSkybox *Create(float fScale);
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	HRESULT MakeIndex(LPDIRECT3DDEVICE9 pDevice);

	//  �Z�b�g�֐�
	void	SetPos(const D3DXVECTOR3 pos);

private:
	CMatrix					m_Matrix;									//  �}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;								//  ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;								//  �C���f�b�N�X�o�b�t�@�ւ̃|�C���^�[
	float					m_Scale;									//  �{��
	D3DXVECTOR3				m_Pos;										//  �ʒu
	D3DXVECTOR3				m_Rot;										//  ��]
	D3DXVECTOR3				m_Scl;										//  �g��k��

};
#endif