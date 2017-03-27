//------------------------------------------------------------------------------
//	�^�C�g���F		�~�T�C���̃w�b�_�[
//	�t�@�C�����F	missile.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/01/03
//------------------------------------------------------------------------------
#ifndef _MISSILE_H_
#define _MISSILE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define MISSILE_MAX				(256)

typedef enum{
	MISSILE_STATE_NONE = -1,
	MISSILE_READY,
	MISSILE_RISE,
	MISSILE_PURSUIT,
	MISSILE_EXPLOSION,
	MISSILE_STATE_MAX
}MISSILE_STATE;

//  �~�T�C���f�[�^�̃N���X
class CMissile_Data
{
public:
	D3DXVECTOR3		Pos;			//  ���݂̈ʒu
	D3DXVECTOR3		RandPos;
	D3DXVECTOR3		*TargetPos;		//  �^�[�Q�b�g�̈ʒu�ւ̃|�C���^
	D3DXVECTOR3		*ShipPos;		//  �D�̈ʒu�ւ̃|�C���^
	D3DXVECTOR3		*ShipRot;		//  �D�̉�]�ւ̃|�C���^
	bool			*ShipFlag;		//  �D�̃t���O�ւ̃|�C���^
	D3DXVECTOR3		DeviationPos;	//  �ʒu�̕Έڗ�
	float			DeviationRot;	//  �Έڗʂ̊p�x
	float			Radius;
	D3DXVECTOR3		Rot;			//  ���݂̉�]
	D3DXVECTOR3		GoalRot;		//  �ڕW��]
	D3DXVECTOR3		Vector;			//  ���_����ړI�n�܂ł̃x�N�g��
	D3DXVECTOR3		Scl;			//  �g��k��
	CMatrix			Matrix;			//  �}�g���b�N�X
	int				Life;			//  ���C�t
	float			Speed;			//  �ړ����x
	float			Gravity;		//  �d��
	float			Distance;
	bool			Flag;			//  true�͎g�p�Afalse�͖��g�p
	bool			CheckSea;		//  true���ƊC�Ɠ�����
	USER_TYPE		UserType;		//  �g�p��
	MISSILE_STATE	State;			//  ���
	bool			bUserMap;
	int				LockShipID;
	D3DXMATRIX		*ShipMatrix;
	bool			bParent;

	CMissile_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, TargetPos(NULL)
		, ShipPos(NULL)
		, ShipRot(NULL)
		, DeviationPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, DeviationRot(0.0f)
		, Radius(0.0f)
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, GoalRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Vector(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Life(3)
		, Speed(0.0f)
		, Gravity(0.0f)
		, Distance(0.0f)
		, Flag(false)
		, CheckSea(false)
		, UserType(USER_NONE)
		, State(MISSILE_STATE_NONE)
		, bUserMap(false)
	{}

	void SetFlag(bool bFlag) { Flag = bFlag; }
	void SetDamage(int nDamage) { Life -= nDamage; }
	void SetLockShipID(int nID) { LockShipID = nID; };
};

//  �~�T�C���N���X
class CMissile : public CScene
{
private:
	CMissile_Data			m_Missile[MISSILE_MAX];
	CModel					*m_Model;

public:
	CMissile(int nPriority = 2, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CMissile();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	static	CMissile *Create(void);
	void	Set(D3DXVECTOR3 *TargetPos, int nID);
	int		Reset(D3DXMATRIX *ShipMatrix, USER_TYPE User_Type, D3DXVECTOR3 *ShipPos, D3DXVECTOR3 *ShipRot, bool *bShipFlag, D3DXVECTOR3 DeviationPos);
	CMissile_Data *GetMissileData(void);
	void	MissileDataInit(void);
};

#endif