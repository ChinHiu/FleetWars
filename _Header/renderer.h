//------------------------------------------------------------------------------
//	�^�C�g���F		DirectX�֘A�̃w�b�_�[
//	�t�@�C�����F	renderer.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/18
//------------------------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "d3dx9.h"
#define  DIRECTINPUT_VERSION ( 0x0800 )
#include "dinput.h"							//  DirectInput�֘A�̃w�b�_�[

//------------------------------------------------------------------------------
//	���C�u�����̃����N
//------------------------------------------------------------------------------
#pragma comment ( lib, "d3d9.lib" )			//  �`�揈���ɕK�v
#pragma comment ( lib, "d3dx9.lib" )		//  ��L�̊g�����C�u����
#pragma comment ( lib, "dxguid.lib" )		//  DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment ( lib, "dinput8.lib" )		//  ���͏����ɕK�v
#pragma warning ( disable: 4996 )			//  sprintf�̃E�H�[�~���O

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define	FVF_VERTEX_2D	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )				//  ���_���W(3d) | ���_�J���[ | �e�N�X�`�����W
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//  ���_���W(3d) | �@�� | ���_�J���[ | �e�N�X�`�����W

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CDebugProc;

//------------------------------------------------------------------------------
//	�\���̒�`
//------------------------------------------------------------------------------

//  2D�p�\����
typedef struct
{
	D3DXVECTOR3 pos;	//  ���_���W
	float		rhw;	//  �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR	col;	//  ���_�J���[
	D3DXVECTOR2 tex;	//  �e�N�X�`�����W
}VERTEX_2D;

//  3D�p�\����	
typedef struct
{
	D3DXVECTOR3	pos;	//  ���_���W
	D3DXVECTOR3	nor;	//  �@���x�N�g��( �ʂ̌����ɐݒ� )
	D3DCOLOR	col;	//  ���_�J���[
	D3DXVECTOR2	tex;	//  �e�N�X�`�����W
}VERTEX_3D;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �����_���N���X
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT					Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void					Uninit(void);
	void					Update(void);
	void					Begin(void);
	void					End(void);
	LPDIRECT3DDEVICE9		GetDevice(void);
#ifdef _DEBUG
	void					DrawFPS(void);
#endif

private:
	LPDIRECT3D9				m_D3D;				//  Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_D3DDevice;		//  Direct3D�f�o�C�X�ւ̃|�C���^
	bool					m_bFog;
	bool					m_bFillMode;		//  ���C���[�t���[�����[�h�̃t���O
#ifdef _DEBUG
	LPD3DXFONT				m_D3DXFont;			//  �t�H���g�ւ̃|�C���^
	float					m_Alpha;			//  ���l
#endif
};

#endif