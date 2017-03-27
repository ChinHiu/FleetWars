//------------------------------------------------------------------------------
//	�^�C�g���F		���C���̃w�b�_�[
//	�t�@�C�����F	main.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/18
//------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "Windows.h"
#include "manager.h"

//------------------------------------------------------------------------------
//	���C�u�����̃����N
//------------------------------------------------------------------------------
#pragma comment ( lib, "winmm.lib" )		//  �}���`���f�B�A�^�C�}�[�g�p�ɕK�v

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------
const int nNumVertex = 4;						// ���_��
const int nNumPolygon = 2;						// �|���S����
const float fScreenSizeWidthMax = 1920.0f;		//  ��ʕ��ő�l

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
//  RELEASE�J��
#define SAFE_RELEASE( p )	if( p != NULL )					\
							{								\
								( p ) -> Release();			\
								p = NULL;					\
							}

//  �p�x�̃`�F�b�N
#define SAFE_ROTCHECK( rot )	if( rot > D3DX_PI )				\
								{								\
									rot -= D3DX_PI * 2.0f;		\
								}								\
								else if( rot < -D3DX_PI )		\
								{								\
									rot += D3DX_PI * 2.0f;		\
								}

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  ���w��p�i�l�דI�ȃ~�X�������j
typedef enum
{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS
}AXIS;

//  ���[�U�[�^�C�v
typedef enum
{
	USER_NONE = -1,
	USER_PLAYER,
	USER_ENEMY,
	USER_MAX
}USER_TYPE;

//------------------------------------------------------------------------------
//	�\���̒�`
//------------------------------------------------------------------------------

//  KEY�\����
typedef struct
{
	int UP;
	int DOWN;
	int LEFT;
	int RIGHT;
	int CAMERA;
	int HIT;
	int LOCK;
}KEY;

//  ��ʏ��\����
typedef struct
{
	D3DXVECTOR2 ScreenSize;
	float		ScreenRate;
	bool		bWindow;
	int			iDifficulty;
	KEY			Key;
}DISPLAY;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  2D�e�N�X�`���f�[�^
class CTex2D_Data
{
public:
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 Rot;
	D3DXVECTOR2 Size;
	D3DXCOLOR	Col;
	bool		Flag;

	CTex2D_Data()
		: Pos(D3DXVECTOR2(0.0f, 0.0f))
		, Rot(D3DXVECTOR2(0.0f, 0.0f))
		, Size(D3DXVECTOR2(0.0f, 0.0f))
		, Col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
		, Flag(false)
	{}
};

//  �I��UI�p�N���X
class CSelect_Data
{
public:
	D3DXCOLOR	Col;
	int			nFrameCnt;
	int			nPattern;
	bool		bSelect;
	int			nChangeTime;

	CSelect_Data()
		: Col(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
		, nFrameCnt(0)
		, nPattern(0)
		, bSelect(false)
		, nChangeTime(0)
	{}
};

//  �}�g���b�N�X�N���X
class CMatrix
{
public:
	D3DXMATRIX	World;			//  ���[���h�}�g���b�N�X
	D3DXMATRIX	Scl;			//  �X�P�[���}�g���b�N�X
	D3DXMATRIX	Rot;			//  ��]�}�g���b�N�X
	D3DXMATRIX	Trans;			//  �ʒu�}�g���b�N�X

	CMatrix()
	{
		D3DXMatrixIdentity(&World);
		D3DXMatrixIdentity(&Scl);
		D3DXMatrixIdentity(&Rot);
		D3DXMatrixIdentity(&Trans);
	}
};

//  �L�����N�^�[�f�[�^�N���X
class CCharacter_Data
{
public:
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 OldPos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 OldRot;
	D3DXVECTOR3 Scl;
	float		fAimSpeed;
	float		fSpeed;
	int			nLife;
	bool		bFlag;

	CCharacter_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, OldPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, OldRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, fAimSpeed(0.0f)
		, fSpeed(0.0f)
		, nLife(0)
		, bFlag(false)
	{}
};

//  ����f�[�^�N���X
class CWeapon_Data
{
public:
	int nNum;
	float fCoolDown;
	int	nCoolDown;
	bool bFlag;


	CWeapon_Data()
		: nNum(0)
		, fCoolDown(0)
		, nCoolDown(0)
		, bFlag(false)
	{}
};

//  Obb�N���X
class CObb
{
private:
	D3DXVECTOR3 Pos;			//  �ʒu
	D3DXVECTOR3 Direct[3];		//  �����x�N�g��
	D3DXVECTOR3 Length;			//  �e�������̒���

public:
	D3DXVECTOR3 GetDirect(int nID)	{ return Direct[nID]; };		//  �w�莲�ԍ��̕����x�N�g�����擾
	FLOAT		GetLength(int nID)	{ return Length[nID]; };		//  �w�莲�����̒������擾
	D3DXVECTOR3 GetPos(void)		{ return Pos; };				//  �ʒu���擾

	void		SetDirect(int nID, D3DXVECTOR3 direct)	{ Direct[nID] = direct; }
	void		SetPos(D3DXVECTOR3 pos)					{ Pos = pos; };
	void		SetLength(D3DXVECTOR3 length)			{ Length = length; };
};

//  �A�j���[�V�����N���X
class CAnimation
{
public:
	int PatternX;		//  �����p�^�[��
	int	PatternY;		//  �c���p�^�[��
	int	Pattern;		//  ���݂̃p�^�[��
	int	Cnt;			//  �J�E���g
	int	Frame;			//  �X�V�t���[��

	CAnimation()
	{
		PatternX =
		PatternY =
		Pattern =
		Cnt =
		Frame = 0;
	}
};

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
int				*GetFPS(void);				//  FPS���擾
HWND			GetWnd(void);				//  �E�B���h�E�n���h�����擾
D3DXVECTOR2		*GetScreenSize(void);		//  �X�N���[���T�C�Y���擾
float			*GetScreenRate(void);
#endif