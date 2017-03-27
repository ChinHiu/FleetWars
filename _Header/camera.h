//------------------------------------------------------------------------------
//	�^�C�g���F		�J�����̃w�b�_�[
//	�t�@�C�����F	camera.h
//	�쐬�ҁF		AT12A244 33 CHIN HIU
//	�쐬���F		2015/10/21
//------------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "player.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CKeyboard;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �J�����f�[�^�N���X
class CCamera_Data
{
public:
	D3DXMATRIX		mtxProjection;	//�@�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX		mtxView;		//  �r���[�}�g���b�N�X
	D3DXVECTOR3		posV;			//  ���_���W
	D3DXVECTOR3		posR;			//  �����_���W
	D3DXVECTOR3		vecU;			//  ��������x�N�g��
	D3DXVECTOR3		rot;			//  ��]�p�x
	D3DXVECTOR3		posRAim;		//  �����_�ڕW�ړ����W
	D3DXVECTOR3		rotAim;			//  ��]�ڕW�p�x
	int				nMoveCount;		//  �ړ��J�E���^
	float			fMove;			//  �ړ���
	float			fDistance;		//  ���_�ƒ����_�̋���
	bool			bLookAt;
};

// �J�����N���X
class CCamera
{
public:
	CCamera();
	~CCamera();
	void			Init(D3DXVECTOR3 rot, bool bLookAt);
	void			Uninit(void);
	void			Update(void);
	void			SetCamera(void);
	CCamera_Data	*GetCameraData(void);

#ifdef _DEBUG
	void	Move(
		CKeyboard *keyboard,
		int UP_KEY,
		int DOWN_KEY,
		int LEFT_KEY,
		int RIGHT_KEY,
		int VIEW_LTURNING_KEY,
		int VIEW_RTURNING_KEY,
		int LOOKAT_LTURNING_KEY,
		int LOOKAT_RTURNING_KEY);
#endif

private:
	CCamera_Data	m_CameraData;
	WEAPON_TYPE		m_OldWeapon;
};

#endif