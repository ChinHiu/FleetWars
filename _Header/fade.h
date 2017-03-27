//------------------------------------------------------------------------------
//	�^�C�g���F		�t�F�[�h�����̃w�b�_�[
//	�t�@�C�����F	fade.h
//	�쐬�ҁF		AT12A244 33 CHIN HIU
//	�쐬���F		2016/07/11
//------------------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define FADE_TEXTURE_FILE "./data/TEXTURE/UI/Fade.png"
//  �O���錾
//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,	//�������Ȃ�
	FADE_IN,		//�t�F�[�h�C��
	FADE_OUT,		//�t�F�[�h�A�E�g
	FADE_MAX
}FADE;

// �J�����N���X
class CFade
{
private:
	LPDIRECT3DTEXTURE9 m_TextureBuffer;				//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;			//  ���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_Col;								//  �t�F�[�h�F
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Size;
	FADE m_Fade;									//  �t�F�[�h�̏��
	bool m_bFlag;									//  �t���O
	CMode *m_NextMode;								//  ���̃��[�h

public:
	CFade();
	~CFade();
	static CFade *Create(CMode *NextMode);
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	Set(CMode *NextMode);
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
};
#endif